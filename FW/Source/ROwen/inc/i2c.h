#ifndef __I2C_H
#define __I2C_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
	read,
	write
}e_rw;
typedef enum {
	receive,
	transmit
}e_direction;

typedef enum {
	session_expander_config = 1,
	session_expander_set,
	session_config_tcn75_temp,
	session_get_tcn75_temp,
	session_get_ext_ADC_voltages
}e_i2c_session;

extern struct i2c_sess {
	e_rw rw;
	uint8_t byte_count;
	uint8_t param_count;
	void (*session_data)(uint8_t session_id, e_direction direction);

}i2c_sessions[32];

extern struct i2c_curr_sess {
	uint8_t id;
	bool running;
	uint8_t params_transfered;
	uint8_t bytes_transfered;
	uint8_t dest_address;
}i2c_curr_session;

extern struct i2c_sess_buff {
	e_i2c_session session_id;
	uint8_t slave_address;
}i2c_sessions_buffer[21];


/* Exported constants --------------------------------------------------------*/
extern uint8_t parameters_master[0x0A];
extern uint8_t transfer_data_master[0x0A];
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
bool i2c_send_session(e_i2c_session session_id, uint8_t slave_address);
void i2c_process_session(void);
void Define_I2C_Sessions(void);

void expander_config(uint8_t session_id, e_direction direction);
void expander_set(uint8_t session_id, e_direction direction);
void config_tcn75_temp(uint8_t session_id, e_direction direction);
void get_tcn75_temp(uint8_t session_id, e_direction direction);
void get_ext_ADC_voltages(uint8_t session_id, e_direction direction);
#endif /* __I2C_H */
