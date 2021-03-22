/* STM32F767ZI Memory Map (Internal Memories):
 *
 * Region                Address Bounds
 * Auxiliiary SRAM       0x2007 C000 - 0x2007 FFFF
 * Main SRAM             0x2002 0000 - 0x2007 BFFF
 * DTCM                  0x2000 0000 - 0x2001 FFFF
 * Option Bytes          0x1FFF 0000 - 0x1FFF 001F
 * AXIM OTP              0x1FF0 F000 - 0x1FF0 F41F
 * AXIM System Memory    0x1FF0 0000 - 0x1FF0 EDBF
 * AXIM Flash            0x0800 0000 - 0x081F FFFF
 * ITCM Flash            0x0020 0000 - 0x003F FFFF
 * ITCM OTP              0x0010 F000 - 0x0010 F41F
 * ITCM System Memory    0x0010 0000 - 0x0010 EDBF
 * ITCM                  0x0000 0000 - 0x0000 3FFF
 *
 * SRAM
 * - 16 kB Auxiliary SRAM
 *      Can be accessed as bytes, half-words, or full-words. Accessible by all AHB masters from the AHB bus matrix.
 * - 368 kB Main SRAM
 *      Can be accessed as bytes, half-words or full-words. Accessible by all AHB masters from the AHB bus matrix.
 * - 128 kB Data TCM (TCM is implemented with SRAM)
 *      Can be accessed as bytes, half-words, full-words, or double words. Accessible by all AHB masters from the
 *      AHB bus matrix but through a specific AHB slave bus of the CPU.
 * - 16 kB Instruction TCM (TCM is implemented with SRAM)
 *      Can be accessed as bytes, half-words, or full-words. Accessible by ONLY the CPU.
 *
 * Flash
 * - 2 MB Internal Flash
 *      The two flash regions (called AXIM/ITCM Flash) refer to the same physical flash memory and differ in which
 *      bus is used to communicate to the flash.
 *      AXIM Flash
 *         This memory region is defined by access via the 64-bit AHB interface (which is connected to the AXI
 *         master bus of the M7 core through the AHB bus matrix). Accesses are accelerated by the L1 cache. This
 *         interface supports read and write accesses.
 *      ITCM Flash
 *         This memory region is defined by access via the ITCM bus of the M7 core. Accesses are accelerated by the
 *         ART accelerator which contains a unified 64 cache lines. This interface supports ONLY read accesses thus
 *         is recommended for instruction execution and data reading.
 *
 * System Memory
 * - 60 kB System Memory
 *      The two system memory regions (called AXIM/ITCM System Memory) refer to the same physical boot ROM and
 *      differ in which bus is used to communicate to the flash. Irregardless of the flash bank configurations, the
 *      address of the system memory (accessed either through the AXIM or ITCM interfaces) will not change. This
 *      region also contains the embedded bootloader which is programmed by ST during production.
 *
 * OTP (One-Time Programmable)
 *      The two OTP memory regions (called AXIM/ITCM OTP) refer to the same physical memory and differ in which bus
 *      is used to communicate with said memory. Irregardless of the flash bank configurations, the address of the
 *      OTP (accessed either through the AXIM or ITCM interfaces) will not change. This region also contains an
 *      additional 16 bytes (which have been taken into consideration for the listed address range) used to lock
 *      OTP data block.
 */

/*! Note to future Nick regarding LMA and VMA for ITCM/AXIM flash.
 *
 * If you see issues pop regarding execution of seemingly random instructions and the PC becoming garbage refer to
 * this link about LMA and VMA alignment, discussing the use of ALIGN_WITH_INPUT:
 * https://github.com/DISTORTEC/distortos/commit/12765ae58aefad3d51d579a3b90c0abbb7eb75a0
 */

ENTRY(Reset_Handler)

MEMORY
{
	FLASH_AXIM (rwx) : ORIGIN = 0x08000000, LENGTH = 0x00200000 /*    2 MB */
	FLASH_ITCM  (rx) : ORIGIN = 0x00200000, LENGTH = 0x00200000 /*    2 MB */
	OTP_AXIM     (r) : ORIGIN = 0x1FF0F000, LENGTH = 0x00000420 /* 1024  B */
	OTP_ITCM     (r) : ORIGIN = 0x0010F000, LENGTH = 0x00000420 /* 1024  B */
	AUX_SRAM  (rw!x) : ORIGIN = 0x2007C000, LENGTH = 0x00004000 /*   16 kB */
	MAIN_SRAM (rw!x) : ORIGIN = 0x20020000, LENGTH = 0x0005C000 /*  368 kB */
	DTCM      (rw!x) : ORIGIN = 0x20000000, LENGTH = 0x00020000 /*  128 kB */
	ITCM       (rwx) : ORIGIN = 0x00000000, LENGTH = 0x00004000 /*   16 kB */
}

/*! Stack size declaration.
 *
 *  The heap size is not declared here because the heap is a statically allocated array declared within
 *  startup_stm32f767zi.c (whose size is defined in FreeRTOSConfig.h).
 *  Note that the main stack is so small because it is only needed for the startup logic and main(). The stacks of
 *  all the FreeRTOS tasks (as well as the task's TCB structure) comes from the heap.
 */
__STACK_SIZE = 0x00004650; /* 18 kB */

SECTIONS
{
	/* ========================================================================================================== */
	/* Text Section                                                                                               */
	/* ========================================================================================================== */
	/*! The .text section for the interrupt vector table.
	 *
	 * @note  The vector table need not be in ITCM/AXIM flash. Depending on the value of the BOOT pin during
	 *        system POR (more specifically the 4th clock pulse of the sysclk after POR) and the subsequent value of
	 *        BOOT_ADD0 or BOOT_ADD1, the vector table can be located to any number of pre-determined locations.
	 *        The default behavior though, programmed by ST, is to boot at address 0x0020 0000, a.k.a ITCM flash.
	 *
	 * @note  The 'ALIGN_WITH_INPUT' instruction isn't technically necessary in this situation b/c both the VMA and
	 *        LMA for the .text.vector_table output section should be starting from the beginning of their
	 *        respective memory regions as the .text.vector_table output section is the first output section in the
	 *        linker script. More specifically, the VMA will be starting from 0x0020_0000 and the LMA will be
	 *        starting from 0x0800_0000 irregardless of whether or not the 'ALIGN_WITH_INPUT' instruction is
	 *        present and as such both the LMA and VMA will correctly follow any alignment commands present.
	 *        The 'ALIGN_WITH_INPUT' instruction would become necessary if the BOOT address is changed via the BOOT
	 *        pin + BOOT_ADD0/BOOT_ADD1 and the vector table would then be located in a spot in memory such that
	 *        the .text.vector_table output section is not the first output section in the linker script and there
	 *        are other output sections before it that have VMAs or LMAs in AXIM or ITCM flash. In this case,
	 *        without the 'ALIGN_WITH_INPUT' instruction, the VMA of the .text.vector_table output section would
	 *        follow alignment directives but the LMA would not which would inevitably cause the VMA and LMA to have
	 *        different offsets from the base of ITCM flash and AXIM flash respectively.
	 */
	.text.vector_table : ALIGN_WITH_INPUT
	{
		. = ALIGN(4);

		KEEP(*(.vectors))

		. = ALIGN(4);
	} > FLASH_ITCM AT > FLASH_AXIM /* VMA in ITCM flash, LMA in AXIM flash */

	/*! The .text section containing the global section table.
	 *
	 * @note  The global section table is used to track the VMA, LMA, and size of the .text.fast_text, .data, and
	 *        .bss sections. The GST is used by the boot code to determine the addressing involved with copying the
	 *        .text.fast_text section from flash to ITCM, copying the .data section from flash to DTCM, and zero-ing
	 *        out the .bss section.
	 */
	.global_section_table : ALIGN_WITH_INPUT
	{
		. = ALIGN(4);
		__gst_start__ = .;

		LONG(LOADADDR(.text.fast_text)); /* LMA of .text.fast_text section  */
		LONG(    ADDR(.text.fast_text)); /* VMA of .text.fast_text section  */
		LONG(  SIZEOF(.text.fast_text)); /* Size of .text.fast_text section */
		LONG(LOADADDR(.data));           /* LMA of .data section            */
		LONG(    ADDR(.data));           /* VMA of .data section            */
		LONG(  SIZEOF(.data));           /* Size of .data section           */
		LONG(LOADADDR(.bss));            /* LMA of .bss section             */
		LONG(    ADDR(.bss));            /* VMA of .bss section             */
		LONG(  SIZEOF(.bss));            /* Size of .bss section            */

		. = ALIGN(4);
		__gst_end__ = .;
	} > FLASH_ITCM AT > FLASH_AXIM /* VMA in ITCM flash, LMA in AXIM flash */

	/*! The .text section containing program code.
	 *
	 * @note  This section MUST come before the .text.fast_text section!!! This is because if it does not, the
	 *        linker will move the LMA location forward through AXIM flash as it reads through the .text.fast_text
	 *        output section and when the linker gets to this output section, the VMA will still be at the end of
	 *        the .global_section_table but the LMA location will be at the end of the .global_section_table + the
	 *        size of the .text.fast_text section. Having the VMA and LMA out-of-sync with different offsets from
	 *        the bases of their respective memory regions will have undefined behavior.
	 *
	 * @note  The output section starts off on a 32-byte alignment b/c when the embedded flash is configured in
	 *        single bank mode (which it is b/c that is the default behavior i.e. nDBANK=1), reads of the flash over
	 *        the ITCM bus results in an access of 256 bits. Thus we align to the nearest ART cache line read size
	 *        of 256 bits.
	 */
	.text : ALIGN_WITH_INPUT
	{
		. = ALIGN(32);

		*(.text)

		. = ALIGN(4);
		__etext = .;
	} > FLASH_ITCM AT > FLASH_AXIM /* VMA in ITCM flash, LMA in AXIM flash */

	/*! The .text section for critical, real-time routines.
	 *
	 * @note  This section MUST come after the .text section. See the comments for the .text section for why.
	 */
	.text.fast_text :
	{
		. = ALIGN(4);
		__fast_text_start__ = .;

		*(.text.fast_text)

		. = ALIGN(4);
		__fast_text_end__ = .;
	} > ITCM AT > FLASH_AXIM /* VMA in ITCM, LMA in AXIM flash */

	.roddata :
	{
		. = ALIGN(4);

		*(.rodata)
		*(.rodata*)

		. = ALIGN(4);
	} > FLASH_ITCM AT > FLASH_AXIM /* VMA in ITCM flash, LMA in AXIM flash */

	/* ========================================================================================================== */
	/* Data Section                                                                                               */
	/* ========================================================================================================== */
	.data : 
	{
		. = ALIGN(4);
		__data_start__ = .;

		*(.data)
		*(.data*)

		. = ALIGN(4);
		__data_end__ = .;
	} > DTCM AT > FLASH_AXIM /* VMA in DTCM, LMA in AXIM flash */

	/* ========================================================================================================== */
	/* .BSS, Uninitialized Data, Section                                                                          */
	/* ========================================================================================================== */
	.bss : ALIGN(4)
	{
		__bss_start__ = .;

		*(.bss)
		*(.bss*)
		*(COMMON) /* input section for global uninitialized variables that go beyond file scope */

		. = ALIGN(4);
		__bss_end__ = .;
	} > DTCM /* VMA and LMA in DTCM */

	/* ========================================================================================================== */
	/* Dummy Heap                                                                                                 */
	/* ========================================================================================================== */
	/*! The output section containing the statically allocated array representing the heap.
	 *
	 * @note  This section is marked as NOLOAD because in the OpenOCD configuration script for the stm32f767zi there
	 *        are two flash banks declared (three if you include the virtual alias for the ITCM flash but that is
	 *        not applicable for this note). The first of the two flash banks is the AXIM flash which is used for
	 *        *normal* code. The second flash bank is the OTP flash which is used for *non-normal* one-time write
	 *        code. When the GDB loader attempts to load the .elf the stm32f2x OpenOCD flash driver will infer which
	 *        flash bank to load to based on the address of each linker script output section. If the dummy heap
	 *        section is loaded OpenOCD will throw a warning because there is no flash bank at 0x2020 0000 (the
	 *        start of the main SRAM region). The NOLOAD prevents this warning during flashing.
	 */
	.heap_dummy (NOLOAD) : ALIGN(4)
	{
		__heap_base = .;

		KEEP(*(.heap))

		__heap_limit = .;
	} > MAIN_SRAM /* VMA and LMA in main SRAM */

	/* ========================================================================================================== */
	/* User Stack                                                                                                 */
	/* ========================================================================================================== */
	.user_stack :
	{
		. = ALIGN(8);
		__stack_limit = .; /* base of stack, aligned on 8-byte boundary as per AAPCS */

		. = . + __STACK_SIZE;

		. = ALIGN(8);
		__stack_top = .;
		__stack_base = .;
	} > MAIN_SRAM /* VMA and LMA in main SRAM */

	/* Check if the heap + stack overflows the amount of space available in main SRAM */
	ASSERT(((ORIGIN(MAIN_SRAM) + LENGTH(MAIN_SRAM)) > __stack_base), "region main SRAM overflowed")
}

/* EOF */
