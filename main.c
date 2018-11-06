/*
 * MB16 MIDI board
 */
#ifndef __AVR_ATmega16__
	#define __AVR_ATmega16__
#endif
#include <avr/interrupt.h>
#include <util/delay_basic.h>
#include "lib/system_m16.h"
#include "App/module.h"

struct SYSTEM_MODULE system;
struct MIDI_MODULE midi;
struct CONTROLLER_MODULE controller;

/*
 * System_Timer_0 interrupt vector
 */
ISR(TIMER0_OVF_vect) {
	System_Timer_0_OVF_InterruptVector();
}

/*
 * USART interrupt vector
 */
ISR (USART_RXC_vect) {
    System_USART_RXC_InterruptVector();
}

/*
 * main
 */
int main() {
	App_Init();
	while(1) {
		App_Process();
	}
	return 0;
}
