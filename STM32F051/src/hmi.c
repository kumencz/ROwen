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
bool buttons_flags[5];
uint16_t buttons_delay[5] = {0};
uint8_t buzzer_beeps_counter = 0;
uint16_t buzzer_beep_time_counter = 0;
uint8_t buzzer_beep_time = 0;
e_buzzer_mode buzzer_mode = off;


const uint8_t segments[4][8] = {
{0x20,0x40,0x80,0x01,0x01,0x01,0x01,0x10}, // doplnit!!!
{0x04,0x02,0x01,0x80,0x10,0x20,0x40,0x08},
{0x02,0x04,0x08,0x10,0x80,0x40,0x20,0x01},
{0}};
uint8_t display[4];

const uint8_t charset[4][255]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0x10,//65->A
0x09 //66->B
},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0x0A,	//65->A
	0x38,	//66->B
	0x19,	//67->C
	0x68,	//68->D
	0x1C,	//69->E
	0x1E,	//70->F
	0x98,	//71->G
	0x2A,	//72->H
	
	0x0A,	//73->I
	0x38,	//74->J
	0x19,	//75->K
	0x68,	//76->L
	0x1C,	//77->M
	0x1E,	//78->N
	0x98,	//80->O
	0x2A,	//81->P
	
	0x0A,	//73->Q
	0x38,	//74->R
	0x19,	//75->S
	0x68,	//76->T
	0x1C,	//77->U
	0x1E,	//78->V
	0x98,	//80->W
	0x2A,	//81->X
	
	0x98,	//80->Y
	0x2A,	//81->Z



},{0},{0}
};
/*
45	2d	-

48	30	0
49	31	1
50	32	2
51	33	3
52	34	4
53	35	5
54	36	6
55	37	7
56	38	8
57	39	9


65	41	A
66	42	B
67	43	C
68	44	D
69	45	E
70	46	F
71	47	G
72	48	H
73	49	I
74	4a	J
75	4b	K
76	4c	L
77	4d	M
78	4e	N
79	4f	O
80	50	P
81	51	Q
82	52	R
83	53	S
84	54	T
85	55	U
86	56	V
87	57	W
88	58	X
89	59	Y
90	5a	Z


97	61	a
98	62	b
99	63	c
100	64	d
101	65	e
102	66	f
103	67	g
104	68	h
105	69	i
106	6a	j
107	6b	k
108	6c	l
109	6d	m
110	6e	n
111	6f	o
112	70	p
113	71	q
114	72	r
115	73	s
116	74	t
117	75	u
118	76	v
119	77	w
120	78	x
121	79	y
122	7a	z
*/


void buzzer(e_buzzer_mode b_mode, uint8_t beep_count)
{
	buzzer_mode = b_mode;
	switch(buzzer_mode)
	{
		case off:
			GPIO_SetBits(GPIOB, GPIO_Pin_15);
		break;
		case beep_const:
			GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		break;
		case strobo:
			buzzer_beeps_counter = 1;
		break;
		case beeps:
			buzzer_beeps_counter = beep_count*2;
		break;
	}
}
void buzzer_speed(uint8_t speed)
{
	buzzer_beep_time_counter = 0;
	buzzer_beep_time = speed; //time in [ms] for one beep
}

void button_handler(e_buttons button)
{
	bool beep = false;
	
	buttons_delay[button] = button_press_delay;
	
	/* ====== ENCODER button =========== */
	if(button == button_enc)
	{

		beep = true;
	}
	/* ====== BUTTONS =========== */
	if(button == button_1)
	{

		beep = true;
	}
	if(button == button_2)
	{

		beep = true;
	}
	if(button == button_3)
	{

		beep = true;
	}
	if(button == button_4)
	{
		
		beep = true;
	}
	if(beep)
	{
  		buzzer(beeps,1);
		buzzer_speed(30);
	}
}
void encoder_handler(void)
{
	GPIOB->ODR ^= GPIO_Pin_7; // toggle
	buzzer(beeps,1);
	buzzer_speed(3);
	
	
}


/***************** DISPLAY  ****************/
void write_char(char* character, uint8_t display_id)
{
	display[display_id] = charset[display_id][(uint8_t)*character];
	
	i2c_send_session(2,GPIO_EXPANDER_0_ADDRESS);
	i2c_send_session(2,GPIO_EXPANDER_1_ADDRESS);
}
