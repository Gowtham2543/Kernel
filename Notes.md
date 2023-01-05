Most registers of the x86 CPU have well defined values after power-on. The Instruction Pointer (EIP) register holds the memory address for the instruction being executed by the processor. EIP is hardcoded to the value 0xFFFFFFF0. Thus, the x86 CPU is hardwired to begin execution at the physical address 0xFFFFFFF0. It is in fact, the last 16 bytes of the 32-bit address space. This memory address is called reset vector.

Now, the chipset’s memory map makes sure that 0xFFFFFFF0 is mapped to a certain part of the BIOS, not to the RAM. Meanwhile, the BIOS copies itself to the RAM for faster access. This is called shadowing. The address 0xFFFFFFF0 will contain just a jump instruction to the address in memory where BIOS has copied itself.

Thus, the BIOS code starts its execution.  BIOS first searches for a bootable device in the configured boot device order. It checks for a certain magic number to determine if the device is bootable or not. (whether bytes 511 and 512 of first sector are 0xAA55)

Once the BIOS has found a bootable device, it copies the contents of the device’s first sector into RAM starting from physical address 0x7c00; and then jumps into the address and executes the code just loaded. This code is called the bootloader.

The bootloader then loads the kernel at the physical address 0x100000. The address 0x100000 is used as the start-address for all big kernels on x86 machines.
