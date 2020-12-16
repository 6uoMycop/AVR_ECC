/*
 * main.c
 *
 * Created: 12/11/2020 2:18:44 PM
 *  Author: Аркадий
 */ 
1
#include <xc.h>
#ifndef F_CPU
#define F_CPU 1000000UL // 16 MHz clock speed
#endif
#include <util/delay.h>

#include <avr/io.h>
#include <util/delay.h>
#include "main_init.h"
#include "i2c.h"
#include "exponentiation.h"

uint8_t buffer_index = 0;
uint8_t buffer[BUF_BYTES * 8] = { 0 }; // строка char (+'0')
TYPE bin_buffer = 0;

void print_message(const uint8_t *msg, const uint8_t *next_msg, const uint8_t next_len)
{
	str_out(msg, NULL);
	_delay_ms(MSG_DELAY);
	str_out(next_msg, next_len);
}

void init(void)
{
	// Кнопки
	BTNS_DDR =	0x00;		// Input
	BTNS_PORT =	0b00111111;
	
	// Таймер
	TCCR1B =	0b00000010;	// clk/8
	
	// Экран
	init_i2c();
	
	
	print_message("Started", "----", NULL);
}

uint8_t insert_bit(uint8_t bit)
{
	if (buffer_index < BUF_BYTES * 8)
	{
		buffer[buffer_index] = bit + '0';
		buffer_index++;
		return 0;
	}
	return 1;
}

void create_number()
{
	bin_buffer = 0;
	for (uint8_t i = 0; i < BUF_BYTES * 8; i++)
	{
		bin_buffer |= 1 << i;
	}
}

//
// Обработчики кнопок
//

void f_1(void)
{
	if (insert_bit(1) == 0);
	{
		str_out(buffer, buffer_index);
	}
}

void f_0(void)
{
	if (buffer_index == 0)
	{
		return;
	}
	if (insert_bit(0) == 0);
	{
		str_out(buffer, buffer_index);
	}
}

// 16 bit max
void f_rnd(void)
{
	uint16_t t = TCNT1;
	uint8_t bit = 0;
	buffer_index = 0;
	for (uint8_t i = 0; i < 16; i++)
	{
		bit = (uint8_t)((t >> i) & 1);
		if (bit == 0 && buffer_index == 0)
		{
			continue;
		}
		
		buffer[i] = bit + '0';
		buffer_index++;
	}
	
	if (buffer_index == 0) // generated 0, prob=1/(2^16) whatever
	{
		print_message("Generated 0, retry", "----", NULL);
		return;
	}
	str_out(&(buffer[BUF_BYTES * 8 - buffer_index]), buffer_index);
}

void f_del(void)
{
	if (buffer_index == 0)
	{
		return;
	}
	
	if (buffer_index >= 1)
	{
		buffer_index--;
	}
	if (buffer_index == 0)
	{
		str_out("----", NULL);
	}
	else
	{
		str_out(buffer, buffer_index);
	}
}

void f_ok(void)
{
	if (buffer_index == 0)
	{
		return;
	}
	create_number();
	str_out("Computing", NULL);
	_delay_ms(MSG_DELAY);
	test_exp(bin_buffer, buffer_index);
	_delay_ms(MSG_DELAY);
	str_out(buffer, buffer_index);
}

void f_rst(void)
{
	if (buffer_index == 0)
	{
		return;
	}
	buffer_index = 0;
	print_message("Buffer dropped", "----", NULL);
}

void button_handler(uint8_t btn, void (*func)(void))
{
	if (!(BTNS_PIN & btn))
	{
		_delay_ms(BTN_DELAY);
		if (!(BTNS_PIN & btn))
		{
			(*func)();
			while(!(BTNS_PIN & btn));
		}
	}
}


int main(void)
{
	init();
	
	while(1)
	{
		button_handler(BTNS_B_1,	&f_1);
		button_handler(BTNS_B_0,	&f_0);
		button_handler(BTNS_B_RND,	&f_rnd);
		button_handler(BTNS_B_DEL,	&f_del);
		button_handler(BTNS_B_OK,	&f_ok);
		button_handler(BTNS_B_RST,	&f_rst);
	}
}