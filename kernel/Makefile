arch ?= x86_64
kernel := build/kernel-$(arch).bin
iso := build/os-$(arch).iso
target := $(arch)-bodaciOS
rust_lib := target/$(target)/debug/libbodaciOS.a

linker_script := kernel/arch/$(arch)/linker.ld
grub_cfg := kernel/arch/$(arch)/grub.cfg
asm_src_files := $(wildcard kernel/arch/$(arch)/*.asm)
asm_obj_files := $(patsubst kernel/arch/$(arch)/%.asm, build/arch/$(arch)/%.o, $(asm_src_files))

.PHONY: all clean run iso kernel

all: $(kernel)

clean:
	@rm -r build

run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso)

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles

$(kernel): kernel $(asm_obj_files) $(linker_script)
	@i686-elf-gcc -T $(linker_script) -o $(kernel) -ffreestanding -O2 -nostdlib $(asm_object_files) kernel/arch/$(arch)/kernel.o
	# @ld -n -T $(linker_script) -o $(kernel) $(asm_obj_files)
	# @ld -n --gc-sections -T $(linker_script) -o $(kernel) $(asm_obj_files) $(rust_os)

build/arch/$(arch)/%.o: kernel/arch/$(arch)/%.asm
	@mkdir -p $(shell dirname $@)
	@i686-elf-gcc -std=gnu99 -ffreestanding -g -c $< -o $@

kernel:
	i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel/arch/$(arch)/main.c -o build/$(arch)/kernel.o
