#include <xc.h>

#include <stdint.h>

#include "ledctl.h"

/*
KAB OCM1A
KAG OCM1B RP26
KBR OCM2A
KBG RP27
KBB OCM3A
KAR RP22
DB OC5
DA OC6
PG RP25
PR OC4
PB RP20
 */
void led_ctl_init()
{
    ////Init CCPs
    
    //KAB OCM1A
    CCP1CON1L = 0;
    CCP1CON1H = 0;
    CCP1CON2L = 0;
    CCP1TMRL = 0;
    CCP1PRL = 0xFE; //Full period
    CCP1RA = 0; //Rising edge on 0
    CCP1RB = 0x80; //50% duty cycle
    CCP1CON1Lbits.MOD = 0b0101; //Dual Edge Compare Mode Buffered (PWM)
    CCP1CON1Lbits.TMRPS = 0b11; //1:64 prescale: 250kHz
    CCP1CON2Hbits.OCAEN = 1; //Enable OCA
    CCP1CON1Lbits.CCPON = 1;  
    
    //KBR OCM2A
    CCP2CON1L = 0;
    CCP2CON1H = 0;
    CCP2CON2L = 0;
    CCP2TMRL = 0;
    CCP2PRL = 0xFE; //Full period
    CCP2RA = 0x00; //Rising edge on 0
    CCP2RB = 0x80; //50% duty cycle
    CCP2CON1Lbits.MOD = 0b0101; //Dual Edge Compare Mode Buffered (PWM)
    CCP2CON1Lbits.TMRPS = 0b11; //1:64 prescale: 250kHz
    CCP2CON2Hbits.OCAEN = 1; //Enable OCA
    CCP2CON1Lbits.CCPON = 1; 

    //KBB OCM3A
    CCP3CON1L = 0;
    CCP3CON1H = 0;
    CCP3CON2L = 0;
    CCP3TMRL = 0;
    CCP3PRL = 0xFE; //Full period
    CCP3RA = 0; //Rising edge on 0
    CCP3RB = 0x80; //50% duty cycle
    CCP3CON1Lbits.MOD = 0b0101; //Dual Edge Compare Mode Buffered (PWM)
    CCP3CON1Lbits.TMRPS = 0b11; //1:64 prescale: 250kHz
    CCP3CON2Hbits.OCAEN = 1; //Enable OCA
    CCP3CON1Lbits.CCPON = 1; 
    

    //KAG OCM4A via RP26
    CCP4CON1L = 0;
    CCP4CON1H = 0;
    CCP4CON2L = 0;
    CCP4TMRL = 0;
    CCP4PRL = 0xFE; //Full period
    CCP4RA = 0; //Rising edge on 0
    CCP4RB = 0x80; //50% duty cycle
    CCP4CON1Lbits.MOD = 0b0101; //Dual Edge Compare Mode Buffered (PWM)
    CCP4CON1Lbits.TMRPS = 0b11; //1:64 prescale: 250kHz
    CCP4CON2Hbits.OCAEN = 1; //Enable OCA
    CCP4CON1Lbits.CCPON = 1; 

    
    //KBG OCM5 via RP27
    CCP5CON1L = 0;
    CCP5CON1H = 0;
    CCP5CON2L = 0;
    CCP5TMRL = 0;
    CCP5PRL = 0xFE; //Full period
    CCP5RA = 0; //Rising edge on 0
    CCP5RB = 0x80; //50% duty cycle
    CCP5CON1Lbits.MOD = 0b0101; //Dual Edge Compare Mode Buffered (PWM)
    CCP5CON1Lbits.TMRPS = 0b11; //1:64 prescale: 250kHz
    CCP5CON2Hbits.OCAEN = 1; //Enable OCA
    CCP5CON1Lbits.CCPON = 1; 

    //KAR OCM6 via RP22
    CCP6CON1L = 0;
    CCP6CON1H = 0;
    CCP6CON2L = 0;
    CCP6TMRL = 0;
    CCP6PRL = 0xFE; //Full period
    CCP6RA = 0; //Rising edge on 0
    CCP6RB = 0x80; //50% duty cycle
    CCP6CON1Lbits.MOD = 0b0101; //Dual Edge Compare Mode Buffered (PWM)
    CCP6CON1Lbits.TMRPS = 0b11; //1:64 prescale: 250kHz
    CCP6CON2Hbits.OCAEN = 1; //Enable OCA
    CCP6CON1Lbits.CCPON = 1; 
 
    ////Init TMR2
    T2CON = 0;
    T2CONbits.TCKPS = 0b10; //1:64 prescale : 250kHz
    T2CONbits.TON = 1;
    
    ///Init TMR1 ticking at 128 Hz
    T1CON = 0;
    T1CONbits.TECS = 0b10; //use LPRC (32768Hz)
    T1CONbits.TCS = 1; //Use TECS
    T1CONbits.TCKPS = 0b11; //Prescale 1:256
    T1CONbits.TON = 1;
    
    ////Init OCs
    //PG OC1(13) via RP25
    OC1CON1 = 0;
    OC1CON2 = 0;
    OC1CON1bits.OCTSEL = 0b000; //Use TMR2 as the clock
    OC1R = 0x80;
    OC1RS = 0xFF;
    OC1CON2bits.SYNCSEL = 0x1F; //Use itself as sync source
    OC1CON1bits.OCM = 6; //Edge aligned PWM
    
    //PB OC2(14) via RP20
    OC2CON1 = 0;
    OC2CON2 = 0;
    OC2CON1bits.OCTSEL = 0b000; //Use TMR2 as the clock
    OC2R = 0x80;
    OC2RS = 0xFF;
    OC2CON2bits.SYNCSEL = 0x1F; //Use itself as sync source
    OC2CON1bits.OCM = 6; //Edge aligned PWM
    
    //PR OC4 direct
    OC4CON1 = 0;
    OC4CON2 = 0;
    OC4CON1bits.OCTSEL = 0b000; //Use TMR2 as the clock
    OC4R = 0x80;
    OC4RS = 0xFF;
    OC4CON2bits.SYNCSEL = 0x1F; //Use itself as sync source
    OC4CON1bits.OCM = 6; //Edge aligned PWM
    
    //DB OC5 direct
    OC5CON1 = 0;
    OC5CON2 = 0;
    OC5CON1bits.OCTSEL = 0b000; //Use TMR2 as the clock
    OC5R = 0x80;
    OC5RS = 0xFF;
    OC5CON2bits.SYNCSEL = 0x1F; //Use itself as sync source
    OC5CON1bits.OCM = 6; //Edge aligned PWM
    
    //DA OC6 direct
    OC6CON1 = 0;
    OC6CON2 = 0;
    OC6CON1bits.OCTSEL = 0b000; //Use TMR2 as the clock
    OC6R = 0x80;
    OC6RS = 0xFF;
    OC6CON2bits.SYNCSEL = 0x1F; //Use itself as sync source
    OC6CON1bits.OCM = 6; //Edge aligned PWM
   
    //Clear IOLOCK for RP
    SET_CPU_IPL(7);
    __builtin_write_OSCCONL(OSCCONL & 0xbf); //Clear IOLOCK
    SET_CPU_IPL(0);
    
    //On RP:
    //OC1 = 13  = PG (RP25)
    //OC2 = 14  = PB (RP20)
    //OC3 = 15  = unused
    //OCM4 = 16 = KAG (RP26)
    //OCM5 = 17 = KBG (RP27)
    //OCM6 = 18 = KAR (RP22)
    
    _RP25R = 13; //assign OC1(13) to RP25 for PR
    _RP20R = 14; //assign OC2(14) to RP20 for PB
    _RP26R = 16; //assign OCM4(16) to RP26 for KAG
    _RP27R = 17; //assign OCM5(17) to RP27 for KBG
    _RP22R = 18; //assign OCM6(18) to RP22 for KAR
    
    //Setup TRIS
    _TRISF3  = 0; 
    _TRISF2  = 0; 
    _TRISF8  = 0; 
    _TRISF7  = 0; 
    _TRISF6  = 0; 
    _TRISA2  = 0; 
    _TRISA3  = 0; 
    _TRISA4  = 0; 
    _TRISA5  = 0; 
    _TRISC12 = 0; 
    _TRISC15 = 0; 
    _TRISA14 = 0; 
    _TRISA15 = 0; 
    _TRISD8  = 0; 
    _TRISD9  = 0; 
    _TRISD10 = 0; 
    _TRISD11 = 0; 
    _TRISD0  = 0; 
    _TRISD1  = 0; 
    _TRISD2  = 0; 
    _TRISD12 = 0; 
    _TRISD13 = 0; 
    _TRISF1  = 0; 
    _TRISG1  = 0; 
    _TRISG0  = 0;
    _TRISC3  = 0;
    _TRISC4  = 0;
    _TRISA0  = 0;
    _TRISE8  = 0;
    _TRISE9  = 0;
    _TRISB4  = 0;
    _TRISB3  = 0;
    _TRISB2  = 0;
    _TRISB6  = 0;
    _TRISB7  = 0;
    _TRISA9  = 0;
    _TRISA10 = 0;
    _TRISB8  = 0;
    _TRISB9  = 0;
    _TRISB10 = 0;
    _TRISB11 = 0;
    _TRISA1  = 0;
    _TRISF13 = 0;
    _TRISF12 = 0;
    _TRISB13 = 0;
    _TRISB12 = 0;
    _TRISB14 = 0;
    _TRISB15 = 0;
    _TRISD14 = 0;
    _TRISD15 = 0;
    _TRISF4  = 0;
    _TRISF5  = 0; 
    
}





void sync_top_dial()
{
    OC5R = *top_dial_brightness;
    _LATF3  = (top_dial_colors[0] & RED_MASK) ? 1 : 0;
    _LATF2  = (top_dial_colors[0] & GREEN_MASK) ? 1 : 0;
    _LATF8  = (top_dial_colors[0] & BLUE_MASK) ? 1 : 0;
    _LATF7  = (top_dial_colors[1] & RED_MASK) ? 1 : 0;
    _LATF6  = (top_dial_colors[1] & GREEN_MASK) ? 1 : 0;
    _LATA2  = (top_dial_colors[1] & BLUE_MASK) ? 1 : 0;
    _LATA3  = (top_dial_colors[2] & RED_MASK) ? 1 : 0;
    _LATA4  = (top_dial_colors[2] & GREEN_MASK) ? 1 : 0;
    _LATA5  = (top_dial_colors[2] & BLUE_MASK) ? 1 : 0;
    _LATC12 = (top_dial_colors[3] & RED_MASK) ? 1 : 0;
    _LATC15 = (top_dial_colors[3] & GREEN_MASK) ? 1 : 0;
    _LATA14 = (top_dial_colors[3] & BLUE_MASK) ? 1 : 0;
    _LATA15 = (top_dial_colors[4] & RED_MASK) ? 1 : 0;
    _LATD8  = (top_dial_colors[4] & GREEN_MASK) ? 1 : 0;
    _LATD9  = (top_dial_colors[4] & BLUE_MASK) ? 1 : 0;
    _LATD10 = (top_dial_colors[5] & RED_MASK) ? 1 : 0;
    _LATD11 = (top_dial_colors[5] & GREEN_MASK) ? 1 : 0;
    _LATD0  = (top_dial_colors[5] & BLUE_MASK) ? 1 : 0;
   // GOD FUCKING DAMMIT MICROCHIP!
   // _LATC13 = (top_dial_colors[6] & RED_MASK) ? 1 : 0;
   // _LATC14 = (top_dial_colors[6] & GREEN_MASK) ? 1 : 0;
    _LATD1  = (top_dial_colors[6] & BLUE_MASK) ? 1 : 0;
    _LATD2  = (top_dial_colors[7] & RED_MASK) ? 1 : 0;
    _LATD12 = (top_dial_colors[7] & GREEN_MASK) ? 1 : 0;
    _LATD13 = (top_dial_colors[7] & BLUE_MASK) ? 1 : 0;
    _LATF1 = (top_dial_colors[8] & RED_MASK) ? 1 : 0;
    _LATG1 = (top_dial_colors[8] & GREEN_MASK) ? 1 : 0;
    _LATG0 = (top_dial_colors[8] & BLUE_MASK) ? 1 : 0;
    
    //KBR
    CCP2RB = 255 - top_knob_color[0];
    //KBG
    CCP5RB = 255 - top_knob_color[1];
    //KBB
    CCP3RB = 255 - top_knob_color[2];
    
}

void sync_bottom_dial()
{
    OC6R = *bottom_dial_brightness;
    
    _LATC3 = (bottom_dial_colors[0] & RED_MASK) ? 1 : 0;
    _LATC4 = (bottom_dial_colors[0] & GREEN_MASK) ? 1 : 0;
    _LATA0 = (bottom_dial_colors[0] & BLUE_MASK) ? 1 : 0;
    _LATE8 = (bottom_dial_colors[1] & RED_MASK) ? 1 : 0;
    _LATE9 = (bottom_dial_colors[1] & GREEN_MASK) ? 1 : 0;
    _LATB4 = (bottom_dial_colors[1] & BLUE_MASK) ? 1 : 0;
    _LATB3 = (bottom_dial_colors[2] & RED_MASK) ? 1 : 0;
    _LATB2 = (bottom_dial_colors[2] & GREEN_MASK) ? 1 : 0;
    _LATB6 = (bottom_dial_colors[2] & BLUE_MASK) ? 1 : 0;
    _LATB7 = (bottom_dial_colors[3] & RED_MASK) ? 1 : 0;
    _LATA9 = (bottom_dial_colors[3] & GREEN_MASK) ? 1 : 0;
    _LATA10 = (bottom_dial_colors[3] & BLUE_MASK) ? 1 : 0;
    _LATB8 = (bottom_dial_colors[4] & RED_MASK) ? 1 : 0;
    _LATB9 = (bottom_dial_colors[4] & GREEN_MASK) ? 1 : 0;
    _LATB10 = (bottom_dial_colors[4] & BLUE_MASK) ? 1 : 0;
    _LATB11 = (bottom_dial_colors[5] & RED_MASK) ? 1 : 0;
    _LATA1 = (bottom_dial_colors[5] & GREEN_MASK) ? 1 : 0;
    _LATF13 = (bottom_dial_colors[5] & BLUE_MASK) ? 1 : 0;
    _LATF12 = (bottom_dial_colors[6] & RED_MASK) ? 1 : 0;
    _LATB13 = (bottom_dial_colors[6] & GREEN_MASK) ? 1 : 0;
    _LATB12 = (bottom_dial_colors[6] & BLUE_MASK) ? 1 : 0;
    _LATB14 = (bottom_dial_colors[7] & RED_MASK) ? 1 : 0;
    _LATB15 = (bottom_dial_colors[7] & GREEN_MASK) ? 1 : 0;
    _LATD14 = (bottom_dial_colors[7] & BLUE_MASK) ? 1 : 0;
    _LATD15 = (bottom_dial_colors[8] & RED_MASK) ? 1 : 0;
    _LATF4 = (bottom_dial_colors[8] & GREEN_MASK) ? 1 : 0;
    _LATF5 = (bottom_dial_colors[8] & BLUE_MASK) ? 1 : 0; 
    
    //KAR
    CCP6RB = 255 - bottom_knob_color[0];
    //KAG
    CCP4RB = 255 - bottom_knob_color[1];
    //KAB
    CCP1RB = 255 - bottom_knob_color[2]; 
}

void sync_status()
{
    if (*status_led_mode != MODE_BLINK || (TMR1 & 0x7F) < 0x40)
    {
        OC4R = status_led_color[0];
        OC1R = status_led_color[1];
        OC2R = status_led_color[2];
    }
    else 
    {
        OC4R = 0;
        OC1R = 0;
        OC2R = 0;
    }
}

void ledctl_tasks()
{
    sync_status();
    sync_bottom_dial();
    sync_top_dial();
}
