/*
 * App module
 * 
 * Connects all other nested sub modules together
 * Defines GPIO ports mapping, events and action calls routing
 */
#include "config.controller.C8145.h"
#include "System/module.h"
#include "MIDI/module.h"
#include "Controller/module.h"

/*
 * Application start up once, before main loop
 */
#define App_Init() {\
    cli();\
  	System_Init();\
  	MIDI_Init();\
    Controller_Init();\
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
    Controller_Process();\
    System_USART_TxProcess();\
}

/*
 * System software timer event
 */
#define App_System_Timer_1msProcessEvent() {\
    MIDI_In_TimeoutTimerProcess();\
}

#define App_System_Timer_5msProcessEvent() {\
    System_Key_ScanTimerProcess();\
}

#define App_System_Timer_10msProcessEvent() {\
    System_Led_TimersProcess();\
    Controller_Timer10msProcess();\
}

#define App_System_Timer_100msProcessEvent() {\
    Controller_Timer100msProcess();\
}

/*
 * Analog inputs events
 */
#define App_System_ADC_ValueChangeEvent(chn, val) {\
    Controller_Mode_ADCAction(chn, val);\
}

/*
 * Key scan events
 * Example module use Key actions
 */
#define App_System_Key_ScanEvent() {\
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 0, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 1, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 2, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 3, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 4, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPort2In, system.key.states, 5, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPort3In, system.key.states2, 6, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPort3In, system.key.states2, 7, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPort3In, system.key.states2, 8, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPort3In, system.key.states2, 9, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPort3In, system.key.states2, 10, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPort3In, system.key.states2, 11, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPort3In, system.key.states2, 12, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPort3In, system.key.states2, 13, Controller_Mode_KeyDownAction, Controller_Mode_KeyUpAction);\
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
}

#define App_MIDI_In_NoteOffEvent(noteNum) {\
}
