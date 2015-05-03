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

volatile uint16_t ADC_Output[2];
uint16_t temp[10] = {0};
uint8_t temp_counter = 0;

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
