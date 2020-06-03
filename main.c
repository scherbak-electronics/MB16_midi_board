/*
 * MB16 MIDI board
 */
#ifndef __AVR_ATmega16__
	#define __AVR_ATmega16__
#endif
#include <avr/interrupt.h>
#include <util/delay_basic.h>
#include "Main/module.h"

struct APP_MODULE app;
struct SYSTEM_MODULE system;
struct MIDI_MODULE midi;


/*
 * System_Timer_0 interrupt vector
 */
ISR(TIMER0_OVF_vect){
	System_Timer_0_OVF_InterruptVector();
}

/*
 * USART interrupt vector
 */
ISR (USART_RXC_vect) {
    System_USART_RXC_InterruptVector();
}

/*
 * Add 3 bytes to TX buffer
 */
void System_USART_Send3Bytes(BYTE b1, BYTE b2, BYTE b3) {
	if ((system.usart.txBufferLevel + 3) < USART_CFG_TX_BUFFER_SIZE) {
		cli();
		system.usart.txBuffer[system.usart.txBufferLevel] = b1;
		system.usart.txBuffer[system.usart.txBufferLevel + 1] = b2;
		system.usart.txBuffer[system.usart.txBufferLevel + 2] = b3;
		system.usart.txBufferLevel += 3;
		sei();
	}
}

/*
 * Add 2 bytes to TX buffer
 */
void System_USART_Send2Bytes(BYTE b1, BYTE b2) {
	if ((system.usart.txBufferLevel + 2) < USART_CFG_TX_BUFFER_SIZE) {
		cli();
		system.usart.txBuffer[system.usart.txBufferLevel] = b1;
		system.usart.txBuffer[system.usart.txBufferLevel + 1] = b2;
		system.usart.txBufferLevel += 2;
		sei();
	}
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
