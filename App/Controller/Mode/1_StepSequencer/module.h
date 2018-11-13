/*
 * Controller_Mode_1 module
 * 
 * Mode 1 specific data and logic.
 * Step Sequencer Mode with grain note triggering
 * Provides logic of interaction between all other modules.
 */
#include "Key/module.h"
#include "Knob/module.h"
#include "View/template.h"

#define CONTROLLER_MODE_1_FLAG_PLAY                 0
#define CONTROLLER_MODE_1_FLAG_REC                  1
#define CONTROLLER_MODE_1_FLAG_SHIFT_LEFT           2
#define CONTROLLER_MODE_1_FLAG_ALT_LEFT             3
#define CONTROLLER_MODE_1_FLAG_SHIFT_RIGHT          4
#define CONTROLLER_MODE_1_FLAG_ALT_RIGHT            5
#define CONTROLLER_MODE_1_FLAG_FUNCTION             6

#define CONTROLLER_MODE_1_CFG_TRIG_DIR_OFF          0
#define CONTROLLER_MODE_1_CFG_TRIG_DIR_FWD          1
#define CONTROLLER_MODE_1_CFG_TRIG_DIR_BCK          2
#define CONTROLLER_MODE_1_CFG_TRIG_DIR_ALL          3
#define CONTROLLER_MODE_1_CFG_KEY_NOTES_COUNT       4
#define CONTROLLER_MODE_1_CFG_KEY_NOTE_1_NUM        10
#define CONTROLLER_MODE_1_CFG_KEY_NOTE_2_NUM        11
#define CONTROLLER_MODE_1_CFG_KEY_NOTE_3_NUM        12
#define CONTROLLER_MODE_1_CFG_KEY_NOTE_4_NUM        13

struct MODE_1_KEY_NOTE {
    BYTE number;
};

struct MODE_1_MODULE {
    BYTE flags;
    BYTE lastNoteNumber;
    struct MODE_1_KEY_NOTE keyNote[CONTROLLER_MODE_1_CFG_KEY_NOTES_COUNT];
    BYTE trigNoteStep;
    BYTE trigDirection;
};

#define Controller_Mode_1_setAltLeftFlag()            set_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_ALT_LEFT)
#define Controller_Mode_1_clrAltLeftFlag()            clr_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_ALT_LEFT)
#define Controller_Mode_1_isAltLeftFlag()             bit_is_set(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_ALT_LEFT)

#define Controller_Mode_1_setShiftLeftFlag()          set_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_SHIFT_LEFT)
#define Controller_Mode_1_clrShiftLeftFlag()          clr_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_SHIFT_LEFT)
#define Controller_Mode_1_isShiftLeftFlag()           bit_is_set(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_SHIFT_LEFT)

#define Controller_Mode_1_setShiftRightFlag()         set_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_SHIFT_RIGHT)
#define Controller_Mode_1_clrShiftRightFlag()         clr_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_SHIFT_RIGHT)
#define Controller_Mode_1_isShiftRightFlag()          bit_is_set(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_SHIFT_RIGHT)

#define Controller_Mode_1_setAltRightFlag()           set_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_ALT_RIGHT)
#define Controller_Mode_1_clrAltRightFlag()           clr_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_ALT_RIGHT)
#define Controller_Mode_1_isAltRightFlag()            bit_is_set(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_ALT_RIGHT)

#define Controller_Mode_1_setFunctionFlag()           set_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_FUNCTION)
#define Controller_Mode_1_clrFunctionFlag()           clr_bit(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_FUNCTION)
#define Controller_Mode_1_isFunctionFlag()            bit_is_set(controller.mode.mode1.flags, CONTROLLER_MODE_1_FLAG_FUNCTION)

#define Controller_Mode_1_GetTrigDirection()            controller.mode.mode1.trigDirection
#define Controller_Mode_1_SetTrigDirection(dir)         controller.mode.mode1.trigDirection = dir
#define Controller_Mode_1_NextTrigDirection()           controller.mode.mode1.trigDirection = (BYTE)((Controller_Mode_1_GetTrigDirection() + 1) & 0b00000011)

#define Controller_Mode_1_isKeyNoteDown(keyNum)         System_Key_isDown(systemKeyPort3In, keyNum)

/*
 * Module Initialization.
 */
#define Controller_Mode_1_Init() {\
    controller.mode.mode1.lastNoteNumber = 0;\
    controller.mode.mode1.flags = 0;\
    controller.mode.mode1.trigNoteStep = 1;\
    Controller_Mode_1_SetTrigDirection(CONTROLLER_MODE_1_CFG_TRIG_DIR_ALL);\
    system.var = 0;\
    for (; system.var < CONTROLLER_MODE_1_CFG_KEY_NOTES_COUNT; system.var++) {\
        controller.mode.mode1.keyNote[system.var].number = MIDI_Notes_GetNoteNumber(MIDI_NOTE_C + (system.var * 3), 3);\
    }\
}

/*
 * Module Main Process.
 */
#define Controller_Mode_1_Process() {\
}

/*
 * Mode specific internal initialisation. 
 * Call this method each time when selecting this mode.
 */
#define Controller_Mode_1_Select() {\
    Controller_Mode_1_View_Show();\
}

/*
 * Method used to clear resources after using.
 */
#define Controller_Mode_1_Unselect() {\
    Controller_Mode_1_View_Clean();\
}
