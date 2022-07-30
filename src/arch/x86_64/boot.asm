global start
extern long_mode_start


section .text
bits 32
    start:
	mov esp, stack_top

	call check_multiboot
	call check_cpuid
	call check_long_mode

	call set_up_paging
	call enable_paging

	lgdt [gdt64.pointer]

	jmp gdt64.code:long_mode_start

	hlt

    check_multiboot:
	cmp eax, 0x36d76289
        jne .no_multiboot
	ret

    .no_multiboot:
	mov al, "0"
        jmp error

    ; https://wiki.osdev.org/Setting_Up_Long_Mode#Detection_of_CPUID
    check_cpuid:
        ; Check if CPUID is supported by attempting to flip the ID bit (bit 21) in
        ; the FLAGS register. If we can flip it, CPUID is available.
 
        ; Copy FLAGS in to EAX via stack
	pushfd
        pop eax
 
        ; Copy to ECX as well for comparing later on
	mov ecx, eax
 
        ; Flip the ID bit
	xor eax, 1 << 21
 
        ; Copy EAX to FLAGS via the stack
	push eax
        popfd
 
	; Copy FLAGS back to EAX (with the flipped bit if CPUID is supported)
        pushfd
	pop eax
 
        ; Restore FLAGS from the old version stored in ECX (i.e. flipping the ID bit
	; back if it was ever flipped).
        push ecx
	popfd
 
	; Compare EAX and ECX. If they are equal then that means the bit wasn't
        ; flipped, and CPUID isn't supported.
	xor eax, ecx
        jz .no_cpuid
	ret

    .no_cpuid:
	mov al, "1"
	jmp error

    check_long_mode:
	mov eax, 0x80000000    ; Set the A-register to 0x80000000.
        cpuid                  ; CPU identification.
	cmp eax, 0x80000001    ; Compare the A-register with 0x80000001.
        jb .no_long_mode       ; It is less, there is no long mode.

	mov eax, 0x80000001    ; Set the A-register to 0x80000001.
        cpuid                  ; CPU identification.
	test edx, 1 << 29      ; Test if the LM-bit, which is bit 29, is set in the D-register.
        jz .no_long_mode       ; They aren't, there is no long mode.

	ret

    .no_long_mode:
	mov al, "2"
	jmp error

    set_up_paging:
	mov eax, p3_table
	or eax, 0b11
	mov [p4_table], eax
	
	mov eax, p2_table
	or eax, 0b11
	mov [p3_table], eax

	mov ecx, 0

    .map_p2_table:
	mov eax, 0x200000
	mul ecx
	or eax, 0b10000011
	mov [p2_table + ecx * 8], eax

	inc ecx
	cmp ecx, 512
	jne .map_p2_table

	ret

    enable_paging:
	mov eax, p4_table
	mov cr3, eax

	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

	ret

    error:
	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
        mov dword [0xb8008], 0x4f204f20
        mov byte  [0xb800a], al
	hlt

section .bss
    align 4096

    p4_table:
	resb 4096
    p3_table:
	resb 4096
    p2_table:
	resb 4096

    stack_bottom:
	resb 64

    stack_top:

section .rodata
    gdt64:
	dq 0
    .code: equ $ - gdt64
	dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)

    .pointer:
	dw $ - gdt64 - 1
	dq gdt64
