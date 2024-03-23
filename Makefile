CCFLAGS = -m32 -fno-rtti -fno-exceptions -ffreestanding -Wno-narrowing -Wno-return-local-addr -Wno-sizeof-array-argument

CPPFILES := $(shell find -L . -type f -name '*.cpp')
OBJ := $(CPPFILES:.cpp=.o)

all: kernel.elf
	qemu-system-i386 -kernel kernel.elf -m 512M

BuildISO: kernel.elf
	mkdir -p DevKitISO/boot/grub
	cp kernel.elf DevKitISO/boot/kernel.elf
	cp GrubConfigs/grub.cfg DevKitISO/boot/grub/grub.cfg
	grub-mkrescue -o OS.iso DevKitISO

RunISO: OS.iso
	qemu-system-i386 -cdrom OS.iso -m 512M

kernel.elf: $(OBJ) kernelentry.o
	ld -m elf_i386 -T link.ld -o kernel.elf kernelentry.o $(OBJ)

%.o: %.cpp
	g++ $(CCFLAGS) -c $< -o $@

kernelentry.o: kernel.asm
	nasm -f elf32 kernel.asm -o kernelentry.o

InstallTools:
	sudo apt install nasm ld g++ grub-common grub-pc-bin qemu-system

clean:
	rm $(OBJ) *.elf

fullclean:
	rm -r DevKitISO
	rm -r *.o *.elf *.iso