#include "pic18f4550.h"
#include "timer.h"
#include "event.h"
#include "output.h"
#include "ds1307.h"
#include "serial.h"
#include "var.h"
#include "stateMachine.h"
#include "config.h"
#include "led.h"
#include "adc.h"


void main(void) {

    //init das bibliotecas
    timerInit();
    eventInit(); // Inicializa as teclas
    outputInit(); // lcdInit()
    dsInit();
    adcInit();
    varInit(); // TEM que ser depois do dsInit()
    smInit();
    initLed();
    serialInit();
    
    for (;;) {
        timerReset(getTime());
        
        //infraestrutura da placa
        //máquina de estados
        smLoop();
        timerWait();
        
       
    }




}