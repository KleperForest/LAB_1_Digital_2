// Definimos los registros y bits específicos del ATmega328P
#include <avr/io.h>
#include <util/delay.h>

// Definimos el pin donde conectaremos el LED
#define LED_PIN PD7

int main(void) {
	// Configuramos el pin LED_PIN como salida
	DDRD |= (1 << LED_PIN);

	while (1) {
		// Encendemos el LED
		PORTD |= (1 << LED_PIN);
		_delay_ms(500); // Esperamos 500 milisegundos

		// Apagamos el LED
		PORTD &= ~(1 << LED_PIN);
		_delay_ms(1000); // Esperamos 500 milisegundos
	}

	return 0;
}
