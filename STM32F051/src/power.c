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


void triac_set_duty(e_triacs triac, uint8_t duty)
{
	//duty = TIM3->ARR*((100-duty)/(100.0f));
	
	switch(triac)
	{
		case top_heat:
			TIM3->CCR3 = duty;
		break;
		case bottom_heat:
			TIM3->CCR4 = duty;
		break;
		case light:
			TIM3->CCR1 = duty;
		break;
		case fan:
			TIM3->CCR2 = duty;
		break;
	}
}

void triac_modify_duty(e_triacs triac, int16_t count)
{
	switch(triac)
	{
		case top_heat:
			TIM3->CCR3 += count;
			if(TIM3->CCR3 > 65000) TIM3->CCR3 = 0;
			if(TIM3->CCR3 > 1000) TIM3->CCR3 = 1000;
			write_to_display(TIM3->CCR3/10);
		break;
		case bottom_heat:
			TIM3->CCR4 += count;
			if(TIM3->CCR4 > 65000) TIM3->CCR4 = 0;
			if(TIM3->CCR4 > 1000) TIM3->CCR4 = 1000;
			write_to_display(TIM3->CCR4/10);
		break;
		case light:
			write_to_display(TIM3->CCR1/10);
		break;
		case fan:
			write_to_display(TIM3->CCR2/10);
		break;
	}
	
}
