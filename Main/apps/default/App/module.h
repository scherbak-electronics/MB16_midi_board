/*
 * default App module
 * 
 * Default application example 
 * Defines GPIO ports mapping, events and action calls routing
 */

struct APP_MODULE {
    BYTE flags;
};

/*
 * Application start up once, before main loop
 */
#define App_Init() {\
    cli();\
  	System_Init();\
  	MIDI_Init();\
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
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 0, App_UI_KeyDownEvent, App_UI_KeyUpEvent);\
    System_Key_ScanByNum(systemKeyPortIn, system.key.states, 1, App_UI_KeyDownEvent, App_UI_KeyUpEvent);\
}

/*
 * MIDI In message events 
 */
#define App_MIDI_In_ExtSyncEvent() {\
    System_Led_Blink(0);\
}

#define App_MIDI_In_PlayEvent() {\
    System_Led_Blink(0);\
}

#define App_MIDI_in_StopEvent() {\
    System_Led_Blink(0);\
}

#define App_MIDI_In_NoteOnEvent(noteNum, velocity) {\
    App_NoteOn(midi.in.msgBuffer[midi.in.msgBufferReadPointer].data1, midi.in.msgBuffer[midi.in.msgBufferReadPointer].data2);\
    System_Led_Blink(1);\
}

#define App_MIDI_In_NoteOffEvent(noteNum) {\
    App_NoteOff(midi.in.msgBuffer[midi.in.msgBufferReadPointer].data1);\
    System_Led_Blink(1);\
}

#define App_NoteOn(noteNum, velocity) {\
}

#define App_NoteOff(noteNum) {\
}
