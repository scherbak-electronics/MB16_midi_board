/*
 * Controller_Mode module
 * 
 * Knobs and keys action router
 * Provides logic of switching between different modes,
 * knobs and keys actions routing depending on selected mode.
 */
#include "0_Default/module.h"
#include "1_StepSequencer/module.h"

#define CONTROLLER_MODE_NUMBER_0   0
#define CONTROLLER_MODE_NUMBER_1   1

#define CONTROLLER_MODE_FLAG_ACTIONS_DISABLED       0

struct MODE_MODULE {
    BYTE flags;
    BYTE number;
    struct MODE_1_MODULE mode1;
    WORD keyActionAllowFlags;
    BYTE knobActionAllowFlags;
};

#define Controller_Mode_isActionsDisabledFlag()     bit_is_set(controller.mode.flags, CONTROLLER_MODE_FLAG_ACTIONS_DISABLED)
#define Controller_Mode_setActionsDisabledFlag()    set_bit(controller.mode.flags, CONTROLLER_MODE_FLAG_ACTIONS_DISABLED)
#define Controller_Mode_clrActionsDisabledFlag()    clr_bit(controller.mode.flags, CONTROLLER_MODE_FLAG_ACTIONS_DISABLED)


/*
 * Module Initialization.
 */
#define Controller_Mode_Init() {\
    controller.mode.number = 0;\
    controller.mode.flags = 0b00000000;\
    Controller_Mode_EnableAllActions();\
    Controller_Mode_0_Init();\
    Controller_Mode_1_Init();\
}

/*
 * Check is key action enabled.
 * keyNum is zero based.
 */
#define Controller_Mode_IsEnabledKeyAction(keyNum)  word_bit_is_set(controller.mode.keyActionAllowFlags, keyNum)

/*
 * Enables key action.
 * keyNum is zero based.
 */
#define Controller_Mode_EnableKeyAction(keyNum) {\
    set_bit(controller.mode.keyActionAllowFlags, keyNum);\
}

/*
 * Disable key action.
 * keyNum is zero based.
 */
#define Controller_Mode_DisableKeyAction(keyNum) {\
    clr_bit(controller.mode.keyActionAllowFlags, keyNum);\
}

/*
 * Check is knob action enabled.
 * knobNum is zero based.
 */
#define Controller_Mode_IsEnabledKnobAction(knobNum)  bit_is_set(controller.mode.knobActionAllowFlags, knobNum)

/*
 * Enables knob action.
 * knobNum is zero based.
 */
#define Controller_Mode_EnableKnobAction(knobNum) {\
    set_bit(controller.mode.knobActionAllowFlags, knobNum);\
}

/*
 * Disable knob action.
 * knobNum is zero based.
 */
#define Controller_Mode_DisableKnobAction(knobNum) {\
    clr_bit(controller.mode.knobActionAllowFlags, knobNum);\
}

/*
 * Disable all key actions.
 */
#define Controller_Mode_DisableAllKeyActions() {\
    controller.mode.keyActionAllowFlags = 0x0000;\
}

/*
 * Enable all key actions.
 */
#define Controller_Mode_EnableAllKeyActions() {\
    controller.mode.keyActionAllowFlags = 0xffff;\
}

/*
 * Disable all key actions.
 */
#define Controller_Mode_DisableAllActions() {\
    controller.mode.keyActionAllowFlags = 0x0000;\
    controller.mode.knobActionAllowFlags = 0x00;\
    Controller_Mode_setActionsDisabledFlag();\
}

/*
 * Enable key and knob actions.
 */
#define Controller_Mode_EnableAllActions() {\
    controller.mode.keyActionAllowFlags = 0xffff;\
    controller.mode.knobActionAllowFlags = 0xff;\
    Controller_Mode_clrActionsDisabledFlag();\
}

/*
 * Module Main Process.
 */
#define Controller_Mode_Process() {\
    Controller_Mode_0_Process();\
    Controller_Mode_1_Process();\
}

/*
 * Routes ADC value change actions to mode specific
 * knob actions which depends on currently selected mode.
 */
#define Controller_Mode_ADCAction(knobNum, knobVal) {\
    if (Controller_Mode_IsEnabledKnobAction(knobNum)) {\
        switch (controller.mode.number) {\
            case CONTROLLER_MODE_NUMBER_0:\
                Controller_Mode_KnobAction(0, knobNum, knobVal);\
                break;\
            case CONTROLLER_MODE_NUMBER_1:\
                Controller_Mode_KnobAction(1, knobNum, knobVal);\
                break;\
        }\
    }\
}

#define Controller_Mode_KnobAction(modeNum, knobNum, knobVal) {\
    switch (knobNum) {\
        case 0:\
            Controller_Mode_##modeNum##_Knob_0_Action(knobVal);\
            break;\
        case 1:\
            Controller_Mode_##modeNum##_Knob_1_Action(knobVal);\
            break;\
        case 2:\
            Controller_Mode_##modeNum##_Knob_2_Action(knobVal);\
            break;\
        case 3:\
            Controller_Mode_##modeNum##_Knob_3_Action(knobVal);\
            break;\
        case 4:\
            Controller_Mode_##modeNum##_Knob_4_Action(knobVal);\
            break;\
        case 5:\
            Controller_Mode_##modeNum##_Knob_5_Action(knobVal);\
            break;\
        case 6:\
            Controller_Mode_##modeNum##_Knob_6_Action(knobVal);\
            break;\
        case 7:\
            Controller_Mode_##modeNum##_Knob_7_Action(knobVal);\
            break;\
    }\
}

/*
 * Keys actions routing depends on selected mode.
 * Routes KeyDown action to mode key down action depending on selected mode.
 */
#define Controller_Mode_KeyDownAction(keyNum) {\
    if (Controller_Mode_IsEnabledKeyAction(keyNum)) {\
        switch (controller.mode.number) {\
            case CONTROLLER_MODE_NUMBER_0:\
                Controller_Mode_0_Key_##keyNum##_DownAction();\
                break;\
            case CONTROLLER_MODE_NUMBER_1:\
                Controller_Mode_1_Key_##keyNum##_DownAction();\
                break;\
        }\
    }\
}

#define Controller_Mode_KeyUpAction(keyNum) {\
    if (Controller_Mode_IsEnabledKeyAction(keyNum)) {\
        switch (controller.mode.number) {\
            case CONTROLLER_MODE_NUMBER_0:\
                Controller_Mode_0_Key_##keyNum##_UpAction();\
                break;\
            case CONTROLLER_MODE_NUMBER_1:\
                Controller_Mode_1_Key_##keyNum##_UpAction();\
                break;\
        }\
    }\
}

/*
 * Switching through the modes one by one
 */
#define Controller_Mode_SelectNext() {\
    controller.mode.number = (controller.mode.number + 1) & 0b00000001;\
    Controller_Mode_SelectByNumber(controller.mode.number);\
}

/*
 * Selects specific mode by its number
 */
#define Controller_Mode_SelectByNumber(modeNum) {\
    switch (modeNum) {\
        case CONTROLLER_MODE_NUMBER_0:\
        Controller_Mode_1_Unselect();\
        Controller_Mode_0_Select();\
        break;\
        case CONTROLLER_MODE_NUMBER_1:\
        Controller_Mode_0_Unselect();\
        Controller_Mode_1_Select();\
        break;\
    }\
}
