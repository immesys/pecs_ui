
#include <p24FJ128GA410.h>
#include "ledctl.h"
#include <stdint.h>

#define KAQA_FLAG IOCFGbits.IOCFG15
#define KAQB_FLAG IOCFEbits.IOCFE5
#define KBQA_FLAG IOCFEbits.IOCFE6
#define KBQB_FLAG IOCFEbits.IOCFE7
#define KAS_FLAG IOCFCbits.IOCFC1
#define KBS_FLAG IOCFCbits.IOCFC2
#define KAQA _RG15
#define KAQB _RE5
#define KBQA _RE6
#define KBQB _RE7

//Ticks are 7ms. I think buttons should inhibit by 200ms so 26 ticks
#define INHIBIT_TIME 26
uint16_t kas_inhibit_time;
uint16_t kbs_inhibit_time;
uint8_t kas_inhibited;
uint8_t kbs_inhibited;

#define S_IDLE 0
#define S_A_FELL 1
#define S_B_FELL 2
#define S_AB_FELL 3
#define S_BA_FELL 4
#define S_AB_A_ROSE 5
#define S_BA_B_ROSE 6

uint8_t ka_state;
uint8_t kb_state;

void encoders_init()
{
    //Pins we are interested in
    //KAS RC1    
    //KBS RC2    
    //KAQA RG15
    //KAQB RE5   
    //KBQA RE6
    //KBQB RE7
    
    KAQA_FLAG = 0;
    KAQB_FLAG = 0;
    KBQA_FLAG = 0;
    KBQB_FLAG = 0;
    KAS_FLAG = 0;
    KBS_FLAG = 0;
    
    //Quadrature encoder
    IOCNGbits.IOCNG15 = 1;
    IOCPGbits.IOCPG15 = 1;
    IOCNEbits.IOCNE5 = 1;
    IOCPEbits.IOCPE5 = 1;
    IOCNEbits.IOCNE6 = 1;
    IOCPEbits.IOCPE6 = 1;
    IOCNEbits.IOCNE7 = 1;
    IOCPEbits.IOCPE7 = 1;
    
    //Switches, rising only
    IOCPCbits.IOCPC1 = 1;
    IOCPCbits.IOCPC2 = 1;
    
    _IOCON = 1;
    _CNIE = 1;
    
}
void __attribute__ ((__interrupt__, no_auto_psv)) _CNInterrupt(void)
{
    if (KAQA_FLAG)
    {
        switch (ka_state)
        {
            case S_IDLE:
                if (KAQA)
                {
                    //Odd, we are in idle, why is it rising
                }
                else 
                {
                    ka_state = S_A_FELL;
                }
                break;
            case S_A_FELL:
                if (KAQA)
                {
                    ka_state = S_IDLE;
                }
                else 
                {
                    //Odd, we should be low already
                }
                break;
            case S_B_FELL:
                if (KAQA)
                {
                    //Odd, we should be like this already
                }
                else
                {
                    ka_state = S_BA_FELL;
                }
                break;
            case S_AB_FELL:
                if (KAQA)
                {
                    ka_state = S_AB_A_ROSE;
                }
                else
                {
                    //Odd, both should be low
                }
                break;
            case S_BA_FELL:
                if (KAQA)
                {
                    //Step back
                    ka_state = S_B_FELL;
                }
                else
                {
                    //Already meant to be low...
                }
                break;
            case S_BA_B_ROSE:
                if (KAQA)
                {
                    //This is a BA turn
                    (*bottom_clicks)--;
                    ka_state = S_IDLE;
                }
                else
                {
                    //We should be low already
                }
                break;
            case S_AB_A_ROSE:
                if (KAQA)
                {
                    //Already meant to be high
                }
                else
                {
                    //Step backwards
                    ka_state = S_AB_FELL;
                }
                break;
        }
        KAQA_FLAG = 0;
    }
    if (_IOCPEF)
    {
        if (KAQB_FLAG)
        {
            switch (ka_state)
            {
                case S_IDLE:
                    if (KAQB)
                    {
                        //Odd, we are in idle, why is it rising
                    }
                    else 
                    {
                        ka_state = S_B_FELL;
                    }
                    break;
                case S_A_FELL:
                    if (KAQB)
                    {
                        //Odd we should be here already
                    }
                    else 
                    {
                        ka_state = S_AB_FELL;
                    }
                    break;
                case S_B_FELL:
                    if (KAQB)
                    {
                        ka_state = S_IDLE;
                    }
                    else
                    {
                        //Odd we should be here already
                    }
                    break;
                case S_AB_FELL:
                    if (KAQB)
                    {
                        //Step back
                        ka_state = S_A_FELL;
                    }
                    else
                    {
                        //Odd, both should be low
                    }
                    break;
                case S_BA_FELL:
                    if (KAQB)
                    {
                        ka_state = S_BA_B_ROSE;
                    }
                    else
                    {
                        //Already meant to be low...
                    }
                    break;
                case S_BA_B_ROSE:
                    if (KAQB)
                    {
                        //Already meant to be high
                    }
                    else
                    {
                        //Step backwards
                        ka_state = S_BA_FELL;
                    }
                    break;
                case S_AB_A_ROSE:
                    if (KAQB)
                    {
                        //This is a AB turn
                        (*bottom_clicks)++;
                        ka_state = S_IDLE;
                    }
                    else
                    {
                        //We should be low already
                    }
                    break;
            }
            KAQB_FLAG = 0;
        }
        if (KBQA_FLAG)
        {
            switch (kb_state)
            {
                case S_IDLE:
                    if (KBQA)
                    {
                        //Odd, we are in idle, why is it rising
                    }
                    else 
                    {
                        kb_state = S_A_FELL;
                    }
                    break;
                case S_A_FELL:
                    if (KBQA)
                    {
                        kb_state = S_IDLE;
                    }
                    else 
                    {
                        //Odd, we should be low already
                    }
                    break;
                case S_B_FELL:
                    if (KBQA)
                    {
                        //Odd, we should be like this already
                    }
                    else
                    {
                        kb_state = S_BA_FELL;
                    }
                    break;
                case S_AB_FELL:
                    if (KBQA)
                    {
                        kb_state = S_AB_A_ROSE;
                    }
                    else
                    {
                        //Odd, both should be low
                    }
                    break;
                case S_BA_FELL:
                    if (KBQA)
                    {
                        //Step back
                        kb_state = S_B_FELL;
                    }
                    else
                    {
                        //Already meant to be low...
                    }
                    break;
                case S_BA_B_ROSE:
                    if (KBQA)
                    {
                        //This is a BA turn
                        (*top_clicks)--;
                        kb_state = S_IDLE;
                    }
                    else
                    {
                        //We should be low already
                    }
                    break;
                case S_AB_A_ROSE:
                    if (KBQA)
                    {
                        //Already meant to be high
                    }
                    else
                    {
                        //Step backwards
                        kb_state = S_AB_FELL;
                    }
                    break;
            }
            KBQA_FLAG = 0;
        }
        if (KBQB_FLAG)
        {
            switch (kb_state)
            {
                case S_IDLE:
                    if (KBQB)
                    {
                        //Odd, we are in idle, why is it rising
                    }
                    else 
                    {
                        kb_state = S_B_FELL;
                    }
                    break;
                case S_A_FELL:
                    if (KBQB)
                    {
                        //Odd we should be here already
                    }
                    else 
                    {
                        kb_state = S_AB_FELL;
                    }
                    break;
                case S_B_FELL:
                    if (KBQB)
                    {
                        kb_state = S_IDLE;
                    }
                    else
                    {
                        //Odd we should be here already
                    }
                    break;
                case S_AB_FELL:
                    if (KBQB)
                    {
                        //Step back
                        kb_state = S_A_FELL;
                    }
                    else
                    {
                        //Odd, both should be low
                    }
                    break;
                case S_BA_FELL:
                    if (KBQB)
                    {
                        kb_state = S_BA_B_ROSE;
                    }
                    else
                    {
                        //Already meant to be low...
                    }
                    break;
                case S_BA_B_ROSE:
                    if (KBQB)
                    {
                        //Already meant to be high
                    }
                    else
                    {
                        //Step backwards
                        kb_state = S_BA_FELL;
                    }
                    break;
                case S_AB_A_ROSE:
                    if (KBQB)
                    {
                        //This is a AB turn
                        (*top_clicks)++;
                        kb_state = S_IDLE;
                    }
                    else
                    {
                        //We should be low already
                    }
                    break;
            }
            KBQB_FLAG = 0;
        }
    }
    if (_IOCPCF)
    {
        if (KAS_FLAG)
        {
            if(!kas_inhibited)
            {
                (*bottom_presses)++;
                kas_inhibited = 1;
                kas_inhibit_time = TMR1;
            }
            KAS_FLAG = 0;
        }
        if (KBS_FLAG)
        {
            if(!kbs_inhibited)
            {
                (*top_presses)++;
                kbs_inhibited = 1;
                kbs_inhibit_time = TMR1;
            }
            KBS_FLAG = 0;
        }
    }
    _CNIF = 0;
    
}

void encoders_tasks()
{
    uint16_t now = TMR1;
    if (kas_inhibited && (uint16_t)(now-kas_inhibit_time) > INHIBIT_TIME)
    {
        kas_inhibited = 0;
    }
    if (kbs_inhibited && (uint16_t)(now-kbs_inhibit_time) > INHIBIT_TIME)
    {
        kbs_inhibited = 0;
    }
}