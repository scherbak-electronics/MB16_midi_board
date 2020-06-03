/*
 * instrument_HDD_heads App module
 * 
 * Connects all other nested sub modules together
 * Defines GPIO ports mapping, events and action calls routing
 */
#include "config.h"
#include "Instrument/module.h"

/*
 * Application start up once, before main loop
 */
#define App_Init() {\
    cli();\
  	System_Init();\
  	MIDI_Init();\
    Instrument_Init();\
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
    MIDI_In_TimeoutTimerProcess();\
    Instrument_Osc_TimersProcess();\
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
 * Example module use Key actions
 */
#define App_System_Key_ScanEvent() {\
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 0, Instrument_KeyDownAction, Instrument_KeyUpAction);\
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 1, Instrument_KeyDownAction, Instrument_KeyUpAction);\
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
    Instrument_NoteOn(midi.in.msgBuffer[midi.in.msgBufferReadPointer].data1, midi.in.msgBuffer[midi.in.msgBufferReadPointer].data2);\
}

#define App_MIDI_In_NoteOffEvent(noteNum) {\
    Instrument_NoteOff(midi.in.msgBuffer[midi.in.msgBufferReadPointer].data1);\
}
