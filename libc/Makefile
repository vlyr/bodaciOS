arch ?= x86_64
cc := $(arch)-elf-gcc
build_dir := ../build/arch/$(arch)

libc_input_files := $(wildcard **/*.c)
libc_output_files := $(patsubst %.c, %.o, $(libc_input_files))

all: $(libc_output_files)

clean:
	@rm -r ../build

prepare:
	@rm -r ../build
	@mkdir -p $(build_dir)

# libc
%.o: %.c prepare
	@mkdir -p $(shell dirname $@)
	@$(cc) -MD -c $< -o $(build_dir)/$(notdir $@) -std=gnu11 -ffreestanding -Wall -Wextra -Iinclude
