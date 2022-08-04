# BodaciOS - A Minimal Operating System for Learning Purposes

## Usage

### Dependencies
* QEMU
* Cross-compiled GCC for your intended target (`x86_64-elf-gcc` or `i686-elf-gcc`, for example). Arch Linux users can download a cross-compiled GCC from the [AUR](https://aur.archlinux.org/packages?K=elf-gcc).

### Building and Running

NOTE: The only supported targets as of now are `i686` and `x86_64`.
```
git clone https://github.com/vlyr/bodaciOS
cd bodaciOS

# `make run` Builds the kernel, creates an ISO file and runs it via `qemu-system-x86_64`.
make run
```