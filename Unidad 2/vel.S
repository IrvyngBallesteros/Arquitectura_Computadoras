#include <avr/io.h>

; --------- Constantes importantes --------
.equ ENT1, 0
.equ ENT2, 1

.equ LED1, 0
.equ LED2, 1
.equ LED3, 2
.equ LED4, 3

;=============================

.global main

main:
    ; PD0, PD1, PD2 y PD3 como salidas
    sbi 0x04, LED1
    sbi 0x04, LED2
    sbi 0x04, LED3
    sbi 0x04, LED4
    
    ; PD0 PD1 como entradas
    cbi _SFR_IO_ADDR(DDRD), ENT1
    cbi _SFR_IO_ADDR(DDRD), ENT2
    
; --------------- Loop principal ------------------------
LOOP:
;------- Leer solamente las entradas 0 y 1 -----------
    in r16, _SFR_IO_ADDR(PIND)
    andi r16, 0b00000011
    
    cpi r16, 0b00000000
    breq VEL0
    
    cpi r16, 0b00000001
    breq VEL1    
    
    cpi r16, 0b00000010
    breq VEL2
    
    cpi r16, 0b00000011
    breq VEL3
    
 ; ================================= 

  ;------------------- Velocidades ---------------------------
VEL0:
    ldi r21, 0x25
    rjmp PENDULO
    
VEL1:
    ldi r21, 0x50
    rjmp PENDULO

VEL2:
    ldi r21, 0xBB
    rjmp PENDULO

VEL3:
    ldi r21, 0xFF
    rjmp PENDULO    
; ====================================
    
 ;---------------------- Algoritmo dle pendulo -------------------
PENDULO:
    ; PD0
    sbi 0x05, LED1
    rcall DELAY
    cbi 0x05, LED1
    rcall DELAY

    ; PD1
    sbi 0x05, LED2
    rcall DELAY
    cbi 0x05, LED2
    rcall DELAY

    ; PD2
    sbi 0x05, LED3
    rcall DELAY
    cbi 0x05, LED3
    rcall DELAY

    ; PD3
    sbi 0x05, LED4
    rcall DELAY
    cbi 0x05, LED4
    rcall DELAY

    ; Regreso a PB2
    sbi 0x05, LED3
    rcall DELAY
    cbi 0x05, LED3
    rcall DELAY

    ; Regreso a PB1
    sbi 0x05, LED2
    rcall DELAY
    cbi 0x05, LED2
    rcall DELAY
     rjmp LOOP
     
;=============================
     
     
; ---------------------------- Rutina delay ----------------------------
DELAY:
    mov r18, r21
DELAY1:
    ldi R19, 0xFF
DELAY2:
    ldi R20, 0xFF
DELAY3:
    subi R20, 1
    brne DELAY3
    subi R19, 1
    brne DELAY2
    subi R18, 1
    brne DELAY1
    ret
;==========================================