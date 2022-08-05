arch ?= x86_64
cc := $(arch)-elf-gcc
kernel := ../build/kernel-$(arch).bin
iso := ../build/os-$(arch).iso
linker_script := arch/$(arch)/linker.ld
grub_cfg := ../grub.cfg
build_dir := ../build/arch/$(arch)
iso_dir := ../build/isofiles

cflags := -std=gnu99 -ffreestanding -g -c -lgcc

asm_input_files := $(wildcard arch/$(arch)/*.S)
asm_output_files := $(asm_input_files:%.S=$(build_dir)/%.o)

c_input_files := $(wildcard core/**/*.c)
c_output_files := $(c_input_files:%.c=$(build_dir)/%.o)

crti_obj := arch/$(arch)/crti.s
crtbegin_obj := $(shell $(cc) $(CFLAGS) -print-file-name=crtbegin.o)
crtend_obj := $(shell $(cc) $(CFLAGS) -print-file-name=crtend.o)
crtn_obj := arch/$(arch)/crtn.s

.PHONY: all clean run iso kernel

all: prepare $(asm_output_files) $(c_output_files) $(build_dir)/kernel.o crt link

clean:
	@rm -r ../build

run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso)

iso: $(iso)

prepare:
	@mkdir -p $(build_dir)/crt

$(iso): prepare all 
	@mkdir -p $(iso_dir)/boot/grub
	@cp $(kernel) $(iso_dir)/boot/kernel.bin
	@cp $(grub_cfg) $(iso_dir)/boot/grub
	@grub-mkrescue -o $(iso) $(iso_dir) 2> /dev/null
	@rm -r $(iso_dir)

link:
	x86_64-elf-ld -n -o ../build/kernel-$(arch).bin -T $(linker_script) $(build_dir)/crt/crti.o \
		$(crtibegin_obj) \
		$(wildcard $(build_dir)/*.o) \
		$(crtend_obj) \
		$(build_dir)/crt/crtn.o

$(build_dir)/%.o: %.S
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $(build_dir)/$(notdir $@)

$(build_dir)/%.o: %.c
	@$(cc) -std=gnu99 -ffreestanding -g -c $< -o $(build_dir)/$(notdir $@) -I ../libc/include -I core/include

crt:
	@$(cc) -std=gnu99 --freestanding -g -c arch/$(arch)/crti.s -o $(build_dir)/crt/crti.o
	@$(cc) -std=gnu99 --freestanding -g -c arch/$(arch)/crtn.s -o $(build_dir)/crt/crtn.o
