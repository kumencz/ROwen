#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "comp.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"
#include "dma.h"
#include "hmi.h"
#include "time.h"
#include "power.h"
#include "comunication.h"
#include "control.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define ADC1_DR_Address			0x40012440

/* Exported functions ------------------------------------------------------- */
void init_all(void);

void ADC_read(void);
#endif /* __MAIN_H */
