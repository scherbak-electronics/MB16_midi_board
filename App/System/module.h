/*
 * System Module
 * 
 * Hardware Peripheral drivers.
 * For interaction with hardware modules USART, GPIO, ADC, TIMER, etc.. 
 */
#include "Led/module.h"
#include "Port/module.h"
#include "Timer/module.h"
#include "ADC/module.h"
#include "USART/module.h"
#include "Key/module.h"
#include "EEPROM/module.h"

/*
 * System config
 */
struct SYSTEM_MODULE {
    BYTE flags;
    BYTE var;
    struct SYSTEM_KEY_MODULE key;
    struct SYSTEM_LED_MODULE led;
    struct SYSTEM_TIMER_MODULE timer;
    struct SYSTEM_USART_MODULE usart;
    struct SYSTEM_ADC_MODULE adc;
    struct SYSTEM_EEPROM_MODULE eeprom;
};

/*
 * System Initialization
 */
#define System_Init() {\
    System_EEPROM_Init();\
    System_Port_Init();\
    System_Led_Init();\
    System_Timer_Init();\
    System_ADC_Init();\
    System_USART_Init();\
    System_Key_Init();\
}
