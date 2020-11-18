MEMORY
{
	FLASH (RX) : ORIGIN = 0x08000000 LENGTH = 64K
	RAM (W!RX) : ORIGIN = 0x20000000 LENGTH = 8K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector*))
		*(.text*)
		*(.rodata*)
	} > FLASH

	__etext = .;

	.data : AT(__etext)
	{
		. = ALIGN(4);
		__data_start__ = .;
		*(.data*)
		. = ALIGN(4);
		__data_end__ = .;
	} > FLASH

	.bss (NOLOAD) :
	{
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		__bss_end__ = .;
	} > RAM

	__StackTop = ORIGIN(RAM) + LENGTH(RAM);
	PROVIDE(__stack = __StackTop);
}	
