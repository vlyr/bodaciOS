.PHONY: run build

all: run

run: build

build:
	@make -C libc
	@make -C kernel

run: build
	@make -C kernel run
