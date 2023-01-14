#ifndef TIMERS_H_
#define TIMERS_H_

#include <util/delay.h>
#include <avr/interrupt.h>
#include "global.h"

int8_t mode = 0;
int8_t speed = 1;
int8_t num = 0, a = 1;

void timer_init(void);

ISR(TIMER1_OVF_vect) //Обработчик прерываний
{
	switch(mode)
	{
	case 1:
	{
	PORTA=((1<<num)|(1<<(7-num))); //Установка состояний для порта A в зависимости от num
	if(num>2)
	{
		a=0;
	}
	if(num==0)
	{
		a=1;
	}
	if (a)
	{
		num++;
	}
	if (!a)
	{
		num--;
	}
	break;
	}
	case 2:
	{
		PORTA=(1<<num);
		if(num>=7)
		{
			a=0;
		}
		if(num==0)
		{
			a=1;
		}
		if (a)
		{
			num++;
		}
		if (!a)
		{
			num--;
		}
		break;
	}
	default: {PORTA=0x00; break;}
	}
	if(speed==1) {TCNT1=64318;}
	if(speed==2) {TCNT1=65318;}	
}

void timer_init()
{
	DDRA=0xFF; //Переводим все биты порта A в режим вывода (1111 1111)
	TCCR1B|=(1<<CS12)|(1<<CS10); //Это регистр управления, он настраивает работу таймера (устанавливает значение 1024 для предделителя)
	TIMSK|=(1<<TOIE1); //Регистр масок прерываний. Прерывание возникает при переполнении таймера TCNT1
	TCNT1=65318;
}	

#endif