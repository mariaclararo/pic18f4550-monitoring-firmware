/* 
 * File:   stateMachine.h
 * Author: Avell
 *
 * Created on 18 de Junho de 2017, 22:17
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H


//estados da maquina de Estados

enum {
    STATE_SCREEN_01,
    STATE_SCREEN_02,
    STATE_SCREEN_02_EDIT,
    STATE_SCREEN_03,
    STATE_SCREEN_03_EDIT,
    STATE_SCREEN_04,
    STATE_SCREEN_04_EDIT,
    STATE_ALARM_OVERFLOW,
    STATE_FIM
};

typedef enum {
    HORAS,
    MINUTOS,
    SEGUNDOS
};

typedef enum {
    SEM_ESTOURO,
    ESTOURO_ALTO,
    ESTOURO_BAIXO
};

void smInit(void);
void smLoop(void);

unsigned char old_alarm_flag;

#endif	/* STATEMACHINE_H */

