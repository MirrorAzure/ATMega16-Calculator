#ifndef LCD_H_
#define LCD_H_

#include <util/delay.h>
#include <avr/io.h>
#define RS 2
#define RW 1
#define EN 0 //816 при заданной паузе 750 us

void lcd_init(void);
void lcd_com(unsigned char);
void lcd_dat(unsigned char);
void lcd_string(char*);

void lcd_com (unsigned char p) //Работа с шиной управления
{
	PORTB &=~(1<<RS);	//RS=0
	PORTB |=(1<<EN);	//EN=1, начало записи команды
	PORTC = p;			//Вывод команды на шину данных экрана
	_delay_us(750);		//Длительность команды данных
	PORTB &=~(1<<EN);	//Конец записи данных
	_delay_us(750);		//Пауза для выполнения команды
}

void lcd_dat (unsigned char p) //Работа с шиной данных
{
	PORTB |=(1<<RS)|(1<<EN);	//Начало записи данных
	PORTC=p;
	_delay_us(750);				//Длительность сигнала EN
	PORTB&=~(1<<EN);			//Конец записи данных
	_delay_us(750);				//Пауза для записи команды данных
}

void lcd_init(void)					//Настройка дисплея
{
	DDRB|=(1<<RS)|(1<<RW)|(1<<EN);	//Управление на вывод
	PORTB = 0x00;					//Все биты управления - нули
	DDRC=0xFF;						//То же самое с шиной данных
	PORTC=0x00;						//Все биты на шине данных - нули
	_delay_us(750);
	
	lcd_com(0x08);					//Полное включение дисплея
	_delay_us(750);
	lcd_com(0x3C);					//8 бит данных, две строки
	_delay_us(750);
	lcd_com(0x01);					//Очистка строки
	_delay_us(750);
	lcd_com(0x06);					//Курсор двигается вправо
	_delay_us(750);
	lcd_com(0x0F);					//Курсор показан и мигает
}

void lcd_string (char *str)			//Функция обработки строки
{
	char data=0;
	while (*str)
	{
		data=*str++;
		lcd_dat(data);
	}
}

#endif