#ifndef __HMI_H
#define __HMI_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
	off,
	beep_const,
	strobo,
	beeps
}e_buzzer_mode;

typedef enum {
	button_1,
	button_2,
	button_3,
	button_4,
	button_enc
}e_buttons;


/* Exported constants --------------------------------------------------------*/
extern e_buzzer_mode buzzer_mode;
extern uint8_t buzzer_beeps_counter;
extern uint8_t buzzer_beep_time;
extern uint16_t buzzer_beep_time_counter;
/* Exported macro ------------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */
bool check_button(e_buttons button);
void buzzer_speed(uint8_t speed);
void buzzer(e_buzzer_mode b_mode, uint8_t beep_count);
#endif /* __HMI_H */
