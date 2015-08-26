
MEMORY
{
    rom (rx)  : ORIGIN = 0x08000000, LENGTH = 0x00040000
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

SECTIONS
{
    /* Image is loaded to RAM at 0x20000000 */
     . = 0x20000000; 



    .text : 
    {
        *(.init) 
        *(.text .text.*) 
        *(.rodata) *(.rodata.*)
    } > ram
    
    . = ALIGN(4);
    _etext = .;
    _sidata = .;
    .data : AT (_etext)
    {
        _sdata = .;
        *(.data .data.*)
        . = ALIGN(4);
        _edata = .;
    } > ram

    .bss (NOLOAD):
    {
        _sbss = .;
        *(.bss .bss.*)
        . = ALIGN(4);
        _ebss = .;
    } > ram

}
