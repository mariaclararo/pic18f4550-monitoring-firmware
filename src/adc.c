// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: adc.c
//            Biblioteca do conversor AD para o PIC18F4520
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#include "adc.h"
#include "pic18f4550.h" 
#include "lcd.h"

 void adcInit(void)
{
	BitSet(TRISE,0); //seta o bit 0 como entrada
	
	ADCON0 = 0b00010101; //seleciona o canal 5 e liga o ad
	//ADCON1 = 0b00001001; //apenas AN0 é analogico, a referencia é baseada na fonte
	ADCON2 = 0b10101010; //FOSC /32, Alinhamento à direita e tempo de conv = 12 TAD
}

int adcRead(void)
{
    ADCON1 = 0b00001001;//setando o pino como analogico
    
    Delay40us();
    
	unsigned int ADvalor;
	ADCON0 |= 0b00000010;	 //inicia conversao

	while(BitTst(ADCON0,1)); // espera terminar a conversão;

	ADvalor = ADRESH ; // le o resultado
	ADvalor <<= 8;
	ADvalor += ADRESL;
    
    ADCON1 = 0b00001111;//retornando os pinos para digitais
    
	return ADvalor;
}