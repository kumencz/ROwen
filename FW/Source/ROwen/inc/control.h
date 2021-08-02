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
		float		reflow_temp;
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
	uint32_t duration;		// [ms]
	float final_temp;
}ramp[][10];
extern struct h_curr_ramp{
	bool running;
	struct h_ramp (*current_ramp);
	uint8_t current_step;
	uint32_t time_in_step;
	uint16_t step_start_temp;
}curr_ramp;

extern uint8_t mode_showed;
extern uint8_t mode_current;
extern float P_term, I_term, D_term;
extern volatile uint16_t ADC_Output[2];
extern uint16_t set_temp_mem;
extern uint16_t set_duty_mem;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC_read(void);
void mode_selector(e_action action);
uint8_t mode_get_child(uint8_t parrent_id, uint8_t start_id, bool upcount);
uint16_t ramp_get_temp(struct h_curr_ramp *ramp);
void PID_update_temp(uint16_t temp);
int16_t PID_controller(uint16_t setPoint, uint16_t feedback);
#endif /* __CONTROL_H */
