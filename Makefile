arch ?= x86_64
cc := $(arch)-elf-gcc
kernel := build/kernel-$(arch).bin
iso := build/os-$(arch).iso
linker_script := kernel/arch/$(arch)/linker.ld
grub_cfg := grub.cfg
build_dir := build/arch/$(arch)

cflags := -std=gnu99 -ffreestanding -g -c -lgcc

asm_input_files := $(wildcard kernel/arch/$(arch)/*.S)
asm_output_files := $(patsubst kernel/arch/$(arch)/%.S, $(build_dir)/%.o, $(asm_input_files))

c_input_files := $(wildcard kernel/core/*/*.c)
c_output_files := $(c_input_files:kernel/%.c=$(build_dir)/%.o)

crti_obj := kernel/arch/$(arch)/crti.s
crtbegin_obj := $(shell $(cc) $(CFLAGS) -print-file-name=crtbegin.o)
crtend_obj := $(shell $(cc) $(CFLAGS) -print-file-name=crtend.o)
crtn_obj := kernel/arch/$(arch)/crtn.s

local_crt_objs = $(crti_obj) $(crtn_obj)

libc_input_files := $(wildcard libc/string/*.c)
libc_output_files := $(patsubst libc/string/%.c, $(build_dir)/%.o, $(libc_input_files))

.PHONY: all clean run iso kernel

all: kernel link

clean:
	@rm -r build

run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso)

iso: $(iso)

prepare:
	@mkdir -p $(build_dir)

$(iso): prepare all 
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles

link:
	@x86_64-elf-ld -n -o build/kernel-$(arch).bin -T $(linker_script) $(wildcard $(build_dir)/*.o) # $(crti_obj) $(crtibegin_obj) $(wildcard $(build_dir)/*.o) $(crtend_obj) $(crtn_obj)

kernel: prepare $(asm_output_files) $(c_output_files) $(libc_output_files) $(linker_script)
	@$(cc) $(cflags) kernel/kernel.c -o $(build_dir)/kernel.o -I libc/include -I kernel/core/include

# assembly
$(build_dir)/%.o: kernel/arch/$(arch)/%.S
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@

# c kernel code
$(build_dir)/%.o: $(c_input_files)
	@$(cc) -std=gnu99 -ffreestanding -g -c $< -o $(build_dir)/$(notdir $@) -I libc/include -I kernel/core/include

# libc
$(libc_output_files): $(libc_input_files) prepare
	@mkdir -p $(shell dirname $@)
	@$(cc) -MD -c $< -o $@ -std=gnu11 -ffreestanding -Wall -Wextra -Iinclude
