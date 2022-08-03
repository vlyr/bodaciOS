linker_script := linker.ld

c_input_files := $(wildcard *.c)
c_output_files := $(patsubst %.c, build/%.o, $(c_input_files))

asm_input_files := $(wildcard *.S)
asm_output_files := $(patsubst %.S, build/%.o, $(asm_input_files))

all: prepare $(c_output_files) $(asm_output_files) link

$(c_output_files): $(c_input_files)
	@i686-elf-gcc -m32 -c $< -o $@ -ffreestanding -z max-page-size=0x1000 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -std=gnu99 -O2 -Wall -Wextra

$(asm_output_files): $(asm_input_files)
	@nasm -felf32 $< -o $@

prepare:
	@mkdir -p build

link:
	@i686-elf-gcc -T $(linker_script) -o build/loader.bin $(wildcard build/*.o) -ffreestanding -O2 -nostdlib -lgcc
