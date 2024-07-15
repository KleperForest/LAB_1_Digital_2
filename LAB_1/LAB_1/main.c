#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t counter = 5;// Valor de cuenta regresiba

const uint8_t fila[] = {0x3F, 0x0C, 0x5B, 0x5D, 0x6C, 0x75};  // Valores para los pines de PORTD


void timer1_init() {
	// Configurar el Timer1 en modo CTC
	TCCR1B |= (1 << WGM12);  // Configurar el modo CTC (Clear Timer on Compare Match)
	TIMSK1 |= (1 << OCIE1A);  // Habilitar la interrupción por comparación del OCR1A
	OCR1A = 15624;  // Valor de comparación para generar una interrupción cada segundo (con prescaler 1024)
	TCCR1B |= (1 << CS12) | (1 << CS10);  // Configurar el prescaler en 1024
}

ISR(TIMER1_COMPA_vect) {
	if (counter > 0) {
		counter--;  // Decrementar el contador
	}
}

int main(void) {
	// Configuración del puerto D como salida
	DDRD = 0xFF;  // 0xFF en binario es 11111111, lo que significa que todos los pines del puerto D son configurados como salida
	
	// Configuración de los pines PC3, PC4 y PC5 como salida
	DDRC |= (1 << PC3) | (1 << PC4) | (1 << PC5);  // Configura PC3, PC4 y PC5 como salidas
	
	// Inicializar el timer
	timer1_init();
	   
	// Habilitar interrupciones globales
	sei();

	// Bucle principal vacío
	while (1) {
		// Aquí puede ir el código adicional que quieras ejecutar continuamente
		//Establecer PC5 en alto (HIGH) y PC4, PC3 en bajo (LOW)
		PORTC |= (1 << PC5);  // Establece PC5 en alto Transistor de Display
		PORTC &= ~((1 << PC3) | (1 << PC4));  // Establece PC3 y PC4 en bajo
		PORTD = fila[counter];// Mostrar valores en Display de Timer. 
		
	}
	
	return 0;
}
