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
uint8_t aTxStartMessage[] = "\n\rHallo\n\r";

bool send_temp(e_temp_sensor temp_sensor)
{
	char temp_out[] = {100,100,100,100,100,100,100,100,100,100};
	sprintf(temp_out, "%d\n\r", s_system.s_temp.MCU_temp);
	//HAL_UART_Transmit(&huart1, (uint8_t*)temp_out, 8,200);
	
	switch(temp_sensor)
	{
		case thermocouple_1:
			
		break;
		case thermocouple_2:
			
		break;
		case thermocouple_3:
			
		break;
		case thermocouple_4:
			
		break;
		case thermocouple_board:
			
		break;
		case MCU_temp:
			
		break;
	}
	
	

	return false;
}
