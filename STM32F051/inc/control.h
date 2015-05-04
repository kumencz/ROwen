#ifndef __CONTROL_H
#define __CONTROL_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern struct sys
{
	struct{
		uint16_t		thermocouple[4];
		uint16_t			thermocouple_board;
		uint16_t		MCU_temp;
	}s_temp;
	struct{
		uint16_t mcu_voltage;
		int32_t ADC_uvolt[4];
	}s_power;
}s_system;

extern volatile uint16_t ADC_Output[2];
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC_read(void);

#endif /* __CONTROL_H */
