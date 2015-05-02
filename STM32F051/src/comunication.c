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
uint8_t aTxStartMessage[] = "\n\rHallo\n\r";

bool send_temp(e_temp_sensor temp_sensor)
{
	char temp_out[] = {100,100,100,100,100,100,100,100,100,100};
	sprintf(temp_out, "%d\n\r", s_system.s_temp.MCU_temp);
	//HAL_UART_Transmit(&huart1, (uint8_t*)temp_out, 8,200);
	
	switch(temp_sensor)
	{
		case thermocouple_1:
			
		break;
		case thermocouple_2:
			
		break;
		case thermocouple_3:
			
		break;
		case thermocouple_4:
			
		break;
		case thermocouple_board:
			
		break;
		case MCU_temp:
			
		break;
	}
	
	

	return false;
}


void test_i2c(void)
{
  uint32_t I2C_TimeOut = I2C_TIMEOUT;

	
	I2C_TransferHandling(I2C1, I2C_ADDR, 3, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */

  while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)   
  {
    //if((LM75Timeout--) == 0) return LM75_TIMEOUT_UserCallback();
  }
  
  /* Send Register address */
  I2C_SendData(I2C1, (uint8_t)0x6);
  I2C_SendData(I2C1, (uint8_t)0x00);
  I2C_SendData(I2C1, (uint8_t)0x00);
  
  
//  	I2C_TransferHandling(I2C1, I2C_ADDR, 3, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);
//  
//  /* Wait until TXIS flag is set */

//  while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)   
//  {
//    //if((LM75Timeout--) == 0) return LM75_TIMEOUT_UserCallback();
//  }
//  
//  /* Send Register address */
//  I2C_SendData(I2C1, (uint8_t)0x2);
//  I2C_SendData(I2C1, (uint8_t)0xff);
//  I2C_SendData(I2C1, (uint8_t)0xff);
  
  
  
	
  /* Check if Temp sensor is ready for use */
  if ((I2C_GetFlagStatus(I2C1, I2C_ISR_NACKF) != RESET) || (I2C_TimeOut == 0))
  {      
    /* Clear NACKF and STOPF */
    I2C_ClearFlag(I2C1, I2C_ICR_NACKCF | I2C_ICR_STOPCF);
    
    //return ERROR;
  }
  else
  {
    /* Clear STOPF */
    I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
    
    //return SUCCESS;
  }    
}
