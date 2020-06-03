/*
 * Controller_Memory module
 * 
 * MIDI Controller specific
 * functionality for read/write access to EEPROM memory
 */
#include "View/module.h"

#define CONTROLLER_MEMORY_FLAG_PATTERN_DATA_SAVING      0
#define CONTROLLER_MEMORY_FLAG_OPTIONS_SAVING           1
#define CONTROLLER_MEMORY_FLAG_KNOB_MAPPING_SAVING      2
#define CONTROLLER_MEMORY_FLAG_PATTERN_DATA_READING     3

#define CONTROLLER_MEMORY_CFG_PATTERN_DATA_LEN              CONTROLLER_SEQUENCER_CFG_PATTERN_LEN * CONTROLLER_SEQUENCER_CFG_PATTERNS_COUNT * 3

struct CONTROLLER_MEMORY_MODULE {
    BYTE flags;
    BYTE *patternDataBaseAddress;
    WORD patternDataEEPROMAddress;
};

#define Controller_Memory_isPatternDataSavingProcessRunning()     bit_is_set(controller.memory.flags, CONTROLLER_MEMORY_FLAG_PATTERN_DATA_SAVING)
#define Controller_Memory_startPatternDataSavingProcess()    set_bit(controller.memory.flags, CONTROLLER_MEMORY_FLAG_PATTERN_DATA_SAVING)
#define Controller_Memory_stopPatternDataSavingProcess()    clr_bit(controller.memory.flags, CONTROLLER_MEMORY_FLAG_PATTERN_DATA_SAVING)

#define Controller_Memory_isPatternDataReadingProcessRunning()     bit_is_set(controller.memory.flags, CONTROLLER_MEMORY_FLAG_PATTERN_DATA_READING)
#define Controller_Memory_startPatternDataReadingProcess()    set_bit(controller.memory.flags, CONTROLLER_MEMORY_FLAG_PATTERN_DATA_READING)
#define Controller_Memory_stopPatternDataReadingProcess()    clr_bit(controller.memory.flags, CONTROLLER_MEMORY_FLAG_PATTERN_DATA_READING)


/*
 * Module init
 */
#define Controller_Memory_Init() {\
    controller.memory.flags = 0;\
    Controller_Memory_InitPointers();\
}

#define Controller_Memory_InitPointers() {\
    controller.memory.patternDataEEPROMAddress = 0;\
    /* controller.memory.patternDataBaseAddress = &controller.sequencer.patterns[0][0].noteNumber; */\
    controller.memory.patternDataBaseAddress = controller.sequencer.patterns;\
}

/*
 * Save sequencer patterns data to EEPROM memory.
 */
#define Controller_Memory_SavePatternData() {\
    if (!Controller_Memory_isPatternDataSavingProcessRunning()) {\
        Controller_Memory_InitPointers();\
        Controller_Memory_startPatternDataSavingProcess();\
    }\
}

/*
 * Starts the process of reading patterns data from EEPROM memory and
 * copies data to pattern memory.
 */
#define Controller_Memory_ReadPatternData() {\
    if (!Controller_Memory_isPatternDataReadingProcessRunning()) {\
        Controller_Memory_InitPointers();\
        Controller_Memory_startPatternDataReadingProcess();\
    }\
}

/*
 * Module main loop process..
 */
#define Controller_Memory_Process() {\
    Controller_Memory_PatternDataSavingProcess();\
    Controller_Memory_OptionsSavingProcess();\
    Controller_Memory_KnobMappingSavingProcess();\
    Controller_Memory_PatternDataReadingProcess();\
}

/*
 * Pattern data saving process.
 * Copy pattern structure to EEPROM memory 
 */
#define Controller_Memory_PatternDataSavingProcess() {\
    if (Controller_Memory_isPatternDataSavingProcessRunning()) {\
        if (System_EEPROM_isWriteEnabled()) {\
            if (controller.memory.patternDataEEPROMAddress < CONTROLLER_MEMORY_CFG_PATTERN_DATA_LEN) {\
                System_EEPROM_WriteByte(\
                    controller.memory.patternDataEEPROMAddress, \
                    *controller.memory.patternDataBaseAddress\
                );\
                controller.memory.patternDataEEPROMAddress++;\
                controller.memory.patternDataBaseAddress++;\
            } else {\
                Controller_Memory_stopPatternDataSavingProcess();\
                Controller_Memory_PatternDataSavingCompleteEvent();\
            }\
        }\
    }\
}

/*
 * Pattern data reading process.
 * Copy pattern structure from EEPROM memory to RAM
 */
#define Controller_Memory_PatternDataReadingProcess() {\
    if (Controller_Memory_isPatternDataReadingProcessRunning()) {\
        if (System_EEPROM_isWriteEnabled()) {\
            if (controller.memory.patternDataEEPROMAddress < CONTROLLER_MEMORY_CFG_PATTERN_DATA_LEN) {\
                System_EEPROM_SetAddress(controller.memory.patternDataEEPROMAddress);\
                System_EEPROM_StartReading();\
                *controller.memory.patternDataBaseAddress = System_EEPROM_ReadByte();\
                controller.memory.patternDataEEPROMAddress++;\
                controller.memory.patternDataBaseAddress++;\
            } else {\
                Controller_Memory_stopPatternDataReadingProcess();\
                Controller_Memory_PatternDataReadingCompleteEvent();\
            }\
        }\
    }\
}

/*
 * Event fire when all bytes from pattern memory copied to EEPROM
 */
#define Controller_Memory_PatternDataSavingCompleteEvent() {\
    Controller_Memory_View_HideSaveDialog();\
    Controller_Mode_EnableAllActions();\
}

#define Controller_Memory_PatternDataReadingCompleteEvent() {\
    /* Controller_Mode_EnableAllActions(); */\
}

#define Controller_Memory_OptionsSavingProcess() {\
}

#define Controller_Memory_KnobMappingSavingProcess() {\
}

