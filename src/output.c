#include "output.h"
#include "lcd.h"
#include "stateMachine.h"
#include "var.h"
#include "led.h"
#include "event.h"
#include "serial.h"

#define NUM_IDIOMAS 2


//msgs com 16 caracteres
//1 msg por estado (apenas linha de cima)
static char * msgs[STATE_FIM][NUM_IDIOMAS] = {
    {"V/A: ", "C/V: "},
    {"ALTO: ", "HIGH: "},
    {"BAIXO: ", "LOW: "},
    {"LINGUAGEM: ", "LANGUAGE: "},
    {"PORT            ", "ENG             "},
    {"HORA:           ", "SET TIME:       "},
    {"ALERTA ALTO AS:  ", "HIGH FLAG AT:   "},
    {"ALERTA BAIXO AS:", "LOW FLAG AT:    "},
};

static char oldState;

void outputInit(void) {
    lcdInitNew();
    oldState = 10;
}


//fun��o que imprime na tela em fun��o do estado
void outputPrint(int numTela, int idioma) {
    int hh = getHoras();
    int mm = getMinutos();
    int ss = getSegundos();
    
    if (numTela == STATE_SCREEN_01) {
        
        //verificando requisi��o de atualiza��o por flag
        //so atualiza se houver requisi��o
        if((getVarsT01() == 1) || (oldState != numTela))
        {
            //abaixando flag
            setVarsT01(0);
            
            lcdClear();
            lcdStringNew(msgs[0][idioma]);
            lcdIntNew(getMidLevel());
            lcdStringNew("       ");
            lcdPositionNew(0, 15);
            lcdTempoNew(hh, mm, ss);
            lcdStringNew("        ");
            
            if(oldState != numTela)
            {
                oldState = numTela;
            }
        }
    }
    if (numTela == STATE_SCREEN_02) {
        
        //verificando requisi��o de atualiza��o por flag
        //so atualiza se houver requisi��o
        if((getVarsT02() == 1) || (oldState != numTela))
        {
            //abaixando flag
            setVarsT02(0);
            
            lcdClear();
            lcdStringNew(msgs[1][idioma]);
            lcdIntNew(getMskUpperLevel());
            lcdStringNew("      ");
            lcdPositionNew(1, 0);
            lcdDataNew((getMskAlarmHighFlag() + '0'));
            lcdPositionNew(0, 15);
            lcdStringNew(msgs[2][idioma]);
            lcdIntNew(getMskLowerLevel());
            lcdStringNew("     ");
            lcdPositionNew(0, 0);
            lcdDataNew((getMskAlarmLowFlag() + '0'));
            
            if(oldState != numTela)
            {
                oldState = numTela;
            }
        }
    }
    if (numTela == STATE_SCREEN_03) {
        
        //verificando requisi��o de atualiza��o por flag
        //so atualiza se houver requisi��o
        if((getVarsT03() == 1) || (oldState != numTela))
        {
            //abaixando flag
            setVarsT03(0);
            
            lcdClear();
            lcdStringNew(msgs[3][idioma]);
            lcdStringNew("       ");
            lcdPositionNew(0, 15);
            lcdStringNew(msgs[4][idioma]);
            
            if(oldState != numTela)
            {
                oldState = numTela;
            }
        }
    }
    if (numTela == STATE_SCREEN_04) {
        
        //verificando requisi��o de atualiza��o por flag
        //so atualiza se houver requisi��o
        if((getVarsT01() == 1) || (oldState != numTela))
        {
            //abaixando flag
            setVarsT01(0);
            
            lcdClear();
            lcdStringNew(msgs[5][idioma]);
            lcdPositionNew(0, 15);
            lcdTempoNew(hh, mm, ss);
            
            if(oldState != numTela)
            {
                oldState = numTela;
            }
        }
    }
    
    
        if (numTela == STATE_SCREEN_02_EDIT) {
        
        //verificando requisi��o de atualiza��o por flag
        //so atualiza se houver requisi��o
        if((getVarsT02() == 1) || (oldState != numTela))
        {
            //abaixando flag
            setVarsT02(0);
            
            //desligando blink
            lcdCommand(0x0c);
            
            lcdClear();
            lcdStringNew(msgs[1][idioma]);
            lcdIntNew(getMskUpperLevel());
            lcdStringNew("      ");
            lcdPositionNew(1, 0);
            lcdDataNew((getMskAlarmHighFlag() + '0'));
            lcdPositionNew(0, 15);
            lcdStringNew(msgs[2][idioma]);
            lcdIntNew(getMskLowerLevel());
            lcdStringNew("     ");
            lcdPositionNew(0, 0);
            lcdDataNew((getMskAlarmLowFlag() + '0'));
            
            if(oldState != numTela)
            {
                oldState = numTela;
            }
            
            //ligando blink e setando posi��o
            lcdCommand(0x0f);
            lcdCommand(getBlink_T02());
        }
    }
    
    if (numTela == STATE_SCREEN_03_EDIT) {
        
        //verificando requisi��o de atualiza��o por flag
        //so atualiza se houver requisi��o
        if((getVarsT03() == 1) || (oldState != numTela))
        {
            //abaixando flag
            setVarsT03(0);
            
            //desligando blink
            lcdCommand(0x0c);
            
            lcdClear();
            lcdStringNew(msgs[3][idioma]);
            lcdStringNew("       ");
            lcdPositionNew(0, 15);
            lcdDataNew(0x7f);
            lcdStringNew(msgs[4][idioma]);
            lcdPositionNew(0, 0);
            lcdDataNew(0x7e);
            
            if(oldState != numTela)
            {
                oldState = numTela;
            }
            
            //ligando blink e setando posi��o
            lcdCommand(0x0f);
            lcdCommand(getBlink_T03());
        }
    }
    
    if (numTela == STATE_SCREEN_04_EDIT) {
        
        //verificando requisi��o de atualiza��o por flag
        //so atualiza se houver requisi��o
        if((getVarsT04() == 1) || (oldState != numTela))
        {
            //abaixando flag
            setVarsT04(0);
            
            //desligando blink
            lcdCommand(0x0c);
            
            lcdClear();
            lcdStringNew(msgs[5][idioma]);
            lcdPositionNew(0, 15);
            lcdTempoNew(getHorasEdit(), getMinutosEdit(), getSegundosEdit());
            
            if(oldState != numTela)
            {
                oldState = numTela;
            }
            
            //ligando blink e setando posi��o
            lcdCommand(0x0f);
            lcdCommand(getBlink_T04());
        }
    }
    
    if(numTela == STATE_ALARM_OVERFLOW)
    {
        int cnt = 0;
        
        //enviando log para a serial
        switch(idioma)
        {
            case 0:
                if(getAlarmFlag() == ESTOURO_ALTO)
                {
                    serialString("Uma violacao no limite alto de monitoramento foi detectado e registrado as: ");
                }else
                {
                    serialString("Uma violacao no limite baixo de monitoramento foi detectado e registrado as: ");
                }
                serialTempo(hh, mm, ss);
                break;
                
            case 1:
                if(getAlarmFlag() == ESTOURO_ALTO)
                {
                    serialString("A violation of the high monitoring limit was detected and recorded at: ");
                }else
                {
                    serialString("A violation of the low monitoring limit was detected and recorded at: ");
                }
                serialTempo(hh, mm, ss);
                break;
        }
        
        while(cnt <= 20)//fica em estado de alerta por 20 segundos, ou reset
        {
            //sinaliza��o verbal
            lcdClear();
            if(getAlarmFlag() == ESTOURO_ALTO)
            {
                lcdStringNew(msgs[6][idioma]);
            }else
            {
                lcdStringNew(msgs[7][idioma]);
            }
            lcdPositionNew(0, 15);
            lcdTempoNew(hh, mm, ss);
            
            //sinaliza��o sensorial
            ledON(2);
            ledON(3);
            ledON(4);
            ledON(5);
            
            tempo(500);
            
            ledOFF(2);
            ledOFF(3);
            ledOFF(4);
            ledOFF(5);
            
            tempo(500);
            
            lcdCommand(0x01);
            lcdClear();
            
            ledON(2);
            ledON(3);
            ledON(4);
            ledON(5);
            
            tempo(500);
            
            ledOFF(2);
            ledOFF(3);
            ledOFF(4);
            ledOFF(5);
            
            tempo(500);
            
            cnt++;
        }
        
        setState(STATE_SCREEN_01);
    }
    
}

