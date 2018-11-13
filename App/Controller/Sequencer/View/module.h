/*
 * Controller_Sequencer_View module
 */
#define CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR_SHOW          0
#define CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR               1

#define CONTROLLER_SEQUENCER_VIEW_CFG_CURSOR_TIME           2
#define CONTROLLER_SEQUENCER_VIEW_CFG_VISIBLE_AREA_LEN      4

struct SEQUENCER_VIEW_MODULE {
    BYTE flags;
    BYTE firstVisibleStep;
    BYTE cursorPosition;
    BYTE cursorTimer;
    BYTE cursorPositionRelative;
};

#define Controller_Sequencer_View_setCursorShowFlag()                           set_bit(controller.sequencer.view.flags, CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR_SHOW)
#define Controller_Sequencer_View_clrCursorShowFlag()                           clr_bit(controller.sequencer.view.flags, CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR_SHOW)
#define Controller_Sequencer_View_isCursorShowFlag()                            bit_is_set(controller.sequencer.view.flags, CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR_SHOW)

#define Controller_Sequencer_View_setCursorFlag()                           set_bit(controller.sequencer.view.flags, CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR)
#define Controller_Sequencer_View_clrCursorFlag()                           clr_bit(controller.sequencer.view.flags, CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR)
#define Controller_Sequencer_View_isCursorFlag()                            bit_is_set(controller.sequencer.view.flags, CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR)
#define Controller_Sequencer_View_invCursorFlag()                            inv_bit(controller.sequencer.view.flags, CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR)

#define Controller_Sequencer_View_Init() {\
    controller.sequencer.view.flags = 0;\
    controller.sequencer.view.cursorPosition = 0;\
    controller.sequencer.view.cursorPositionRelative = 0;\
    controller.sequencer.view.firstVisibleStep = 0;\
    controller.sequencer.view.cursorTimer = 0;\
}

#define Controller_Sequencer_View_Process() {\
    Controller_Sequencer_View_CursorTimerProcess();\
}

#define Controller_Sequencer_View_CursorTimerProcess() {\
    if (Controller_Sequencer_View_isCursorShowFlag()) {\
        if (controller.sequencer.view.cursorTimer != 0) {\
            controller.sequencer.view.cursorTimer--;\
            if (controller.sequencer.view.cursorTimer == 0) {\
                controller.sequencer.view.cursorTimer = CONTROLLER_SEQUENCER_VIEW_CFG_CURSOR_TIME;\
                Controller_View_InvGreenLedsPortBit(controller.sequencer.view.cursorPositionRelative);\
            }\
        }\
    }\
}

/*
 * Show current state of selected pattern and positions under  
 * cursor. Initialise internal view variables, start cursor blinking at 
 * current cursor position. Re-draw entire led view.
 */
#define Controller_Sequencer_View_Show() {\
    Controller_Sequencer_View_SetPositions();\
    Controller_Sequencer_View_ShowPatternContent(\
        Controller_Sequencer_GetEditPatternNumber(),\
        controller.sequencer.view.firstVisibleStep\
    );\
    Controller_Sequencer_View_ShowCursor();\
}

/*
 * Show currently edited active pattern
 */
#define Controller_Sequencer_View_ShowCurrentPattern() {\
    Controller_Sequencer_View_HideCursor();\
    Controller_View_CleanGreenPort();\
    Controller_View_SetGreenLedsPortBit(controller.sequencer.editPatternNumber);\
}


/*
 * Set all internal view relative position variables based on current 
 * pattern step absolute position. Positions should set before
 * view re-draw. 
 */
#define Controller_Sequencer_View_SetPositions() {\
    if (Controller_Sequencer_GetEditStepNumber() < controller.sequencer.view.firstVisibleStep) {\
        controller.sequencer.view.firstVisibleStep = Controller_Sequencer_GetEditStepNumber();\
    } else {\
        if (Controller_Sequencer_GetEditStepNumber() >= (controller.sequencer.view.firstVisibleStep + CONTROLLER_SEQUENCER_VIEW_CFG_VISIBLE_AREA_LEN)) {\
            controller.sequencer.view.firstVisibleStep = Controller_Sequencer_GetEditStepNumber() - (CONTROLLER_SEQUENCER_VIEW_CFG_VISIBLE_AREA_LEN - 1);\
        }\
    }\
    controller.sequencer.view.cursorPositionRelative = Controller_Sequencer_GetEditStepNumber() - controller.sequencer.view.firstVisibleStep;\
}

/*
 * Begins cursor blinking 
 * at specified pattern position.
 */
#define Controller_Sequencer_View_ShowCursor() {\
    controller.sequencer.view.cursorTimer = CONTROLLER_SEQUENCER_VIEW_CFG_CURSOR_TIME;\
    Controller_Sequencer_View_setCursorShowFlag();\
    Controller_View_SetGreenLedsPortBit(controller.sequencer.view.cursorPositionRelative);\
}

/*
 * Stop cursor blinking and restore pattern content view.
 */
#define Controller_Sequencer_View_HideCursor() {\
    controller.sequencer.view.cursorTimer = 0;\
    Controller_Sequencer_View_clrCursorShowFlag();\
}

/*
 * Shows pattern (patt, ..) steps content 
 * begining from step (.., pos)
 */
#define Controller_Sequencer_View_ShowPatternContent(patt, pos) {\
    Controller_View_CleanGreenPort();\
    if (controller.sequencer.patterns[patt][pos].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        Controller_View_SetGreenLedsPortBit(0);\
    }\
    if (controller.sequencer.patterns[patt][pos + 1].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        Controller_View_SetGreenLedsPortBit(1);\
    }\
    if (controller.sequencer.patterns[patt][pos + 2].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        Controller_View_SetGreenLedsPortBit(2);\
    }\
    if (controller.sequencer.patterns[patt][pos + 3].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        Controller_View_SetGreenLedsPortBit(3);\
    }\
}
