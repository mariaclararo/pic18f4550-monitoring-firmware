// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: serial.c
//            Biblioteca da porta serial (USART) do PIC18F4520
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   LicenÃ§a: GNU GPL 2
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

#include "serial.h"
#include "pic18f4550.h"

void serialSend(unsigned char c) {
    while (!BitTst(PIR1, 4)); //aguarda o registro ficar disponivel�vel
    TXREG = c; //coloca o valor para ser enviado
}

unsigned char serialRead(void) {
    char resp = 0;

    if (BitTst(RCSTA, 1)) //Verifica se hÃ¡ erro de overrun e reseta a serial
    {
        BitClr(RCSTA, 4);
        BitSet(RCSTA, 4);
    }

    if (BitTst(PIR1, 5)) //Verifica se existe algum valor disponivel
    {
        resp = RCREG; //retorna o valor
    }
    return resp; //retorna zero


}

void serialInit(void) {
    TXSTA = 0b00101100; //configura a transmissÃ£o de dados da serial
    RCSTA = 0b10010000; //configura a recepÃ§Ã£o de dados da serial
    BAUDCON = 0b00001000; //configura sistema de velocidade da serial
    SPBRGH = 0b00000000; //configura para 56k
    SPBRG = 0b01010110; //configura para 56k
    BitSet(TRISC, 6); //pino de recepÃ§Ã£o de dados
    BitSet(TRISC, 7); //pino de envio de dados
}

void serialString(char msg[]) {
    int i = 0;
    while (msg[i] != '\0') {
        serialSend(msg[i]);
        i++;
    }

}

void serialInt(int val) {
    serialSend(((val / 100000) % 10) + '0');
    serialSend(((val / 10000) % 10) + '0');
    serialSend(((val / 1000) % 10) + '0');
    serialSend(((val / 100) % 10) + '0');
    serialSend(((val / 10) % 10) + '0');
    serialSend(val % 10 + '0');
}

void serialTempo(int hh, int mm, int ss) {
    serialSend(( hh / 10) + '0');
    serialSend(( hh % 10) + '0');
    serialSend(':');
    serialSend(( mm / 10) + '0');
    serialSend(( mm % 10) + '0');
    serialSend(':');
    serialSend(( ss / 10) + '0');
    serialSend(( ss % 10) + '0');
}