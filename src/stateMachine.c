#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "lcd.h"


void smInit(void) {
    setState(STATE_SCREEN_01);
    setTimeFlag(SEGUNDOS);
    setAlarmFlag(SEM_ESTOURO);
    old_alarm_flag = 100; 
}


//atualiza os estados com base nos eventos
void smLoop(void) {
    unsigned char evento;

    //m�quina de estados
    evento = eventRead();

    if(getAlarmHighFlag() == 1)//verifica estado de habilita��o da flag antes de verificar o alarme
    {
        if(getMidLevel() > getUpperLevel()){
        setState(STATE_ALARM_OVERFLOW);
        setAlarmFlag(ESTOURO_ALTO);
        }
    }
    
    if(getAlarmLowFlag() == 1)//verifica estado de habilita��o da flag antes de verificar o alarme
    {
        if(getMidLevel() < getLowerLevel){
        setState(STATE_ALARM_OVERFLOW);
        setAlarmFlag(ESTOURO_BAIXO);
     }
    }
    
    switch (getState()) {
        case STATE_SCREEN_01:
            
            if (evento == EV_LEFT)
            {
                setState(STATE_SCREEN_04);
            }
            
            if (evento == EV_RIGHT)
            {
                setState(STATE_SCREEN_02);
            }
            
            //edi��o da hora sera em outra tela
            /*
            if (evento == EV_ENTER)
            {
                setState(STATE_SCREEN_01_EDIT);
                
                //ligando blink
                lcdCommand(0x0f);
                
                //setando cursor
                lcdCommand(getBlink_T01());
            }*/
            
            break;
        case STATE_SCREEN_02:
        {
            
            if (evento == EV_LEFT)
            {
                setState(STATE_SCREEN_01);
            }
            
            if (evento == EV_RIGHT)
            {
                setState(STATE_SCREEN_03);
            }
            
            if (evento == EV_ENTER)
            {
                setState(STATE_SCREEN_02_EDIT);
            }
            break;
        }
        
        case STATE_SCREEN_03:
        {
            
            if (evento == EV_LEFT)
            {
                setState(STATE_SCREEN_02);
            }
            
            if (evento == EV_RIGHT)
            {
                setState(STATE_SCREEN_04);
            }
            
            if (evento == EV_ENTER)
            {
                setState(STATE_SCREEN_03_EDIT);
            }
            break;
        }
        
        case STATE_SCREEN_04:
        {
            
            if (evento == EV_LEFT)
            {
                setState(STATE_SCREEN_03);
            }
            
            if (evento == EV_RIGHT)
            {
                setState(STATE_SCREEN_01);
            }
            
            if (evento == EV_ENTER)
            {
                setState(STATE_SCREEN_04_EDIT);
                
                //pegando amostra das horas para a tela de edi��o
                setHorasEdit(getHoras());
                setMinutosEdit(getMinutos());
                setSegundosEdit(getSegundos());
            }
            break;
        }
        
        //telas de edi��o
        case STATE_SCREEN_02_EDIT:
        {
            if(getLanguage() == 1)
            {
                Screen02Eng(evento);
            }else
            {
                Screen02Port(evento);
            }break;
        }
        
        case STATE_SCREEN_03_EDIT:
        {
            //enter
            if (evento == EV_ENTER)
            {
                setState(STATE_SCREEN_03);
                
                //desligando blink
                lcdCommand(0x0c);
            }
            
            //movimento para a esquerda
            if(evento == EV_LEFT)
            {
                setBlink_T03(0x8f);
                setLanguage(getLanguage() - 1);
            }
            
            //movimento para a direita
            if(evento == EV_RIGHT)
            {
                setBlink_T03(0x80);
                setLanguage(getLanguage() + 1);
            }
            
            setBlink_T02(0xc9);//se troca a linguagem, reseta o blink
            
            break;
        }
        
        case STATE_SCREEN_04_EDIT:
        {
            //enter 
            if (evento == EV_ENTER)
            {
                setState(STATE_SCREEN_04);
                
                //desligando blink
                lcdCommand(0x0c);
                
                //salvando altera��es
                setHoras(getHorasEdit());
                setMinutos(getMinutosEdit());
                setSegundos(getSegundosEdit());
            }
            
            //movimento para a esquerda
            if(evento == EV_LEFT)
            {
                if(getBlink_T04() < 0x8f)
                {
                    setBlink_T04(getBlink_T04() + 1);//se dentro do limite, incrementa
                }
                
                if(getBlink_T04() == 0x8d)//ajuste pra nao ficar em cima do ":"
                {
                    setBlink_T04(0x8e);
                }
                if(getBlink_T04() == 0x8a)//ajuste pra nao ficar em cima do ":"
                {
                    setBlink_T04(0x8b);
                }
                
            }
            
            //movimento para a direita
            if(evento == EV_RIGHT)
            {
                if(getBlink_T04() > 0x88)
                {
                    setBlink_T04(getBlink_T04() - 1);//se dentro do limite, decrementa
                }
                
                if(getBlink_T04() == 0x8d)//ajuste pra nao ficar em cima do ":"
                {
                    setBlink_T04(0x8c);
                }
                
                if(getBlink_T04() == 0x8a)//ajuste pra nao ficar em cima do ":"
                {
                    setBlink_T04(0x89);
                }
            }
            
            //incrementando valores
            if(evento == EV_UP)
            {
                switch(getBlink_T04())
                {
                    case 0x8f:
                    {
                        if(getHorasEdit() >= 20)
                        {
                            break;
                        }
                        setHorasEdit(getHorasEdit() + 10);
                        break;
                    }
                    case 0x8e:
                    {
                        if(getHorasEdit() >= 20)
                        {
                            if((getHorasEdit() % 10) >= 4)
                            {
                                break;
                            }
                            
                            if((getHorasEdit() % 10) >= 9)
                            {
                                break;
                            }
                        }
                        
                        setHorasEdit(getHorasEdit() + 1);
                       break;
                    }    
                    case 0x8c:
                    {
                        if(getMinutosEdit() > 50)
                        {
                            break;
                        }
                        setMinutosEdit(getMinutosEdit() + 10);
                       break;
                    }    
                    case 0x8b:
                    {
                        if((getMinutosEdit() % 10) >= 9)
                        {
                            break;
                        }
                        setMinutosEdit(getMinutosEdit() + 1);
                       break;
                    }    
                    case 0x89:
                    {
                        if(getSegundosEdit() > 50)
                        {
                            break;
                        }
                        setSegundosEdit(getSegundosEdit() + 10);
                       break;
                    }    
                    case 0x88:
                    {
                        if((getSegundosEdit() % 10) >= 9)
                        {
                            break;
                        }
                        setSegundosEdit(getSegundosEdit() + 1);
                        break;
                    }    
                }
        }
            
            //decrementando valores
            if(evento == EV_DOWN)
            {
                switch(getBlink_T04())
                {
                    case 0x8f:
                    {
                        if(getHorasEdit() < 10)
                        {
                            break;
                        }
                        setHorasEdit(getHorasEdit() - 10);
                        break;
                    }
                    case 0x8e:
                    {
                        if(getHorasEdit() == 0)
                        {
                            break;
                        }
                        setHorasEdit(getHorasEdit() - 1);
                       break;
                    }    
                    case 0x8c:
                    {
                        if(getMinutosEdit() < 10)
                        {
                            break;
                        }
                        setMinutosEdit(getMinutosEdit() - 10);
                       break;
                    }    
                    case 0x8b:
                    {
                        if(getMinutosEdit() == 0)
                        {
                            break;
                        }
                        setMinutosEdit(getMinutosEdit() - 1);
                       break;
                    }    
                    case 0x89:
                    {
                        if(getSegundosEdit() < 10)
                        {
                            break;
                        }
                        setSegundosEdit(getSegundosEdit() - 10);
                       break;
                    }    
                    case 0x88:
                    {
                        if(getSegundosEdit() == 0)
                        {
                            break;
                        }
                        setSegundosEdit(getSegundosEdit() - 1);
                        break;
                    }    
                }
        }
            break;
        }
    }
    
    outputPrint(getState(), getLanguage());
    old_alarm_flag = getAlarmFlag();
}


//___________________________________________________________________________________________





Screen02Eng(int evento)
{
    if (evento == EV_ENTER)
            {
                setState(STATE_SCREEN_02);
                
                //desligando blink
                lcdCommand(0x0c);
                
                //atualizando os valores com base nos masked values
                setUpperLevel(getMskUpperLevel());
                setLowerLevel(getMskLowerLevel());
                
                setAlarmHighFlag(getMskAlarmHighFlag());
                setAlarmLowFlag(getMskAlarmLowFlag());
            }
            
            //movimento para a esquerda
            if(evento == EV_LEFT)
            {
                if(getBlink_T02() > 0x8f)//se for maior entao esta na linha de cima
                {
                    if(getBlink_T02() == 0xc0)//se estiver na flag de habilita��o, volta pro editor de valor
                    {
                        setBlink_T02(0xc4);
                    }
                    
                    if(getBlink_T02() < 0xc9)//se esta dentro do limite da linha de cima, incrementa
                    {
                        setBlink_T02(getBlink_T02() + 1);
                    }
                } else
                {
                    if(getBlink_T02() == 0x80)//se estiver na flag de habilita��o, joga pro editor de valor
                    {
                        setBlink_T02(0x85);
                    }
                    
                    if(getBlink_T02() < 0x8b)//se esta dentro do limite da linha debaixo, incrementa
                    {
                        setBlink_T02(getBlink_T02() + 1);
                    }
                    
                    if(getBlink_T02() == 0x8b)//se estiver no limite, joga pra linha de cima na flag de habilita��o
                    {
                        setBlink_T02(0xc0);
                    }
                }
            }
            
            //movimento para a direita
            if(evento == EV_RIGHT)
            {
                if(getBlink_T02() > 0x8f)//se for maior entao esta na linha de cima
                {
                    if(getBlink_T02() == 0xc0)//se estiver na flag de habilita��o, joga pra linha de baixo
                    {
                        setBlink_T02(0x8a);
                    }
                    
                    if(getBlink_T02() == 0xc5)//se estiver no limite, joga pra flag de habilita��o
                    {
                        setBlink_T02(0xc0);
                    }
                    
                    if(getBlink_T02() > 0xc4)//se esta dentro do limite da linha de cima, decrementa
                    {
                        setBlink_T02(getBlink_T02() - 1);
                    }
                } else
                {
                    if(getBlink_T02() == 0x86)//se estiver no limite, joga pra flag de habilita��o
                    {
                        setBlink_T02(0x80);
                    }
                    
                    if(getBlink_T02() > 0x86)//se esta dentro do limite da linha debaixo, decrementa
                    {
                        setBlink_T02(getBlink_T02() - 1);
                    }
                }
            }

        
        //incrementando valores
        if(evento == EV_UP)
        {
            switch(getBlink_T02())
            {
                case 0xc9:
                    setMskUpperLevel(getMskUpperLevel() + 0);
                    break;
                case 0xc8:
                    setMskUpperLevel(getMskUpperLevel() + 1000);
                    break;
                case 0xc7:
                    setMskUpperLevel(getMskUpperLevel() + 100);
                    break;
                case 0xc6:
                    setMskUpperLevel(getMskUpperLevel() + 10);
                    break;
                case 0xc5:
                    setMskUpperLevel(getMskUpperLevel() + 1);
                    break;
                case 0xc0:
                    setMskAlarmHighFlag((getMskAlarmHighFlag() ^ 0x01));
                    break;
                    
                case 0x8a:
                    setMskLowerLevel(getMskLowerLevel() + 0);
                    break;
                case 0x89:
                    setMskLowerLevel(getMskLowerLevel() + 1000);
                    break;
                case 0x88:
                    setMskLowerLevel(getMskLowerLevel() + 100);
                    break;
                case 0x87:
                    setMskLowerLevel(getMskLowerLevel() + 10);
                    break;
                case 0x86:
                    setMskLowerLevel(getMskLowerLevel() + 1);
                    break;
                case 0x80:
                    setMskAlarmLowFlag((getMskAlarmLowFlag() ^ 0x01));
                    break;
            }
        }
        
        //decrementando valores
        if(evento == EV_DOWN)
        {
            switch(getBlink_T02())
            {
                case 0xc9:
                    setMskUpperLevel(getMskUpperLevel() - 0);
                    break;
                case 0xc8:
                    if(getMskUpperLevel() < 1000)
                    {
                        break;
                    }
                    setMskUpperLevel(getMskUpperLevel() - 1000);
                    break;
                case 0xc7:
                    if(getMskUpperLevel() < 100)
                    {
                        break;
                    }
                    setMskUpperLevel(getMskUpperLevel() - 100);
                    break;
                case 0xc6:
                    if(getMskUpperLevel() < 10)
                    {
                        break;
                    }
                    setMskUpperLevel(getMskUpperLevel() - 10);
                    break;
                case 0xc5:
                    if(getMskUpperLevel() < 1)
                    {
                        break;
                    }
                    setMskUpperLevel(getMskUpperLevel() - 1);
                    break;
                case 0xc0:
                    setMskAlarmHighFlag((getMskAlarmHighFlag() ^ 0x01));
                    break;
                    
                case 0x8a:
                    setMskLowerLevel(getMskLowerLevel() - 0);
                    break;
                case 0x89:
                    if(getMskLowerLevel() < 1000)
                    {
                        break;
                    }
                    setMskLowerLevel(getMskLowerLevel() - 1000);
                    break;
                case 0x88:
                    if(getMskLowerLevel() < 100)
                    {
                        break;
                    }
                    setMskLowerLevel(getMskLowerLevel() - 100);
                    break;
                case 0x87:
                    if(getMskLowerLevel() < 10)
                    {
                        break;
                    }
                    setMskLowerLevel(getMskLowerLevel() - 10);
                    break;
                case 0x86:
                    if(getMskLowerLevel() < 1)
                    {
                        break;
                    }
                    setMskLowerLevel(getMskLowerLevel() - 1);
                    break;
                case 0x80:
                    setMskAlarmLowFlag((getMskAlarmLowFlag() ^ 0x01));
                    break;
            }
        }
}
        




Screen02Port(int evento)
{
    if (evento == EV_ENTER)
            {
                setState(STATE_SCREEN_02);
                
                //desligando blink
                lcdCommand(0x0c);
                
                //atualizando os valores com base nos masked values
                setUpperLevel(getMskUpperLevel());
                setLowerLevel(getMskLowerLevel());
                
                setAlarmHighFlag(getMskAlarmHighFlag());
                setAlarmLowFlag(getMskAlarmLowFlag());
            }
            
            //movimento para a esquerda
            if(evento == EV_LEFT)
            {
                if(getBlink_T02() > 0x8f)//se for maior entao esta na linha de cima
                {
                    if(getBlink_T02() == 0xc0)//se estiver na flag de habilita��o, volta pro editor de valor
                    {
                        setBlink_T02(0xc4);
                    }
                    
                    if(getBlink_T02() < 0xc9)//se esta dentro do limite da linha de cima, incrementa
                    {
                        setBlink_T02(getBlink_T02() + 1);
                    }
                } else
                {
                    if(getBlink_T02() == 0x80)//se estiver na flag de habilita��o, joga pro editor de valor
                    {
                        setBlink_T02(0x83);
                    }
                    
                    if(getBlink_T02() < 0x88)//se esta dentro do limite da linha debaixo, incrementa
                    {
                        setBlink_T02(getBlink_T02() + 1);
                    }
                    
                    if(getBlink_T02() == 0x89)//se estiver no limite, joga pra linha de cima na flag de habilita��o
                    {
                        setBlink_T02(0xc0);
                    }
                }
            }
            
            //movimento para a direita
            if(evento == EV_RIGHT)
            {
                if(getBlink_T02() > 0x8f)//se for maior entao esta na linha de cima
                {
                    if(getBlink_T02() == 0xc0)//se estiver na flag de habilita��o, joga pra linha de baixo
                    {
                        setBlink_T02(0x88);
                    }
                    
                    if(getBlink_T02() == 0xc5)//se estiver no limite, joga pra flag de habilita��o
                    {
                        setBlink_T02(0xc0);
                    }
                    
                    if(getBlink_T02() > 0xc4)//se esta dentro do limite da linha de cima, decrementa
                    {
                        setBlink_T02(getBlink_T02() - 1);
                    }
                } else
                {
                    if(getBlink_T02() == 0x84)//se estiver no limite, joga pra flag de habilita��o
                    {
                        setBlink_T02(0x80);
                    }
                    
                    if(getBlink_T02() > 0x84)//se esta dentro do limite da linha debaixo, decrementa
                    {
                        setBlink_T02(getBlink_T02() - 1);
                    }
                }
            }

        
        //incrementando valores
        if(evento == EV_UP)
        {
            switch(getBlink_T02())
            {
                case 0xc9:
                    setMskUpperLevel(getMskUpperLevel() + 0);
                    break;
                case 0xc8:
                    setMskUpperLevel(getMskUpperLevel() + 1000);
                    break;
                case 0xc7:
                    setMskUpperLevel(getMskUpperLevel() + 100);
                    break;
                case 0xc6:
                    setMskUpperLevel(getMskUpperLevel() + 10);
                    break;
                case 0xc5:
                    setMskUpperLevel(getMskUpperLevel() + 1);
                    break;
                case 0xc0:
                    setMskAlarmHighFlag((getMskAlarmHighFlag() ^ 0x01));
                    break;
                    
                case 0x88:
                    setMskLowerLevel(getMskLowerLevel() + 0);
                    break;
                case 0x87:
                    setMskLowerLevel(getMskLowerLevel() + 1000);
                    break;
                case 0x86:
                    setMskLowerLevel(getMskLowerLevel() + 100);
                    break;
                case 0x85:
                    setMskLowerLevel(getMskLowerLevel() + 10);
                    break;
                case 0x84:
                    setMskLowerLevel(getMskLowerLevel() + 1);
                    break;
                case 0x80:
                    setMskAlarmLowFlag((getMskAlarmLowFlag() ^ 0x01));
                    break;
            }
        }
        
        //decrementando valores
        if(evento == EV_DOWN)
        {
            switch(getBlink_T02())
            {
                case 0xc9:
                    setMskUpperLevel(getMskUpperLevel() - 0);
                    break;
                case 0xc8:
                    if(getMskUpperLevel() < 1000)
                    {
                        break;
                    }
                    setMskUpperLevel(getMskUpperLevel() - 1000);
                    break;
                case 0xc7:
                    if(getMskUpperLevel() < 100)
                    {
                        break;
                    }
                    setMskUpperLevel(getMskUpperLevel() - 100);
                    break;
                case 0xc6:
                    if(getMskUpperLevel() < 10)
                    {
                        break;
                    }
                    setMskUpperLevel(getMskUpperLevel() - 10);
                    break;
                case 0xc5:
                    if(getMskUpperLevel() < 1)
                    {
                        break;
                    }
                    setMskUpperLevel(getMskUpperLevel() - 1);
                    break;
                case 0xc0:
                    setMskAlarmHighFlag((getMskAlarmHighFlag() ^ 0x01));
                    break;
                    
                case 0x88:
                    setMskLowerLevel(getMskLowerLevel() - 0);
                    break;
                case 0x87:
                    if(getMskLowerLevel() < 1000)
                    {
                        break;
                    }
                    setMskLowerLevel(getMskLowerLevel() - 1000);
                    break;
                case 0x86:
                    if(getMskLowerLevel() < 100)
                    {
                        break;
                    }
                    setMskLowerLevel(getMskLowerLevel() - 100);
                    break;
                case 0x85:
                    if(getMskLowerLevel() < 10)
                    {
                        break;
                    }
                    setMskLowerLevel(getMskLowerLevel() - 10);
                    break;
                case 0x84:
                    if(getMskLowerLevel() < 1)
                    {
                        break;
                    }
                    setMskLowerLevel(getMskLowerLevel() - 1);
                    break;
                case 0x80:
                    setMskAlarmLowFlag((getMskAlarmLowFlag() ^ 0x01));
                    break;
            }
        }
}