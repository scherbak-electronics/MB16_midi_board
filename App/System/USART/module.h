/*
 * System USART module
 */
#define USART_CFG_BITRATE                   USART_VAL_16MHz_31250bps
#define USART_CFG_TX_BUFFER_SIZE            12
#define USART_CFG_RX_BUFFER_SIZE            3
#define USART_CFG_RX_TIMEOUT_TIME		    10

/*
 * Status register flags
 */
#define USART_FLAG_TX							      	3
#define USART_FLAG_RX_ERROR								0

struct SYSTEM_USART_MODULE {
	BYTE flags;
  	BYTE txBuffer[USART_CFG_TX_BUFFER_SIZE];
  	BYTE txBufferLevel;
  	BYTE txBufferPointer;
  	BYTE rxBuffer[USART_CFG_RX_BUFFER_SIZE];
  	BYTE rxBufferPointer;
	BYTE rxBufferReadPointer;
	BYTE rxTimeoutTimer;
	BYTE dummy;
};

/*
 * USART methods
 */
#define System_USART_setFlagTx() 								set_bit(system.usart.flags, USART_FLAG_TX)
#define System_USART_clrFlagTx() 								clr_bit(system.usart.flags, USART_FLAG_TX)
#define System_USART_setFlagRxError() 							set_bit(system.usart.flags, USART_FLAG_RX_ERROR)
#define System_USART_clrFlagRxError() 							clr_bit(system.usart.flags, USART_FLAG_RX_ERROR)
#define System_USART_isFlagRxError() 							bit_is_set(system.usart.flags, USART_FLAG_RX_ERROR)

/*
 * USART Initialization
 */
#define System_USART_Init() {\
  	System_USART_clrFlagTx();\
	System_USART_clrFlagRxError();\
	system.usart.txBufferLevel = 0;\
	system.usart.txBufferPointer = 0;\
	system.usart.rxBufferPointer = 0;\
	system.usart.rxBufferReadPointer = 0;\
	USART_Init(USART_CFG_BITRATE);\
  	USART_enableRx();\
}

/*
 * USART transmit main process
 */
#define System_USART_TxProcess(){\
	if(system.usart.txBufferLevel != 0){\
		if(system.usart.txBufferPointer < USART_CFG_TX_BUFFER_SIZE && system.usart.txBufferPointer < system.usart.txBufferLevel){\
			if(USART_isTxDataRegEmpty()){\
				usartDataReg = system.usart.txBuffer[system.usart.txBufferPointer];\
				/* Set TX LED active */\
                System_Led_Blink(0);\
				if(system.usart.txBufferPointer == system.usart.txBufferLevel - 1){\
					system.usart.txBufferPointer = 0;\
					system.usart.txBufferLevel = 0;\
				}else{\
					system.usart.txBufferPointer++;\
				}\
			}\
		}else{\
			/* Error: TX buffer overflow */\
			system.usart.txBufferPointer = 0;\
			system.usart.txBufferLevel = 0;\
		}\
	}\
}

#define System_USART_RxProcess() {\
	if (system.usart.rxBufferPointer > system.usart.rxBufferReadPointer) {\
		MIDI_In_ParseMessage();\
		system.usart.rxBufferReadPointer++;\
		if (system.usart.rxBufferPointer == system.usart.rxBufferReadPointer) {\
			System_USART_ResetRxBuffer();\
		}\
	}\
}

#define System_USART_ResetRxBuffer() {\
	system.usart.rxBufferPointer = 0;\
	system.usart.rxBufferReadPointer = 0;\
}

/*
 * Hardware interrupt vector handler
 */
#define System_USART_RXC_InterruptVector() {\
    if (!USART_isRxFrameError() && !USART_isRxOverflow()) {\
		if (system.usart.rxBufferPointer < USART_CFG_RX_BUFFER_SIZE) {\
			system.usart.rxBuffer[system.usart.rxBufferPointer] = usartDataReg;\
			system.usart.rxBufferPointer++;\
		}\
	} else {\
		/* Flush buffer on USART frame error or USART overflow error */\
		system.usart.dummy = usartDataReg;\
		if (USART_isRxFrameError() || USART_isRxOverflow()) {\
			system.usart.dummy = usartDataReg;\
		}\
		System_USART_setFlagRxError();\
	}\
}

/*
 * Add 3 bytes to TX buffer
 */
#define System_USART_Send3Bytes(b1, b2, b3) {\
	if ((system.usart.txBufferLevel + 3) < USART_CFG_TX_BUFFER_SIZE) {\
		cli();\
		system.usart.txBuffer[system.usart.txBufferLevel] = b1;\
		system.usart.txBuffer[system.usart.txBufferLevel + 1] = b2;\
		system.usart.txBuffer[system.usart.txBufferLevel + 2] = b3;\
		system.usart.txBufferLevel += 3;\
		sei();\
	}\
}

/*
 * Add 2 bytes to TX buffer
 */
#define System_USART_Send2Bytes(b1, b2) {\
	if ((system.usart.txBufferLevel + 2) < USART_CFG_TX_BUFFER_SIZE) {\
		cli();\
		system.usart.txBuffer[system.usart.txBufferLevel] = b1;\
		system.usart.txBuffer[system.usart.txBufferLevel + 1] = b2;\
		system.usart.txBufferLevel += 2;\
		sei();\
	}\
}

