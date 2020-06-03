/*
 * note_gates App Module
 */
#include "config.h"
#include "Control/module.h"
#include "Osc/module.h"
#include "Program/module.h"
#include "Voice/module.h"
#include "Gates/module.h"

#define APP_CFG_MAX_POLYPHONY            8

struct APP_MODULE {
    BYTE flags;
    struct VOICE_MODULE voice;
    struct OSC_MODULE osc;
    struct GATES_MODULE gates;
};

#define App_Init() {\
    instrument.flags = 0b00000000;\
    App_Voice_Init();\
    App_Osc_Init();\
    App_Program_Init();\
    App_Gates_Init();\
}

#define App_NoteOn(noteNum, velocity) {\
    /* App_Voice_NoteOn(noteNum, velocity); */\
    App_Gates_NoteOn(noteNum, velocity);\
}

#define App_NoteOff(noteNum) {\
    /* App_Voice_NoteOff(noteNum); */\
    App_Gates_NoteOff(noteNum);\
}

/*
 * Key Events
 */
#define App_KeyDownEvent(keyNum) {\
}

#define App_KeyUpEvent(keyNum) {\
}
