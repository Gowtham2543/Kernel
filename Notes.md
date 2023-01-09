# Boot Process

Most registers of the x86 CPU have well defined values after power-on. The Instruction Pointer (EIP) register holds the memory address for the instruction being executed by the processor. EIP is hardcoded to the value 0xFFFFFFF0. Thus, the x86 CPU is hardwired to begin execution at the physical address 0xFFFFFFF0. It is in fact, the last 16 bytes of the 32-bit address space. This memory address is called reset vector.

Now, the chipset’s memory map makes sure that 0xFFFFFFF0 is mapped to a certain part of the BIOS, not to the RAM. Meanwhile, the BIOS copies itself to the RAM for faster access. This is called shadowing. The address 0xFFFFFFF0 will contain just a jump instruction to the address in memory where BIOS has copied itself.

Thus, the BIOS code starts its execution.  BIOS first searches for a bootable device in the configured boot device order. It checks for a certain magic number to determine if the device is bootable or not. (whether bytes 511 and 512 of first sector are 0xAA55)

Once the BIOS has found a bootable device, it copies the contents of the device’s first sector into RAM starting from physical address 0x7c00; and then jumps into the address and executes the code just loaded. This code is called the bootloader.

The bootloader then loads the kernel at the physical address 0x100000. The address 0x100000 is used as the start-address for all big kernels on x86 machines.

# Multiboot

There is a standard for loading various x86 kernels using a boot loader; called as Multiboot specification.

GRUB will only load our kernel if it complies with the Multiboot spec.

According to the spec, the kernel must contain a header (known as Multiboot header) within its first 8 KiloBytes.

Further, This Multiboot header must contain 3 fields that are 4 byte aligned namely:

1. magic field: containing the magic number 0x1BADB002, to identify the header.
2. flags field: We will not care about this field. We will simply set it to zero.
3. checksum field: the checksum field when added to the fields ‘magic’ and ‘flags’ must give zero.

# VGA 
Each screen character is represented by two bytes aligned as a 16-bit word  


![Screenshot_20230109_224911](https://user-images.githubusercontent.com/74668263/211368297-e927377d-7fed-420b-93ab-be3b3b5a473b.png)

