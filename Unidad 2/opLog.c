/*
#include <avr/io.h>     // Librería para registros de I/O
#include <util/delay.h> // Librería de AVR para retardos temporales

int main(void) {
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);  //salidas;
   DDRD &= 0b00000000; //entradas
   
   uint8_t n1;
   uint8_t n2;
   
   
   
    while (1) {
        // Codigo Principal
	 
	 n1 = PIND & 0b00001111;
	 n2 = (PIND >> 4) & 0b00001111; //para iniciar despues del cuarto bit a contar
       
// -------------------------------  Operaci[on AND ---------------------------------- //
	 if ((n1 & (1 << 0)) & (n2 & (1 << 0))) {
	    PORTB |= (1 << PORTB0);
	 } else {
	     PORTB &= ~(1 << PORTB0);
	 }
	 if ((n1 & (1 << 1)) & (n2 & (1 << 1))) {
	    PORTB |= (1 << PORTB1);
	 } else {
	     PORTB &= ~(1 << PORTB1);
	 }
	 if ((n1 & (1 << 2)) & (n2 & (1 << 2))) {
	    PORTB |= (1 << PORTB2);
	 } else {
	     PORTB &= ~(1 << PORTB2);
	 }
	 if ((n1 & (1 << 3)) & (n2 & (1 << 3))) {
	    PORTB |= (1 << PORTB3);
	 } else {
	     PORTB &= ~(1 << PORTB3);
	 }
	 _delay_ms(500);
	 
// ----------------------------------- Operacion OR ------------------------------------------ //	 
	 
	 if ((n1 & (1 << 0)) | (n2 & (1 << 0))) {
	    PORTB |= (1 << PORTB0);
	 } else {
	     PORTB &= ~(1 << PORTB0);
	 }
	 if ((n1 & (1 << 1)) | (n2 & (1 << 1))) {
	    PORTB |= (1 << PORTB1);
	 } else {
	     PORTB &= ~(1 << PORTB1);
	 }
	 if ((n1 & (1 << 2)) | (n2 & (1 << 2))) {
	    PORTB |= (1 << PORTB2);
	 } else {
	     PORTB &= ~(1 << PORTB2);
	 }
	 if ((n1 & (1 << 3)) | (n2 & (1 << 3))) {
	    PORTB |= (1 << PORTB3);
	 } else {
	     PORTB &= ~(1 << PORTB3);
	 }
	 _delay_ms(500);
	 
// ------------------------------------------- Operacion EXOR ----------------------------------- //
	
	if ((n1 & (1 << 0)) ^ (n2 & (1 << 0))) {
	    PORTB |= (1 << PORTB0);
	 } else {
	     PORTB &= ~(1 << PORTB0);
	 }
	 if ((n1 & (1 << 1)) ^ (n2 & (1 << 1))) {
	    PORTB |= (1 << PORTB1);
	 } else {
	     PORTB &= ~(1 << PORTB1);
	 }
	 if ((n1 & (1 << 2)) ^ (n2 & (1 << 2))) {
	    PORTB |= (1 << PORTB2);
	 } else {
	     PORTB &= ~(1 << PORTB2);
	 }
	 if ((n1 & (1 << 3)) ^ (n2 & (1 << 3))) {
	    PORTB |= (1 << PORTB3);
	 } else {
	     PORTB &= ~(1 << PORTB3);
	 }
	 _delay_ms(500); 
	
    }

    return 0;
}*/