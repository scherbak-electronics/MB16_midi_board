/*
 * MIDI Module
 * Inplements MIDI messages receiving, parsing and sending functionality
 * Generates events by seting status register flags. 
 */
#include "notes.h"
#include "In/module.h"
#include "Out/module.h"

/*
 * MIDI config
 */
#define MIDI_CFG_CHANNEL                            0
#define MIDI_CFG_CTRL_START_NUM                     102
#define MIDI_CFG_DEFAULT_VELOCITY                   64
#define MIDI_CFG_DEFAULT_GATETIME                   15
#define MIDI_CFG_LFO_COUNT                          2
#define MIDI_CFG_KEY_COUNT                          2
#define MIDI_CFG_GRAIN_COUNT                        2
#define MIDI_CFG_DEFAULT_NOTE_NUMBER                64
#define MIDI_CFG_BANK_SEL_CTRL_NUM_32               0x20

/*
 * Status register flags
 */
#define MIDI_FLAG_SYSEX_MODE                        0
#define MIDI_FLAG_MESSAGE_SENT		                5

/*
 * MIDI status bytes
 *
 * Pitch Bend MIDI Message Status Byte
 * 3 bytes: [cmd & chn], [lsb], [msb]
 */
#define MIDI_STATUS_PITCH_BEND_MSG                  0xe0

/*
 * Note On / Note Off MIDI Message Status Byte
 * 3 bytes: [cmd & chn], [note], [velocity]
 */
#define MIDI_STATUS_NOTE_ON_MSG                     0x90
#define MIDI_STATUS_NOTE_OFF_MSG                    0x80

/*
 * Control Change MIDI Message Status Byte
 * 3 bytes: [cmd & chn], [ctrl num], [ctrl val]
 */
#define MIDI_STATUS_CTRL_CHANGE_MSG                 0xb0

#define MIDI_STATUS_PROG_CHANGE_MSG                 0xc0
#define MIDI_STATUS_SYSEX_MSG                       0xF0
#define MIDI_STATUS_EOX_MSG                         0xF7
#define MIDI_STATUS_CLK_MSG                         0xF8
#define MIDI_STATUS_START_MSG                       0xFA
#define MIDI_STATUS_CONTINUE_MSG                    0xFB
#define MIDI_STATUS_STOP_MSG                        0xFC
#define MIDI_STATUS_ACTIVE_SENS_MSG                 0xFE
#define MIDI_STATUS_RESET_MSG                       0xFF
#define MIDI_STATUS_TIMECODE_MSG                    0xF1  // 0nnndddd
#define MIDI_STATUS_SONG_POS_MSG                    0xF2  // 0lllllll, 0hhhhhhh
#define MIDI_STATUS_SONG_SEL_MSG                    0xF3  // 0sssssss
#define MIDI_STATUS_TUNE_RQ_MSG                     0xF6

#define MIDI_STATUS_MASK_REALTIME_MSG               0b11111000
#define MIDI_STATUS_MASK_CHANNEL_VOICE_MSG          0b11110000  // ssssnnnn
#define MIDI_STATUS_MASK_NOTE_ON_MSG                0b10010000  // 0kkkkkkk, 0vvvvvvv
#define MIDI_STATUS_MASK_NOTE_OFF_MSG               0b10000000  // 0kkkkkkk, 0vvvvvvv
#define MIDI_STATUS_MASK_AFTCH_MSG                  0b10100000  // 0kkkkkkk, 0vvvvvvv
#define MIDI_STATUS_MASK_CTRL_CHANGE_MSG            0b10110000  // 0ccccccc, 0vvvvvvv
#define MIDI_STATUS_MASK_PITCH_MSG                  0b11100000  // 0vvvvvvv, 0vvvvvvv
#define MIDI_STATUS_MASK_PROG_CHANGE_MSG            0b11000000  // 0ppppppp
#define MIDI_STATUS_MASK_CHN_AFTCH_MSG              0b11010000  // 0vvvvvvv

struct MIDI_MODULE {
    BYTE flags;
    struct MIDI_IN_MODULE in;
    struct MIDI_OUT_MODULE out;
};

/*
 * MIDI specific macros
 */
#define MIDI_setFlagMessageSent()					    set_bit(midi.flags, MIDI_FLAG_MESSAGE_SENT)
#define MIDI_clrFlagMessageSent()					    clr_bit(midi.flags, MIDI_FLAG_MESSAGE_SENT)
#define MIDI_isChannelChangeEnabled()			        bit_is_set(midi.flags, MIDI_FLAG_MESSAGE_SENT)

#define MIDI_isSysExModeFlag()                          bit_is_set(midi.flags, MIDI_FLAG_SYSEX_MODE)
#define MIDI_setSysExModeFlag()                         set_bit(midi.flags, MIDI_FLAG_SYSEX_MODE)
#define MIDI_clrSysExModeFlag()                         clr_bit(midi.flags, MIDI_FLAG_SYSEX_MODE)

#define MIDI_makeStatusByte(statusByte, midiChannel)    (BYTE)(statusByte | (midiChannel & 0x0f))
#define MIDI_getStatusByte(byte)                        (byte & MIDI_STATUS_MASK_CHANNEL_VOICE_MSG)
#define MIDI_isRealTimeMessage(statusByte)              ((statusByte & MIDI_STATUS_MASK_REALTIME_MSG) == MIDI_STATUS_MASK_REALTIME_MSG)
#define MIDI_isSysExMessage(statusByte)                 (statusByte == MIDI_STATUS_SYSEX_MSG)
#define MIDI_isChannelVoiceMessage(statusByte)          ((statusByte & MIDI_STATUS_MASK_CHANNEL_VOICE_MSG) > 0x7F && (statusByte & MIDI_STATUS_MASK_CHANNEL_VOICE_MSG) < 0xF0)
#define MIDI_isDataByte(byte)                           ((byte & 0b10000000) == 0b00000000)

/*
 * MIDI Initialization
 */
#define MIDI_Init() {\
    MIDI_Out_Init();\
    MIDI_In_Init();\
}

/*
 * Checking MIDI module event flags, trigger events, actions or processes of other modules
 */
#define MIDI_EventsProcess() {\
    if (MIDI_isSysExModeFlag()) {\
        /* Enter system exclusive mode ... */\
    }\
    if (MIDI_In_isNewRealTimeMessage()) {\
        if (MIDI_In_isTimeClockFlag()) {\
            MIDI_In_clrTimeClockFlag();\
            /* ext sync byte received ... */\
            App_MIDI_In_ExtSyncEvent();\
        }\
        if (MIDI_In_isStartFlag()) {\
            MIDI_In_clrStartFlag();\
            /* start play sequence and reset sync counters... */\
            App_MIDI_In_PlayEvent();\
        }\
        if (MIDI_In_isStopFlag()) {\
            MIDI_In_clrStopFlag();\
            /* stop play sequence ... */\
            App_MIDI_in_StopEvent();\
        }\
        midi.in.rtmMsgBufferReadPointer++;\
        if (midi.in.rtmMsgBufferReadPointer == midi.in.rtmMsgBufferPointer) {\
            MIDI_In_ResetRtmMsgBuffer();\
        }\
    }\
    if (MIDI_In_isNewMessage()) {\
        /* Voice channel message handlers ... */\
        if (MIDI_STATUS_MASK_NOTE_ON_MSG == MIDI_getStatusByte(midi.in.currentStatus)) {\
            if (midi.in.msgBuffer[midi.in.msgBufferReadPointer].data2 > 0) {\
                App_MIDI_In_NoteOnEvent(midi.in.msgBuffer[midi.in.msgBufferReadPointer].data1, midi.in.msgBuffer[midi.in.msgBufferReadPointer].data2);\
            } else {\
                App_MIDI_In_NoteOffEvent(midi.in.msgBuffer[midi.in.msgBufferReadPointer].data1);\
            }\
        }\
        if (MIDI_STATUS_MASK_NOTE_OFF_MSG == MIDI_getStatusByte(midi.in.currentStatus)) {\
            App_MIDI_In_NoteOffEvent(midi.in.msgBuffer[midi.in.msgBufferReadPointer].data1);\
        }\
        if (MIDI_STATUS_MASK_PITCH_MSG == MIDI_getStatusByte(midi.in.currentStatus)) {\
            App_MIDI_In_PitchBendEvent(midi.in.msgBuffer[midi.in.msgBufferReadPointer].data1, midi.in.msgBuffer[midi.in.msgBufferReadPointer].data2);\
        }\
        midi.in.msgBufferReadPointer++;\
        if (midi.in.msgBufferReadPointer == midi.in.msgBufferPointer) {\
            MIDI_In_ResetMsgBuffer();\
        }\
    }\
    if (MIDI_In_isTimeoutErrorFlag()) {\
        /* TIMEOUT error handler ... */\
    }\
}
