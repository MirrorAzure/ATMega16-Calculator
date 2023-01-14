#ifndef UART_H_
#define UART_H_

void UART_init(void);
void UART_Send_Char(unsigned char);
void UART_Send_Str(char*);
void UART_Send_Arr(unsigned char mas[], char);

void UART_init(void)
{
	UCSRB|=(1<<TXEN)|(1<<RXEN)|(1<<RXCIE);
	UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	UBRRL=103;
};

void UART_Send_Char(unsigned char c)
{
	while(!(UCSRA&(1<<UDRE)))
	{
		UDR=c;
	}
}

void UART_Send_Str(char *str)
{
	char data=0;
	while(*str)
	{
		data=*str++;
		UART_Send_Char(data);
	}
}

void UART_Send_Arr(unsigned char mas[], char size)
{
	unsigned char i=0;
	
	for(i=0;i<size;i++)
	{
		UART_Send_Char(mas[i]);
	}
}

#endif