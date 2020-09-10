#include "main.h"
#include <avr/io.h>

/*
 * TIMER0
 */
#define T0_CLK_0                                0x00
#define T0_CLK_1                                0x01
#define T0_CLK_8                                0x02
#define T0_CLK_64                               0x03
#define T0_CLK_256                              0x04
#define T0_CLK_1024                             0x05
#define T0_VAL_CLK_256_10MHz_1ms                217
#define T0_VAL_CLK_256_16MHz_1ms                194
#define T0_VAL_CLK_64_16MHz_100us               231

/*
 * ADC definitions
 */
#define ADC_PRESCLR_2                           0x01
#define ADC_PRESCLR_4                           0x02
#define ADC_PRESCLR_8                           0x03
#define ADC_PRESCLR_16                          0x04
#define ADC_PRESCLR_32                          0x05
#define ADC_PRESCLR_64                          0x06
#define ADC_PRESCLR_128                         0x07
#define ADC_VREF_EXTERNAL                       0x00
#define ADC_VREF_VCC                            0x40
#define ADC_VREF_INTERNAL                       0xc0

/*
 * USART definitions
 */
#define USART_VAL_16MHz_31250bps                31
#define USART_VAL_10MHz_31250bps                19
#define usartDataReg                            UDR

/*
 * USART default configuration
 */
#define USART_CONFIG_UCSRA                      0x00
#define USART_CONFIG_UCSRB                      0x88
#define USART_CONFIG_UCSRC                      0x86

/*
 * ADC methods
 */
#define ADC_setChannel(channel)                (ADMUX = ((ADMUX & 0xe0) | (channel & 0x1f)))
#define ADC_setVref(ref)                       (ADMUX = ((ADMUX & 0x3f) | (ref & 0xc0)))
#define ADC_getResultLeft7Bit()                 ((ADCH >> 1) & 0x7f)
#define ADC_getResultLeft5Bit()                 ((ADCH >> 3) & 0x1f)
#define ADC_getResultLeft4Bit()                 ((ADCH >> 4) & 0x0f)
#define ADC_getResultLeft3Bit()                 ((ADCH >> 5) & 0x07)
#define ADC_getResultLeft2Bit()                 ((ADCH >> 6) & 0x03)

/*
 * USART methods
 */
#define USART_isTxDataRegEmpty()                bit_is_set(UCSRA, 5)
#define USART_isRxNewData()                     bit_is_set(UCSRA, 7)
#define USART_isRxFrameError()                  bit_is_set(UCSRA, 4)
#define USART_isRxOverflow()                    bit_is_set(UCSRA, 3)
#define USART_enableRx()                        set_bit(UCSRB, 4)
#define USART_disableRx()                       clr_bit(UCSRB, 4)

/*
 * TIMER0 initialization
 */
#define TIMER0_Init(prescaler, tcntValue){\
    TCCR0 = prescaler;\
    set_bit(TIMSK, TOIE0);\
    TCNT0 = tcntValue;\
}

/*
 * USART initialization
 */
#define USART_Init(bitrateL){\
    UBRRL = bitrateL;\
    UBRRH = 0x00;\
    UCSRA = USART_CONFIG_UCSRA;\
    UCSRB = USART_CONFIG_UCSRB;\
    UCSRC = USART_CONFIG_UCSRC;\
}
