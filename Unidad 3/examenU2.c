#include <avr/io.h>     // Libreri­a para registros de I/O
   #include <util/delay.h> // Libreri­a de AVR para retardos temporales
   #include <avr/pgmspace.h>
   #include <string.h>

   const uint16_t velocidades[] PROGMEM = {0,1000,500,2000};
   /*  Velocidades (posicion 0 apagado)  */
   
   const char estados[][4] PROGMEM = {"VR0","AR0","RV0","RA0","RRP"};
   /*   Estados: 
	 V  verde encendido, rojo apagado. Solo la parte del mismo semaforo
	 R rojo encendido, rojo apagado. Solo la parte del mismo semaforo
	 P peatonal encendido
	 0 peatonal apagado
   
	 Peatonal puede ser rojo si se cambia de lugar, regularmente es la tercera letra del estado
   */
   
   const uint8_t trans[][4] PROGMEM ={ {0,1,1}, {1,2,2}, {2,3,3}, {3,0,4}, {4,0,0} };
   
   /*  Matriz de transicion
	 Estado actual
	 Estado siguiente
	 Estado siguiente si se tiene paso peatonal encendido
   */

   const uint8_t leds[] PROGMEM = {PORTB0, PORTB1, PORTB2, PORTB3, PORTB4};
   /*   leds que utilizamos dentro del ciclo, su orden importa. rojo verde rojo verde peatonal  */
   
   
   void delay(uint16_t tiempo) {
      while (tiempo > 0) {
	   _delay_ms(1);
	   tiempo--;
       }
   }
   /*  Funcion porque delay puede funcionar mal si lo usamos con variables  */
   

   #define NUM_ESTADOS (sizeof(estados) / sizeof(estados[0]))

   int main(void) {
      DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4);
      DDRD &= ~((1 << PD0) | (1 << PD1) |  (1 << PD7));
     PORTD |= 0b10000011;
      /*  Entradas y salidas  */
      
      uint16_t vel;
      uint8_t estado = 0;
      uint8_t flagA = 0;
      
      while(1) {
	 if((PIND & 0b00000011) != 0b00000000) {
	     vel = pgm_read_word(&velocidades[PIND & 0b00000011]);
	    
	    uint8_t i=0;
	    for(i=0; i< ((NUM_ESTADOS+1)/2); i++) {
		if(pgm_read_byte(&estados[estado][i]) == 'V') { 
		  PORTB &= ~(1 << pgm_read_byte(&leds[2*i]));  // rojo apagado
		  PORTB |= (1 << pgm_read_byte(&leds[2*i+1])); // verde encendido
	       }
	       else  if(pgm_read_byte(&estados[estado][i]) == 'R') {
		  PORTB |= (1 << pgm_read_byte(&leds[2*i]));  // rojo encendido
		  PORTB &= ~(1 << pgm_read_byte(&leds[2*i+1])); // verde apagado
	       } else if(pgm_read_byte(&estados[estado][i]) == 'P') {
		   PORTB |= (1 << pgm_read_byte(&leds[2*i]));
	       } 
	       if(pgm_read_byte(&estados[estado][i]) == '0') 
		  PORTB &= ~(1 << pgm_read_byte(&leds[2*i]));
	    }
	    /*  Se aplican las condiciones para que pueda funcionar con letras */
	    
	    
	     for(i=0; i<((NUM_ESTADOS+1)/2); i++) {
	       if(pgm_read_byte(&estados[estado][i]) == 'A') {
		  uint8_t j=0;
		  for(j=0; j<3; j++) {
		   PORTB |= (1 << pgm_read_byte(&leds[2*i+1]));
		   delay(vel/6);
		   PORTB &= ~(1 << pgm_read_byte(&leds[2*i+1]));
		   delay(vel/6);  
		  }
		  flagA = 1;
	       }
	    } 
	    /*  La letra A esta separada porque ocupa un delay especial y utiliza una bandera para señalar que ya se utilizo o no */
	    
	    if(flagA == 1)
	       flagA = 0;
	    else
	       delay(vel);
	   /*   Si la bandera esta apagada, se llama la funcion delay normal  */
	    
	    uint8_t swit = (PIND & 0b10000000) ;
	   if(swit == 0b10000000) 
	       estado = pgm_read_byte(&trans[estado][2]);
	   else
	       estado = pgm_read_byte(&trans[estado][1]);
	   /*  Estado siguiente depende de si peatonal esta encendido o no, normalmente solo se utiliza una vez */ 
	   
	 } else {
	    PORTB &= ~(1 << PORTB0);
	    PORTB &= ~(1 << PORTB1);
	    PORTB &= ~(1 << PORTB2);
	    PORTB &= ~(1 << PORTB3);
	    PORTB &= ~(1 << PORTB4);
	 } 
      }
      return 0;
      }