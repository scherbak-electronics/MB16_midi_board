/*
 * Mode 0 knobs 0 - 7 value change actions.
 */
#define Controller_Mode_0_Knob_0_Action(knobVal) {\
    MIDI_Out_SendControlChange(Controller_Knob_GetCCNumber(0), knobVal);\
}

#define Controller_Mode_0_Knob_1_Action(knobVal) {\
    MIDI_Out_SendControlChange(Controller_Knob_GetCCNumber(1), knobVal);\
}

#define Controller_Mode_0_Knob_2_Action(knobVal) {\
    MIDI_Out_SendControlChange(Controller_Knob_GetCCNumber(2), knobVal);\
}

#define Controller_Mode_0_Knob_3_Action(knobVal) {\
    MIDI_Out_SendControlChange(Controller_Knob_GetCCNumber(3), knobVal);\
}

#define Controller_Mode_0_Knob_4_Action(knobVal) {\
    MIDI_Out_SendControlChange(Controller_Knob_GetCCNumber(4), knobVal);\
}

#define Controller_Mode_0_Knob_5_Action(knobVal) {\
    MIDI_Out_SendControlChange(Controller_Knob_GetCCNumber(5), knobVal);\
}

#define Controller_Mode_0_Knob_6_Action(knobVal) {\
    MIDI_Out_SendControlChange(Controller_Knob_GetCCNumber(6), knobVal);\
}

#define Controller_Mode_0_Knob_7_Action(knobVal) {\
    MIDI_Out_SendControlChange(Controller_Knob_GetCCNumber(7), knobVal);\
}

