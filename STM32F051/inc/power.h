#ifndef __POWER_H
#define __POWER_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
/* Exported types ------------------------------------------------------------*/
typedef enum
{
	triac_1 = 0,
	triac_2,
	triac_3,
	triac_4
}e_triacs;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint16_t triac_get_duty(e_triacs triac);
void triac_set_duty(e_triacs triac, uint8_t duty);
void triac_modify_duty(e_triacs triac, int8_t count);
#endif /* __POWER_H */
