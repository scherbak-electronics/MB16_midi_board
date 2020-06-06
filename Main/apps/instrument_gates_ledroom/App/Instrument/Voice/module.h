/*
 * Instrument_Voice module
 * 
 * Provides voice assignment
 * Performs routing of Note On/Off messages to the voices
 */
#define INSTRUMENT_VOICE_CFG_MAX_POLYPHONY                      8

#define INSTRUMENT_VOICE_FLAG_PLAY                              0
#define INSTRUMENT_VOICE_FLAG_FREE_VOICE_FOUND                  1

struct VOICE_DATA {
    BYTE flags;
    BYTE noteNumber;
};

struct VOICE_MODULE {
    BYTE flags;
    BYTE firstAvailableNumber;
    BYTE lastAssignedVoiceNumber;
    BYTE voiceToOscMap[INSTRUMENT_VOICE_CFG_MAX_POLYPHONY];
    struct VOICE_DATA activeVoices[INSTRUMENT_VOICE_CFG_MAX_POLYPHONY];
};

#define Instrument_Voice_isFlagFreeVoiceFound()		                bit_is_set(instrument.voice.flags, INSTRUMENT_VOICE_FLAG_FREE_VOICE_FOUND)
#define Instrument_Voice_setFlagFreeVoiceFound()		            set_bit(instrument.voice.flags, INSTRUMENT_VOICE_FLAG_FREE_VOICE_FOUND)
#define Instrument_Voice_clrFlagFreeVoiceFound()		            clr_bit(instrument.voice.flags, INSTRUMENT_VOICE_FLAG_FREE_VOICE_FOUND)

#define Instrument_Voice_isFlagPlay(voiceNum)			            bit_is_set(instrument.voice.activeVoices[voiceNum].flags, INSTRUMENT_VOICE_FLAG_PLAY)
#define Instrument_Voice_setFlagPlay(voiceNum) 			            set_bit(instrument.voice.activeVoices[voiceNum].flags, INSTRUMENT_VOICE_FLAG_PLAY)
#define Instrument_Voice_clrFlagPlay(voiceNum) 			            clr_bit(instrument.voice.activeVoices[voiceNum].flags, INSTRUMENT_VOICE_FLAG_PLAY)

#define Instrument_Voice_GetVoiceNumberByNote(noteNum)              (noteNum & 0b00000111)
#define Instrument_Voice_GetIsActiveByNumber(voiceNum)			    Instrument_Voice_isFlagPlay(voiceNum)
#define Instrument_Voice_GetOscNumberByVoice(voiceNum)              instrument.voice.voiceToOscMap[voiceNum]

#define Instrument_Voice_Init() {\
    instrument.voice.firstAvailableNumber = 0;\
    instrument.voice.lastAssignedVoiceNumber = 0;\
    instrument.voice.voiceToOscMap[0] = 0;\
    instrument.voice.voiceToOscMap[1] = 1;\
    instrument.voice.voiceToOscMap[2] = 2;\
    instrument.voice.voiceToOscMap[3] = 3;\
    instrument.voice.voiceToOscMap[4] = 4;\
    instrument.voice.voiceToOscMap[5] = 5;\
    instrument.voice.voiceToOscMap[6] = 6;\
    instrument.voice.voiceToOscMap[7] = 7;\
    Instrument_Voice_clrFlagPlay(0);\
    Instrument_Voice_clrFlagPlay(1);\
    Instrument_Voice_clrFlagPlay(2);\
    Instrument_Voice_clrFlagPlay(3);\
    Instrument_Voice_clrFlagPlay(4);\
    Instrument_Voice_clrFlagPlay(5);\
    Instrument_Voice_clrFlagPlay(6);\
    Instrument_Voice_clrFlagPlay(7);\
}

#define Instrument_Voice_NoteOn(noteNum, velocity) {\
    if (!Instrument_Voice_GetIsActiveByNumber(Instrument_Voice_GetVoiceNumberByNote(noteNum))) {\
        Instrument_Voice_Play(Instrument_Voice_GetVoiceNumberByNote(noteNum), noteNum, velocity);\
    } else {\
        Instrument_Voice_PlayFirstAvailable(noteNum, velocity);\
    }\
}

/*
 * searching for free available voice and 
 * set first found free voice number to instrument.voice.firstAvailableNumber
 * if there is no free voice found set last assigned voice number to instrument.voice.firstAvailableNumber
 */
#define Instrument_Voice_PlayFirstAvailable(noteNum, velocity) {\
    Instrument_Voice_clrFlagFreeVoiceFound();\
    for (instrument.voice.firstAvailableNumber = 0; instrument.voice.firstAvailableNumber < INSTRUMENT_VOICE_CFG_MAX_POLYPHONY; instrument.voice.firstAvailableNumber++) {\
        if (!Instrument_Voice_GetIsActiveByNumber(instrument.voice.firstAvailableNumber)) {\
            Instrument_Voice_Play(instrument.voice.firstAvailableNumber, noteNum, velocity);\
            break;\
        }\
    }\
    if (!Instrument_Voice_isFlagFreeVoiceFound()) {\
        instrument.voice.firstAvailableNumber = instrument.voice.lastAssignedVoiceNumber;\
    }\
}

#define Instrument_Voice_Play(voiceNum, noteNum, velocity) {\
    instrument.voice.lastAssignedVoiceNumber = voiceNum;\
    Instrument_Voice_setFlagPlay(voiceNum);\
    instrument.voice.activeVoices[voiceNum].noteNumber = noteNum;\
    Instrument_Osc_NoteOn(\
        Instrument_Voice_GetOscNumberByVoice(voiceNum),\
        noteNum,\
        velocity\
    );\
}

#define Instrument_Voice_NoteOff(noteNum) {\
    Instrument_Voice_StopIfActive(0, noteNum);\
    Instrument_Voice_StopIfActive(1, noteNum);\
    Instrument_Voice_StopIfActive(2, noteNum);\
    Instrument_Voice_StopIfActive(3, noteNum);\
    Instrument_Voice_StopIfActive(4, noteNum);\
    Instrument_Voice_StopIfActive(5, noteNum);\
    Instrument_Voice_StopIfActive(6, noteNum);\
    Instrument_Voice_StopIfActive(7, noteNum);\
}

#define Instrument_Voice_StopIfActive(voiceNum, noteNum) {\
    if (Instrument_Voice_isFlagPlay(voiceNum) && instrument.voice.activeVoices[voiceNum].noteNumber == noteNum) {\
        Instrument_Voice_Stop(voiceNum);\
    }\
}

#define Instrument_Voice_Stop(voiceNum) {\
    Instrument_Osc_NoteOff(\
        Instrument_Voice_GetOscNumberByVoice(voiceNum)\
    );\
    Instrument_Voice_clrFlagPlay(voiceNum);\
}
