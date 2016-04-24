/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void encoder_cw(void);
void encoder_ccw(void);
void write_buffer_to_display(void);
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

uint8_t display[4] = {0xFF,0xFF,0xFF,0xFF};
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
			/*Turn lights on */
			GPIOB->BRR = GPIO_Pin_7;
			triac_set_duty(triac_3,100);
			triac_set_duty(triac_4,100);
			TIM3->CCR3 = 0;
			TIM3->CCR4 = 0;
			
			buzzer(beeps,2);
			buzzer_speed(80);
		}else
		{
			GPIOB->BSRR = GPIO_Pin_7;
			
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
		if(triac_get_duty(triac_3) != 0)
		{
			triac_set_duty(triac_3,0);
		}else
		{
			triac_set_duty(triac_3,100);
		}
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
		
		triac_modify_duty(triac_1,10);
		triac_modify_duty(triac_2,10);
		number_to_display(triac_get_duty(triac_1),0);

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
		
		triac_modify_duty(triac_1,-10);
		triac_modify_duty(triac_2,-10);
		number_to_display(triac_get_duty(triac_1),0);

		display_block = 3000;
		buzzer(beeps,1);
		buzzer_speed(3);
	}
}

void write_buffer_to_display(void)
{
	i2c_send_session(session_expander_set,GPIO_EXPANDER_0_ADDRESS);
	i2c_send_session(session_expander_set,GPIO_EXPANDER_1_ADDRESS);
}
/***************** DISPLAY  ****************/
void write_to_display(uint8_t byte, uint8_t display_id)
{
	display[display_id] = byte;
	write_buffer_to_display();
}
void number_to_display(float number_in, uint8_t dot_pos)
{
	/* Show precision, as "dot_pos", not implemented yet!!! */
	if(!display_block)
	{
		if(number_in >= 1000)
			number_in = 999;
		uint32_t number = number_in * 100;
		uint8_t count = 0;
		uint8_t disp_buff[5];
		display[0] = 0xFF;
		display[1] = 0xFF;
		display[2] = 0xFF;

		while(number)
		{
			disp_buff[count] = (uint16_t) number % 10;
			number /= 10;
			count++;
		}

		if(count == 1 || count == 2 || count == 3 || dot_pos == 1)
			display[0] = ~segments[0][7];
		else if(count == 4 || dot_pos == 2)
			display[1] = ~segments[1][7];

		while(count < 3)
		{
			disp_buff[count] = 0;
			count++;
		}
		if(!number_in)
		{
			display[2] = numbers[0][0];
		}else
		{
			display[0] &= numbers[0][disp_buff[count-1]];
			display[1] &= numbers[1][disp_buff[count-2]];
			display[2] &= numbers[2][disp_buff[count-3]];
		}
		write_buffer_to_display();
	}
}
/***************** TOP LEDS  ****************/
void set_i2c_led(uint8_t led_id, bool state)
{
	static const uint8_t led_matrix[7] = {6,5,4,3,2,1,0};
	if(state)
	{
		display[3] &= ~(1<<led_matrix[led_id]);
		
	}else
	{
		display[3] |= (1<<led_matrix[led_id]);
	}
	write_buffer_to_display();
}
void led_bargraph_set(uint8_t number)
{
	for(int i = 0; i < number; i++)
	{
		set_i2c_led(i, ENABLE);
	}
	for(int i = number; i < 7; i++)
	{
		set_i2c_led(i, DISABLE);
	}
}
