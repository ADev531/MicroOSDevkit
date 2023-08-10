CCFLAGS = -m32 -fno-rtti -fno-exceptions -ffreestanding -Wno-narrowing -Wno-return-local-addr

CPPFILES := $(shell find -L . -type f -name '*.cpp')
OBJ := $(CPPFILES:.cpp=.o)

all: kernel.elf
	qemu-system-i386 -kernel kernel.elf

buildisoimage: kernel.elf
	mkdir -p DevKitISO/boot/grub
	cp kernel.elf DevKitISO/boot/kernel.elf
	cp GrubConfigs/grub.cfg DevKitISO/boot/grub/grub.cfg
	grub-mkrescue -o MicroOSImage.iso DevKitISO
	qemu-system-i386 -cdrom MicroOSImage.iso

kernel.elf: $(OBJ) kernelentry.o
	ld -m elf_i386 -T link.ld -o kernel.elf kernelentry.o $(OBJ)

%.o: %.cpp
	g++ $(CCFLAGS) -c $< -o $@

kernelentry.o: kernel.asm
	nasm -f elf32 kernel.asm -o kernelentry.o

clean:
	rm $(OBJ) *.elf