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
extern uint16_t buzzer_beep_time;
extern uint16_t buzzer_beep_time_counter;
extern uint16_t buttons_delay[5];
extern uint16_t display_block;

extern uint8_t display[4];
/* Exported macro ------------------------------------------------------------*/
#define button_press_delay			500


/* Exported functions ------------------------------------------------------- */
void buzzer_speed(uint16_t speed);
void buzzer(e_buzzer_mode b_mode, uint8_t beep_count);
void button_handler(e_buttons button);
void encoder_handler(void);
void write_to_display(uint8_t byte, uint8_t display_id);
void number_to_display(float number_in, uint8_t dot_pos);
void text_to_display(char text[3]);
void set_i2c_led(uint8_t led_id, bool state);
void led_bargraph_set(uint8_t number);
#endif /* __HMI_H */


