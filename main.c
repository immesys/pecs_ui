/*
 * File:   main.c
 * Author: immesys
 *
 * Created on October 4, 2015, 9:42 PM
 */


#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "ledctl.h"

void sleep()
{
    uint16_t then = TMR1;
    uint16_t now = TMR1;
    while (now - then < 30)
    {
        now = TMR1;
        __builtin_clrwdt();
        ledctl_tasks();
    }
    
}
int main(void) {
    SYSTEM_Initialize();
    led_ctl_init();
    encoders_init();
    
    //Indicating no connection from controller
    status_led_color[0] = 255;
    status_led_color[1] = 0;
    status_led_color[2] = 0;
    *status_led_mode = 1;
    
    //Default to dim dial
    *top_dial_brightness = 1;
    *bottom_dial_brightness = 1;
    
    //Set knob colors
    top_knob_color[0] = 0;
    top_knob_color[1] = 0;
    top_knob_color[2] = 0;
    bottom_knob_color[0] = 0;
    bottom_knob_color[1] = 0;                                                                                                                                                                                 ;
    bottom_knob_color[2] = 0;
    
    //Default to off settings
    *top_setting = 0;
    *bottom_setting = 0;
    *enable_autoset = 1;
    
    //Give the controller a little bit of a break on initial powerup
    __builtin_clrwdt();
    while(1)
    {
        register_tasks();
        ledctl_tasks();
        encoders_tasks();
    }
    return 0;
}
