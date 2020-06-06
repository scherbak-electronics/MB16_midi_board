/*
 * default App module
 * 
 * Default application example 
 * Defines GPIO ports mapping, events and action calls routing
 */
#include "config.h"
#include "Logic/module.h"
#include "Gates/module.h"

struct APP_MODULE {
    struct APP_LOGIC_MODULE logic;
    struct GATES_MODULE gates;
};

/*
 * Application start up once, before main loop
 */
#define App_Init() {\
    cli();\
  	System_Init();\
  	MIDI_Init();\
    App_Gates_Init();\
    App_Logic_Init();\
	sei();\
	ADC_startConversion();\
}

/*
 * Application Process in main loop
 */
#define App_Process() {\
    System_Timer_Process();\
    System_ADC_Process();\
    System_Key_ScanFlagObserverProcess();\
    System_USART_RxProcess();\
    MIDI_EventsProcess();\
    System_USART_TxProcess();\
}

/*
 * System software timer event
 */
#define App_System_Timer_1msProcessEvent() {\
    App_Gates_TimersProcess();\
}

#define App_System_Timer_5msProcessEvent() {\
    System_Key_ScanTimerProcess();\
}

#define App_System_Timer_10msProcessEvent() {\
    System_Led_TimersProcess();\
}

#define App_System_Timer_100msProcessEvent() {\
}

/*
 * Analog inputs events
 */
#define App_System_ADC_ValueChangeEvent(chn, val) {\
}

/*
 * Key scan events
 */
#define App_System_Key_ScanEvent() {\
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 0, App_Logic_KeyDownEvent, App_Logic_KeyUpEvent);\
}

/*
 * MIDI In message events 
 */
#define App_MIDI_In_ExtSyncEvent() {\
}

#define App_MIDI_In_PlayEvent() {\
}

#define App_MIDI_in_StopEvent() {\
}

#define App_MIDI_In_NoteOnEvent(noteNum, velocity) {\
    App_Logic_NoteOn(noteNum, velocity);\
}

#define App_MIDI_In_NoteOffEvent(noteNum) {\
}

#define App_MIDI_In_ControlChangeEvent(ctrlNum, ctrlValue) {\
}

#define App_MIDI_In_PitchBendEvent(lsb, msb) {\
}
