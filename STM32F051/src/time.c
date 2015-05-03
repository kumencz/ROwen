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
uint32_t real_time = 0;		//presnost = 0.1s

uint8_t TIM_10MS_COUNTER;
uint16_t TIM_100MS_COUNTER;
uint16_t TIM_1000MS_COUNTER;

uint8_t TIM_1MS_FLAG;
uint8_t TIM_10MS_FLAG;
uint8_t TIM_100MS_FLAG;
uint8_t TIM_1000MS_FLAG;

uint8_t test_counter = 0;
uint32_t speed_counter = 0;
uint32_t speed = 0;
static volatile uint32_t TimingDelay;

inline void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

inline void Delay_tick(__IO uint32_t nCount)
{
	while(nCount--);
}
inline void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
    TimingDelay--;
}

void Period_timer_increment(void) //called each 1ms
{
		TimingDelay_Decrement();
		TIM_1MS_FLAG = 1;
		TIM_10MS_COUNTER++;	
	if (TIM_10MS_COUNTER >= 10)
	{
		TIM_10MS_COUNTER = 0;
		TIM_10MS_FLAG = 1;
		TIM_100MS_COUNTER += 10;
	}				
	if (TIM_100MS_COUNTER >= 100)
	{
		TIM_100MS_COUNTER = 0;
		TIM_100MS_FLAG = 1;
		TIM_1000MS_COUNTER += 100;
	}		
	if (TIM_1000MS_COUNTER >= 1000)
	{
		TIM_1000MS_COUNTER = 0;
		TIM_1000MS_FLAG = 1;
	}
}

void period_time_check_flags(void)
{
	if (TIM_1MS_FLAG)
	{
		tim_1ms_loop();
		TIM_1MS_FLAG = 0;
	}
	if (TIM_10MS_FLAG)
	{
		tim_10ms_loop();
		TIM_10MS_FLAG = 0;
	}
	if (TIM_100MS_FLAG)
	{
		tim_100ms_loop();
		TIM_100MS_FLAG = 0;
	}
	if (TIM_1000MS_FLAG)
	{
		tim_1000ms_loop();
		TIM_1000MS_FLAG = 0;
	}
}

void tim_1ms_loop(void)
{
	for(int i = 0; i <= 4; i++)
	{
		if(buttons_delay[i] > 0)
			buttons_delay[i]--;
	}
	
	if(buzzer_mode == strobo || buzzer_mode == beeps)
	{
		if(buzzer_beep_time_counter++ >= buzzer_beep_time)
		{
			buzzer_beep_time_counter = 0;
			
			
			if(buzzer_mode == strobo)
			{
				if(buzzer_beeps_counter)
				{
					GPIO_ResetBits(GPIOB, GPIO_Pin_15);
					buzzer_beeps_counter--;
				}else
				{
					GPIO_SetBits(GPIOB, GPIO_Pin_15);
					buzzer_beeps_counter++;
				}
			}else if(buzzer_mode == beeps && buzzer_beeps_counter)
			{
				if(buzzer_beeps_counter%2 == 0)
				{
					GPIO_ResetBits(GPIOB, GPIO_Pin_15);
				}
				else
				{
					GPIO_SetBits(GPIOB, GPIO_Pin_15);
				}
				buzzer_beeps_counter--;
			}
		}
	}
}
void tim_10ms_loop(void)
{
	i2c_process_session();
	
}

void tim_100ms_loop(void)
{ 
	real_time++;
	ADC_read();
	i2c_send_session(4,TEMP_TCN75A_ADDRESS); //get temp from TCN75A
	send_temps();
}

void tim_1000ms_loop(void)
{
//	test_counter += 5;
//	if(test_counter > 100) test_counter=0;
//	triac_set_duty(1,test_counter);
//	triac_set_duty(2,100-test_counter);
	
	
	GPIOB->ODR ^= GPIO_Pin_7;

	write_char("B",1);

	/* SPEED meter */
	speed = speed_counter;
	speed_counter = 0;
}
