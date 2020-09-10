/*
 * App_Osc module
 * 
 * Polyphonic square wave oscilator.
 * Generates audio signal at GPIO outputs.
 */
#define APP_OSC_CFG_MAX_POLYPHONY                      8
#define APP_OSC_CFG_NOTE_RANGE_LEN                      35

#define APP_OSC_FLAG_PLAY                         0

struct OSC_DATA {
    BYTE flags;
    BYTE noteNumber;
    WORD timer;
    WORD time;
};

struct OSC_MODULE {
    BYTE flags;
    struct OSC_DATA oscillators[APP_OSC_CFG_MAX_POLYPHONY];
    WORD noteFreqTable[APP_OSC_CFG_NOTE_RANGE_LEN];
};

#define App_Osc_isFlagPlay(oscNum)		            bit_is_set(app.osc.oscillators[oscNum].flags, APP_OSC_FLAG_PLAY)
#define App_Osc_setFlagPlay(oscNum)		            set_bit(app.osc.oscillators[oscNum].flags, APP_OSC_FLAG_PLAY)
#define App_Osc_clrFlagPlay(oscNum)		            clr_bit(app.osc.oscillators[oscNum].flags, APP_OSC_FLAG_PLAY)

#define App_Osc_GetTimeByNote(noteNum)              app.osc.noteFreqTable[noteNum % APP_OSC_CFG_NOTE_RANGE_LEN]             

#define App_Osc_Init() {\
    app.osc.flags = 0;\
    system.var = 0;\
    for (; system.var < APP_OSC_CFG_MAX_POLYPHONY; system.var++) {\
        app.osc.oscillators[system.var].flags = 0;\
        app.osc.oscillators[system.var].time = 0;\
        app.osc.oscillators[system.var].timer = 0;\
        app.osc.oscillators[system.var].noteNumber = 0xff;\
    }\
    app.osc.noteFreqTable[0] = 306; /* C1 #24 */\
    app.osc.noteFreqTable[1] = 288;\
    app.osc.noteFreqTable[2] = 272;\
    app.osc.noteFreqTable[3] = 257;\
    app.osc.noteFreqTable[4] = 242;\
    app.osc.noteFreqTable[5] = 229;\
    app.osc.noteFreqTable[6] = 216;\
    app.osc.noteFreqTable[7] = 204;\
    app.osc.noteFreqTable[8] = 192;\
    app.osc.noteFreqTable[9] = 182;\
    app.osc.noteFreqTable[10] = 171;\
    app.osc.noteFreqTable[11] = 162;\
    app.osc.noteFreqTable[12] = 153;\
    app.osc.noteFreqTable[13] = 143;\
    app.osc.noteFreqTable[14] = 136;\
    app.osc.noteFreqTable[15] = 128;\
    app.osc.noteFreqTable[16] = 121;\
    app.osc.noteFreqTable[17] = 114;\
    app.osc.noteFreqTable[18] = 108;\
    app.osc.noteFreqTable[19] = 102;\
    app.osc.noteFreqTable[20] = 96;\
    app.osc.noteFreqTable[21] = 91;\
    app.osc.noteFreqTable[22] = 86;\
    app.osc.noteFreqTable[23] = 81;\
    app.osc.noteFreqTable[24] = 76;\
    app.osc.noteFreqTable[25] = 72;\
    app.osc.noteFreqTable[26] = 68;\
    app.osc.noteFreqTable[27] = 64;\
    app.osc.noteFreqTable[28] = 61;\
    app.osc.noteFreqTable[29] = 57;\
    app.osc.noteFreqTable[30] = 54;\
    app.osc.noteFreqTable[31] = 51;\
    app.osc.noteFreqTable[32] = 48;\
    app.osc.noteFreqTable[33] = 45;\
    app.osc.noteFreqTable[34] = 43;\
}

/* 
 * Start play note on specified oscillator number 
 * Audio signal produced at configured GPIO out
 * Assign note number to first available oscilator
 */
#define App_Osc_NoteOn(noteNum, velocity) {\
    system.var = 0;\
    for (; system.var < APP_OSC_CFG_MAX_POLYPHONY; system.var++) {\
        if (!App_Osc_isFlagPlay(system.var)) {\
            App_Osc_AssignNoteAndStartOsc(system.var, noteNum);\
            break;\
        } else {\
            if (system.var == (APP_OSC_CFG_MAX_POLYPHONY - 1)) {\
                App_Osc_AssignNoteAndStartOsc(system.var, noteNum);\
            }\
        }\
    }\
}

/* 
 * Assign note number to first available oscilator
 * Set oscilator timer
 */
#define App_Osc_AssignNoteAndStartOsc(oscNum, noteNum) {\
    app.osc.oscillators[oscNum].noteNumber = noteNum;\
    app.osc.oscillators[oscNum].time = App_Osc_GetTimeByNote(app.osc.oscillators[oscNum].noteNumber);\
    app.osc.oscillators[oscNum].timer = app.osc.oscillators[oscNum].time;\
    App_Osc_setFlagPlay(oscNum);\
}

/* 
 * Stop play note by searching assigned oscillator by note number 
 * configured GPIO out will be set to low
 */
#define App_Osc_NoteOff(noteNum) {\
    system.var = 0;\
    for (; system.var < APP_OSC_CFG_MAX_POLYPHONY; system.var++) {\
        if (app.osc.oscillators[system.var].noteNumber == noteNum) {\
            clr_bit(appOscPortOut, system.var);\
            App_Osc_clrFlagPlay(system.var);\
            app.osc.oscillators[system.var].noteNumber = 0xff;\
            break;\
        }\
    }\
}

/* 
 * Waveform generation frequency timers 
 * process 
 */
#define App_Osc_TimersProcess() {\
    system.var = 0;\
    for (; system.var < APP_OSC_CFG_MAX_POLYPHONY; system.var++) {\
        if (App_Osc_isFlagPlay(system.var)) {\
            if (app.osc.oscillators[system.var].timer != 0) {\
                app.osc.oscillators[system.var].timer--;\
            } else {\
                app.osc.oscillators[system.var].timer = app.osc.oscillators[system.var].time;\
                inv_bit(appOscPortOut, system.var);\
            }\
        }\
    }\
}

 
