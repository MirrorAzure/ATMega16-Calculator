#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "global.h"
#include <avr/interrupt.h>

void button_init(void);

ISR(INT0_vect)
{
	lcd_com(0x01);
	_delay_ms(100);
	lcd_com(0x80);
	lcd_string("Mode one");
	if(mode==2){
		speed=1;
		lcd_com(0xC3);
		lcd_string("Speed: slow");
		}
	if(mode==1){
		speed=2;
		lcd_com(0xC3);
		lcd_string("Speed: fast");}	
	mode = 1;
}

ISR(INT1_vect)
{
	lcd_com(0x01);
	_delay_ms(100);
	lcd_com(0x80);
	lcd_string("Mode two");
	if(mode==1){
		speed=1;
		lcd_com(0xC3);
		lcd_string("Speed: slow");}
	if(mode==2){
		speed=2;
		lcd_com(0xC3);
		lcd_string("Speed: fast");}
	mode = 2;
}

void button_init(void)
{
	DDRD &=~(1<<PD2); //Настройка PD2(int0) на вход
	DDRD &=~(1<<PD3);
	PORTD |= (1<<PD2)|(1<<PD3); //Настройка уровня pull-up
	GICR |=(1<<INT0)|(1<<INT1); //Включение прерываний
	MCUCR &=~(1<<ISC01)|(1<<ISC00); //Условие обработки int0
	MCUCR &=~(1<<ISC11)|(1<<ISC10); //Условие обработки int1
}


#endif