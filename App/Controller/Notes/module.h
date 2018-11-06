/*
 * Controller_Notes module
 * 
 * Notes Module
 * Provides play notes logic, keeps current note numbers in memory.
 * Controls note gate time and velocity.
 */

#define CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN        8
#define CONTROLLER_NOTES_CFG_GATE_TIME_INFINIT      0xff
#define CONTROLLER_NOTES_CFG_GATE_TIME_DEFAULT      30
#define CONTROLLER_NOTES_CFG_DEFAULT_VELOCITY       64
#define CONTROLLER_NOTES_CFG_NOTE_OFF               0xff

struct NOTE_BUFFER {
    BYTE number;
    BYTE gateTimer;
};

struct NOTES_MODULE {
    BYTE flags;
    struct NOTE_BUFFER buffer[CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN];
    BYTE velocity;
    BYTE gateTime;
};

/*
 * Module Initialization.
 */
#define Controller_Notes_Init() {\
    system.var = 0;\
    controller.notes.velocity = CONTROLLER_NOTES_CFG_DEFAULT_VELOCITY;\
    controller.notes.gateTime = CONTROLLER_NOTES_CFG_GATE_TIME_DEFAULT;\
    for (; system.var < CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN; system.var++) {\
        controller.notes.buffer[system.var].number = CONTROLLER_NOTES_CFG_NOTE_OFF;\
        controller.notes.buffer[system.var].gateTimer = 0;\
    }\
}

/*
 * Module Main Process.
 */
#define Controller_Notes_Process() {\
    Controller_Notes_GateTimerProcess();\
}

/*
 * Gate Timer Process. 
 */
#define Controller_Notes_GateTimerProcess() {\
    system.var = 0;\
    for (; system.var < CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN; system.var++) {\
        if (controller.notes.buffer[system.var].gateTimer != 0) {\
            controller.notes.buffer[system.var].gateTimer--;\
            if (controller.notes.buffer[system.var].gateTimer == 0) {\
                Controller_Notes_OffByBufferIndex(system.var);\
            }\
        }\
    }\
}

/*
 * Play (send MIDI msg note on) note by number with velocity and gate time.
 * Finds first available note slot in buffer and allocate it. 
 * If gate time is CONTROLLER_NOTES_CFG_GATE_TIME_INF note will play infinitive time,
 * until note off message arrives.
 */
#define Controller_Notes_On(noteNum, velo, gate) {\
    system.var = 0;\
    for (; system.var < CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN; system.var++) {\
        if (controller.notes.buffer[system.var].number == CONTROLLER_NOTES_CFG_NOTE_OFF) {\
            controller.notes.buffer[system.var].number = noteNum;\
            controller.notes.buffer[system.var].gateTimer = gate + 1;\
            MIDI_Out_SendNoteOn(noteNum, velo);\
            break;\
        } else {\
            if (system.var == (CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN - 1)) {\
                MIDI_Out_SendNoteOff(controller.notes.buffer[CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN - 1].number, 0);\
                controller.notes.buffer[CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN - 1].number = noteNum;\
                controller.notes.buffer[CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN - 1].gateTimer = gate + 1;\
                MIDI_Out_SendNoteOn(noteNum, velo);\
                break;\
            }\
        }\
    }\
}

/*
 * Stop play note (send MIDI msg note off) note by number.
 * Finds note by note number and free note slot in buffer by setting velocity and gate time to zero. 
 */
#define Controller_Notes_Off(noteNum) {\
    system.var = 0;\
    for (; system.var < CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN; system.var++) {\
        if (controller.notes.buffer[system.var].number == noteNum) {\
            controller.notes.buffer[system.var].number = CONTROLLER_NOTES_CFG_NOTE_OFF;\
            controller.notes.buffer[system.var].gateTimer = 0;\
            MIDI_Out_SendNoteOff(noteNum, 0);\
            break;\
        }\
    }\
}

/*
 * Stop play note (send MIDI msg note off) by note buffer index.
 * Finds note by buffer index and free note slot in buffer by setting 
 * note number CONTROLLER_NOTES_CFG_NOTE_OFF value and gate time to zero. 
 * works faster then by number.
 */
#define Controller_Notes_OffByBufferIndex(bufferIndex) {\
    if (controller.notes.buffer[bufferIndex].number != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        MIDI_Out_SendNoteOff(controller.notes.buffer[bufferIndex].number, 0);\
        controller.notes.buffer[bufferIndex].number = CONTROLLER_NOTES_CFG_NOTE_OFF;\
        controller.notes.buffer[bufferIndex].gateTimer = 0;\
    }\
}

