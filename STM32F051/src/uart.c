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

uint8_t RX_Buffer[5][MAX_MESSAGE_LENGHT];
uint8_t RX_r_pointer = 0;
uint8_t RX_w_pointer = 0;

uint8_t TX_Buffer[5][50];
uint8_t TX_r_pointer = 0;
uint8_t TX_w_pointer = 0;

volatile uint8_t received_string[MAX_MESSAGE_LENGHT+1];

void USART_puts(USART_TypeDef* USARTx, volatile char *s)
{
	while(*s){
		// wait until data register is empty
		while( !(USARTx->ISR & USART_FLAG_TC) );
		USART_SendData(USARTx, *s);
		*s++;
	}
}

void uart_parse(uint8_t * string)
{
	
	
}

