# BodaciOS - A Minimal Operating System for Learning Purposes
![Preview](media/preview.png?raw=true "Preview")

## Usage

### Dependencies
* GNU Make
* QEMU
* Cross-compiled GCC for your intended target (`x86_64-elf-gcc` or `i686-elf-gcc`, for example).

### Building and Running
**NOTE: The only supported targets as of now are `i686` and `x86_64`.**

 Arch Linux users can download a cross-compiled GCC from the [AUR](https://aur.archlinux.org/packages?K=elf-gcc).


```
git clone https://github.com/vlyr/bodaciOS
cd bodaciOS

# ./run.sh Builds the kernel, creates an ISO file and runs it via `qemu-system-x86_64`.
./build.sh
```
