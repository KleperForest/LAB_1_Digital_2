#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

// Definición de valores hexadecimales para los números del 5 al 0
#define NUM_5 0xF8
#define NUM_4 0x72
#define NUM_3 0xBA
#define NUM_2 0xAE
#define NUM_1 0x12
#define NUM_0 0xDE

// Tabla para mapear los números a los valores hexadecimales
const uint8_t display_values[] = {
	NUM_0,   // 0
	NUM_1,   // 1
	NUM_2,   // 2
	NUM_3,   // 3
	NUM_4,   // 4
	NUM_5    // 5
};

// Función para inicializar el puerto y configurar PB1 como entrada con pull-up
void init_GPIO() {
	// Configurar PB1 como entrada (botón) con pull-up
	DDRB &= ~(1 << PB1);    // PB1 como entrada
	PORTB |= (1 << PB1);    // Habilitar pull-up en PB1
	
	// Configurar PD1 a PD7 como salidas para el display de 7 segmentos
	DDRD |= 0xFE;   // PD1 a PD7 como salidas (0xFE en binario es 11111110)
}

// Función para mostrar un número en el display de 7 segmentos usando la tabla
void display_number(uint8_t number) {
	if (number <= 5) {
		PORTD = display_values[number];
		} else {
		// Apagar todos los segmentos si se recibe un número fuera del rango esperado
		PORTD = 0x00;
	}
}

int main() {
	// Inicializar puertos y configuraciones
	init_GPIO();
	
	// Variable para el contador
	uint8_t contador = 5;
	
	while (1) {
		// Verificar estado del botón en PB1 (se presiona cuando está en bajo debido al pull-up)
		if (!(PINB & (1 << PB1))) {
			// Iniciar contador del 5 al 0 y mostrar en el display de 7 segmentos
			while (contador >= 0) {
				display_number(contador);
				_delay_ms(1000);    // Esperar 1 segundo
				contador--;
			}
		}
	}
	
	return 0;
}
