/*
 * Controller C8145 App Configuration
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
#define SYSTEM_PORT_CFG_PORTB        0b00011111 // Resistor: 0 = none, 1 = pull-up

/*
 * Port C config
 *///                                  76543210
#define SYSTEM_PORT_CFG_DDRC         0b00000000 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTC        0b11111111 // Resistor: 0 = none, 1 = pull-up

/*
 * Port D config
 *///                                  765432--
#define SYSTEM_PORT_CFG_DDRD         0b11111000 // Direction: 0 = input, 1 = output
#define SYSTEM_PORT_CFG_PORTD        0b00000100 // Resistor: 0 = none, 1 = pull-up

/*
 * System Port Mappings
 */
#define systemKeyPortIn                     PINB
#define SYSTEM_KEY_0_CFG_PORT_IN_BIT        0
#define SYSTEM_KEY_0_CFG_STREG_BIT          0
#define SYSTEM_KEY_1_CFG_PORT_IN_BIT        1
#define SYSTEM_KEY_1_CFG_STREG_BIT          1
#define SYSTEM_KEY_2_CFG_PORT_IN_BIT        2
#define SYSTEM_KEY_2_CFG_STREG_BIT          2
#define SYSTEM_KEY_3_CFG_PORT_IN_BIT        3
#define SYSTEM_KEY_3_CFG_STREG_BIT          3
#define SYSTEM_KEY_4_CFG_PORT_IN_BIT        4
#define SYSTEM_KEY_4_CFG_STREG_BIT          4

#define systemKeyPort2In                    PIND
#define SYSTEM_KEY_5_CFG_PORT_IN_BIT        2
#define SYSTEM_KEY_5_CFG_STREG_BIT          5

#define systemKeyPort3In                    PINC
#define SYSTEM_KEY_6_CFG_PORT_IN_BIT        7
#define SYSTEM_KEY_6_CFG_STREG_BIT          7
#define SYSTEM_KEY_7_CFG_PORT_IN_BIT        6
#define SYSTEM_KEY_7_CFG_STREG_BIT          6
#define SYSTEM_KEY_8_CFG_PORT_IN_BIT        5
#define SYSTEM_KEY_8_CFG_STREG_BIT          5
#define SYSTEM_KEY_9_CFG_PORT_IN_BIT        4
#define SYSTEM_KEY_9_CFG_STREG_BIT          4
#define SYSTEM_KEY_10_CFG_PORT_IN_BIT       3
#define SYSTEM_KEY_10_CFG_STREG_BIT         3
#define SYSTEM_KEY_11_CFG_PORT_IN_BIT       2
#define SYSTEM_KEY_11_CFG_STREG_BIT         2
#define SYSTEM_KEY_12_CFG_PORT_IN_BIT       1
#define SYSTEM_KEY_12_CFG_STREG_BIT         1
#define SYSTEM_KEY_13_CFG_PORT_IN_BIT       0 
#define SYSTEM_KEY_13_CFG_STREG_BIT         0

#define systemLedPortOut                    PORTD
#define SYSTEM_LED_0_CFG_PORT_OUT_BIT       3
#define SYSTEM_LED_1_CFG_PORT_OUT_BIT       4
#define SYSTEM_LED_2_CFG_PORT_OUT_BIT       5
#define SYSTEM_LED_3_CFG_PORT_OUT_BIT       6
#define SYSTEM_LED_4_CFG_PORT_OUT_BIT       7
