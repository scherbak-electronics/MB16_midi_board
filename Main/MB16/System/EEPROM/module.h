/*
 * System_EEPROM module
 * 
 * functionality for read/write access to EEPROM memory
 */

struct SYSTEM_EEPROM_MODULE {
    BYTE flags;
};

#define System_EEPROM_isWriteEnabled()          !bit_is_set(EECR, EEWE)
#define System_EEPROM_setMasterWriteEnable()    set_bit(EECR, EEMWE)
#define System_EEPROM_setWriteEnable()          set_bit(EECR, EEWE)
#define System_EEPROM_setReadEnable()          set_bit(EECR, EERE)

/*
 * Module init
 */
#define System_EEPROM_Init() {\
    system.eeprom.flags = 0;\
}

/*
 * Set address
 */
#define System_EEPROM_SetAddress(addr) {\
    EEARL = (BYTE)(0b11111111 & (addr));\
    EEARH = (BYTE)(addr >> 8);\
} 

/*
 * Set address and data registers
 */
#define System_EEPROM_SetAddressAndData(addr, data) {\
    System_EEPROM_SetAddress(addr);\
    EEDR = data;\
}

/*
 * Module main loop process..
 */
#define System_EEPROM_Process() {\
}

/*
 * Write one byte to address
 */
#define System_EEPROM_WriteByte(addr, data) {\
    System_EEPROM_SetAddressAndData(addr, data);\
    System_EEPROM_setMasterWriteEnable();\
    System_EEPROM_setWriteEnable();\
}

#define System_EEPROM_StartReading() {\
    System_EEPROM_setReadEnable();\
}

/*
 * Read the byte from address.
 */
#define System_EEPROM_ReadByte() (EEDR)

