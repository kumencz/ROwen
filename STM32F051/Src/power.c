/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


void triac_set_duty(uint8_t triac_id, uint8_t duty)
{
	duty = TIM3->ARR*((100-duty)/(100.0f));
	
	switch(triac_id)
	{
		case 1:
			TIM3->CCR3 = duty;
		break;
		case 2:
			TIM3->CCR4 = duty;
		break;
		case 3:
			TIM3->CCR1 = duty;
		break;
		case 4:
			TIM3->CCR2 = duty;
		break;
	}
}
