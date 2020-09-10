/*
 * Timer module
 * Hardware timers / counters module configuration, 
 * software processes runing and control 
 */
#include "0/module.h"
#include "1/module.h"

/*
 * Timer status flags
 */
#define SYSTEM_TIMER_FLAG_100uS                           4
#define SYSTEM_TIMER_FLAG_1MS						      0
#define SYSTEM_TIMER_FLAG_5MS						      1
#define SYSTEM_TIMER_FLAG_10MS						      2
#define SYSTEM_TIMER_FLAG_100MS 					      3

struct SYSTEM_TIMER_MODULE {
	BYTE flags;
    BYTE t1ms;
	BYTE t5ms;
	BYTE t10ms;
    WORD t100ms;
};

/*
 * Module Initialization
 */
#define System_Timer_Init() {\
    system.timer.t100ms = SYSTEM_TIMER_0_CFG_TIME_100MS;\
    system.timer.t10ms = SYSTEM_TIMER_0_CFG_TIME_10MS;\
	system.timer.t5ms = SYSTEM_TIMER_0_CFG_TIME_5MS;\
    system.timer.t1ms = SYSTEM_TIMER_0_CFG_TIME_1MS;\
    System_Timer_0_clrFlag100us();\
	System_Timer_0_clrFlag1ms();\
	System_Timer_0_clrFlag5ms();\
	System_Timer_0_clrFlag10ms();\
    System_Timer_0_clrFlag100ms();\
    TIMER0_Init(T0_CLK_64, SYSTEM_TIMER_0_CFG_TIME_100uS);\
}

#define System_Timer_1msProcessEvent() {\
	System_Timer_0_5msProcess();\
	System_Timer_0_10msProcess();\
	System_Timer_0_100msProcess();\
}

/*
 * A process that checks all other timers flags and generates corresponding events
 * must be called from main function infinitive loop
 */
#define System_Timer_Process() {\
	if (System_Timer_0_isFlag1ms()) {\
		System_Timer_0_clrFlag1ms();\
        System_Timer_1msProcessEvent();\
        App_System_Timer_1msProcessEvent();\
	}\
	if (System_Timer_0_isFlag5ms()) {\
		System_Timer_0_clrFlag5ms();\
		App_System_Timer_5msProcessEvent();\
	}\
	if (System_Timer_0_isFlag10ms()) {\
		System_Timer_0_clrFlag10ms();\
		App_System_Timer_10msProcessEvent();\
	}\
	if (System_Timer_0_isFlag100ms()) {\
		System_Timer_0_clrFlag100ms();\
		App_System_Timer_100msProcessEvent();\
	}\
}

