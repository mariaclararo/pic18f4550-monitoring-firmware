// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
// -----------------------------------------------------------------------
//   Arquivo: keypad.c
//            Biblioteca de operaÃ§Ã£o de um teclado matricial
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
#include "keypad.h"
#include "pic18f4550.h"
#include <xc.h>

static unsigned char valor = 0x00;

unsigned char kpRead(void) {
    return valor;
}

void kpDebounce(void) {
    unsigned char i;
    static unsigned char tempo;
    static unsigned int valorNovo = 0x00000000;
    static unsigned int valorAntigo = 0x00000000;

    for (i = 0; i < 6; i++) {
        if (i == 3)
            continue;
        if (!BitTst(PORTC, i)) {
            BitSet(valorNovo, i);
        } else {
            BitClr(valorNovo, i);
        }
    }

    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 10;
        valorAntigo = valorNovo;
    }
    if (tempo == 0) {
        valor = valorAntigo;
    }


}

void kpInit(void) {
    TRISC = 0x1F; // RC0 -> RC5 sao os botoes
    UCON &= 0b11110111;
    UCFG |= 0b00001000;

#ifdef PIC18F4550
    SPPCFG = 0x00; // SFR nao presente no PIC18F4520
#endif
}