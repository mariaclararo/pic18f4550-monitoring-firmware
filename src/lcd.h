// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: lcd.h
//            Header da biblioteca de manipulação do LCD
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

#ifndef LCD_H
	#define LCD_H

	void lcdCommand(unsigned char cmd);
    void lcdPosition(int line, int col);
	void lcdData(unsigned char valor);
    void lcdString(char msg[]);
	void lcdInit(void);
    void tempo(int x);
    void lcdDataNew(unsigned char valor);
    void lcdDataSwitch(unsigned char valor, unsigned char index);
    void lcdRepeatChar(unsigned char indx);
    void lcdPositionNew(int line, int col);
    void InternalLcdDataSwitch(unsigned char *valor, unsigned char indx);
    void lcdStringNew(char msg[]);
    void lcdClear();
    int lcdReuseChar(unsigned char valor);
    void lcdInitNew(void);
    void Delay40us(void);
    
    void lcdTempo(int hh, int mm, int ss);
    void lcdInt(int val);
    
    void lcdTempoNew(int hh, int mm, int ss);
    void lcdIntNew(int val);
    void lcdPositionNew(int line, int col);


        
#endif