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

#define TS_CAL1     (*((uint16_t*) 0x1FFFF7B8))               // TS_CAL1 = 1727
#define TS_CAL2     (*((uint16_t*) 0x1FFFF7C2))               // TS_CAL2 = 1308
#define VREFINT_CAL (*((uint16_t*) 0x1FFFF7BA))
#define AVG_SLOPE   (float)((TS_CAL1 - TS_CAL2)/80.0f) 

struct sys s_system;
struct h_ramp ramp[][10]={
{
{.duration = 20, 	.final_temp = 25},
{.duration = 40, 	.final_temp = 50},
{.duration = 40, 	.final_temp = 80},
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
/* ID = 0  */ {.text = "---", .parent_id = 0xFF,.start_func = NULL, .quit_func = NULL},
/* ID = 1  */ {.text = "Prf", .parent_id = 0, 	.start_func = NULL, .quit_func = NULL},
/* ID = 2  */ {.text = "Man", .parent_id = 0, 	.start_func = NULL, .quit_func = NULL},
/* ID = 3  */ {.text = " PC", .parent_id = 0, 	.start_func = NULL, .quit_func = NULL},

/* ID = 4  */ {.text = "Pb0", .parent_id = 1},
/* ID = 5  */ {.text = "Pb1", .parent_id = 1},
/* ID = 6  */ {.text = "Pb2", .parent_id = 1},
/* ID = 7  */ {.text = "SAC", .parent_id = 1},
/* ID = 8  */ {.text = "PbF", .parent_id = 1},

/* ID = 9  */ {.text = "Tep", .parent_id = 2},
/* ID = 10 */ {.text = "Dut", .parent_id = 2},
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
			mode_current = menu_entry[mode_current].parent_id;
			mode_showed = mode_get_child(mode_current,0,true);
			text_to_display(menu_entry[mode_showed].text);
			if(menu_entry[mode_current].quit_func != NULL)
			{
				menu_entry[mode_current].quit_func(mode_current);
			}
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

