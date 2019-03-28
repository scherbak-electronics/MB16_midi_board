/*
 * MIDI Out Modeule
 * Sends MIDI messages using USART.
 */
struct MIDI_OUT_MODULE {
    BYTE flags;
    BYTE channel;
};

/*
 * MIDI Out Initialization
 */
#define MIDI_Out_Init() {\
    midi.out.flags = 0;\
    midi.out.channel = MIDI_CFG_CHANNEL;\
    MIDI_setFlagMessageSent();\
}

/*
 * Sets MIDI out channel.
 */
#define MIDI_Out_SetChannel(chn) {\
    midi.out.channel = chn;\
}

/*
 * Get MIDI out channel.
 */
#define MIDI_Out_GetChannel() midi.out.channel

/*
 * Send Note On message
 */
#define MIDI_Out_SendNoteOn(number, velocity) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_NOTE_ON_MSG, midi.out.channel), number, velocity);\
    System_Led_Blink(SYSTEM_LED_CFG_TX_LED_NUM);\
}

/*
 * Send Note Off message
 */
#define MIDI_Out_SendNoteOff(number, velocity) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_NOTE_OFF_MSG, midi.out.channel), number, velocity);\
    System_Led_Blink(SYSTEM_LED_CFG_TX_LED_NUM);\
}

/*
 * Send Pitch Bend message
 */
#define MIDI_Out_SendPitchBend(msb) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_PITCH_BEND_MSG, midi.out.channel), 0, msb);\
    System_Led_Blink(SYSTEM_LED_CFG_TX_LED_NUM);\
}

/*
 * Send Control Change message
 */
#define MIDI_Out_SendControlChange(num, val) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_CTRL_CHANGE_MSG, midi.out.channel), num, val);\
    System_Led_Blink(SYSTEM_LED_CFG_TX_LED_NUM);\
}

/*
 * Send Bank Select message
 */
#define MIDI_Out_SendBankSelect(bank) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_CTRL_CHANGE_MSG, midi.out.channel), MIDI_CFG_BANK_SEL_CTRL_NUM_32, bank);\
    System_Led_Blink(SYSTEM_LED_CFG_TX_LED_NUM);\
}

/*
 * Send Prog Change message
 */
#define MIDI_Out_SendProgramChange(prog) {\
    System_USART_Send2Bytes(MIDI_makeStatusByte(MIDI_STATUS_PROG_CHANGE_MSG, midi.out.channel), prog);\
    System_Led_Blink(SYSTEM_LED_CFG_TX_LED_NUM);\
}

