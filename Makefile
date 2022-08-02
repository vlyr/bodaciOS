# kernel
arch ?= i686
kernel := build/kernel-$(arch).bin
iso := build/os-$(arch).iso
linker_script := kernel/arch/$(arch)/linker.ld
grub_cfg := kernel/arch/$(arch)/grub.cfg

asm_src_files := $(wildcard kernel/arch/$(arch)/*.S)
asm_obj_files := $(patsubst kernel/arch/$(arch)/%.S, build/arch/$(arch)/%.o, $(asm_src_files))

c_input_files := $(wildcard kernel/*.c)
c_output_files := $(patsubst kernel/%.c, build/arch/$(arch)/%.o, $(c_input_files))

libc_input_files := $(wildcard libc/string/*.c)
libc_output_files := $(patsubst libc/string/%.c, build/arch/$(arch)/%.o, $(libc_input_files))

.PHONY: all clean run iso kernel

all: $(libc_output_files) $(c_output_files) $(kernel)

clean:
	@rm -r build

run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso)

iso: $(iso)

prepare:
	@mkdir -p build/arch/$(arch)

$(iso): prepare all 
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles

$(kernel): prepare kernel $(asm_obj_files) $(linker_script)
	@i686-elf-gcc -T $(linker_script) -o build/kernel-$(arch).bin $(wildcard build/arch/$(arch)/*.o) -ffreestanding -O2 -nostdlib -lgcc

# assembly
build/arch/$(arch)/%.o: kernel/arch/$(arch)/%.S
	@mkdir -p $(shell dirname $@)
	@nasm -felf32 $< -o $@

# c kernel code
$(c_output_files): $(c_input_files)
	@i686-elf-gcc -m32 -c $< -o $@ -ffreestanding -z max-page-size=0x1000 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -std=gnu99 -O2 -Wall -Wextra -I libc/include

# libc
$(libc_output_files): $(libc_input_files) prepare
	@echo building lib
	@mkdir -p $(shell dirname $@)
	@i686-elf-gcc -MD -c $< -o $@ -std=gnu11 -ffreestanding -Wall -Wextra -Iinclude
