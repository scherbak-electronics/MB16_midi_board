/*
 * GATE TIME
 * 
 * Knob 6 action in mode number 1.
 */
#define Controller_Mode_1_Knob_6_Action(knobVal) {\
    if (Controller_Mode_1_isFunctionFlag()) {\
        Controller_Mode_1_Knob_6_SetShuffleTimeAction(knobVal);\
    } else {\
        if (Controller_Mode_1_isAltRightFlag()) {\
            if (Controller_Mode_1_isShiftLeftFlag()) {\
                Controller_Mode_1_Knob_6_SelectScaleAction(knobVal);\
            } else {\
                Controller_Mode_1_Knob_6_SelectPatternAction(knobVal);\
            }\
        } else {\
            Controller_Mode_1_Knob_6_SetGateTimeAction(knobVal);\
        }\
    }\
}

/*
 * Set gate time.
 */
#define Controller_Mode_1_Knob_6_SetGateTimeAction(knobVal) {\
    if ((knobVal >> 2) < 3) {\
        controller.notes.gateTime = 3;\
    } else {\
        controller.notes.gateTime = knobVal >> 2;\
    }\
    if (Controller_Sequencer_isRecFlag()) {\
        Controller_Sequencer_SetStepGateTime(\
            Controller_Sequencer_GetEditPatternNumber(), \
            Controller_Sequencer_GetEditStepNumber(),\
            controller.notes.gateTime \
        );\
    }\
    Controller_View_Param_Show(controller.notes.gateTime);\
}

/*
 * Pattern select
 * 
 * Knob 6 action in mode number 1.
 */
#define Controller_Mode_1_Knob_6_SelectPatternAction(knobVal) {\
    controller.sequencer.editPatternNumber = knobVal >> 5;\
    Controller_Sequencer_View_ShowCurrentPattern();\
}

/*
 * Scale select action. 0-3
 */
#define Controller_Mode_1_Knob_6_SelectScaleAction(knobVal) {\
    controller.notes.scale.scaleNumber = knobVal >> 5;\
    Controller_Notes_Scale_LoadScaleByNumber(controller.notes.scale.scaleNumber);\
    Controller_View_Param_Show(controller.notes.scale.scaleNumber);\
}

/*
 * Set shuffle time.
 */
#define Controller_Mode_1_Knob_6_SetShuffleTimeAction(knobVal) {\
    controller.sequencer.shuffleTime = knobVal >> 5;\
    Controller_View_Param_Show(controller.sequencer.shuffleTime);\
}
