/*
 * PROG CHANGE 8
 * Knob 1 action in mode number 1.
 */
#define Controller_Mode_1_Knob_1_Action(knobVal) {\
    Controller_Program_setHi8(knobVal);\
    if (!Controller_Sequencer_isPlayingFlag()) {\
        Controller_Program_Change();\
    }\
    if (Controller_Mode_1_isFunctionFlag()) {\
        Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
    }\
}
