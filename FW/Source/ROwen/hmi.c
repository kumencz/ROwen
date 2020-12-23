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
const uint8_t letters[3][26] = {
/*   A,   b,   C,   d,   E,   F,   g,   H,   I,   J,   K,   L,   M,   n,   O,   P,   q,   r,   S,   t,   U,   v,   w,   x,   y,   Z*/
	{0x50,0x1C,0x39,0x16,0x38,0x78,0x90,0x54,0x7D,0x17,0x44,0x3D,0x5B,0x5E,0x11,0x70,0xD0,0x7E,0x98,0x3C,0x15,0x1F,0x00,0x00,0x94,0x32},
	{0x0A,0x38,0x9C,0x68,0x1C,0x1E,0x09,0x2A,0xBE,0xE8,0x22,0xBC,0xDA,0x7A,0x88,0x0E,0x0B,0x7E,0x19,0x3C,0xA8,0xF8,0x00,0x00,0x29,0x4C},
	{0x05,0xC1,0x93,0x61,0x83,0x87,0x09,0x45,0xD7,0x71,0x44,0xD3,0xB5,0xE5,0x11,0x07,0x0D,0xE7,0x89,0xC3,0x51,0xF1,0x00,0x00,0x49,0x23}
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
	if(button == button_enc)
	{
		mode_selector(enter_action);
		beep = true;
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
		mode_selector(quit_action);
		buzzer(beeps,2);
		buzzer_speed(50);
		beep = true;
		
	}
	if(button == button_4)
	{
		if(mode_current == 10)
		{
			TIM3->CR1 ^= TIM_CR1_CEN;
			if(TIM3->CR1 & TIM_CR1_CEN)
			{
				/*Turn lights on */
				GPIOB->BRR = GPIO_Pin_7;
				triac_set_duty(triac_3,100);
				triac_set_duty(triac_1,0);
				triac_set_duty(triac_2,0);
				triac_set_duty(triac_4,0);

				buzzer(beeps,2);
				buzzer_speed(80);
			}else
			{
				GPIOB->BSRR = GPIO_Pin_7;
				triac_set_duty(triac_1,0);
				triac_set_duty(triac_2,0);
				triac_set_duty(triac_3,0);
				triac_set_duty(triac_4,0);

				buzzer(beeps,3);
				buzzer_speed(80);
			}
			beep = false;
		}else
		{
			beep = true;
		}
	}
	if(beep)
	{
		buzzer(beeps,1);
		buzzer_speed(30);
	}
	buttons_delay[button] = button_press_delay;		// set min delay between button presses
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
	if(mode_showed != 0)
	{
		mode_selector(next_action);
	}else if(mode_current == 16)
	{
		display_block = 0;
		
		triac_modify_duty(triac_4,10);
		number_to_display(triac_get_duty(triac_4),0);

		display_block = 3000;
	}else if(mode_current == 2)
	{
		display_block = 0;
		
		triac_modify_duty(triac_1,10);
		triac_modify_duty(triac_2,10);
		number_to_display(triac_get_duty(triac_1),0);

		display_block = 3000;
	}
	buzzer(beeps,1);
	buzzer_speed(3);
}
void encoder_ccw(void)
{
	if(mode_showed != 0)
	{
		mode_selector(previous_action);
	}else if(mode_current == 16)
	{
		display_block = 0;
		
		triac_modify_duty(triac_4,-10);
		number_to_display(triac_get_duty(triac_4),0);

		display_block = 3000;
	}else if(mode_current == 2)
	{
		display_block = 0;
		
		triac_modify_duty(triac_1,-10);
		triac_modify_duty(triac_2,-10);
		number_to_display(triac_get_duty(triac_1),0);

		display_block = 3000;
	}
	buzzer(beeps,1);
	buzzer_speed(1);
}


/***************** DISPLAY  ****************/
void write_buffer_to_display(void)
{
	i2c_send_session(session_expander_set,GPIO_EXPANDER_0_ADDRESS);
	i2c_send_session(session_expander_set,GPIO_EXPANDER_1_ADDRESS);
}
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
void text_to_display(char text[3])
{
	for(int i = 0; i < 3; i++)
	{
		/* NUMBERS */
		if(text[i] >= 48 && text[i] <= 57)
		{
			display[i] = numbers[i][text[i]-48];
		}
		/* Upper case LETTERS */
		else if(text[i] >= 65 && text[i] <= 90)
		{
			display[i] = letters[i][text[i]-65];
		}
		/* Lower case LETTERS */
		else if(text[i] >= 97 && text[i] <= 122)
		{
			display[i] = letters[i][text[i]-97];
		}else if(text[i] == ' ')
		{
			display[i] = 0xFF;
		}else if(text[i] == '-')
		{
			display[i] = ~segments[i][3];
		}else
		{
			display[i] = 0xFF;
		}
	}
	write_buffer_to_display();
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
