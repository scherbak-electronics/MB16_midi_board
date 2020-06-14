/*
 * Port A config
 *///                                             76543210
#define SYSTEM_PORT_CFG_DDRA                    0b00000000 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTA                   0b00000000 // Resistor: 0 = none, 1 = pull-up

/*
 * Port B config
 *///                                             ---43210
#define SYSTEM_PORT_CFG_DDRB                    0b00001111 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTB                   0b00000000 // Resistor: 0 = none, 1 = pull-up

/*
 * Port C config
 *///                                             76543210
#define SYSTEM_PORT_CFG_DDRC                    0b11111111 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTC                   0b00000000 // Resistor: 0 = none, 1 = pull-up

/*
 * Port D config
 *///                                             765432--
#define SYSTEM_PORT_CFG_DDRD                    0b00000000 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTD                   0b00011000 // Resistor: 0 = none, 1 = pull-up

#define instrumentOscPortOut				    PORTC
#define INSTRUMENT_OSC_0_CFG_PORT_OUT_BIT	    0
#define INSTRUMENT_OSC_1_CFG_PORT_OUT_BIT	    1
#define INSTRUMENT_OSC_2_CFG_PORT_OUT_BIT	    2
#define INSTRUMENT_OSC_3_CFG_PORT_OUT_BIT	    3
#define INSTRUMENT_OSC_4_CFG_PORT_OUT_BIT	    4
#define INSTRUMENT_OSC_5_CFG_PORT_OUT_BIT	    5
#define INSTRUMENT_OSC_6_CFG_PORT_OUT_BIT	    6
#define INSTRUMENT_OSC_7_CFG_PORT_OUT_BIT	    7

#define instrumentGatesPortOut				    PORTC
#define INSTRUMENT_GATES_0_CFG_PORT_OUT_BIT	    0
#define INSTRUMENT_GATES_1_CFG_PORT_OUT_BIT	    1
#define INSTRUMENT_GATES_2_CFG_PORT_OUT_BIT	    2
#define INSTRUMENT_GATES_3_CFG_PORT_OUT_BIT	    3
#define INSTRUMENT_GATES_4_CFG_PORT_OUT_BIT	    4
#define INSTRUMENT_GATES_5_CFG_PORT_OUT_BIT	    5
#define INSTRUMENT_GATES_6_CFG_PORT_OUT_BIT	    6
#define INSTRUMENT_GATES_7_CFG_PORT_OUT_BIT	    7


/*
 * System_Key Port Mappings
 * Module System_Key use lower 2 bits of PORTB
 * And 2 bits of key state (buffer) register
 */
#define systemKeyPortIn                         PIND
#define SYSTEM_KEY_0_CFG_PORT_IN_BIT            3
#define SYSTEM_KEY_0_CFG_STREG_BIT              3
#define SYSTEM_KEY_1_CFG_PORT_IN_BIT            4
#define SYSTEM_KEY_1_CFG_STREG_BIT              4

/*
 * Leds to PORT mapping
 */
#define systemLedPortOut                        PORTB
#define SYSTEM_LED_0_CFG_PORT_OUT_BIT           2
#define SYSTEM_LED_1_CFG_PORT_OUT_BIT           3