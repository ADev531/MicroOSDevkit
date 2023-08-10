CCFLAGS = -m32 -fno-rtti -fno-exceptions -ffreestanding -Wno-narrowing

all: kernel.elf
	qemu-system-i386 -kernel kernel.elf

kernel.elf: kernelentry.o kernel.o osdevkit.o
	ld -m elf_i386 -T link.ld -o kernel.elf kernelentry.o osdevkit.o kernel.o

osdevkit.o: Drivers/OSDevkit.cpp
	g++ $(CCFLAGS) -c Drivers/OSDevkit.cpp -o osdevkit.o

kernelentry.o: kernel.asm
	nasm -f elf32 kernel.asm -o kernelentry.o

kernel.o: kernel.cpp
	g++ $(CCFLAGS) -c kernel.cpp -o kernel.o