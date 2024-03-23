CCFLAGS = -m32 -fno-rtti -fno-exceptions -ffreestanding -Wno-narrowing -Wno-return-local-addr -Wno-sizeof-array-argument -Wno-write-strings

override CPPFILES := $(shell cd src && find -L * -type f -name '*.cpp')
override OBJ := $(addprefix src/,$(CPPFILES:.cpp=.o))

all: RunISO

serialdebug :
	g++ $(CCFLAGS) -D SERIALDEBUG -c etc/debugger.cpp -o debugger.o

fakedebug :
	g++ $(CCFLAGS) -c etc/debugger.cpp -o debugger.o

OS.iso : BuildISO
RunISO: OS.iso
	qemu-system-i386 -cdrom OS.iso -serial stdio -m 512M

BuildISO: kernel.elf
	mkdir -p ISO/boot/grub
	cp kernel.elf ISO/boot/kernel.elf
	cp GrubConfigs/grub.cfg ISO/boot/grub/grub.cfg
	grub-mkrescue -o OS.iso ISO

DebugMode: debuggingkernel BuildISO clean RunISO
debuggingkernel : $(OBJ) kernelentry.o serialdebug linkkernel
kernel.elf: $(OBJ) kernelentry.o fakedebug linkkernel

linkkernel: $(OBJ)
	ld -m elf_i386 -T link.ld -o kernel.elf kernelentry.o debugger.o $(OBJ)

src/%.o: src/%.cpp
	g++ $(CCFLAGS) -c $< -o $@

kernelentry.o: src/kernel.asm
	nasm -f elf32 src/kernel.asm -o kernelentry.o

InstallTools:
	sudo apt install nasm ld g++ grub-common grub-pc-bin qemu-system

clean:
	rm $(OBJ) debugger.o *.elf

fullclean:
	rm -r ISO
	rm -r *.o *.elf *.iso