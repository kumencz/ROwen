#ifndef __POWER_H
#define __POWER_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void triac_set_duty(uint8_t triac_id, uint8_t duty);
#endif /* __POWER_H */
