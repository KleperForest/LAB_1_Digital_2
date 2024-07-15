#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t counter = 5; // Valor de cuenta regresiva

const uint8_t fila_1[] = {0x3F, 0x0C, 0x5B, 0x5D, 0x6C, 0x75};  // Valores para los pines de PORTD Display
const uint8_t fila_2[] = {0x00, 0x40, 0x20, 0x10, 0x80};        // Valores para los pines de PORTD Display

volatile uint8_t Bandera_1 = 0;// Bandera para Diplay
volatile uint8_t Bandera_2 = 0;// Bnadera para jugadores
volatile uint8_t P2_RED = 0;// Jugador 2
volatile uint8_t P1_BLUE = 0;// Jugador 1

ISR(PCINT0_vect) {
	// Comprobar si el botón en PB0 está presionado (PB0 es bajo)
	if (!(PINB & (1 << PB0))) {
		if (Bandera_2 == 1) {
			P2_RED++;// Incremento de jugador dos
			P2_RED = (P2_RED > 4) ? 0 : P2_RED;// Evitar que sobre pase 5
			_delay_ms(150); // Antirebote
		}
	}
	
	// Comprobar si el botón en PB1 está presionado (PB1 es bajo)
	if (!(PINB & (1 << PB1))) {
		if (Bandera_2 == 1) {
			P1_BLUE++;// Incremento de jugador uno
			P1_BLUE = (P1_BLUE > 4) ? 0 : P1_BLUE;// Evitar que sobre pase 5
			_delay_ms(150);// Antirebote
		}
	}

	// Comprobar si el botón en PB2 está presionado (PB2 es bajo)
	if (!(PINB & (1 << PB2))) {
		// Activar Timer.
		Bandera_1 = 1;// Activar decremento de display
		_delay_ms(150);// Antirebote
		
	}
}

void pcint_init() {
	PCICR |= (1 << PCIE0);       // Habilitar interrupciones de cambio de pin para PCINT[7:0]
	PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2);  // Habilitar interrupción para PB0, PB1, PB2
}

int main(void) {
	// Configuración del puerto D como salida
	DDRD = 0xFF;  // Todos los pines del puerto D son salidas

	// Configuración de los pines PC3, PC4 y PC5 como salida
	DDRC |= (1 << PC3) | (1 << PC4) | (1 << PC5);  // PC3, PC4 y PC5 como salidas

	// Configuración de PB0, PB1, PB2 como entradas con resistencias pull-up
	DDRB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));  // PB0, PB1, PB2 como entradas
	PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);   // Resistencias pull-up en PB0, PB1, PB2

	// Inicializar interrupciones de puerto B (botones)
	pcint_init();

	// Habilitar interrupciones globales
	sei();

	// Bucle principal
	while (1) {
		// Control de Timer
		while (Bandera_1) {
			// Mostrar valores en Display de Timer (cuenta regresiva)
			PORTC |= (1 << PC5);   // BJT_Display en alto
			PORTC &= ~((1 << PC3) | (1 << PC4));  // BJT_BLUE y BJT_RED en bajo
			
			PORTD = fila_1[counter];  // Mostrar valores en Display de Timer
			
			Bandera_1 = (counter == 0) ? 0 : 1;  // Desactivar Bandera_1 cuando counter llega a 0
			Bandera_2 = (counter == 0) ? 1 : 0;  // Activar Bandera_2 cuando counter llega a 0
			
			_delay_ms(999);  // Esperar 1 segundo (timer)
			
			counter--;  // Decrementar contador
			_delay_ms(1);
		}

		// Control de estados para Bandera_2
		while (Bandera_2) {
			// BJT_Display en bajo, mostrar valores alternativos en Display
			PORTC |= (1 << PC3);   // BJT_BLUE en alto
			PORTC &= ~((1 << PC5) | (1 << PC4));  // BJT_Display y BJT_RED en bajo
			PORTD = fila_2[P1_BLUE];  // Mostrar valores en Display
			_delay_ms(6);

			// BJT_Display en bajo, mostrar valores alternativos en Display
			PORTC |= (1 << PC4);   // BJT_RED en alto
			PORTC &= ~((1 << PC3) | (1 << PC5));  // BJT_Display y BJT_BLUE en bajo
			PORTD = fila_2[P2_RED];  // Mostrar valores en Display
			_delay_ms(6);

		}
	}

	return 0;
}
