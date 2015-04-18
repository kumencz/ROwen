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
bool buttons_flags[5];

uint8_t buzzer_beeps_counter = 0;
uint16_t buzzer_beep_time_counter = 0;
uint8_t buzzer_beep_time = 0;
e_buzzer_mode buzzer_mode = off;

void buzzer(e_buzzer_mode b_mode, uint8_t beep_count)
{
	buzzer_mode = b_mode;
	switch(buzzer_mode)
	{
		case off:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		break;
		case beep_const:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		break;
		case strobo:
			buzzer_beeps_counter = 1;
		break;
		case beeps:
			buzzer_beeps_counter = beep_count*2;
		break;
	}
}
void buzzer_speed(uint8_t speed)
{
	buzzer_beep_time_counter = 0;
	buzzer_beep_time = speed; //time in [ms] for one beep
}

bool check_button(e_buttons button)
{
	if(buttons_flags[button] == true) 
	{
		buttons_flags[button] = false;
		return true;
	}else
		return false;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	bool beep = false;
	/* ====== ENCODER button =========== */
	if(GPIO_Pin == GPIO_PIN_4)
	{
		buttons_flags[button_enc] = true;
		beep = true;
	}
	/* ====== ENCODER rotation =========== */
	if(GPIO_Pin == GPIO_PIN_15)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
		buzzer(beeps,1);
		buzzer_speed(3);
	}
	
	/* ====== BUTTONS =========== */
	if(GPIO_Pin == GPIO_PIN_14)
	{
		buttons_flags[button_1] = true;
		beep = true;
	}
	if(GPIO_Pin == GPIO_PIN_13)
	{
		buttons_flags[button_2] = true;
		beep = true;
	}
	if(GPIO_Pin == GPIO_PIN_12)
	{
		buttons_flags[button_3] = true;
		beep = true;
	}
	if(GPIO_Pin == GPIO_PIN_5)
	{
		buttons_flags[button_4] = true;
		beep = true;
	}
	if(beep)
	{
		buzzer(beeps,1);
		buzzer_speed(30);
	}
}
