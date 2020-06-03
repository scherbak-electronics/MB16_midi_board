/*
 * Controller_Notes module
 * 
 * Notes Module
 * Provides play notes logic, keeps current note numbers in memory.
 * Controls note gate time and velocity.
 */
#include "Scale/module.h"

#define CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN        4
#define CONTROLLER_NOTES_CFG_GATE_TIME_INFINIT      0xff
#define CONTROLLER_NOTES_CFG_GATE_TIME_DEFAULT      5
#define CONTROLLER_NOTES_CFG_DEFAULT_VELOCITY       100
#define CONTROLLER_NOTES_CFG_NOTE_OFF               0xff
#define CONTROLLER_NOTES_CFG_GATE_TIMEOUT_TIME      10

struct NOTE_BUFFER {
    BYTE number;
    BYTE gateTimer;
};

struct NOTES_MODULE {
    BYTE flags;
    struct NOTE_BUFFER buffer[CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN];
    BYTE velocity;
    BYTE gateTime;
    struct NOTES_SCALE_MODULE scale;
    int octaveNumber;
    BYTE noteNumberTmp;
    BYTE singleNoteNumber;
    BYTE singleNoteGateTimer;
};

/*
 * Module Initialization.
 */
#define Controller_Notes_Init() {\
    system.var = 0;\
    controller.notes.flags = 0;\
    controller.notes.octaveNumber = 4;\
    controller.notes.noteNumberTmp = 0;\
    controller.notes.singleNoteNumber = 0;\
    controller.notes.singleNoteGateTimer = 0;\
    controller.notes.velocity = CONTROLLER_NOTES_CFG_DEFAULT_VELOCITY;\
    controller.notes.gateTime = CONTROLLER_NOTES_CFG_GATE_TIME_DEFAULT;\
    for (; system.var < CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN; system.var++) {\
        controller.notes.buffer[system.var].number = CONTROLLER_NOTES_CFG_NOTE_OFF;\
        controller.notes.buffer[system.var].gateTimer = 1;\
    }\
    Controller_Notes_Scale_Init();\
}

/*
 * Notes module main loop process.
 */
#define Controller_Notes_Process() {\
}

/*
 * System timer 10ms process alias.
 */
#define Controller_Notes_Timer10msProcess() {\
    Controller_Notes_GateTimerProcess();\
    Controller_Notes_SingleNoteGateTimerProcess();\
}

/*
 * Gate timer event handler. 
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
 * Gate timeout timer process
 */
#define Controller_Notes_SingleNoteGateTimerProcess() {\
    if (controller.notes.singleNoteGateTimer != 0) {\
        controller.notes.singleNoteGateTimer--;\
        if (controller.notes.singleNoteGateTimer == 0) {\
            Controller_Gates_NoteOff(controller.notes.singleNoteNumber);\
            MIDI_Out_SendNoteOff(controller.notes.singleNoteNumber, 0);\
            controller.notes.singleNoteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF;\
        }\
    }\
}

/*
 * Play (send MIDI msg note on) one single note by number with velocity and gate time.
 */
#define Controller_Notes_OnSingle(noteNum, velo, gate) {\
    if (controller.notes.singleNoteGateTimer == 0) {\
        if (controller.notes.singleNoteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
            MIDI_Out_SendNoteOff(controller.notes.singleNoteNumber, 0);\
        }\
        Controller_Gates_NoteOn(noteNum);\
        MIDI_Out_SendNoteOn(noteNum, velo);\
        controller.notes.singleNoteNumber = noteNum;\
        Controller_Notes_AssignToKeysByNumber(noteNum);\
    }\
    controller.notes.singleNoteGateTimer = gate;\
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
            controller.notes.buffer[system.var].gateTimer = gate;\
            Controller_Gates_NoteOn(noteNum);\
            MIDI_Out_SendNoteOn(noteNum, velo);\
            break;\
        } else {\
            if (system.var == (CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN - 1)) {\
                MIDI_Out_SendNoteOff(controller.notes.buffer[CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN - 1].number, 0);\
                controller.notes.buffer[CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN - 1].number = noteNum;\
                controller.notes.buffer[CONTROLLER_NOTES_CFG_NOTE_BUFFER_LEN - 1].gateTimer = gate;\
                Controller_Gates_NoteOn(noteNum);\
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
            Controller_Gates_NoteOff(noteNum);\
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
        Controller_Gates_NoteOff(controller.notes.buffer[bufferIndex].number);\
        MIDI_Out_SendNoteOff(controller.notes.buffer[bufferIndex].number, 0);\
        controller.notes.buffer[bufferIndex].number = CONTROLLER_NOTES_CFG_NOTE_OFF;\
        controller.notes.buffer[bufferIndex].gateTimer = 0;\
    }\
}

#define Controller_Notes_OnMono(bufferIndex, noteNum, velo, gate) {\
    if (controller.notes.buffer[bufferIndex].number == CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        controller.notes.buffer[bufferIndex].number = noteNum;\
        controller.notes.buffer[bufferIndex].gateTimer = gate + 1;\
        Controller_Gates_NoteOn(noteNum);\
        MIDI_Out_SendNoteOn(noteNum, velo);\
    } else {\
        MIDI_Out_SendNoteOff(controller.notes.buffer[bufferIndex].number, 0);\
        controller.notes.buffer[bufferIndex].number = noteNum;\
        controller.notes.buffer[bufferIndex].gateTimer = gate + 1;\
        Controller_Gates_NoteOn(noteNum);\
        MIDI_Out_SendNoteOn(noteNum, velo);\
    }\
}

/*
 * Increase octave number
 */
#define Controller_Notes_OctaveUp() {\
    if (controller.notes.octaveNumber < 9) {\
        controller.notes.octaveNumber++;\
    }\
}

/*
 * Decrease octave number
 */
#define Controller_Notes_OctaveDown() {\
    if (controller.notes.octaveNumber != 0) {\
        controller.notes.octaveNumber--;\
    }\
}

/*
 * Calculates note C number for current octave.
 */
#define Controller_Notes_GetOctaveNoteNumber()  ((controller.notes.octaveNumber - 4) * 12)

/*
 * Set octave number 0-9.
 */
#define Controller_Notes_SetOctaveNumber(octNum) {\
    if (octNum == 0) {\
        controller.notes.octaveNumber = 4;\
    } else {\
        controller.notes.octaveNumber = octNum;\
    }\
}

/*
 * Note assignment by number action.
 * TODO: need to improve integrity.
 */
#define Controller_Notes_AssignToKeysByNumber(noteNum) {\
    controller.mode.mode1.keyNote[(controller.mode.mode1.keyNoteCounter & 0b00000011)].number = noteNum;\
    controller.mode.mode1.keyNoteCounter++;\
}

