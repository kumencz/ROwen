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
extern uint16_t buttons_delay[5];

extern uint8_t display[4];
extern const uint8_t charset[4][255];
/* Exported macro ------------------------------------------------------------*/
#define button_press_delay			500


/* Exported functions ------------------------------------------------------- */
void buzzer_speed(uint8_t speed);
void buzzer(e_buzzer_mode b_mode, uint8_t beep_count);
void button_handler(e_buttons button);
void encoder_handler(void);
void write_char(char* character, uint8_t display_id);
#endif /* __HMI_H */


