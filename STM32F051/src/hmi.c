/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void encoder_cw(void);
void encoder_ccw(void);
/* Private functions ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
bool buttons_flags[5];
uint16_t display_block = 0;
uint16_t buttons_delay[5] = {0};
uint8_t buzzer_beeps_counter = 0;
uint16_t buzzer_beep_time_counter = 0;
uint16_t buzzer_beep_time = 0;
e_buzzer_mode buzzer_mode = off;

uint8_t display[4] = {1};
/*         ______
          /  6  /
         /7   5/
        /--4--/
       /3   1/
      /__2__/ O 8
*/
const uint8_t segments[4][8] = {
	{0x20,0x40,0x80,0x01,0x08,0x04,0x02,0x10},
	{0x04,0x02,0x01,0x80,0x10,0x20,0x40,0x08},
	{0x02,0x04,0x08,0x10,0x80,0x40,0x20,0x01},
	{0}
};
const uint8_t numbers[3][10] = {
	{0x11,0xD7,0x32,0x92,0xD4,0x98,0x18,0xD3,0x10,0x90},
	{0x88,0xEB,0x4C,0x49,0x2B,0x19,0x18,0xCB,0x08,0x09},
	{0x11,0x7d,0x23,0x29,0x4D,0x89,0x81,0x3D,0x01,0x09}
};


const struct s_encoder{
	GPIO_TypeDef * port_A;
	GPIO_TypeDef * port_B;
	uint32_t pin_A;
	uint32_t pin_B;
}encoder_hw = {
	.port_A = GPIOA,
	.port_B = GPIOB,
	.pin_A = GPIO_Pin_15,
	.pin_B = GPIO_Pin_3
};

int8_t enc_count = 0;
uint8_t enc_val = 0;




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
void buzzer_speed(uint16_t speed)
{
	buzzer_beep_time_counter = 0;
	buzzer_beep_time = speed; //time in [ms] for one beep
}

void button_handler(e_buttons button)
{
	bool beep = false;
	
	/* ====== ENCODER button =========== */
	if(button == button_enc && !buttons_delay[button_enc])
	{
		TIM3->CR1 ^= TIM_CR1_CEN;
		if(TIM3->CR1 & TIM_CR1_CEN)
		{
			GPIOB->BRR = GPIO_Pin_6;
			
			buzzer(beeps,2);
			buzzer_speed(80);
		}else
		{
			GPIOB->BSRR = GPIO_Pin_6;
			
			TIM3->CCR1 = 0;
			TIM3->CCR2 = 0;
			TIM3->CCR3 = 0;
			TIM3->CCR4 = 0;
			
			buzzer(beeps,3);
			buzzer_speed(80);
		}
		beep = false;
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
	buttons_delay[button] = button_press_delay;
}

void encoder_handler(void)
{
	static const int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

	enc_val = enc_val << 2;
	enc_val = enc_val | ((!!(encoder_hw.port_A->IDR & encoder_hw.pin_A) << 1) | (!!(encoder_hw.port_B->IDR & encoder_hw.pin_B)));

	enc_count += lookup_table[enc_val & 0xf];
	if(((enc_val & 0x3) == 3) && ((enc_count >= 4) | (enc_count <= -4)))
	{
		if(enc_count >= 4)
			encoder_cw();
		else 
			encoder_ccw();
		
		enc_count = 0;
	}
}
void encoder_cw(void)
{
	if(TIM3->CR1 & TIM_CR1_CEN)
	{
		display_block = 0;
		
		triac_modify_duty(top_heat,100);
		triac_modify_duty(bottom_heat,100);
		
		display_block = 3000;
		buzzer(beeps,1);
		buzzer_speed(3);
	}
}

void encoder_ccw(void)
{
	if(TIM3->CR1 & TIM_CR1_CEN)
	{
		display_block = 0;
		
		triac_modify_duty(top_heat,-100);
		triac_modify_duty(bottom_heat,-100);
		
		display_block = 3000;
		buzzer(beeps,1);
		buzzer_speed(3);
	}
}



/***************** DISPLAY  ****************/
void write_to_display(uint16_t number)
{
	uint8_t display_out = 3;
	if(!display_block)
	{
		display[0] = 0xff;
		display[1] = 0xff;
		display[2] = 0xff;
		if(!number)
			display[2] = numbers[2][0];
		while(number && display_out)
		{
			display[display_out-1] = numbers[display_out-1][number % 10];
			display_out--;
			number /= 10;
		}
		i2c_send_session(session_expander_set,GPIO_EXPANDER_0_ADDRESS);
		i2c_send_session(session_expander_set,GPIO_EXPANDER_1_ADDRESS);
	}
}
