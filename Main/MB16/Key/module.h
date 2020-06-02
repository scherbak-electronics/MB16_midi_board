/*
 * System_Key Module
 * 
 * Scans availabe gpio ports assuming keys are connected
 * and call assigned up/down actions.
 */

/*
 * System Keys config
 */
#define SYSTEM_KEY_SCAN_TIME          	5

/*
 * Status flags
 */
#define SYSTEM_KEY_FLAG_SCAN			2

/*
 * System Keys config
 */
struct SYSTEM_KEY_MODULE {
    BYTE states;
    BYTE states2;
    BYTE scanTimer;
    BYTE flags;
};

#define System_Key_setFlagScan() 		            set_bit(system.key.flags, SYSTEM_KEY_FLAG_SCAN)
#define System_Key_clrFlagScan() 		            clr_bit(system.key.flags, SYSTEM_KEY_FLAG_SCAN)
#define System_Key_isFlagScan()			            bit_is_set(system.key.flags, SYSTEM_KEY_FLAG_SCAN)

#define System_Key_isDown(portName, keyNum)			!bit_is_set(portName, SYSTEM_KEY_##keyNum##_CFG_PORT_IN_BIT)
#define System_Key_is1Down()			            System_Key_isDown(systemKeyPortIn, 0)

/*
 * Key Initialize
 */
#define System_Key_Init() {\
    system.key.scanTimer = SYSTEM_KEY_SCAN_TIME;\
    system.key.states = 0xff;\
    system.key.states2 = 0xff;\
    System_Key_clrFlagScan();\
}

/*
 * Scan timer process for all keys
 */
#define System_Key_ScanTimerProcess() {\
	if(system.key.scanTimer != 0){\
		system.key.scanTimer--;\
	}else{\
		system.key.scanTimer = SYSTEM_KEY_SCAN_TIME;\
		System_Key_setFlagScan();\
	}\
}

/*
 * Key Scan Process
 * scans all keys when scan timer flag raised
 */
#define System_Key_ScanFlagObserverProcess(){\
	if(System_Key_isFlagScan()){\
		System_Key_clrFlagScan();\
        App_System_Key_ScanEvent();\
	}\
}

/*
 * Assign Key to phisical port and scan
 */
#define System_Key_ScanByNum(port, keyStates, keyNum, keyDownAction, keyUpAction) {\
	if (get_bit(port, SYSTEM_KEY_##keyNum##_CFG_PORT_IN_BIT) != get_bit(keyStates, SYSTEM_KEY_##keyNum##_CFG_STREG_BIT)) {\
		if (!bit_is_set(port, SYSTEM_KEY_##keyNum##_CFG_PORT_IN_BIT)) {\
			clr_bit(keyStates, SYSTEM_KEY_##keyNum##_CFG_STREG_BIT);\
			keyDownAction(keyNum);\
		} else {\
			set_bit(keyStates, SYSTEM_KEY_##keyNum##_CFG_STREG_BIT);\
			keyUpAction(keyNum);\
		}\
	}\
}
