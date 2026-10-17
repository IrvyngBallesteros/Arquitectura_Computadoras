#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdint.h>

const uint16_t vector[] PROGMEM = {15, 300, 450, 600, 750, 900, 1000, 1200};
void esperar_ms(uint16_t tiempo) {
    while (tiempo > 0) {
        _delay_ms(1);
        tiempo--;
    }
}

int main(void) {
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);

    DDRD &= ~((1 << PD0) | (1 << PD1) | (1 << PD2));
    PORTD |= 0b00000111;
    uint16_t vel;

    while (1) {
        vel = pgm_read_word(&vector[PIND & 0b00000111]);

        PORTB |= (1 << PORTB0);
        esperar_ms(vel);
        PORTB &= ~(1 << PORTB0);
        esperar_ms(vel);

        PORTB |= (1 << PORTB1);
        esperar_ms(vel);
        PORTB &= ~(1 << PORTB1);
        esperar_ms(vel);

        PORTB |= (1 << PORTB2);
        esperar_ms(vel);
        PORTB &= ~(1 << PORTB2);
        esperar_ms(vel);

        PORTB |= (1 << PORTB3);
        esperar_ms(vel);
        PORTB &= ~(1 << PORTB3);
        esperar_ms(vel);

        PORTB |= (1 << PORTB2);
        esperar_ms(vel);
        PORTB &= ~(1 << PORTB2);
        esperar_ms(vel);

        PORTB |= (1 << PORTB1);
        esperar_ms(vel);
        PORTB &= ~(1 << PORTB1);
        esperar_ms(vel);
    }

    return 0;
}
