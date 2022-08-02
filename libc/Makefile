arch ?= i686

input_files := $(wildcard string/*.c)
output_files := $(patsubst string/%.c, ../build/arch/$(arch)/%.o, $(input_files))

.PHONY: build

all: $(output_files)

../build/arch/$(arch)/%.o: string/%.c
	@mkdir -p $(shell dirname $@)
	# @i686-elf-gcc -m32 -std=gnu99 -ffreestanding -g -c $< -o $@
	@i686-elf-gcc -MD -c $< -o $@ -std=gnu11 -ffreestanding -Wall -Wextra -Iinclude
