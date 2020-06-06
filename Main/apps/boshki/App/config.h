/*
 * boshki App module Configuration
 * 
 * All modules which use GPIO ports 
 * should define port bits/pins here
 */
/*
 * Port A config
 *///                                  76543210
#define SYSTEM_PORT_CFG_DDRA         0b00000000 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTA        0b00000000 // Resistor: 0 = none, 1 = pull-up

/*
 * Port B config
 *///                                  ---43210
#define SYSTEM_PORT_CFG_DDRB         0b00000000 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTB        0b00000000 // Resistor: 0 = none, 1 = pull-up

/*
 * Port C config
 *///                                  76543210
#define SYSTEM_PORT_CFG_DDRC         0b11111111 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTC        0b00000000 // Resistor: 0 = none, 1 = pull-up

/*
 * Port D config
 *///                                  765432--
#define SYSTEM_PORT_CFG_DDRD         0b00001100 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTD        0b00010000 // Resistor: 0 = none, 1 = pull-up

/*
 * System_Key Port Mappings
 * Module System_Key use lower 2 bits of PORTB
 * And 2 bits of key state (buffer) register
 */
#define systemKeyPortIn                         PIND
#define SYSTEM_KEY_0_CFG_PORT_IN_BIT            4
#define SYSTEM_KEY_0_CFG_STREG_BIT              4

/*
 * Leds to PORT mapping
 */
#define systemLedPortOut                        PORTD
#define SYSTEM_LED_0_CFG_PORT_OUT_BIT           2
#define SYSTEM_LED_1_CFG_PORT_OUT_BIT           3

/*
 * App Gates PORT mapping
 */
#define appGatesPortOut                        PORTC
#define appGatesPortDir                        DDRC
