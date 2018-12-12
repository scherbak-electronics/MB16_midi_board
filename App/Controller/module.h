/*
 * Controller module
 * 
 * Tagret application main module
 * Encapsulate all structurally nested child modules
 * 8 knob MIDI controller with 1-4 possible modes.
 * Modes functionality depends on controller modules implemented. 
 */
#include "Key/module.h"
#include "Knob/module.h"
#include "LFO/module.h"
#include "Sequencer/module.h"
#include "Notes/module.h"
#include "Program/module.h"
#include "Mode/module.h"
#include "View/module.h"
#include "Sync/module.h"

#define CONTROLLER_CFG_DEFAULT_VELOCITY     64 

struct CONTROLLER_MODULE {
    BYTE flags;
    struct SEQUENCER_MODULE sequencer;
    struct LFO_MODULE lfo;
    struct MODE_MODULE mode;
    struct KNOB_MODULE knob;
    struct CONTROLLER_KEY_MODULE key;
    struct NOTES_MODULE notes;
    struct PROGRAM_CHANGE_MODULE program;
    struct VIEW_MODULE view;
    struct SYNC_MODULE sync;
};

/*
 * Module Initialization.
 */
#define Controller_Init() {\
    Controller_Mode_Init();\
    Controller_Knob_Init();\
    Controller_Key_Init();\
    Controller_LFO_Init();\
    Controller_Sequencer_Init();\
    Controller_Program_Init();\
    Controller_Notes_Init();\
    Controller_Sync_Init();\
}

/*
 * Module Main Process.
 */
#define Controller_Process() {\
    Controller_Key_Process();\
    Controller_Mode_Process();\
    Controller_Sync_Process();\
    Controller_Sequencer_Process();\
}

/*
 * Process for low speed view transitions
 */
#define Controller_Timer100msProcess() {\
    Controller_View_Process();\
    Controller_Sequencer_View_Process();\
}

#define Controller_Timer10msProcess() {\
    Controller_Notes_Process();\
    Controller_Sync_ExtTrigTimeoutProcess();\
}

#define Controller_Timer1msProcess() {\
    Controller_Sync_Trig96TimerProcess();\
}
