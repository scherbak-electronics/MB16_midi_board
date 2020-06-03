/*
 * Timer 0 module
 * Hardware timer 0 module configuration, 
 * software processes runing and control 
 */

/*
 * Module configuration  
 */
#define SYSTEM_TIMER_0_CFG_TIME_1MS                 T0_VAL_CLK_256_16MHz_1ms
#define SYSTEM_TIMER_0_CFG_TIME_5MS                 5
#define SYSTEM_TIMER_0_CFG_TIME_10MS                10
#define SYSTEM_TIMER_0_CFG_TIME_100MS               100

/*
 * System_Timer_0 methods
 */
#define System_Timer_0_isFlag1ms()					bit_is_set(system.timer.flags, SYSTEM_TIMER_FLAG_1MS)
#define System_Timer_0_setFlag1ms() 				set_bit(system.timer.flags, SYSTEM_TIMER_FLAG_1MS)
#define System_Timer_0_clrFlag1ms() 				clr_bit(system.timer.flags, SYSTEM_TIMER_FLAG_1MS)

#define System_Timer_0_isFlag5ms()					bit_is_set(system.timer.flags, SYSTEM_TIMER_FLAG_5MS)
#define System_Timer_0_setFlag5ms() 				set_bit(system.timer.flags, SYSTEM_TIMER_FLAG_5MS)
#define System_Timer_0_clrFlag5ms() 				clr_bit(system.timer.flags, SYSTEM_TIMER_FLAG_5MS)

#define System_Timer_0_isFlag10ms()					bit_is_set(system.timer.flags, SYSTEM_TIMER_FLAG_10MS)
#define System_Timer_0_setFlag10ms() 				set_bit(system.timer.flags, SYSTEM_TIMER_FLAG_10MS)
#define System_Timer_0_clrFlag10ms() 				clr_bit(system.timer.flags, SYSTEM_TIMER_FLAG_10MS)

#define System_Timer_0_isFlag100ms()				bit_is_set(system.timer.flags, SYSTEM_TIMER_FLAG_100MS)
#define System_Timer_0_setFlag100ms() 			    set_bit(system.timer.flags, SYSTEM_TIMER_FLAG_100MS)
#define System_Timer_0_clrFlag100ms() 			    clr_bit(system.timer.flags, SYSTEM_TIMER_FLAG_100MS)

/*
 * Hardware interrupt vector handler
 */
#define System_Timer_0_OVF_InterruptVector() {\
    TCNT0 = SYSTEM_TIMER_0_CFG_TIME_1MS;\
	System_Timer_0_setFlag1ms();\
}

/*
 * processes for timer periods longer than 1ms
 */
#define System_Timer_0_5msProcess() {\
    if (system.timer.t5ms != 0) {\
        system.timer.t5ms--;\
    } else {\
	    System_Timer_0_setFlag5ms();\
        system.timer.t5ms = SYSTEM_TIMER_0_CFG_TIME_5MS;\
    }\
}

#define System_Timer_0_10msProcess() {\
    if (system.timer.t10ms != 0) {\
        system.timer.t10ms--;\
    } else {\
		System_Timer_0_setFlag10ms();\
        system.timer.t10ms = SYSTEM_TIMER_0_CFG_TIME_10MS;\
    }\
}

#define System_Timer_0_100msProcess() {\
    if (system.timer.t100ms != 0) {\
        system.timer.t100ms--;\
    } else {\
		System_Timer_0_setFlag100ms();\
        system.timer.t100ms = SYSTEM_TIMER_0_CFG_TIME_100MS;\
    }\
}
