/* 
 * File:   alarme.h
 * Author: Avell
 *
 * Created on 14 de Junho de 2017, 16:10
 */

#ifndef VAR_H
#define	VAR_H

void varInit(void);

int getTime(void);

//Estados
char getState(void);
void setState(char newState);

//Tempo
void setHoras(int hh);
void setMinutos(int mm);
void setSegundos(int ss);
int getHoras(void);
int getMinutos(void);
int getSegundos(void);

char getTimeFlag(void);
void setTimeFlag(char newFlag);

//Alarme
void setUpperLevel(int newMaxAlarmLevel);
void setLowerLevel(int newMinAlarmLevel);
int getMskUpperLevel(void);
int getMskLowerLevel(void);
void setMskUpperLevel(int val);
void setMskLowerLevel(int val);

int getAlarmLevel(void);
int getUpperLevel(void);
int getLowerLevel(void);

char getAlarmFlag(void);
void setAlarmFlag(char newFlag);

//Idiomas
char getLanguage(void);
void setLanguage(char newLanguage);


//blinks
unsigned char getBlink_T02();
unsigned char getBlink_T03();
unsigned char getBlink_T04();

void setBlink_T02(unsigned char set);
void setBlink_T03(unsigned char set);
void setBlink_T04(unsigned char set);

//flags de variaveis 
unsigned char getVarsT01();
unsigned char getVarsT02();
unsigned char getVarsT03();
unsigned char getVarsT04();

void setVarsT01(unsigned char val);
void setVarsT02(unsigned char val);
void setVarsT03(unsigned char val);
void setVarsT04(unsigned char val);

//amostra de hora para edição
int getHorasEdit();
int getMinutosEdit();
int getSegundosEdit();

void setHorasEdit(int val);
void setMinutosEdit(int val);
void setSegundosEdit(int val);

//flags de habilitação de alarme
unsigned char getAlarmHighFlag();
unsigned char getAlarmLowFlag();
void setAlarmHighFlag(unsigned char val);
void setAlarmLowFlag(unsigned char val);

unsigned char getMskAlarmHighFlag();
unsigned char getMskAlarmLowFlag();
void setMskAlarmHighFlag(unsigned char val);
void setMskAlarmLowFlag(unsigned char val);


#endif	/* VAR_H */
