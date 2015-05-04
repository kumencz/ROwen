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
void send_temps(void)
{
	char send_it[100] = {0};
	sprintf(send_it, "#%d=temp/%d/%d/%d/%d/%d/%d--ADC-uV=%d$\n\r",\
	(uint32_t)real_time,\
	(uint8_t)s_system.s_temp.thermocouple[0],\
	(uint8_t)s_system.s_temp.thermocouple[1],\
	(uint8_t)s_system.s_temp.thermocouple[2],\
	(uint8_t)s_system.s_temp.thermocouple[3],\
	(uint8_t)s_system.s_temp.thermocouple_board,\
	(uint8_t)(s_system.s_temp.MCU_temp/10),\
	(uint16_t)s_system.s_power.ADC_uvolt[2]);
	USART_puts(USART1,send_it);
}
