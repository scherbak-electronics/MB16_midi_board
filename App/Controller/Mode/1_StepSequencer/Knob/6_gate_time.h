/*
 * GATE TIME
 * 
 * Knob 6 action in mode number 1.
 */
#define Controller_Mode_1_Knob_6_Action(knobVal) {\
    controller.notes.gateTime = knobVal;\
    if (Controller_Sequencer_isRecFlag()) {\
        Controller_Sequencer_SetPatternStepGateTime(\
            Controller_Sequencer_GetEditPatternNumber(), \
            controller.sequencer.editPatternStepNumber, \
            controller.notes.gateTime \
        );\
    }\
}
