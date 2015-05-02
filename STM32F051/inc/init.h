#ifndef __INIT_H
#define __INIT_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define DAC_DHR12R1_ADDRESS      0x40007408
#define DAC_DHR8R1_ADDRESS       0x40007410
#define ADC1_DR_Address          0x40012440
#define USART_RX_Address         0x40013824
#define USART_TX_Address         0x40013828

/* Exported functions ------------------------------------------------------- */

void initialization(void);
#endif /* __INIT_H */




