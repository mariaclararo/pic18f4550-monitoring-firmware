#include "pic18f4550.h"
#include <xc.h>
#include "event.h"
#include "serial.h"
#include <string.h>
#include "var.h"

typedef enum {
    MSG_START,
    WHILE_MSG
} SerialState;

static char serialBuffer[10]; //XXX000000
static SerialState serialState = MSG_START;
static unsigned int bufferIndex = 0;

//Variaveis para processar o buffer
static unsigned int values = 0;
static unsigned int power = 1; // usa no tempo tambem

//Teclado
unsigned char key_ant;

void eventInit(void) {
    TRISC = 0x17; // RC0 -> RC5 sao os botoes
    UCON &= 0b11110111;
    UCFG |= 0b00001000;
    key_ant = 0;
}

unsigned int eventRead(void) {
    unsigned char key;
    unsigned int ev = EV_NOEVENT;

    //Limpa o valor da serial e pega qual botao esta pressionado
    key = PORTC & 0b00110111;

    if (key != key_ant) {
        if (!BitTst(key, 0)) {
            ev = EV_ENTER;
        }

        if (!BitTst(key, 1)) {
            ev = EV_UP;
        }

        if (!BitTst(key, 2)) {
            ev = EV_DOWN;
        }
        if (!BitTst(key, 4)) {
            ev = EV_RIGHT;
        }
        if (!BitTst(key, 5)) {
            ev = EV_LEFT;
        }
    }
    // atualiza a tecla anterior
    key_ant = key;

    key = serialRead();

    if (key != 0) {
        switch (serialState) {
            case MSG_START:
                if ((key == 'D') || (key == 'd')) {
                        ev = EV_RIGHT;
                    } else if ((key == 'A') || (key == 'a')) {
                        ev = EV_LEFT;
                    } else if ((key == 'W') || (key == 'w')) {
                        ev = EV_UP;
                    } else if ((key == 'S') || (key == 's')) {
                        ev = EV_DOWN;
                    } else if ((key == 'E') || (key == 'e')) {
                        ev = EV_ENTER;
                    } else if (key == '{') {
                        serialState = WHILE_MSG;
                        bufferIndex = 0;
                        serialString(" Inicio do protocolo...");
                    } else {
                        serialString(" Esperando comando...");
                    }

                break;

            case WHILE_MSG:
                switch (key) {
                    case '}':
                        serialBuffer[bufferIndex] = '\0';
                        serialState = MSG_START;

                        if (bufferIndex < 9) {
                            // Lidar com o erro de buffer curto
                            serialString(" Erro: buffer curto ");
                            break;
                        }

                        if (strncmp(serialBuffer, "GAM", 3) == 0) { // GET ALARM MID
                            //GAL000000
                            serialString(" O nivel do alarme eh: ");
                            serialInt(getAlarmLevel());

                        } else if (strncmp(serialBuffer, "GAU", 3) == 0) { // GET ALARM UPPER
                            //GAU000000 
                            serialString(" O nivel superior eh: ");
                            serialInt(getUpperLevel());

                        } else if (strncmp(serialBuffer, "GAL", 3) == 0) { // GET ALARM LOWER
                            //GAL000000
                            serialString(" O nivel inferior eh: ");
                            serialInt(getLowerLevel());

                        } else if (strncmp(serialBuffer, "CAU", 3) == 0) { // CHANGE ALARM UPPER

                            //CAU00XXXX - Indice 3 e 4 nao e utilizado
                            values = 0;
                            power = 1000;
                            int i;

                            // Processamento do buffer
                            for (i = 5; i <= 8; i++) {
                                values += (serialBuffer[i] - '0') * power;
                                power /= 10;
                            }

                            setUpperLevel(values);

                            serialString("O nivel superior foi alterado para: ");
                            serialInt(getUpperLevel());

                        } else if (strncmp(serialBuffer, "CAL", 3) == 0) { // CHANGE ALARM LOWER

                            //CAL00XXXX - Indice 3 nao e utilizado
                            values = 0;
                            power = 1000;
                            int i;

                            // Processamento do buffer
                            for (i = 5; i <= 8; i++) {
                                values += (serialBuffer[i] - '0') * power;
                                power /= 10;
                            }

                            setLowerLevel(values);

                            serialString("O nivel inferior foi alterado para: ");
                            serialInt(getLowerLevel());

                        } else if (strncmp(serialBuffer, "STM", 3) == 0) { // SET TIME 
                            //STMXXXXXX
                            setHoras((serialBuffer[3] - '0') * 10 + (serialBuffer[4] - '0'));
                            setMinutos((serialBuffer[5] - '0') * 10 + (serialBuffer[6] - '0'));
                            setSegundos((serialBuffer[7] - '0') * 10 + (serialBuffer[8] - '0'));

                        } else if (strncmp(serialBuffer, "GTM", 3) == 0) { // GET TIME
                            //GTM000000
                            serialTempo(getHoras(), getMinutos(), getSegundos());
                        }
                        break;
                    default:
                        serialString(" Esperando protocolo...");
                        serialBuffer[bufferIndex++] = key;
                        if (bufferIndex > sizeof (serialBuffer) - 1) {
                            serialState = MSG_START;
                        }
                        break;
                }
                break;

            default:
                serialState = MSG_START;
                break;
        }
    }
    
                setAlarmHighFlag(getMskAlarmHighFlag());
                setAlarmLowFlag(getMskAlarmLowFlag());


    return ev;
}
