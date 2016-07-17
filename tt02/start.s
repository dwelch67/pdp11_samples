

.globl _start
_start:

    mov $0x8000,sp
    jsr pc,_notmain
    halt

.globl _dummy
_dummy:
    rts pc
