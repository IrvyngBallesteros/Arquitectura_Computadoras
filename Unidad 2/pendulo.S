#include <avr/io.h>

.global main

main:
    ; PB0, PB1, PB2 y PB3 como salidas
    sbi 0x04, 0
    sbi 0x04, 1
    sbi 0x04, 2
    sbi 0x04, 3

LOOP:

    ; PB0
    sbi 0x05, 0
    rcall DELAY
    cbi 0x05, 0
    rcall DELAY

    ; PB1
    sbi 0x05, 1
    rcall DELAY
    cbi 0x05, 1
    rcall DELAY

    ; PB2
    sbi 0x05, 2
    rcall DELAY
    cbi 0x05, 2
    rcall DELAY

    ; PB3
    sbi 0x05, 3
    rcall DELAY
    cbi 0x05, 3
    rcall DELAY

    ; Regreso a PB2
    sbi 0x05, 2
    rcall DELAY
    cbi 0x05, 2
    rcall DELAY

    ; Regreso a PB1
    sbi 0x05, 1
    rcall DELAY
    cbi 0x05, 1
    rcall DELAY

    

    rjmp LOOP


DELAY:
    mov R18, R17
DELAY1:
    ldi R19, 0x20
DELAY2:
    ldi R20, 0x20
DELAY3:
    subi R20, 1
    brne DELAY3
    subi R19, 1
    brne DELAY2
    subi R18, 1
    brne DELAY1
    ret
