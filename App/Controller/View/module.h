/*
 * Controller_View module
 * 
 * 4 Led display view module provides viewing of controller modules parameters.
 * Display parameters values, position numbers, modes, etc...
 * 
 *          Buffer:              Port:
 *                    _Red              _Red
 *                   |                 |
 *          0b...GGGGR           0bGGGGR...
 *            xxx43210             76543xxx
 *               ||||_Green        ||||____Green
 *               |||__Green        |||_____Green
 *               ||___Green        ||______Green
 *               |____Green        |_______Green
 */
#define CONTROLLER_VIEW_FLAG_START_BLINKING             0

#define CONTROLLER_VIEW_CFG_DISPLAYS_NUMBER             1
#define CONTROLLER_VIEW_CFG_SHOW_PARAM_TIME             20
#define CONTROLLER_VIEW_CFG_BLINK_TIME                  2
#define CONTROLLER_VIEW_CFG_GREEN_LEDS_BITNUM_OFFSET    4

#define CONTROLLER_VIEW_BITMASK_LEDS                    0b11111000
#define CONTROLLER_VIEW_BITMASK_GREEN_LEDS              0b11110000
#define CONTROLLER_VIEW_BITMASK_GREEN_LEDS_NOT          0b00001111
#define CONTROLLER_VIEW_BITMASK_RED_LED                 0b00001000

struct VIEW_MODULE {
    BYTE flags;
    BYTE leds;
    BYTE ledsBuffer;
    BYTE blinkBuffer;
    BYTE restoreTimer;
    BYTE blinkTimer;
};

#define Controller_View_setBlinkingFlag()           set_bit(controller.view.flags, CONTROLLER_VIEW_FLAG_START_BLINKING)
#define Controller_View_clrBlinkingFlag()           clr_bit(controller.view.flags, CONTROLLER_VIEW_FLAG_START_BLINKING)
#define Controller_View_isBlinkingFlag()            bit_is_set(controller.view.flags, CONTROLLER_VIEW_FLAG_START_BLINKING)

#define Controller_View_IsParamVisible()            (controller.view.restoreTimer != 0)

/*
 * Module Initialization.
 */
#define Controller_View_Init() {\
    controller.view.flags = 0;\
    controller.view.restoreTimer = 0;\
    controller.view.leds = 0b00000000;\
    controller.view.ledsBuffer = 0b00000000;\
}

/*
 * Module Main Process.
 */
#define Controller_View_Process() {\
    Controller_View_RestoreTimerProcess();\
}

/*
 * View led buffer will be restored to default view of 
 * currently selected mode automatically ...
 */
#define Controller_View_RestoreTimerProcess() {\
    if (controller.view.restoreTimer != 0) {\
        controller.view.restoreTimer--;\
        if (controller.view.restoreTimer == 0) {\
            Controller_View_RestoreCurrent();\
        }\
    }\
}

/*
 * Blink buffer period timer. 
 * process can start and stop.
 */
#define Controller_View_BlinkTimerProcess() {\
    if (Controller_View_isBlinkingFlag() && controller.view.blinkTimer != 0) {\
        controller.view.blinkTimer--;\
        if (controller.view.blinkTimer == 0) {\
            Controller_View_RestoreCurrent();\
        }\
    }\
}

#define Controller_View_BlinkGreenLeds(ledBuff) {\
}

/*
 * Restore current leds buffer.
 * Writes leds buffer to the leds port.
 */
#define Controller_View_RestoreCurrent() Controller_View_renderGreenLeds(controller.view.ledsBuffer)

/*
 * Shows parameter value as scrollable 4 leds lenght bar
 * and restores view from leds buffer.
 */
#define Controller_View_ShowParam(val) {\
    Controller_View_renderGreenLeds((0b00001111 << (val & 0b00000111)));\
    controller.view.restoreTimer = CONTROLLER_VIEW_CFG_SHOW_PARAM_TIME;\
}

/*
 * Prepare leds buffer before output to port.
 * buff is Right aligned.
 */
#define Controller_View_SetBuffer(buff) controller.view.ledsBuffer = buff

/*
 * Prepare only green leds buffer before output to port.
 * buff is Right aligned.
 */
#define Controller_View_SetGreenBuffer(buff) controller.view.ledsBuffer = (controller.view.ledsBuffer & 0b00000001) | (buff << 1)

/*
 * Show byte value as bitmap to green leds only.
 * buff is Right aligned.
 */
#define Controller_View_ShowGreenBuffer(buff) {\
    Controller_View_SetGreenBuffer(buff);\
    Controller_View_ShowBuffer();\
}

/*
 * Clean only green leds buffer.
 */
#define Controller_View_CleanGreenBuffer() controller.view.ledsBuffer = controller.view.ledsBuffer & 0b00000001

/*
 * Clean only green leds buffer.
 */
#define Controller_View_CleanGreenPort() systemLedPortOut &= CONTROLLER_VIEW_BITMASK_GREEN_LEDS_NOT


/*
 * Set leds buffer bit.
 * bitNum should be Right aligned.
 * 
 *     0b...GGGGR
 */
#define Controller_View_SetLedsBufferBit(bitNum) set_bit(controller.view.ledsBuffer, bitNum)

/*
 * Clear leds buffer bit.
 * bitNum should be Right aligned.
 * 
 *     0b...GGGGR
 */
#define Controller_View_ClearLedsBufferBit(bitNum) clr_bit(controller.view.ledsBuffer, bitNum)

/*
 * Set green leds port bit.
 * ledNum should be Right aligned. Will be converted to 
 * actual port bit number by adding offset.
 *
 *     0b....GGGG -> 0bGGGG....
 */
#define Controller_View_SetGreenLedsPortBit(ledNum) set_bit(systemLedPortOut, (ledNum + CONTROLLER_VIEW_CFG_GREEN_LEDS_BITNUM_OFFSET))

/*
 * Clear green leds port bit.
 * ledNum should be Right aligned. Will be converted to 
 * actual port bit number by adding offset.
 * 
 *     0b....GGGG -> 0bGGGG....
 */
#define Controller_View_ClearGreenLedsPortBit(ledNum) clr_bit(systemLedPortOut, (ledNum + CONTROLLER_VIEW_CFG_GREEN_LEDS_BITNUM_OFFSET))

/*
 * Invert green leds port bit.
 * bitNum should be Right aligned.
 * 
 *     0b....GGGG -> 0bGGGG....
 */
#define Controller_View_InvGreenLedsPortBit(ledNum) inv_bit(systemLedPortOut, (ledNum + CONTROLLER_VIEW_CFG_GREEN_LEDS_BITNUM_OFFSET))

/*
 * Get is green leds port bit set, returns true if set.
 * bitNum should be Right aligned.
 * 
 *     0b....GGGG -> 0bGGGG....
 */
#define Controller_View_IsSetGreenLedsPortBit(bitNum) bit_is_set(systemLedPortOut, bitNum + 4)

/*
 * Write out leds buffer to the port.
 */
#define Controller_View_ShowBuffer() {\
    systemLedPortOut = (systemLedPortOut & (~CONTROLLER_VIEW_BITMASK_LEDS)) | (controller.view.ledsBuffer << 3);\
}

/*
 * Write only green leds buffer to leds out port.
 * buff is Left aligned.
 */
#define Controller_View_renderGreenLeds(buff) {\
    systemLedPortOut = (systemLedPortOut & (~CONTROLLER_VIEW_BITMASK_GREEN_LEDS)) | (buff & CONTROLLER_VIEW_BITMASK_GREEN_LEDS);\
}

/*
 * Write only red led buffer to led out port.
 * buff is Left aligned.
 */
#define Controller_View_renderRedLed(buff) {\
    systemLedPortOut = (systemLedPortOut & (~CONTROLLER_VIEW_BITMASK_RED_LED)) | (buff & CONTROLLER_VIEW_BITMASK_RED_LED);\
}
