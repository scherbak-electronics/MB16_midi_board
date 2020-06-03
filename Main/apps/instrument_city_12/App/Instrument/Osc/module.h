/*
 * Instrument_Osc module
 * 
 * Sound generation module
 * one of multiple implementations of individual sound oscilator
 */
#define INSTRUMENT_OSC_CFG_RELAY_GATE_TIME                  100
#define INSTRUMENT_OSC_CFG_HDD_HEAD_GATE_TIME               5
#define INSTRUMENT_OSC_PULSE_CFG_MAX_COUNT                  8

struct OSC_PULSE_MODULE {
    BYTE timer;
    BYTE time;
};

struct OSC_MODULE {
    struct OSC_PULSE_MODULE pulse[INSTRUMENT_OSC_PULSE_CFG_MAX_COUNT];
    BYTE lastUsedPulseOscNumber;
};

#define Instrument_Osc_GetOscNumberByNote(noteNum)              (noteNum & 0b00000111)

#define Instrument_Osc_Init() {\
    instrument.osc.lastUsedPulseOscNumber = 0;\
    Instrument_Osc_NoteOff(0);\
    instrument.osc.pulse[0].time = INSTRUMENT_OSC_CFG_HDD_HEAD_GATE_TIME;\
    Instrument_Osc_NoteOff(1);\
    instrument.osc.pulse[1].time = INSTRUMENT_OSC_CFG_HDD_HEAD_GATE_TIME;\
    Instrument_Osc_NoteOff(2);\
    instrument.osc.pulse[2].time = INSTRUMENT_OSC_CFG_HDD_HEAD_GATE_TIME;\
    Instrument_Osc_NoteOff(3);\
    instrument.osc.pulse[3].time = INSTRUMENT_OSC_CFG_HDD_HEAD_GATE_TIME;\
    Instrument_Osc_NoteOff(4);\
    instrument.osc.pulse[4].time = INSTRUMENT_OSC_CFG_HDD_HEAD_GATE_TIME;\
    Instrument_Osc_NoteOff(5);\
    instrument.osc.pulse[5].time = INSTRUMENT_OSC_CFG_HDD_HEAD_GATE_TIME;\
    Instrument_Osc_NoteOff(6);\
    instrument.osc.pulse[6].time = INSTRUMENT_OSC_CFG_HDD_HEAD_GATE_TIME;\
    Instrument_Osc_NoteOff(7);\
    instrument.osc.pulse[7].time = INSTRUMENT_OSC_CFG_HDD_HEAD_GATE_TIME;\
}

#define Instrument_Osc_TimersProcess() {\
    Instrument_Osc_TimerProcess(0);\
    Instrument_Osc_TimerProcess(1);\
    Instrument_Osc_TimerProcess(2);\
    Instrument_Osc_TimerProcess(3);\
    Instrument_Osc_TimerProcess(4);\
    Instrument_Osc_TimerProcess(5);\
    Instrument_Osc_TimerProcess(6);\
    Instrument_Osc_TimerProcess(7);\
}

#define Instrument_Osc_TimerProcess(oscNum) {\
    if (instrument.osc.pulse[oscNum].timer != 0) {\
        instrument.osc.pulse[oscNum].timer--;\
        if (instrument.osc.pulse[oscNum].timer == 0) {\
            Instrument_Osc_clrOutPort(oscNum);\
        }\
    }\
}

/*
 * Turn On oscilator by number
 * oscNum is zero based param
 */
#define Instrument_Osc_NoteOn(oscNum, noteNum, velocity) {\
    instrument.osc.pulse[oscNum].time = (velocity >> 2);\
    Instrument_Osc_setOutPort(oscNum);\
    instrument.osc.pulse[oscNum].timer = instrument.osc.pulse[oscNum].time;\
}

/*
 * Turn Off oscilator by its number
 * oscNum is zero based param
 */
#define Instrument_Osc_NoteOff(oscNum) {\
    Instrument_Osc_clrOutPort(oscNum);\
    instrument.osc.pulse[oscNum].timer = 0;\
}

/*
 * oscNum should be in range 0-7
 * oscNum is a number of port out bit
 */
#define Instrument_Osc_setOutPort(oscNum) {\
    set_bit(instrumentOscPortOut, oscNum);\
}

/*
 * oscNum should be in range 0-7
 * oscNum is a number of port out bit
 */
#define Instrument_Osc_clrOutPort(oscNum) {\
    clr_bit(instrumentOscPortOut, oscNum);\
}
