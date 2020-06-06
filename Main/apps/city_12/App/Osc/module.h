/*
 * App_Osc module
 * 
 * Sound generation module
 * one of multiple implementations of individual sound oscilator
 */
#define APP_OSC_CFG_RELAY_GATE_TIME                  100
#define APP_OSC_CFG_HDD_HEAD_GATE_TIME               5
#define APP_OSC_PULSE_CFG_MAX_COUNT                  8

struct OSC_PULSE_MODULE {
    BYTE timer;
    BYTE time;
};

struct OSC_MODULE {
    struct OSC_PULSE_MODULE pulse[APP_OSC_PULSE_CFG_MAX_COUNT];
    BYTE lastUsedPulseOscNumber;
};

#define App_Osc_GetOscNumberByNote(noteNum)              (noteNum & 0b00000111)

#define App_Osc_Init() {\
    app.osc.lastUsedPulseOscNumber = 0;\
    App_Osc_NoteOff(0);\
    app.osc.pulse[0].time = APP_OSC_CFG_HDD_HEAD_GATE_TIME;\
    App_Osc_NoteOff(1);\
    app.osc.pulse[1].time = APP_OSC_CFG_HDD_HEAD_GATE_TIME;\
    App_Osc_NoteOff(2);\
    app.osc.pulse[2].time = APP_OSC_CFG_HDD_HEAD_GATE_TIME;\
    App_Osc_NoteOff(3);\
    app.osc.pulse[3].time = APP_OSC_CFG_HDD_HEAD_GATE_TIME;\
    App_Osc_NoteOff(4);\
    app.osc.pulse[4].time = APP_OSC_CFG_HDD_HEAD_GATE_TIME;\
    App_Osc_NoteOff(5);\
    app.osc.pulse[5].time = APP_OSC_CFG_HDD_HEAD_GATE_TIME;\
    App_Osc_NoteOff(6);\
    app.osc.pulse[6].time = APP_OSC_CFG_HDD_HEAD_GATE_TIME;\
    App_Osc_NoteOff(7);\
    app.osc.pulse[7].time = APP_OSC_CFG_HDD_HEAD_GATE_TIME;\
}

#define App_Osc_TimersProcess() {\
    App_Osc_TimerProcess(0);\
    App_Osc_TimerProcess(1);\
    App_Osc_TimerProcess(2);\
    App_Osc_TimerProcess(3);\
    App_Osc_TimerProcess(4);\
    App_Osc_TimerProcess(5);\
    App_Osc_TimerProcess(6);\
    App_Osc_TimerProcess(7);\
}

#define App_Osc_TimerProcess(oscNum) {\
    if (app.osc.pulse[oscNum].timer != 0) {\
        app.osc.pulse[oscNum].timer--;\
        if (app.osc.pulse[oscNum].timer == 0) {\
            App_Osc_clrOutPort(oscNum);\
        }\
    }\
}

/*
 * Turn On oscilator by number
 * oscNum is zero based param
 */
#define App_Osc_NoteOn(oscNum, noteNum, velocity) {\
    app.osc.pulse[oscNum].time = (velocity >> 2);\
    App_Osc_setOutPort(oscNum);\
    app.osc.pulse[oscNum].timer = app.osc.pulse[oscNum].time;\
}

/*
 * Turn Off oscilator by its number
 * oscNum is zero based param
 */
#define App_Osc_NoteOff(oscNum) {\
    App_Osc_clrOutPort(oscNum);\
    app.osc.pulse[oscNum].timer = 0;\
}

/*
 * oscNum should be in range 0-7
 * oscNum is a number of port out bit
 */
#define App_Osc_setOutPort(oscNum) {\
    set_bit(appOscPortOut, oscNum);\
}

/*
 * oscNum should be in range 0-7
 * oscNum is a number of port out bit
 */
#define App_Osc_clrOutPort(oscNum) {\
    clr_bit(appOscPortOut, oscNum);\
}
