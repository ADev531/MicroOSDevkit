# MicroOSDevkit
A Kit for making simple os by C++, currently only building on linux is supported.

# Installing

# On Debian
On debian (ubuntu, linux mint, etc...), You can install needed tools by
<code>make InstallTools</code>.

# Other linux
you need to install nasm, qemu, g++, grub-common, grub-pc-bin, ld.

# Building OS
Simply run <code>./build</code>!
Clean objects/elf/iso by <code>make fullclean</code>.

# Debugging OS
Its simple too, just run <code>make DebugMode</code>!

# MDKConsole
Default mode, MDKConsole.

# MDKGraphics
Only VGA Supported, Max mode is 400x600x256.