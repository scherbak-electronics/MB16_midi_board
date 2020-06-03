/*
 * Controller_View_Dialog module
 * 
 * Shows modal dialog by blinking all green leds.
 * Long period blinking means that dialog is opened and waiting for user confirmation.
 * When user confirm action, leds will blink faster.
 */
#define CONTROLLER_VIEW_DIALOG_CFG_BLINK_TIME_LONG          40
#define CONTROLLER_VIEW_DIALOG_CFG_BLINK_TIME_SHORT         20

#define CONTROLLER_VIEW_DIALOG_FLAG_BLINKING                0

struct CONTROLLER_VIEW_DIALOG_MODULE {
    BYTE flags;
    BYTE blinkTimer;
    BYTE blinkTime;
};

#define Controller_View_Dialog_setBlinkingFlag()            set_bit(controller.view.dialog.flags, CONTROLLER_VIEW_DIALOG_FLAG_BLINKING)
#define Controller_View_Dialog_clrBlinkingFlag()            clr_bit(controller.view.dialog.flags, CONTROLLER_VIEW_DIALOG_FLAG_BLINKING)
#define Controller_View_Dialog_isBlinkingFlag()             bit_is_set(controller.view.dialog.flags, CONTROLLER_VIEW_DIALOG_FLAG_BLINKING)

/*
 * Module init
 */
#define Controller_View_Dialog_Init() {\
    controller.view.dialog.flags = 0;\
    controller.view.dialog.blinkTimer = 0;\
}

/*
 * System timer 10ms process alias.
 */
#define Controller_View_Dialog_Timer10msProcess() {\
    Controller_View_Dialog_BlinkTimerProcess();\
}

/*
 * Module main loop process..
 */
#define Controller_View_Dialog_BlinkTimerProcess() {\
    if (Controller_View_Dialog_isBlinkingFlag()) {\
        if (controller.view.dialog.blinkTimer != 0) {\
            controller.view.dialog.blinkTimer--;\
            if (controller.view.dialog.blinkTimer == 0) {\
                controller.view.dialog.blinkTimer = controller.view.dialog.blinkTime;\
                Controller_View_Dialog_InvGreenLeds();\
            }\
        }\
    }\
}

#define Controller_View_Dialog_StartBlinking(time) {\
    controller.view.dialog.blinkTime = time;\
    controller.view.dialog.blinkTimer = time;\
    Controller_View_Dialog_setBlinkingFlag();\
    Controller_View_Dialog_InvGreenLeds();\
}

#define Controller_View_Dialog_StopBlinking() {\
    Controller_View_Dialog_clrBlinkingFlag();\
}

/*
 * Displays confirmation dialog.
 * All 4-leds indicator will blink slowly.
 */
#define Controller_View_Dialog_Show() {\
    Controller_Mode_1_View_Clean();\
    Controller_View_Dialog_StartBlinking(CONTROLLER_VIEW_DIALOG_CFG_BLINK_TIME_LONG);\
}

/*
 * Cancel and clean 4 leds display.
 */
#define Controller_View_Dialog_Hide() {\
    Controller_View_Dialog_clrBlinkingFlag();\
    Controller_View_CleanGreenPort();\
}

/*
 * Starts blinking faster, which means confirmation in progress.
 */
#define Controller_View_Dialog_ShowConfirmation() {\
    controller.view.dialog.blinkTime = CONTROLLER_VIEW_DIALOG_CFG_BLINK_TIME_SHORT;\
}

/*
 * Check if dialog active and 4 leds are blinking.
 */
#define Controller_View_Dialog_isVisible()  Controller_View_Dialog_isBlinkingFlag()

/* 
 * Invert all 4 green leds
 */
#define Controller_View_Dialog_InvGreenLeds() {\
    Controller_View_InvGreenLedsPortBit(0);\
    Controller_View_InvGreenLedsPortBit(1);\
    Controller_View_InvGreenLedsPortBit(2);\
    Controller_View_InvGreenLedsPortBit(3);\
}


