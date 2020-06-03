/*
 * Controller_Sequencer_Notes module
 * 
 * Keeps current note numbers (per pattern) in memory.
 * Controls currently active note gate time and velocity.
 */

#define CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_BUFFER_LEN          4
#define CONTROLLER_SEQUENCER_NOTES_CFG_GATE_TIME_INFINIT        0xff
#define CONTROLLER_SEQUENCER_NOTES_CFG_GATE_TIME_DEFAULT        30
#define CONTROLLER_SEQUENCER_NOTES_CFG_DEFAULT_VELOCITY         64
#define CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_OFF                 0xff

#define CONTROLLER_SEQUENCER_NOTES_FLAG_ON_OFF_ORDER            0

struct SEQUENCER_NOTES_MODULE {
    BYTE flags;
    struct NOTE_BUFFER buffer[CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_BUFFER_LEN];
    BYTE velocity;
    BYTE gateTime;
    BYTE numberTmp;
    BYTE baseNumberTmp;
};

#define Controller_Sequencer_Notes_setOnOffOrderFlag() set_bit(controller.sequencer.notes.flags, CONTROLLER_SEQUENCER_NOTES_FLAG_ON_OFF_ORDER)
#define Controller_Sequencer_Notes_clrOnOffOrderFlag() clr_bit(controller.sequencer.notes.flags, CONTROLLER_SEQUENCER_NOTES_FLAG_ON_OFF_ORDER)
#define Controller_Sequencer_Notes_isOnOffOrderFlag() bit_is_set(controller.sequencer.notes.flags, CONTROLLER_SEQUENCER_NOTES_FLAG_ON_OFF_ORDER)

/*
 * Module Initialization.
 */
#define Controller_Sequencer_Notes_Init() {\
    controller.sequencer.notes.flags = 0;\
    controller.sequencer.notes.baseNumberTmp = 0;\
    system.var = 0;\
    controller.sequencer.notes.velocity = CONTROLLER_SEQUENCER_NOTES_CFG_DEFAULT_VELOCITY;\
    controller.sequencer.notes.gateTime = CONTROLLER_SEQUENCER_NOTES_CFG_GATE_TIME_DEFAULT;\
    for (; system.var < CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_BUFFER_LEN; system.var++) {\
        controller.sequencer.notes.buffer[system.var].number = CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_OFF;\
        controller.sequencer.notes.buffer[system.var].gateTimer = 0;\
    }\
}

/*
 * Notes module main loop process.
 */
#define Controller_Sequencer_Notes_Process() {\
}

/*
 * System timer 10ms process alias.
 */
#define Controller_Sequencer_Notes_Timer10msProcess() {\
    Controller_Sequencer_Notes_GateTimerProcess();\
}

/*
 * Gate timer event handler. 
 */
#define Controller_Sequencer_Notes_GateTimerProcess() {\
    system.var = 0;\
    for (; system.var < CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_BUFFER_LEN; system.var++) {\
        if (controller.sequencer.notes.buffer[system.var].gateTimer != 0) {\
            controller.sequencer.notes.buffer[system.var].gateTimer--;\
            if (controller.sequencer.notes.buffer[system.var].gateTimer == 0) {\
                Controller_Sequencer_Notes_Off(system.var);\
            }\
        }\
    }\
}

/*
 * Stop play note (send MIDI msg note off) by note buffer index.
 * Finds note by buffer index and free note slot in buffer by setting 
 * note number CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_OFF value and gate time to zero. 
 * works faster then by number.
 */
#define Controller_Sequencer_Notes_Off(bufferIndex) {\
    if (controller.sequencer.notes.buffer[bufferIndex].number != CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_OFF) {\
        Controller_Gates_NoteOff(controller.sequencer.notes.buffer[bufferIndex].number);\
        MIDI_Out_SendNoteOff(controller.sequencer.notes.buffer[bufferIndex].number, 0);\
        controller.sequencer.notes.buffer[bufferIndex].number = CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_OFF;\
        controller.sequencer.notes.buffer[bufferIndex].gateTimer = 0;\
    }\
}

#define Controller_Sequencer_Notes_On(bufferIndex, noteNum, velo, gate) {\
    controller.sequencer.notes.baseNumberTmp = noteNum;\
    if (gate > 1) {\
        controller.sequencer.notes.buffer[bufferIndex].gateTimer = gate;\
    }\
    if (controller.sequencer.notes.buffer[bufferIndex].number == CONTROLLER_SEQUENCER_NOTES_CFG_NOTE_OFF) {\
        controller.sequencer.notes.buffer[bufferIndex].number = controller.sequencer.notes.baseNumberTmp;\
        Controller_Gates_NoteOn(controller.sequencer.notes.baseNumberTmp);\
        MIDI_Out_SendNoteOn(controller.sequencer.notes.baseNumberTmp, velo);\
    } else {\
        if (controller.sequencer.notes.buffer[bufferIndex].number != controller.sequencer.notes.baseNumberTmp) {\
            controller.sequencer.notes.numberTmp = controller.sequencer.notes.buffer[bufferIndex].number;\
            if (!Controller_Sequencer_Notes_isOnOffOrderFlag()) {\
                MIDI_Out_SendNoteOff(controller.sequencer.notes.buffer[bufferIndex].number, 0);\
            }\
            controller.sequencer.notes.buffer[bufferIndex].number = controller.sequencer.notes.baseNumberTmp;\
            Controller_Gates_NoteOn(controller.sequencer.notes.buffer[bufferIndex].number);\
            MIDI_Out_SendNoteOn(controller.sequencer.notes.baseNumberTmp, velo);\
            if (Controller_Sequencer_Notes_isOnOffOrderFlag()) {\
                MIDI_Out_SendNoteOff(controller.sequencer.notes.numberTmp, 0);\
            }\
        }\
    }\
}
