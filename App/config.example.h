/*
 * Example module App Configuration
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
#define SYSTEM_PORT_CFG_PORTB        0b00000011 // Resistor: 0 = none, 1 = pull-up

/*
 * Port C config
 *///                                  76543210
#define SYSTEM_PORT_CFG_DDRC         0b00000000 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTC        0b00000000 // Resistor: 0 = none, 1 = pull-up

/*
 * Port D config
 *///                                  765432--
#define SYSTEM_PORT_CFG_DDRD         0b00011000 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTD        0b00000000 // Resistor: 0 = none, 1 = pull-up

/*
 * System_Key Port Mappings
 * Module System_Key use lower 2 bits of PORTB
 * And 2 bits of key state (buffer) register
 */
#define systemKeyPortIn                         PINB
#define SYSTEM_KEY_0_CFG_PORT_IN_BIT            0
#define SYSTEM_KEY_0_CFG_STREG_BIT              0
#define SYSTEM_KEY_1_CFG_PORT_IN_BIT            1
#define SYSTEM_KEY_1_CFG_STREG_BIT              1


/*
 * Leds to PORT mapping
 */
#define systemLedPortOut                        PORTD
#define SYSTEM_LED_0_CFG_PORT_OUT_BIT           3
#define SYSTEM_LED_1_CFG_PORT_OUT_BIT           4


