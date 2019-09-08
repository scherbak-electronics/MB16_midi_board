/*
 * Controller_Notes_Scale module
 * 
 * Provides functionality for calculating musical scales.
 */
#define CONTROLLER_NOTES_SCALE_CFG_TABLE_SIZE       12

struct NOTES_SCALE_MODULE {
    BYTE flags;
    BYTE table[CONTROLLER_NOTES_SCALE_CFG_TABLE_SIZE];
    BYTE scaleLen;
    BYTE scaleNumber;
};

/*
 * Module Initialization.
 */
#define Controller_Notes_Scale_Init() {\
    controller.notes.scale.flags = 0;\
    controller.notes.scale.scaleNumber = 0;\
    Controller_Notes_Scale_LoadChromatic();\
}

/*
 * Notes module main loop process.
 */
#define Controller_Notes_Scale_Process() {\
}

/*
 * System timer 10ms process alias.
 */
#define Controller_Notes_Scale_Timer10msProcess() {\
}

/*
 * Calculates note number by knob value.
 * Knob value will be trimmed to 0-8
 */
#define Controller_Notes_Scale_GetNote(knobVal) controller.notes.scale.table[(knobVal % controller.notes.scale.scaleLen)] + (12 * (BYTE)(knobVal / controller.notes.scale.scaleLen))

/*
 * Load scale by number 0-3
 */
#define Controller_Notes_Scale_LoadScaleByNumber(scaleNum) {\
    switch (scaleNum) {\
        case 1:\
        Controller_Notes_Scale_LoadPhrygianDominant();\
        break;\
        case 0:\
        Controller_Notes_Scale_LoadChromatic();\
        break;\
        case 2:\
        Controller_Notes_Scale_LoadBluesPentatonic();\
        break;\
        case 3:\
        Controller_Notes_Scale_LoadSoFarTriplet();\
        break;\
    }\
}

/*
 * Loads Phrygian Dominant scale to the scale buffer.
 */
#define Controller_Notes_Scale_LoadPhrygianDominant() {\
    controller.notes.scale.table[0] = MIDI_NOTE_C;\
    controller.notes.scale.table[1] = MIDI_NOTE_Db;\
    controller.notes.scale.table[2] = MIDI_NOTE_E;\
    controller.notes.scale.table[3] = MIDI_NOTE_F;\
    controller.notes.scale.table[4] = MIDI_NOTE_G;\
    controller.notes.scale.table[5] = MIDI_NOTE_Ab;\
    controller.notes.scale.table[6] = MIDI_NOTE_Bb;\
    controller.notes.scale.scaleLen = 7;\
}

/*
 * Loads chromatic scale to the scale buffer.
 */
#define Controller_Notes_Scale_LoadChromatic() {\
    controller.notes.scale.table[0] = MIDI_NOTE_C;\
    controller.notes.scale.table[1] = MIDI_NOTE_Db;\
    controller.notes.scale.table[2] = MIDI_NOTE_D;\
    controller.notes.scale.table[3] = MIDI_NOTE_Eb;\
    controller.notes.scale.table[4] = MIDI_NOTE_E;\
    controller.notes.scale.table[5] = MIDI_NOTE_F;\
    controller.notes.scale.table[6] = MIDI_NOTE_Gb;\
    controller.notes.scale.table[7] = MIDI_NOTE_G;\
    controller.notes.scale.table[8] = MIDI_NOTE_Ab;\
    controller.notes.scale.table[9] = MIDI_NOTE_A;\
    controller.notes.scale.table[10] = MIDI_NOTE_Bb;\
    controller.notes.scale.table[11] = MIDI_NOTE_B;\
    controller.notes.scale.scaleLen = 12;\
}

/*
 * Loads Blues Pentatonic scale to the scale buffer.
 */
#define Controller_Notes_Scale_LoadBluesPentatonic() {\
    controller.notes.scale.table[0] = MIDI_NOTE_C;\
    controller.notes.scale.table[1] = MIDI_NOTE_Eb;\
    controller.notes.scale.table[2] = MIDI_NOTE_F;\
    controller.notes.scale.table[3] = MIDI_NOTE_Gb;\
    controller.notes.scale.table[4] = MIDI_NOTE_G;\
    controller.notes.scale.table[5] = MIDI_NOTE_Bb;\
    controller.notes.scale.scaleLen = 6;\
}

/*
 * Loads So Far Triplet scale to the scale buffer.
 */
#define Controller_Notes_Scale_LoadSoFarTriplet() {\
    controller.notes.scale.table[0] = MIDI_NOTE_C;\
    controller.notes.scale.table[1] = MIDI_NOTE_F;\
    controller.notes.scale.table[2] = MIDI_NOTE_Bb;\
    controller.notes.scale.scaleLen = 3;\
}

