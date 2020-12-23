#ifndef __INIT_H
#define __INIT_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define DAC_DHR12R1_ADDRESS		0x40007408
#define DAC_DHR8R1_ADDRESS		0x40007410
#define ADC1_DR_Address 		0x40012440
#define USART_RX_Address		0x40013824
#define USART_TX_Address		0x40013828


#define GPIO_EXPANDER_0_ADDRESS	(0x20<<1)
#define GPIO_EXPANDER_1_ADDRESS	(0x22<<1)
#define TEMP_TCN75A_ADDRESS		(0x48<<1)
#define ADC_EXT_ADDRESS			(0x68<<1)


/* Exported functions ------------------------------------------------------- */

void initialization(void);
#endif /* __INIT_H */




