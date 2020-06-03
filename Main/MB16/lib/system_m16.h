#include "system.h"

/*
 * ADC Control and Status Register A – ADCSRA
 * Bit 7 – ADEN: ADC Enable
 * Bit 6 – ADSC: ADC Start Conversion
 * Bit 5 – ADATE: ADC Auto Trigger Enable (m16)
 * Bit 4 – ADIF: ADC Interrupt Flag
 * Bit 3 – ADIE: ADC Interrupt Enable
 * Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
 */
#define ADC_CONFIG_ADCSRA									0b10000111

/*
 * ADC Multiplexer Selection Register – ADMUX
 * Bit 7:6 – REFS1:0: Reference Selection Bits
 * 			00: AREF, Internal Vref turned off
 * 			01: AVCC with external capacitor at AREF pin
 * 			10: Reserved
 * 			11: Internal 2.56V Voltage Reference with external capacitor at AREF pin
 * Bit 5 – ADLAR: ADC Left Adjust Result
 * Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits (m16)
 */
#define ADC_CONFIG_ADMUX                 	0b01100000

/*
 * ADC methods
 */
#define ADC_setPrescaler(prescaler)				(ADCSRA = ((ADCSRA & 0xf8) | (prescaler & 0x07)))
#define ADC_isConvertionEnd()							bit_is_set(ADCSRA, 4)
#define ADC_setConversionEnd()            clr_bit(ADCSRA, 4)
#define ADC_startConversion()							set_bit(ADCSRA, 6)

/*
 * ADC Initialization
 */
#define ADC_Init(){\
	ADMUX = ADC_CONFIG_ADMUX;\
	ADCSRA = ADC_CONFIG_ADCSRA;\
}
