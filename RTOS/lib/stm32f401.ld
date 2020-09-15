ENTRY(reset_handler)
_estack = 0x20017FFF;
_Min_Leftover_RAM = 0x400;
MEMORY
{
	FLASH ( rx )	: ORIGIN = 0x08000000, LENGTH = 512K
	RAM ( rxw )		: ORIGIN = 0x20000000, LENGTH = 96K
}

SECTIONS
{
	.vector_table :
	{
		. = ALIGN(4);
		KEEP(*(.vector_table))
		. = ALIGN(4);
	} >FLASH
	.preinit_array :
	{
		. = ALIGN(4);
		_spreinit_array = .;
		KEEP (*(.preinit_array))
		KEEP (*(.preinit_array*))
		_epreinit_array = .;
		. = ALIGN(4);
	} >FLASH
	.init_array :
	{
		. = ALIGN(4);
		_sinit_array = .;
		KEEP (*(.init_array))
		KEEP (*(.init_array*))
		_einit_array = .;
		. = ALIGN(4);
	} >FLASH
	.fini_array :
	{
		. = ALIGN(4);
		_sfini_array = .;
		KEEP (*(.fini_array))
		KEEP (*(.fini_array*))
		_efini_array = .;
		. = ALIGN(4);
	} >FLASH
	.text :
	{
		. = ALIGN(4);
		*(.text)
		*(.text*)
		. = ALIGN(4);
	} >FLASH
	/*.ARM.extab :
	{
		. = ALIGN(4);
		*(.ARM.extab*)
		. = ALIGN(4);
	} >FLASH
	.ARM.exidx :
	{
		. = ALIGN(4);
		*(.ARM.exidx*)
		. = ALIGN(4);
	} >FLASH*/
	.rodata :
	{
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	} >FLASH
	_sidata = .;
	.data : AT(_sidata)
	{
		. = ALIGN(4);
        _sdata = .;
		*(.data)
		*(.data*)
		_edata = .;
		. = ALIGN(4);
	} >RAM
	.bss :
	{
		. = ALIGN(4);
		_sbss = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	} >RAM
	.dynamic_allocations :
	{
		. = ALIGN(4);
		_ssystem_ram = .;
		. = . + _Min_Leftover_RAM;
		. = ALIGN(4);
		_esystem_ram = .;
	} >RAM
}
