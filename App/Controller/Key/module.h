/*
 * Controller_Key
 * 
 * Keys Module
 * provides system keys to controller keys mapping and events handling. 
 */
#define CONTROLLER_KEY_CFG_KEYS_COUNT       14

struct CONTROLLER_KEY_MODULE {
    BYTE mapping[CONTROLLER_KEY_CFG_KEYS_COUNT];
};

#define Controller_Key_isNoteNumber(keyNum)         bit_is_set(controller.key.mapping[keyNum], 7)
#define Controller_Key_GetCCNumber(keyNum)          controller.key.mapping[keyNum]
#define Controller_Key_GetNoteNumber(keyNum)        (controller.key.mapping[keyNum] & 0b01111111)

/*
 * Map key to note number instead of controller number.
 * Key action will send Note on/off message instead of CC message.
 */
#define Controller_Key_SetNoteNumber(keyNum, noteNum) {\
    controller.key.mapping[keyNum] = noteNum;\
    set_bit(controller.key.mapping[keyNum], 7);\
}

/*
 * Module Initialization.
 */
#define Controller_Key_Init() {\
    Controller_Key_SetDefaultMapping();\
}

/*
 * Keys default mapping
 */
#define Controller_Key_SetDefaultMapping() {\
    controller.key.mapping[0] = 22;\
    controller.key.mapping[1] = 23;\
    controller.key.mapping[2] = 18;\
    controller.key.mapping[3] = 20;\
    controller.key.mapping[4] = 19;\
    /* Key 5 is used as mode selection key. */\
    controller.key.mapping[5] = 0;\
    controller.key.mapping[6] = 17;\
    controller.key.mapping[7] = 15;\
    controller.key.mapping[8] = 16;\
    controller.key.mapping[9] = 14;\
    controller.key.mapping[10] = 21;\
    Controller_Key_SetNoteNumber(11, MIDI_Notes_GetNoteNumber(MIDI_NOTE_C, 2));\
    Controller_Key_SetNoteNumber(12, MIDI_Notes_GetNoteNumber(MIDI_NOTE_C, 3));\
    Controller_Key_SetNoteNumber(13, MIDI_Notes_GetNoteNumber(MIDI_NOTE_C, 4));\
}

/*
 * Module Main Process.
 */
#define Controller_Key_Process() {\
}
