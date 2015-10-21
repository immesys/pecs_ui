/* 
 * File:   ledctl.h
 * Author: immesys
 *
 * Created on October 5, 2015, 12:26 PM
 */

#ifndef LEDCTL_H
#define	LEDCTL_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

void led_ctl_init();
extern void ledctl_tasks();
extern void register_tasks();
extern void encoders_tasks();
extern void encoders_init();
extern uint8_t *status_led_color;
extern uint8_t *status_led_mode;
extern uint8_t *top_dial_colors;
extern uint8_t *top_dial_brightness;
extern uint8_t *top_knob_color;
extern uint8_t *bottom_dial_colors;
extern uint8_t *bottom_dial_brightness;
extern uint8_t *bottom_knob_color;
extern uint8_t *top_presses;
extern uint8_t *bottom_presses;
extern int8_t  *top_clicks;
extern int8_t  *bottom_clicks;
extern int8_t  *top_setting;
extern int8_t  *bottom_setting;
extern uint8_t *enable_autoset;

#define COLOR_rgb 0
#define COLOR_rgB 1
#define COLOR_rGb 2
#define COLOR_rGB 3
#define COLOR_Rgb 4
#define COLOR_RgB 5
#define COLOR_RGb 6
#define COLOR_RGB 7
#define RED_MASK   4
#define GREEN_MASK 2
#define BLUE_MASK  1

#define MODE_BLINK 1
#define MODE_STEADY 0

#ifdef	__cplusplus
}
#endif

#endif	/* LEDCTL_H */

