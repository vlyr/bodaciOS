compile:
	nasm -f elf64 boot.asm
	nasm -f elf64 multiboot_header.asm
	ld -n -o isofiles/boot/kernel.bin -T linker.ld multiboot_header.o boot.o

iso:
	grub-file --is-x86-multiboot2 isofiles/boot/kernel.bin
	grub-mkrescue -o os.iso isofiles

run:
	qemu-system-i386 -cdrom os.iso
