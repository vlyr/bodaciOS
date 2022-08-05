arch ?= x86_64
cc := $(arch)-elf-gcc
build_dir := ../build/arch/$(arch)

libc_input_files := $(wildcard **/*.c)
libc_output_files := $(patsubst %.c, %.o, $(libc_input_files))

all: $(libc_output_files)

clean:
	@rm -r ../build

prepare:
	@echo libc input: $(libc_input_files)
	@echo libc output: $(libc_output_files)
	@mkdir -p $(build_dir)

# libc
%.o: %.c prepare
	@mkdir -p $(shell dirname $@)
	@echo $<
	$(cc) -MD -c $< -o $(build_dir)/$(notdir $@) -std=gnu11 -ffreestanding -Wall -Wextra -Iinclude
