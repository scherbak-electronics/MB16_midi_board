/*
 * App_UI module
 * 
 * Default application example 
 * User Interface module for user interaction
 */

struct APP_UI_MODULE {
    BYTE flags;
};

#define App_UI_setLed(ledNum)   set_bit(appLedPortOut, APP_LED_##ledNum##_CFG_PORT_OUT_BIT)
#define App_UI_clrLed(ledNum)   clr_bit(appLedPortOut, APP_LED_##ledNum##_CFG_PORT_OUT_BIT)


#define App_UI_KeyDownEvent(keyNum) {\
    if (keyNum == 0) {\
        System_Led_Blink(0);\
    }\
    if (keyNum == 1) {\
        System_Led_Blink(1);\
    }\
    if (keyNum == 2) {\
        App_UI_setLed(0);\
    }\
}

#define App_UI_KeyUpEvent(keyNum) {\
    if (keyNum == 2) {\
        App_UI_clrLed(0);\
    }\
}
