/*
 * App_Voice module
 * 
 * Provides voice assignment
 * Performs routing of Note On/Off messages to the voices
 */
#define APP_VOICE_CFG_MAX_POLYPHONY                      8

#define APP_VOICE_FLAG_PLAY                              0
#define APP_VOICE_FLAG_FREE_VOICE_FOUND                  1

struct VOICE_DATA {
    BYTE flags;
    BYTE noteNumber;
};

struct VOICE_MODULE {
    BYTE flags;
    BYTE firstAvailableNumber;
    BYTE lastAssignedVoiceNumber;
    BYTE voiceToOscMap[APP_VOICE_CFG_MAX_POLYPHONY];
    struct VOICE_DATA activeVoices[APP_VOICE_CFG_MAX_POLYPHONY];
};

#define App_Voice_isFlagFreeVoiceFound()		                bit_is_set(app.voice.flags, APP_VOICE_FLAG_FREE_VOICE_FOUND)
#define App_Voice_setFlagFreeVoiceFound()		            set_bit(app.voice.flags, APP_VOICE_FLAG_FREE_VOICE_FOUND)
#define App_Voice_clrFlagFreeVoiceFound()		            clr_bit(app.voice.flags, APP_VOICE_FLAG_FREE_VOICE_FOUND)

#define App_Voice_isFlagPlay(voiceNum)			            bit_is_set(app.voice.activeVoices[voiceNum].flags, APP_VOICE_FLAG_PLAY)
#define App_Voice_setFlagPlay(voiceNum) 			            set_bit(app.voice.activeVoices[voiceNum].flags, APP_VOICE_FLAG_PLAY)
#define App_Voice_clrFlagPlay(voiceNum) 			            clr_bit(app.voice.activeVoices[voiceNum].flags, APP_VOICE_FLAG_PLAY)

#define App_Voice_GetVoiceNumberByNote(noteNum)              (noteNum & 0b00000111)
#define App_Voice_GetIsActiveByNumber(voiceNum)			    App_Voice_isFlagPlay(voiceNum)
#define App_Voice_GetOscNumberByVoice(voiceNum)              app.voice.voiceToOscMap[voiceNum]

#define App_Voice_Init() {\
    app.voice.firstAvailableNumber = 0;\
    app.voice.lastAssignedVoiceNumber = 0;\
    app.voice.voiceToOscMap[0] = 0;\
    app.voice.voiceToOscMap[1] = 1;\
    app.voice.voiceToOscMap[2] = 2;\
    app.voice.voiceToOscMap[3] = 3;\
    app.voice.voiceToOscMap[4] = 4;\
    app.voice.voiceToOscMap[5] = 5;\
    app.voice.voiceToOscMap[6] = 6;\
    app.voice.voiceToOscMap[7] = 7;\
    App_Voice_clrFlagPlay(0);\
    App_Voice_clrFlagPlay(1);\
    App_Voice_clrFlagPlay(2);\
    App_Voice_clrFlagPlay(3);\
    App_Voice_clrFlagPlay(4);\
    App_Voice_clrFlagPlay(5);\
    App_Voice_clrFlagPlay(6);\
    App_Voice_clrFlagPlay(7);\
}

#define App_Voice_NoteOn(noteNum, velocity) {\
    if (!App_Voice_GetIsActiveByNumber(App_Voice_GetVoiceNumberByNote(noteNum))) {\
        App_Voice_Play(App_Voice_GetVoiceNumberByNote(noteNum), noteNum, velocity);\
    } else {\
        App_Voice_PlayFirstAvailable(noteNum, velocity);\
    }\
}

/*
 * searching for free available voice and 
 * set first found free voice number to app.voice.firstAvailableNumber
 * if there is no free voice found set last assigned voice number to app.voice.firstAvailableNumber
 */
#define App_Voice_PlayFirstAvailable(noteNum, velocity) {\
    App_Voice_clrFlagFreeVoiceFound();\
    for (app.voice.firstAvailableNumber = 0; app.voice.firstAvailableNumber < APP_VOICE_CFG_MAX_POLYPHONY; app.voice.firstAvailableNumber++) {\
        if (!App_Voice_GetIsActiveByNumber(app.voice.firstAvailableNumber)) {\
            App_Voice_Play(app.voice.firstAvailableNumber, noteNum, velocity);\
            break;\
        }\
    }\
    if (!App_Voice_isFlagFreeVoiceFound()) {\
        app.voice.firstAvailableNumber = app.voice.lastAssignedVoiceNumber;\
    }\
}

#define App_Voice_Play(voiceNum, noteNum, velocity) {\
    app.voice.lastAssignedVoiceNumber = voiceNum;\
    App_Voice_setFlagPlay(voiceNum);\
    app.voice.activeVoices[voiceNum].noteNumber = noteNum;\
    App_Osc_NoteOn(\
        App_Voice_GetOscNumberByVoice(voiceNum),\
        noteNum,\
        velocity\
    );\
}

#define App_Voice_NoteOff(noteNum) {\
    App_Voice_StopIfActive(0, noteNum);\
    App_Voice_StopIfActive(1, noteNum);\
    App_Voice_StopIfActive(2, noteNum);\
    App_Voice_StopIfActive(3, noteNum);\
    App_Voice_StopIfActive(4, noteNum);\
    App_Voice_StopIfActive(5, noteNum);\
    App_Voice_StopIfActive(6, noteNum);\
    App_Voice_StopIfActive(7, noteNum);\
}

#define App_Voice_StopIfActive(voiceNum, noteNum) {\
    if (App_Voice_isFlagPlay(voiceNum) && app.voice.activeVoices[voiceNum].noteNumber == noteNum) {\
        App_Voice_Stop(voiceNum);\
    }\
}

#define App_Voice_Stop(voiceNum) {\
    App_Osc_NoteOff(\
        App_Voice_GetOscNumberByVoice(voiceNum)\
    );\
    App_Voice_clrFlagPlay(voiceNum);\
}
