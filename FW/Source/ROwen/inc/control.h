#ifndef __CONTROL_H
#define __CONTROL_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern struct sys
{
	struct{
		float		thermocouple[4];
		float		thermocouple_board;
		uint16_t	MCU_temp;
	}s_temp;
	struct{
		uint16_t mcu_voltage;
		int32_t ADC_uvolt[4];
	}s_power;
}s_system;

typedef enum {
	next_action,
	previous_action,
	enter_action,
	quit_action
}e_action;

extern struct h_ramp
{
	uint16_t duration;
	uint16_t final_temp;
}ramp[][10];

extern uint8_t mode_showed;
extern uint8_t mode_current;
extern volatile uint16_t ADC_Output[2];
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC_read(void);
void mode_selector(e_action action);
uint8_t mode_get_child(uint8_t parrent_id, uint8_t start_id, bool upcount);
#endif /* __CONTROL_H */
