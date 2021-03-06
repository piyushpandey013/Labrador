/*
 * tiny_uart.c
 *
 * Created: 16/07/2015 6:32:52 PM
 *  Author: Esposch
 */ 

#include "tiny_uart.h"
#include "globals.h"


void tiny_uart_setup(void){
	PR.PRPC &= 0b11101111;
	//PR.PRPE &= 0b11111110;  ???
	
	PORTC.DIR |= 0b10101010;
	PORTC.OUT = 0xff;
	PORTC.PIN2CTRL = PORT_INVEN_bm | PORT_OPC_PULLUP_gc;
	//PORTC.REMAP = 0x10; //Remap USART to [7:4]
	#ifndef VERO
		PORTC.REMAP = 0x20; //Swap MOSI and SCK - for small boards only!!!
	#endif
	
	USARTC0.CTRLC = USART_CMODE_MSPI_gc | 0b00000100; //LSB received first, UPCHA disabled
	USARTC0.BAUDCTRLA = 3;  	//BSEL = fper/(2fbaud) -1;  24/(2*3) - 1 = 3
	USARTC0.BAUDCTRLB = 0x00;//USART_BSCALE0_bm;
	USARTC0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
}


void tiny_spi_setup(void){
	//Power Reduction disable
	PR.PRPC &= 0b11110111;
	
	//SPI enable
	SPIC.CTRL = SPI_ENABLE_bm;  //Slave mode
	#ifdef VERO
		PORTC.PIN5CTRL = PORT_INVEN_bm | PORT_OPC_PULLUP_gc;  //Pin5 if not swapped
	#else
		PORTC.PIN7CTRL = PORT_INVEN_bm | PORT_OPC_PULLUP_gc;  //Pin5 if not swapped		
	#endif
		
	return;
}