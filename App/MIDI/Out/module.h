/*
 * MIDI Out Modeule
 * Sends MIDI messages using USART.
 */

/*
 * MIDI Out Initialization
 */
#define MIDI_Out_Init() {\
    MIDI_setFlagMessageSent();\
}

/*
 * Send Note On message
 */
#define MIDI_Out_SendNoteOn(number, velocity) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_NOTE_ON_MSG, MIDI_CFG_CHANNEL), number, velocity);\
}

/*
 * Send Note Off message
 */
#define MIDI_Out_SendNoteOff(number, velocity) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_NOTE_OFF_MSG, MIDI_CFG_CHANNEL), number, velocity);\
}

/*
 * Send Pitch Bend message
 */
#define MIDI_Out_SendPitchBend(msb) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_PITCH_BEND_MSG, MIDI_CFG_CHANNEL), 0, msb);\
}

/*
 * Send Control Change message
 */
#define MIDI_Out_SendControlChange(num, val) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_CTRL_CHANGE_MSG, MIDI_CFG_CHANNEL), num, val);\
}

/*
 * Send Bank Select message
 */
#define MIDI_Out_SendBankSelect(bank) {\
    System_USART_Send3Bytes(MIDI_makeStatusByte(MIDI_STATUS_CTRL_CHANGE_MSG, MIDI_CFG_CHANNEL), MIDI_CFG_BANK_SEL_CTRL_NUM_32, bank);\
}

/*
 * Send Prog Change message
 */
#define MIDI_Out_SendProgramChange(prog) {\
    System_USART_Send2Bytes(MIDI_makeStatusByte(MIDI_STATUS_PROG_CHANGE_MSG, MIDI_CFG_CHANNEL), prog);\
}

