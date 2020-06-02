/*
 * ADC module
 * Reads values from ADC channels, apply noise reduction and if value
 * changed it generates event with channel number and value.
 */
#define ADC_CFG_CHANNELS_COUNT                   8

struct ADC_BUFFER_ITEM {
	BYTE level_1;
	BYTE level_2;
};

struct SYSTEM_ADC_MODULE {
    BYTE channel;
    BYTE values[ADC_CFG_CHANNELS_COUNT];
    struct ADC_BUFFER_ITEM buffer[ADC_CFG_CHANNELS_COUNT];
};

#define System_ADC_Init() {\
    system.adc.channel = 0;\
	system.adc.values[0] = 0;\
    system.adc.values[1] = 0;\
    system.adc.values[2] = 0;\
    system.adc.values[3] = 0;\
	system.adc.values[4] = 0;\
	system.adc.values[5] = 0;\
	system.adc.values[6] = 0;\
	system.adc.values[7] = 0;\
    ADC_Init();\
    ADC_setChannel(system.adc.channel);\
}

/*
 * ADC Process
 */
#define System_ADC_Process(){\
	if(ADC_isConvertionEnd()){\
		if(ADC_getResultLeft7Bit() != system.adc.buffer[system.adc.channel].level_1){\
			if((ADC_getResultLeft7Bit() > system.adc.buffer[system.adc.channel].level_1 && system.adc.buffer[system.adc.channel].level_1 > system.adc.buffer[system.adc.channel].level_2) || (ADC_getResultLeft7Bit() < system.adc.buffer[system.adc.channel].level_1 && system.adc.buffer[system.adc.channel].level_1 < system.adc.buffer[system.adc.channel].level_2)){\
                App_System_ADC_ValueChangeEvent(system.adc.channel, ADC_getResultLeft7Bit());\
                system.adc.values[system.adc.channel] = ADC_getResultLeft7Bit();\
			}\
			system.adc.buffer[system.adc.channel].level_2 = system.adc.buffer[system.adc.channel].level_1;\
			system.adc.buffer[system.adc.channel].level_1 = ADC_getResultLeft7Bit();\
		}\
		if((system.adc.channel + 1) >= ADC_CFG_CHANNELS_COUNT){\
			system.adc.channel = 0;\
		}else{\
			system.adc.channel++;\
		}\
		ADC_setChannel(system.adc.channel);\
		ADC_startConversion();\
	}\
}
