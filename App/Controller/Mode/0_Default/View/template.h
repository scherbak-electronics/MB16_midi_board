/*
 * Shows default mode view after mode selected.
 */
#define Controller_Mode_0_View_Show() {\
    Controller_View_renderGreenLeds(0b00000000);\
    clr_bit(controller.view.leds, SYSTEM_LED_0_CFG_PORT_OUT_BIT);\
    clr_bit(systemLedPortOut, SYSTEM_LED_0_CFG_PORT_OUT_BIT);\
}
