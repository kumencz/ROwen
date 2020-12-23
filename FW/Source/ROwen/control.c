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
void start_ramp_0(uint8_t menu_id);
void start_ramp_1(uint8_t menu_id);
void start_ramp_2(uint8_t menu_id);
void start_ramp_3(uint8_t menu_id);
void start_ramp_4(uint8_t menu_id);
void start_ramp_5(uint8_t menu_id);
void start_ramp_6(uint8_t menu_id);
void start_ramp_7(uint8_t menu_id);
void start_ramp_8(uint8_t menu_id);
void start_ramp_9(uint8_t menu_id);
void stop_ramp(uint8_t menu_id);
void cool_down(uint8_t menu_id);
void cool_down_stop(uint8_t menu_id);

#define TS_CAL1     (*((uint16_t*) 0x1FFFF7B8))               // TS_CAL1 = 1727
#define TS_CAL2     (*((uint16_t*) 0x1FFFF7C2))               // TS_CAL2 = 1308
#define VREFINT_CAL (*((uint16_t*) 0x1FFFF7BA))
#define AVG_SLOPE   (float)((TS_CAL1 - TS_CAL2)/80.0f) 

struct h_curr_ramp curr_ramp;

struct sys s_system;
struct h_ramp ramp_profile[][10]={
{
{.duration = 40, 	.final_temp = 35},
{.duration = 100, 	.final_temp = 130},
{.duration = 140, 	.final_temp = 150},
{.duration = 10, 	.final_temp = 175},
{.duration = 30, 	.final_temp = 225},
{.duration = 10, 	.final_temp = 220},
{.duration = 80, 	.final_temp = 50},
{.duration = 90, 	.final_temp = 30},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0}},
{
{.duration = 30, 	.final_temp = 40},
{.duration = 90, 	.final_temp = 125},
{.duration = 90, 	.final_temp = 175},
{.duration = 50, 	.final_temp = 225},
{.duration = 10, 	.final_temp = 225},
{.duration = 50, 	.final_temp = 183},
{.duration = 80, 	.final_temp = 40},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0}},
{
{.duration = 50, 	.final_temp = 50},
{.duration = 90, 	.final_temp = 125},
{.duration = 90, 	.final_temp = 175},
{.duration = 50, 	.final_temp = 225},
{.duration = 10, 	.final_temp = 225},
{.duration = 50, 	.final_temp = 183},
{.duration = 80, 	.final_temp = 40},
{.duration = 60, 	.final_temp = 35},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0}},
{
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0}},
{
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0}},
{
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0}},
{
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0}},
{
{.duration = 50, 	.final_temp = 60},
{.duration = 90, 	.final_temp = 150},
{.duration = 30, 	.final_temp = 170},
{.duration = 50, 	.final_temp = 220},
{.duration = 40, 	.final_temp = 260},
{.duration = 15, 	.final_temp = 260},
{.duration = 150, 	.final_temp = 50},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0}},
{
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0},
{.duration = 0, 	.final_temp = 0}}
};

uint8_t mode_current = 0;
uint8_t mode_showed = 0;

volatile uint16_t ADC_Output[2];
uint16_t temp[10] = {0};
uint8_t temp_counter = 0;

struct s_menu_entry{
	char 		text[3];
	uint8_t 	parent_id;
	void (* start_func)(uint8_t menu_id);
	void (* quit_func)(uint8_t menu_id);
}menu_entry[]={
/* ID = 0  */ {.text = "---", .parent_id = 0, 	.start_func = NULL, .quit_func = NULL},
/* ID = 1  */ {.text = "Prf", .parent_id = 0, 	.start_func = NULL, .quit_func = NULL},
/* ID = 2  */ {.text = "Man", .parent_id = 0, 	.start_func = NULL, .quit_func = NULL},
/* ID = 3  */ {.text = " PC", .parent_id = 0, 	.start_func = NULL, .quit_func = NULL},

/* ID = 4  */ {.text = "Pb1", .parent_id = 1,	.start_func = start_ramp_0, .quit_func = stop_ramp},
/* ID = 5  */ {.text = "Pb2", .parent_id = 1,	.start_func = start_ramp_1, .quit_func = stop_ramp},
/* ID = 6  */ {.text = "Pb3", .parent_id = 1,	.start_func = start_ramp_2, .quit_func = stop_ramp},
/* ID = 7  */ {.text = "Pb4", .parent_id = 1,	.start_func = start_ramp_3, .quit_func = stop_ramp},
/* ID = 8  */ {.text = "Pb5", .parent_id = 1,	.start_func = start_ramp_4, .quit_func = stop_ramp},
/* ID = 9  */ {.text = " CU", .parent_id = 1,	.start_func = start_ramp_5, .quit_func = stop_ramp},
/* ID = 10 */ {.text = "SN1", .parent_id = 1,	.start_func = start_ramp_6, .quit_func = stop_ramp},
/* ID = 11 */ {.text = "SAC", .parent_id = 1,	.start_func = start_ramp_7, .quit_func = stop_ramp},
/* ID = 12 */ {.text = " SN", .parent_id = 1,	.start_func = start_ramp_8, .quit_func = stop_ramp},
/* ID = 13 */ {.text = " Pb", .parent_id = 1,	.start_func = start_ramp_9, .quit_func = stop_ramp},

/* ID = 14 */ {.text = "Tep", .parent_id = 2, 	.start_func = NULL, .quit_func = NULL},
/* ID = 15 */ {.text = "Dut", .parent_id = 2, 	.start_func = NULL, .quit_func = NULL},

/* ID = 16 */ {.text = "Fan", .parent_id = 0, 	.start_func = cool_down, .quit_func = cool_down_stop},
};

void ADC_read(void)
{
	/* MCU voltage */
	s_system.s_power.mcu_voltage = 3300.0f * VREFINT_CAL / ADC_Output[1];
	
	/* Temperature */
	temp[temp_counter] = (uint16_t)((((((ADC_Output[0] / 3300.0f) * s_system.s_power.mcu_voltage) - TS_CAL1) / (-AVG_SLOPE)) + 30)*10);
	s_system.s_temp.MCU_temp = (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7] + temp[8] + temp[9])/10;
	if(++temp_counter > 9)
		temp_counter = 0;
}

void mode_selector(e_action action)
{
	switch(action)
	{
		case next_action:
			mode_showed = mode_get_child(mode_current,mode_showed,true);
			text_to_display(menu_entry[mode_showed].text);
			break;
		case previous_action:
			mode_showed = mode_get_child(mode_current,mode_showed,false);
			text_to_display(menu_entry[mode_showed].text);
			break;
		case enter_action:
			mode_current = mode_showed;
			mode_showed = mode_get_child(mode_current,0,true);
			text_to_display(menu_entry[mode_showed].text);
			if(menu_entry[mode_current].start_func != NULL)
			{
				menu_entry[mode_current].start_func(mode_current);
			}
			break;
		case quit_action:
			if(menu_entry[mode_current].quit_func != NULL)
			{
				menu_entry[mode_current].quit_func(mode_current);
			}
			mode_current = menu_entry[mode_current].parent_id;
			mode_showed = mode_get_child(mode_current,0,true);
			text_to_display(menu_entry[mode_showed].text);
			break;
	}
}
uint8_t mode_get_child(uint8_t parrent_id, uint8_t start_id, bool upcount)
{
	uint8_t end_child = 0;
		if(upcount)
		{
			for(int i = 0; i < (sizeof(menu_entry)/sizeof(menu_entry[0])); i++)
			{
				if(menu_entry[i].parent_id == parrent_id && i > start_id)
				{
					return i;
				}else if(menu_entry[i].parent_id == parrent_id && !end_child)
				{
					end_child = i;
				}
			}
		}else
		{
			for(int i = (sizeof(menu_entry)/sizeof(menu_entry[0])); i > 0 ; i--)
			{
				if(menu_entry[i].parent_id == parrent_id && i < start_id)
				{
					return i;
				}else if(menu_entry[i].parent_id == parrent_id && !end_child)
				{
					end_child = i;
				}
			}
		}
	return end_child;
}
int16_t prevErr;

float Kp = 20;
float Ki = 0.003f;
float Kd = 40.0f;

float regErr;
float P_term, I_term, D_term;
int32_t duty;

int16_t PID_controller(uint16_t setPoint, uint16_t feedback)
{
	int16_t const max = 100;
	int16_t const min = -100;

	regErr = setPoint - feedback;

	P_term  = regErr;   //Current error
	I_term += prevErr;  //Sum of previous errors
	D_term  = regErr - prevErr;  //Difference with previous error

	duty = (Kp*P_term + Ki*I_term + Kd*D_term);

	if(duty > max)
		duty = max;
	if(duty < min)
		duty = min;
	prevErr = (int16_t)regErr;

	return duty;
}

uint16_t ramp_get_temp(struct h_curr_ramp *ramp)
{
	if(ramp->current_step)
		ramp->step_start_temp = ramp->current_ramp[ramp->current_step-1].final_temp;
	return ramp->step_start_temp + (((ramp->current_ramp[ramp->current_step].final_temp - ramp->step_start_temp) * ramp->time_in_step)/(ramp->current_ramp[ramp->current_step].duration * 1000));
}
void init_ramp_start(uint8_t ramp_id)
{
	curr_ramp.running = false;
	curr_ramp.current_ramp = &ramp_profile[ramp_id][0];
	if(s_system.s_temp.reflow_temp < curr_ramp.current_ramp[0].final_temp)
	{
		curr_ramp.running = true;
		curr_ramp.current_step = 0;
		curr_ramp.step_start_temp = s_system.s_temp.reflow_temp;
		curr_ramp.time_in_step = 0;
		triac_set_duty(triac_3,100);	//light on
	}else
	{
		curr_ramp.running = false;
		text_to_display("err");
		buzzer(beeps,3);
		buzzer_speed(80);
	}
}


void start_ramp_0(uint8_t menu_id)
{
	init_ramp_start(0);
}
void start_ramp_1(uint8_t menu_id)
{
	init_ramp_start(1);
}
void start_ramp_2(uint8_t menu_id)
{
	init_ramp_start(2);
}
void start_ramp_3(uint8_t menu_id)
{
	init_ramp_start(3);
}
void start_ramp_4(uint8_t menu_id)
{
	init_ramp_start(4);
}
void start_ramp_5(uint8_t menu_id)
{
	init_ramp_start(5);
}
void start_ramp_6(uint8_t menu_id)
{
	init_ramp_start(6);
}
void start_ramp_7(uint8_t menu_id)
{
	init_ramp_start(7);
}
void start_ramp_8(uint8_t menu_id)
{
	init_ramp_start(8);
}
void start_ramp_9(uint8_t menu_id)
{
	init_ramp_start(9);
}
void stop_ramp(uint8_t menu_id)
{
	curr_ramp.running = false;
	triac_set_duty(triac_1,0);
	triac_set_duty(triac_2,0);
	triac_set_duty(triac_3,0);	//light off
	triac_set_duty(triac_4,0);	//fan off
}
void cool_down(uint8_t menu_id)
{
	triac_set_duty(triac_4,100);
}
void cool_down_stop(uint8_t menu_id)
{
	triac_set_duty(triac_4,0);
}
