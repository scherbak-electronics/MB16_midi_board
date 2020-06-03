/*
 * Controller_Program
 * 
 * Program change module
 * Implements MIDI program change message logic.
 * Keeps current program number in memory. Combines program num 
 * from lower 16 and high 8 controller knobs
 */
struct PROGRAM_CHANGE_MODULE {
    BYTE number;
    BYTE prevNumber;
    BYTE lastUsedNumber;
};

#define Controller_Program_setLow16(low)        controller.program.number = (controller.program.number & 0b11110000) | (low & 0b00001111)
#define Controller_Program_setHi8(hi)           controller.program.number = (controller.program.number & 0b00001111) | (hi & 0b01110000)
#define Controller_Program_GetLastUsedNumber()  controller.program.lastUsedNumber

/*
 * Module Initialization.
 */
#define Controller_Program_Init() {\
    controller.program.number = 0;\
    controller.program.prevNumber = 0;\
    controller.program.lastUsedNumber = 0;\
}

/*
 * Module Main Process.
 */
#define Controller_Program_Process() {\
}

/*
 * Send program change MIDI message with current program number.
 */
#define Controller_Program_Change() {\
    if (controller.program.prevNumber != controller.program.number) {\
        controller.program.prevNumber = controller.program.number;\
        MIDI_Out_SendProgramChange(controller.program.number);\
        controller.program.lastUsedNumber = controller.program.number;\
    }\
}
