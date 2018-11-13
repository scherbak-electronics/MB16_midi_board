/*
 * GATE TIME
 * 
 * Knob 6 action in mode number 1.
 */
#define Controller_Mode_1_Knob_6_Action(knobVal) {\
    if (Controller_Mode_1_isAltRightFlag()) {\
        Controller_Mode_1_Knob_6_RightAltAction(knobVal);\
    } else {\
        controller.notes.gateTime = knobVal;\
        if (Controller_Sequencer_isRecFlag()) {\
            Controller_Sequencer_SetStepGateTime(\
                Controller_Sequencer_GetEditPatternNumber(), \
                Controller_Sequencer_GetEditStepNumber(),\
                controller.notes.gateTime \
            );\
        }\
    }\
}


/*
 * Pattern select
 * 
 * Knob 6 action in mode number 1.
 */
#define Controller_Mode_1_Knob_6_RightAltAction(knobVal) {\
    controller.sequencer.editPatternNumber = knobVal >> 5;\
    Controller_Sequencer_View_ShowCurrentPattern();\
}
