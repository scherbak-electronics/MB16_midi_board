/*
 * Controller_Sequencer_View module
 */
#define CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR_SHOW          0
#define CONTROLLER_SEQUENCER_VIEW_FLAG_CURSOR               1

#define CONTROLLER_SEQUENCER_VIEW_CFG_CURSOR_TIME           16
#define CONTROLLER_SEQUENCER_VIEW_CFG_VISIBLE_AREA_LEN      4

struct SEQUENCER_VIEW_MODULE {
    BYTE flags;
    BYTE firstVisibleStep;
    BYTE cursorPosition;
    BYTE prevCursorPosition;
    BYTE cursorTimer;
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
    controller.sequencer.view.prevCursorPosition = 0;\
    controller.sequencer.view.firstVisibleStep = 0;\
    controller.sequencer.view.cursorTimer = 0;\
}

#define Controller_Sequencer_View_Process() {\
    Controller_Sequencer_View_CursorTimerProcess();\
}

#define Controller_Sequencer_View_CursorTimerProcess() {\
    if (Controller_Sequencer_View_isCursorShowFlag()) {\
        if (controller.sequencer.view.cursorTimer != 0) {\
            if (Controller_Sequencer_View_isCursorFlag()) {\
                if (controller.sequencer.view.cursorTimer % 2 == 0) {\
                    Controller_View_SetLedsPortGreenBit(controller.sequencer.view.cursorPosition - controller.sequencer.view.firstVisibleStep);\
                } else {\
                    Controller_View_ClearLedsPortGreenBit(controller.sequencer.view.cursorPosition - controller.sequencer.view.firstVisibleStep);\
                }\
            }\
            controller.sequencer.view.cursorTimer--;\
            if (controller.sequencer.view.cursorTimer == 0) {\
                controller.sequencer.view.cursorTimer = CONTROLLER_SEQUENCER_VIEW_CFG_CURSOR_TIME;\
                Controller_Sequencer_View_invCursorFlag();\
                Controller_View_ClearLedsPortGreenBit(controller.sequencer.view.cursorPosition - controller.sequencer.view.firstVisibleStep);\
            }\
        }\
    }\
}

/*
 * Begins cursor blinking 
 * at specified pattern position.
 */
#define Controller_Sequencer_View_ShowCursor(pos) {\
    controller.sequencer.view.cursorPosition = pos;\
    controller.sequencer.view.cursorTimer = CONTROLLER_SEQUENCER_VIEW_CFG_CURSOR_TIME;\
    Controller_Sequencer_View_setCursorShowFlag();\
    Controller_Sequencer_View_setCursorFlag();\
    Controller_View_SetLedsPortGreenBit(controller.sequencer.view.cursorPosition - controller.sequencer.view.firstVisibleStep);\
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
    Controller_View_CleanGreenBuffer();\
    if (controller.sequencer.patterns[patt][pos].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        Controller_View_SetLedsBufferBit(1);\
    }\
    if (controller.sequencer.patterns[patt][pos + 1].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        Controller_View_SetLedsBufferBit(2);\
    }\
    if (controller.sequencer.patterns[patt][pos + 2].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        Controller_View_SetLedsBufferBit(3);\
    }\
    if (controller.sequencer.patterns[patt][pos + 3].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        Controller_View_SetLedsBufferBit(4);\
    }\
    Controller_View_ShowBuffer();\
}

#define Controller_Sequencer_View_ShowPatternContentFromStep(stepNum) {\
    Controller_Sequencer_View_ShowPatternContent(Controller_Sequencer_GetEditPatternNumber(), stepNum);\
}

/*
 * Moves cursor to new position (pos)
 * and moves visible area if needed. 
 */
#define Controller_Sequencer_View_MoveCursor(pos) {\
    if (pos != controller.sequencer.view.prevCursorPosition) {\
        controller.sequencer.view.prevCursorPosition = pos;\
        Controller_Sequencer_View_HideCursor();\
        if (pos < controller.sequencer.view.firstVisibleStep) {\
            Controller_Sequencer_View_MoveVisibleArea(pos);\
            Controller_Sequencer_View_ShowPatternContentFromStep(pos);\
        } else {\
            if (pos >= (controller.sequencer.view.firstVisibleStep + CONTROLLER_SEQUENCER_VIEW_CFG_VISIBLE_AREA_LEN)) {\
                Controller_Sequencer_View_MoveVisibleArea(pos - (CONTROLLER_SEQUENCER_VIEW_CFG_VISIBLE_AREA_LEN - 1));\
                Controller_Sequencer_View_ShowPatternContentFromStep(pos - (CONTROLLER_SEQUENCER_VIEW_CFG_VISIBLE_AREA_LEN - 1));\
            } else {\
                Controller_Sequencer_View_ShowPatternContentFromStep(controller.sequencer.view.firstVisibleStep);\
            }\
        }\
        Controller_Sequencer_View_ShowCursor(pos);\
    }\
}

/*
 * Moves pattern content visible area to new position (pos)
 */
#define Controller_Sequencer_View_MoveVisibleArea(pos) {\
    controller.sequencer.view.firstVisibleStep = pos;\
}
