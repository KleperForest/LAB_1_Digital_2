#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	// Configuración del puerto D como salida
	DDRD = 0xFF;  // 0xFF en binario es 11111111, lo que significa que todos los pines del puerto D son configurados como salida
	
	// Configuración de los pines PC3, PC4 y PC5 como salida
	DDRC |= (1 << PC3) | (1 << PC4) | (1 << PC5);  // Configura PC3, PC4 y PC5 como salidas

	// Bucle principal vacío
	while (1) {
		// Aquí puede ir el código adicional que quieras ejecutar continuamente
		
		//Establecer PC5 en alto (HIGH) y PC4, PC3 en bajo (LOW)
		PORTC |= (1 << PC5);  // Establece PC5 en alto Transistor de Display
		PORTC &= ~((1 << PC3) | (1 << PC4));  // Establece PC3 y PC4 en bajo
		PORTD = 0b01000000;
		_delay_ms(10000);
		
		//Establecer PC5 en alto (HIGH) y PC4, PC3 en bajo (LOW)
		PORTC |= (1 << PC5);  // Establece PC5 en alto Transistor de Display
		PORTC &= ~((1 << PC3) | (1 << PC4));  // Establece PC3 y PC4 en bajo
		PORTD = 0b00100000;
		_delay_ms(10000);
		
		//Establecer PC5 en alto (HIGH) y PC4, PC3 en bajo (LOW)
		PORTC |= (1 << PC5);  // Establece PC5 en alto Transistor de Display
		PORTC &= ~((1 << PC3) | (1 << PC4));  // Establece PC3 y PC4 en bajo
		PORTD = 0b00010000;
		_delay_ms(10000);
		
		//Establecer PC5 en alto (HIGH) y PC4, PC3 en bajo (LOW)
		PORTC |= (1 << PC5);  // Establece PC5 en alto Transistor de Display
		PORTC &= ~((1 << PC3) | (1 << PC4));  // Establece PC3 y PC4 en bajo
		PORTD = 0b00001000;
		_delay_ms(10000);
		
		//Establecer PC5 en alto (HIGH) y PC4, PC3 en bajo (LOW)
		PORTC |= (1 << PC5);  // Establece PC5 en alto Transistor de Display
		PORTC &= ~((1 << PC3) | (1 << PC4));  // Establece PC3 y PC4 en bajo
		PORTD = 0b00000100;
		_delay_ms(10000);
		
		//Establecer PC5 en alto (HIGH) y PC4, PC3 en bajo (LOW)
		PORTC |= (1 << PC5);  // Establece PC5 en alto Transistor de Display
		PORTC &= ~((1 << PC3) | (1 << PC4));  // Establece PC3 y PC4 en bajo
		PORTD = 0b00000010;
		_delay_ms(10000);
		
		//Establecer PC5 en alto (HIGH) y PC4, PC3 en bajo (LOW)
		PORTC |= (1 << PC5);  // Establece PC5 en alto Transistor de Display
		PORTC &= ~((1 << PC3) | (1 << PC4));  // Establece PC3 y PC4 en bajo
		PORTD = 0b00000001;
		_delay_ms(10000);
		
	}
	
	return 0;
}
