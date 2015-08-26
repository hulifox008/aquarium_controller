.thumb
.section .init

.equ    RAM_START, 0x20000000

/* IVT */

.word   0x20008000      /* SP */
.word   start

.org    0x4C
.word   isr_rtc

/* End IVT */

.org    0x300
.thumb_func
start:
#Test we are running in RAM or ROM. If in ROM, we need to copy .data section to RAM
    mov     r0, pc
    ldr     r1, =RAM_START
    cmp     r0, r1 
    bcs     start_main 

#copy data section to RAM
    ldr     r0, =_sidata
    ldr     r1, =_sdata
    ldr     r2, =_edata

copy_data_loop:
    cmp     r1, r2
    beq     zero_bss
    ldr     r7, [r0]
    str     r7, [r1]
    add     r0, #4
    add     r1, #4
    b       copy_data_loop

zero_bss:
    ldr     r0, =_sbss
    ldr     r1, =_ebss
    mov     r7, #0
zero_bss_loop:
    cmp     r0, r1
    beq     start_main
    str     r7, [r0]
    add     r0, #4
    b       zero_bss_loop


start_main:
    bl      main

loop:
    b       loop


