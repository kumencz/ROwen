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


uint16_t triac_get_duty(e_triacs triac)
{
	switch(triac)
	{
		case triac_1:
			return ((TIM3->CCR3)/10);
		case triac_2:
			return ((TIM3->CCR4)/10);
		case triac_3:
			return ((TIM3->CCR1)/10);
		case triac_4:
			return ((TIM3->CCR2)/10);
		default:
			return (0);
	}
}

void triac_set_duty(e_triacs triac, uint8_t duty)
{
	uint16_t duty_scaled = duty*10;

	switch(triac)
	{
		case triac_1:
			TIM3->CCR3 = duty_scaled;
		break;
		case triac_2:
			TIM3->CCR4 = duty_scaled;
		break;
		case triac_3:
			TIM3->CCR1 = duty_scaled;
		break;
		case triac_4:
			TIM3->CCR2 = duty_scaled;
		break;
	}
}

void triac_modify_duty(e_triacs triac, int8_t count)
{
	int16_t count_scaled = count*10;

	if(count_scaled <= 1000 && count_scaled >= -1000)
	{
		switch(triac)
		{
			case triac_1:
				if(TIM3->CCR3 + count_scaled <= (TIM3->ARR+1))
					TIM3->CCR3 += count_scaled;
			break;
			case triac_2:
				if(TIM3->CCR4 + count_scaled <= (TIM3->ARR+1))
					TIM3->CCR4 += count_scaled;
			break;
			case triac_3:
				if(TIM3->CCR1 + count_scaled <= (TIM3->ARR+1))
					TIM3->CCR1 += count_scaled;
			break;
			case triac_4:
				if(TIM3->CCR2 + count_scaled <= (TIM3->ARR+1))
					TIM3->CCR2 += count_scaled;
			break;
		}
	}
}
