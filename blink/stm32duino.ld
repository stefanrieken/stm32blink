MEMORY
{
rom (rx) : ORIGIN = 0x08002000, LENGTH = 56K
ram (xrw) : ORIGIN = 0x20000C00, LENGTH = 17K
}
_initial_stack = ORIGIN(ram)+LENGTH(ram);

SECTIONS
{
	.text : { *(.text*) . = ALIGN(4); } > rom
	.rodata : { *(.rodata*) . = ALIGN(4); } > rom
	.data : { *(.data*) . = ALIGN(4); } > ram
	.bss : { *(.bss*) . = ALIGN(4); } > ram
}
