/*
 * main_init.h
 *
 * Created: 13.12.2020 02:57:06
 *  Author: Аркадий
 */ 


#ifndef MAIN_INIT_H_
#define MAIN_INIT_H_

//-------------------------------------------------------------------------
//	Для работы с шиной I2C необходимо выбрать порт и пин на данном порту
//  \/\/ Это для i2c.h \/\/
//-------------------------------------------------------------------------

#define I2C_DDR		DDRC	// Порт для выбора направления
#define I2C_PORT	PORTC	// Порт для вывода данных
#define I2C_PIN		PINC	// Порт для ввода данных

#define SCL			0		// Пин порта SCL
#define SDA			1		// Пин порта SDA

#define ADD 0x4E // Адрес микросхемы

//////////////////////////////////////////////////////////////////////////

#define NULL 0

#define BTN_DELAY	50
#define MSG_DELAY	500

#define BTNS_DDR	DDRA		/// Порт для ввода информации с кнопок
#define BTNS_PORT	PORTA		/// Порт для ввода информации с кнопок
#define BTNS_PIN	PINA		/// Порт для ввода информации с кнопок
#define BTNS_B_1	0b00000001	// Кнопка "1"
#define BTNS_B_0	0b00000010	// Кнопка "0"
#define BTNS_B_RND	0b00000100	// Кнопка "Случайное число"
#define BTNS_B_DEL	0b00001000	// Кнопка "Стереть"
#define BTNS_B_OK	0b00010000	// Кнопка "Ок"
#define BTNS_B_RST	0b00100000	// Кнопка "Сброс"

//////////////////////////////////////////////////////////////////////////

#define BUF_BYTES	2			// {1,2} (еще мб 4 но пока без вывода на экран)

#if BUF_BYTES == 1
#define TYPE	uint8_t
#elif BUF_BYTES == 2
#define TYPE	uint16_t
#elif BUF_BYTES == 4
#define TYPE	uint32_t
#endif




#endif /* MAIN_INIT_H_ */