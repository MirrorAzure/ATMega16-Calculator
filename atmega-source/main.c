#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "global.h"
#include "lcd.h"
#include "uart.h"

int multip(int a, int b)
{
	int par = 0;
	int i = b;
	for(i; i>0; i--)
	{
		par += a;
	}
	return par;
}

int divis(int a, int b)
{
	int par = 0;
	int i = a;
	while(i >= b)
	{
		i = i - b;
		par += 1;
	}
	return par;
}

char symbol_to_digit(int num)
{
	switch (num)
	{
		case '0':return 0;
		case '1':return 1;
		case '2':return 2;
		case '3':return 3;
		case '4':return 4;
		case '5':return 5;
		case '6':return 6;
		case '7':return 7;
		case '8':return 8;
		case '9':return 9;
		default:return'\0';
	}
}

void calculate(void);

unsigned char rData = 0;
unsigned char IDX = 0;
unsigned char buffer[16];

void calculate(void)
{
	int var1, var2, i;
	var1 = 0;
	var2 = 0;
	unsigned char sign;
	for(i=0; i<=IDX;i++)
	{
		if(buffer[i]==';')
		{
			break;
		}
		var1 = var1 * 10 + symbol_to_digit((unsigned char)buffer[i]);
	}
	sign = buffer[++i];
	for(i=i+1; i<=IDX;i++)
	{
		if(buffer[i]=='&')
		{
			break;
		}
		var2 = var2 * 10 + symbol_to_digit((unsigned char)buffer[i]);
	}
	char* printed;
	lcd_com(0x01);
	lcd_com(0x80);
	itoa(var1, *printed, 10);
	lcd_string(*printed);
	lcd_dat(sign);
	itoa(var2, *printed, 10);
	lcd_string(*printed);
	lcd_dat('=');
	lcd_com(0xC0);
	char* calculation;
	switch (sign)
	{
		case '+': 
		{
			int res;
			res = var1 + var2;
			itoa(res, *calculation, 10);
			lcd_string(*calculation);
			break;
		}
		case '-':
		{
			int res;
			res = var1 - var2;
			itoa(res, *calculation, 10);
			lcd_string(*calculation);
			break;
		}
		case '*':
		{
			int res = multip(var1, var2);
			itoa(res, *calculation, 10);
			lcd_string(*calculation);
			break;
		}
		case '/':
		{
			int res = divis(var1, var2);
			itoa(res, *calculation, 10);
			lcd_string(*calculation);
			break;
		}
		default:
		{
			lcd_string("NaN");
			break;
		}
	}
}

ISR(USART_RXC_vect)
{
	rData=UDR;
	buffer[IDX]=rData;
	if(rData=='&')
	{
		calculate();
		IDX=0;
	}
	else
	{
		IDX++;
	}
}

int main(void)
{
	lcd_init();
	UART_init();
	sei();
    while (1) 
    {
    }
}

