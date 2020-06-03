/*
 * SEQUENCER STRUCTURE KNOB
 * 
 * Sequencer Structure select.
 * MIDI Channel select 1 - 16
 * Octave switch.
 */
#define Controller_Mode_1_Knob_7_Action(knobVal) {\
    if (Controller_Mode_1_isFunctionFlag()) {\
        Controller_Mode_1_Knob_7_MIDIChannelSwitchAction(knobVal);\
    } else {\
        if (Controller_Mode_1_isShiftRightFlag()) {\
            Controller_Mode_1_Knob_7_OctaveSwitchAction(knobVal);\
        } else {\
            Controller_Mode_1_Knob_7_SequencerStructureSelectAction(knobVal);\
        }\
    }\
}

/*
 * Sequencer Structure select action
 */
#define Controller_Mode_1_Knob_7_SequencerStructureSelectAction(knobVal) {\
    controller.sequencer.structureNumber = (knobVal >> 4);\
    if (controller.sequencer.structureNumber != controller.sequencer.structureNumberPrev) {\
        controller.sequencer.structureNumberPrev = controller.sequencer.structureNumber;\
        Controller_View_Param_Show(controller.sequencer.structureNumber);\
    }\
}

/*
 * Octave switch action
 */
#define Controller_Mode_1_Knob_7_OctaveSwitchAction(knobVal) {\
    Controller_Notes_SetOctaveNumber((knobVal >> 4));\
    Controller_View_Param_Show(controller.notes.octaveNumber);\
}

/*
 * MIDI channel switch action
 */
#define Controller_Mode_1_Knob_7_MIDIChannelSwitchAction(knobVal) {\
    MIDI_Out_SetChannel(knobVal >> 3);\
    Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
    Controller_View_Param_Show(MIDI_Out_GetChannel());\
}
