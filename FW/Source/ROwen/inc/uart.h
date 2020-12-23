#ifndef __UART_H
#define __UART_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define MAX_MESSAGE_LENGHT		150
/* Exported constants --------------------------------------------------------*/
extern uint8_t RX_Buffer[5][MAX_MESSAGE_LENGHT];
extern uint8_t RX_r_pointer;
extern uint8_t RX_w_pointer;

extern volatile char* TX_Buffer;
extern volatile char received_string[MAX_MESSAGE_LENGHT+1];
extern bool next_message;
/* Exported functions ------------------------------------------------------- */
void USART_puts(USART_TypeDef* USARTx, volatile char *s);
void uart_parse(char* string);
#endif /* __UART_H */
