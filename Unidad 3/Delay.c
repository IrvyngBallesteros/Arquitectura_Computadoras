#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t contador_ms = 0;

ISR(TIMER1_COMPA_vect) {

    contador_ms++;

    if (contador_ms >= 500) {
        PORTB ^= (1 << PB5);
        contador_ms = 0;
    }
}

int main() {

    DDRB |= (1 << DDB5);

    DDRD &= ~((1 << DDD0) | (1 << DDD1));
    PORTD |= (1 << PORTD0) | (1 << PORTD1);

    TCCR1A = 0;
    TCCR1B = 0;

    TCCR1B |= (1 << WGM12);
    TIMSK1 |= (1 << OCIE1A);

    sei();

    uint8_t velocidad_anterior = 255;

    while (1) {

        uint8_t velocidad = PIND & 0b00000011;

        if (velocidad != velocidad_anterior) {

            velocidad_anterior = velocidad;

            TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

            contador_ms = 0;

            switch (velocidad) {

                case 0b00:
                    OCR1A = 1999;
                    TCCR1B |= (1 << CS11);
                    break;

                case 0b01:
                    OCR1A = 249;
                    TCCR1B |= (1 << CS11) | (1 << CS10);
                    break;

                case 0b10:
                    OCR1A = 1249;
                    TCCR1B |= (1 << CS12);
                    break;

                case 0b11:
                    PORTB &= ~(1 << PB5);
                    break;
            }
        }
    }
}
