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

volatile char *TX_Buffer;

volatile uint8_t received_string[MAX_MESSAGE_LENGHT+1];
bool next_message = true;


void USART_puts(USART_TypeDef* USARTx, volatile char *s)
{
//	if(next_message)
//	{
//		next_message = false;
//		TX_Buffer = s;
//		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
//	}
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

