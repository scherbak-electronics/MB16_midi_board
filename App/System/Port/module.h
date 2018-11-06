/*
 * System_Port module
 * 
 * GPIO Hardware peripherial port setup
 * Be carefull with Initial configuration of GPIO pins
 */
#define System_Port_A_setBit(bit)           set_bit(PORTA, bit)
#define System_Port_A_clrBit(bit)           clr_bit(PORTA, bit)
#define System_Port_A_bitIsSet(bit)         bit_is_set(PORTA, bit)

/*
 * Module Initialization
 */
#define System_Port_Init() {\
  	PORTA = SYSTEM_PORT_CFG_PORTA;\
	DDRA = SYSTEM_PORT_CFG_DDRA;\
	PORTB = SYSTEM_PORT_CFG_PORTB;\
	DDRB = SYSTEM_PORT_CFG_DDRB;\
	PORTC = SYSTEM_PORT_CFG_PORTC;\
	DDRC = SYSTEM_PORT_CFG_DDRC;\
	PORTD = SYSTEM_PORT_CFG_PORTD;\
	DDRD = SYSTEM_PORT_CFG_DDRD;\
}
