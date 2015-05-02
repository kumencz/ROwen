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
bool buttons_flags[5];
uint16_t buttons_delay[5] = {0};
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
			GPIO_SetBits(GPIOB, GPIO_Pin_15);
		break;
		case beep_const:
			GPIO_ResetBits(GPIOB, GPIO_Pin_15);
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

void button_handler(e_buttons button)
{
	bool beep = false;
	
	buttons_delay[button] = button_press_delay;
	
	/* ====== ENCODER button =========== */
	if(button == button_enc)
	{

		beep = true;
	}
	/* ====== BUTTONS =========== */
	if(button == button_1)
	{

		beep = true;
	}
	if(button == button_2)
	{

		beep = true;
	}
	if(button == button_3)
	{

		beep = true;
	}
	if(button == button_4)
	{
		
		beep = true;
	}
	if(beep)
	{
  		buzzer(beeps,1);
		buzzer_speed(30);
	}
}
void encoder_handler(void)
{
	GPIOB->ODR ^= GPIO_Pin_7; // toggle
	buzzer(beeps,1);
	buzzer_speed(3);
	
	
}
