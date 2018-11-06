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

struct MODE_MODULE {
    BYTE flags;
    BYTE number;
    struct MODE_1_MODULE mode1;
};



/*
 * Module Initialization.
 */
#define Controller_Mode_Init() {\
    controller.mode.number = 0;\
    controller.mode.flags = 0b00000000;\
    Controller_Mode_0_Init();\
    Controller_Mode_1_Init();\
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
    switch (controller.mode.number) {\
        case CONTROLLER_MODE_NUMBER_0:\
            Controller_Mode_KnobAction(0, knobNum, knobVal);\
            break;\
        case CONTROLLER_MODE_NUMBER_1:\
            Controller_Mode_KnobAction(1, knobNum, knobVal);\
            break;\
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
    switch (controller.mode.number) {\
        case CONTROLLER_MODE_NUMBER_0:\
            Controller_Mode_0_Key_##keyNum##_DownAction();\
            break;\
        case CONTROLLER_MODE_NUMBER_1:\
            Controller_Mode_1_Key_##keyNum##_DownAction();\
            break;\
    }\
}

#define Controller_Mode_KeyUpAction(keyNum) {\
    switch (controller.mode.number) {\
        case CONTROLLER_MODE_NUMBER_0:\
            Controller_Mode_0_Key_##keyNum##_UpAction();\
            break;\
        case CONTROLLER_MODE_NUMBER_1:\
            Controller_Mode_1_Key_##keyNum##_UpAction();\
            break;\
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
