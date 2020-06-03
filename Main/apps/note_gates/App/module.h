/*
 * Instrument Module
 */
#include "Control/module.h"
#include "Osc/module.h"
#include "Program/module.h"
#include "Voice/module.h"
#include "Gates/module.h"

#define INSTRUMENT_CFG_MAX_POLYPHONY            8

struct INSTRUMENT_MODULE {
    BYTE flags;
    struct VOICE_MODULE voice;
    struct OSC_MODULE osc;
    struct GATES_MODULE gates;
};

#define Instrument_Init() {\
    instrument.flags = 0b00000000;\
    Instrument_Voice_Init();\
    Instrument_Osc_Init();\
    Instrument_Program_Init();\
    Instrument_Gates_Init();\
}

#define Instrument_NoteOn(noteNum, velocity) {\
    /* Instrument_Voice_NoteOn(noteNum, velocity); */\
    Instrument_Gates_NoteOn(noteNum, velocity);\
}

#define Instrument_NoteOff(noteNum) {\
    /* Instrument_Voice_NoteOff(noteNum); */\
    Instrument_Gates_NoteOff(noteNum);\
}

/*
 * Key Events
 */
#define Instrument_KeyDownEvent(keyNum) {\
}

#define Instrument_KeyUpEvent(keyNum) {\
}
