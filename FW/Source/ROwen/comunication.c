/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
void uart_send_temps(void)
{
	char send_it[100] = {0};
	sprintf(send_it, "#%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d$\n",\
	(uint32_t)real_time/10,\
	(uint8_t)s_system.s_temp.thermocouple[0],\
	(uint8_t)s_system.s_temp.thermocouple[1],\
	(uint8_t)s_system.s_temp.thermocouple[2],\
	(uint8_t)s_system.s_temp.thermocouple[3],\
	(uint8_t)s_system.s_temp.thermocouple_board,\
	(uint8_t)s_system.s_temp.reflow_temp,\
	(uint8_t)triac_get_duty(triac_1),\
	(uint8_t)triac_get_duty(triac_2),\
	(uint8_t)triac_get_duty(triac_3),\
	(uint8_t)triac_get_duty(triac_4),\
	(uint8_t)(s_system.s_temp.MCU_temp/10),\
	(uint8_t)ramp_get_temp(&curr_ramp),\
	(uint8_t)P_term,\
	(uint8_t)I_term,\
	(uint8_t)D_term);
	
//	sprintf(send_it, "#Time %ds -> Thermocouplers: %dC,%dC,%dC,%dC ADC: %dC MCU: %dC   ADC voltage=%duV\n\r",\
//	(uint32_t)real_time/10,\
//	(uint8_t)s_system.s_temp.thermocouple[0],\
//	(uint8_t)s_system.s_temp.thermocouple[1],\
//	(uint8_t)s_system.s_temp.thermocouple[2],\
//	(uint8_t)s_system.s_temp.thermocouple[3],\
//	(uint8_t)s_system.s_temp.thermocouple_board,\
//	(uint8_t)(s_system.s_temp.MCU_temp/10),\
//	s_system.s_power.ADC_uvolt[2]);
	
//	sprintf(send_it, "#Time %ds -> Thermocoupler: %dC ADC: %dC MCU: %dC   ADC voltage=%duV\n\r",\
//	(uint32_t)real_time/10,\
//	(uint8_t)s_system.s_temp.thermocouple[2],\
//	(uint8_t)s_system.s_temp.thermocouple_board,\
//	(uint8_t)(s_system.s_temp.MCU_temp/10),\
//	s_system.s_power.ADC_uvolt[2]);
	
	USART_puts(USART1,send_it);
}
