/*
 * status LEDs module
 */
#define SYSTEM_LED_CFG_BLINK_TIME           2
#define SYSTEM_LED_CFG_MAX_LEDS             2
#define SYSTEM_LED_FLAG_BLINK_DISABLED      0
#define SYSTEM_LED_FLAG_BLINK_INVERTED      1
#define SYSTEM_LED_CFG_TX_LED_NUM           0

struct SYSTEM_LED_MODULE {
    BYTE flags;
    BYTE blinkTimer[SYSTEM_LED_CFG_MAX_LEDS];
};

#define System_Led_On(ledNum)               set_bit(systemLedPortOut, SYSTEM_LED_##ledNum##_CFG_PORT_OUT_BIT)
#define System_Led_Off(ledNum)              clr_bit(systemLedPortOut, SYSTEM_LED_##ledNum##_CFG_PORT_OUT_BIT)

#define System_Led_Init() {\
    System_Led_Off(0);\
    system.led.blinkTimer[0] = 0;\
    system.led.blinkTimer[1] = 0;\
    system.led.flags = 0;\
}

/*
 * Proess for all Led Timers
 */
#define System_Led_TimersProcess() {\
    System_Led_BlinkTimerProcess(0);\
    System_Led_BlinkTimerProcess(1);\
}

/*
 * Led blink Timer process
 */
#define System_Led_BlinkTimerProcess(ledNum) {\
    if (system.led.blinkTimer[ledNum] != 0) {\
        system.led.blinkTimer[ledNum]--;\
        if (system.led.blinkTimer[ledNum] == 0) {\
            if (bit_is_set(system.led.flags, SYSTEM_LED_FLAG_BLINK_INVERTED)) {\
                System_Led_On(ledNum);\
            } else {\
                System_Led_Off(ledNum);\
            }\
        }\
    }\
}

/*
 * Blink Led to show activity
 */
#define System_Led_Blink(ledNum) {\
    if (!bit_is_set(system.led.flags, SYSTEM_LED_FLAG_BLINK_DISABLED)) {\
        if (bit_is_set(systemLedPortOut, ledNum)) {\
            System_Led_Off(ledNum);\
            set_bit(system.led.flags, SYSTEM_LED_FLAG_BLINK_INVERTED);\
        } else {\
            System_Led_On(ledNum);\
            clr_bit(system.led.flags, SYSTEM_LED_FLAG_BLINK_INVERTED);\
        }\
	    system.led.blinkTimer[ledNum] = SYSTEM_LED_CFG_BLINK_TIME;\
    }\
}
