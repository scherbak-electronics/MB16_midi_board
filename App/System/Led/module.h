/*
 * status LEDs module
 */
#define SYSTEM_LED_CFG_BLINK_TIME           4

struct SYSTEM_LED_MODULE {
    BYTE blinkTimer;
};

#define System_Led_On(ledNum)               set_bit(systemLedPortOut, SYSTEM_LED_##ledNum##_CFG_PORT_OUT_BIT)
#define System_Led_Off(ledNum)              clr_bit(systemLedPortOut, SYSTEM_LED_##ledNum##_CFG_PORT_OUT_BIT)

#define System_Led_Init() {\
    System_Led_Off(0);\
    system.led.blinkTimer = 0;\
}

/*
 * Proess for all Led Timers
 */
#define System_Led_TimersProcess() {\
    System_Led_BlinkTimerProcess(0);\
}

/*
 * Led blink Timer process
 */
#define System_Led_BlinkTimerProcess(ledNum) {\
    if (system.led.blinkTimer != 0) {\
        system.led.blinkTimer--;\
        if (system.led.blinkTimer == 0) {\
            System_Led_Off(ledNum);\
        }\
    }\
}

/*
 * Blink Led to show activity
 */
#define System_Led_Blink(ledNum) {\
	System_Led_On(ledNum);\
	system.led.blinkTimer = SYSTEM_LED_CFG_BLINK_TIME;\
}
