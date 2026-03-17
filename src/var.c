#include "var.h"
#include "ds1307.h"
#include "adc.h"
//variáveis a serem armazenadas
//Estados
static char state;

//Linguagem
unsigned char language;

//Timer
static int time;

//Alarme
static int upperAlarmLevel;
static int lowerAlarmLevel;

static int MskupperAlarmLevel;
static int MsklowerAlarmLevel;

//Tempo
static char time_flag;

//Estouro alarme
static char alarm_flag;

//controle de blink das telas de edição
static unsigned char blink_T02;
static unsigned char blink_T03;
static unsigned char blink_T04;

//flags de atualização de variavei
static unsigned char varsT01;
static unsigned char varsT02;
static unsigned char varsT03;
static unsigned char varsT04;

//variavel de hora estatica
int static horasEdit;
int static minutosEdit;
int static segundosEdit;

//flags de habilitação de alarme
unsigned char alarmHighFlag;
unsigned char alarmLowFlag;

unsigned char MskAlarmHighFlag;
unsigned char MskAlarmLowFlag;

void varInit(void) {
    //Estados
    state = 0;
   
    //Tempo
    time = 1000;
    
    setSeconds(00);
    setMinutes(11);
    setHours(11);
   
    //Alarme
    if((getUpperLevel() > 9999) || getUpperLevel() < 50)
    {
        setUpperLevel(500);
    }
    
    if((getLowerLevel() > 9999) || getLowerLevel() < 0)
    {
        setLowerLevel(0);
    }
    
    MskupperAlarmLevel = getUpperLevel();
    MsklowerAlarmLevel = getLowerLevel();
    
    //blinks
    blink_T02 = 0xc9;
    blink_T03 = 0x80;
    blink_T04 = 0x8f;
    
    //atualização de variaveis
    varsT01 = 0;
    varsT02 = 0;
    varsT03 = 0;
    varsT04 = 0;
   
    //flags de alarme
    alarmHighFlag = 1;//alarme alto ligado por reset
    alarmLowFlag = 0;//alarme low desligado por reset
    
    MskAlarmHighFlag = 1;
    MskAlarmLowFlag = 0;
}

//_______________________________________________________________________________________

unsigned char getMskAlarmHighFlag()
{
    return MskAlarmHighFlag;
}

unsigned char getMskAlarmLowFlag()
{
    return MskAlarmLowFlag;
}

void setMskAlarmHighFlag(unsigned char val)
{
    setVarsT02(1);
    MskAlarmHighFlag = val;
}

void setMskAlarmLowFlag(unsigned char val)
{
    setVarsT02(1);
    MskAlarmLowFlag = val;
}






unsigned char getAlarmHighFlag()
{
    return alarmHighFlag;
}

unsigned char getAlarmLowFlag()
{
    return alarmLowFlag;
}

void setAlarmHighFlag(unsigned char val)
{
    setVarsT02(1);
    alarmHighFlag = val;
}

void setAlarmLowFlag(unsigned char val)
{
    setVarsT02(1);
    alarmLowFlag = val;
}


//_______________________________________________________________________________________

int getHorasEdit()
{
    return horasEdit;
}

int getMinutosEdit()
{
    return minutosEdit;
}

int getSegundosEdit()
{
    return segundosEdit;
}




void setHorasEdit(int val)
{
    setVarsT04(1);
    horasEdit = val;
}

void setMinutosEdit(int val)
{
    setVarsT04(1);
    minutosEdit = val;
}

void setSegundosEdit(int val)
{
    setVarsT04(1);
    segundosEdit = val;
}




//_______________________________________________________________________________________

unsigned char getBlink_T02()
{
    return blink_T02;
}

unsigned char getBlink_T03()
{
    return blink_T03;
}

unsigned char getBlink_T04()
{
    return blink_T04;
}


//deve ser hexadecimal
void setBlink_T02(unsigned char set)
{
    setVarsT02(1);
    blink_T02 = set;
}

//deve ser hexadecimal
void setBlink_T03(unsigned char set)
{
    setVarsT03(1);
    blink_T03 = set;
}

//deve ser hexadecimal
void setBlink_T04(unsigned char set)
{
    setVarsT04(1);
    blink_T04 = set;
}

//_______________________________________________________________________________________

unsigned char getVarsT01()
{
    return varsT01;
}

unsigned char getVarsT02()
{
    return varsT02;
}

unsigned char getVarsT03()
{
    return varsT03;
}

unsigned char getVarsT04()
{
    return varsT04;
}





//deve ser 0 ou 1
void setVarsT01(unsigned char val)
{
    varsT01 = val;
}

//deve ser 0 ou 1
void setVarsT02(unsigned char val)
{
    varsT02 = val;
}

//deve ser 0 ou 1
void setVarsT03(unsigned char val)
{
    varsT03 = val;
}

//deve ser 0 ou 1
void setVarsT04(unsigned char val)
{
    varsT04 = val;
}


//_______________________________________________________________________________________


int getTime(){
    return time;
}

//Estados
char getState(void) {
    return state;
}
void setState(char newState) {
    state = newState;
}

//Tempo
int getHoras(){
    setVarsT01(1);
    return getHours();
}

int getMinutos(){
    setVarsT01(1);
    return getMinutes();
}

int getSegundos(){
    setVarsT01(1);
    return getSeconds();
}

void setHoras(int hh){
    setVarsT01(1);
    setHours(hh);
}

void setMinutos(int mm){
    setVarsT01(1);
    setMinutes(mm);
}

void setSegundos(int ss){
    setVarsT01(1);
    setSeconds(ss);
}

char getTimeFlag(void) {
    return time_flag;
}
void setTimeFlag(char newFlag) {
    time_flag = newFlag;
}

int getAlarmLevel(void) {
    return adcRead();
}
  
int getUpperLevel(void){
    return dsGetAlarmUpper();
}

int getLowerLevel(void){
    return dsGetAlarmLower();
}

int getMidLevel(){
    return adcRead();
}

void setUpperLevel(int newUpperAlarmLevel){
    setVarsT02(1);
    upperAlarmLevel = newUpperAlarmLevel;
    dsSetAlarmUpper(upperAlarmLevel);
}

void setLowerLevel(int newLowerAlarmLevel){
    setVarsT02(1);
    lowerAlarmLevel = newLowerAlarmLevel;
    dsSetAlarmLower(lowerAlarmLevel);
}

int getMskUpperLevel(void){
    return MskupperAlarmLevel;
}

int getMskLowerLevel(void){
    return MsklowerAlarmLevel;
}

void setMskUpperLevel(int val){
    setVarsT02(1);
    MskupperAlarmLevel = val;
}

void setMskLowerLevel(int val){
    setVarsT02(1);
    MsklowerAlarmLevel = val;
}

char getAlarmFlag(void) {
    return alarm_flag;
}
void setAlarmFlag(char newFlag) {
    alarm_flag = newFlag;
}

char getLanguage(void){
    return dsGetLanguage() % 2;
}

void setLanguage(char newLanguage){
    //só tem 2 linguas
    //usando resto pra evitar colocar valor errado
    setVarsT03(1);
    language = newLanguage%2;
    dsSetLanguage(language);
}