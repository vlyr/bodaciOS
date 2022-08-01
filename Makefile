arch ?= x86_64
kernel := build/kernel-$(arch).bin
iso := build/os-$(arch).iso

linker_script := kernel/arch/$(arch)/linker.ld
grub_cfg := kernel/arch/$(arch)/grub.cfg
asm_src_files := $(wildcard kernel/arch/$(arch)/*.S)
asm_obj_files := $(patsubst kernel/arch/$(arch)/%.S, build/arch/$(arch)/%.o, $(asm_src_files))

.PHONY: all clean run iso kernel

all: $(kernel)

clean:
	@rm -r build

run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso)

iso: $(iso)

prepare:
	@mkdir -p build/arch/$(arch)

$(iso): $(kernel) $(grub_cfg) prepare
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles

$(kernel): prepare kernel $(asm_obj_files) $(linker_script)
	@i686-elf-gcc -m32 -ffreestanding -nostdlib -g -T $(linker_script) $(asm_obj_files) build/arch/$(arch)/kernel.o -o build/kernel-$(arch).bin -lgcc

build/arch/$(arch)/%.o: kernel/arch/$(arch)/%.S
	@mkdir -p $(shell dirname $@)
	# @i686-elf-gcc -m32 -std=gnu99 -ffreestanding -g -c $< -o $@
	@nasm -felf32 $< -o $@

kernel: prepare
	@i686-elf-gcc -m32 -std=gnu99 -ffreestanding -g -c kernel/arch/$(arch)/main.c -o build/arch/$(arch)/kernel.o
