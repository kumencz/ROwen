#ifndef __COMUNICATION_H
#define __COMUNICATION_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
/* Exported types ------------------------------------------------------------*/
typedef enum
{
	thermocouple_1,
	thermocouple_2,
	thermocouple_3,
	thermocouple_4,
	thermocouple_board,
	MCU_temp
}e_temp_sensor;
/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void send_temps(void);



typedef enum
{
  LM75_OK = 0,
  LM75_FAIL
}LM75_Status_TypDef;

#define LM75_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define LM75_LONG_TIMEOUT         ((uint32_t)(10 * LM75_FLAG_TIMEOUT))    

#define I2C_TIMEOUT         ((uint32_t)0x3FFFF) /*!< I2C Time out */
#define I2C_ADDR		0x20<<1
#endif /* __COMUNICATION_H */
