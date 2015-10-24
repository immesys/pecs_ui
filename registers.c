

#include <stdint.h>
#include "mcc_generated_files/i2c1.h"
#include "ledctl.h"

/**
 * REGISTER MAP
 * 0:  STATUS R
 * 1:  STATUS G
 * 2:  STATUS B
 * 3:  STATUS MODE
 * 4:  TOP LED 0
 * 5:  TOP LED 1
 * 6:  TOP LED 2
 * 7:  TOP LED 3
 * 8:  TOP LED 4
 * 9:  TOP LED 5
 * 10: TOP LED 6
 * 11: TOP LED 7
 * 12: TOP LED 8
 * 13: TOP BRIGHTNESS
 * 14: TOP KNOB R
 * 15: TOP KNOB G
 * 16: TOP KNOB B
 * 17: BOT LED 0
 * 18: BOT LED 1
 * 19: BOT LED 2
 * 20: BOT LED 3
 * 21: BOT LED 4
 * 22: BOT LED 5
 * 23: BOT LED 6
 * 24: BOT LED 7
 * 25: BOT LED 8
 * 26: BOT BRIGHTNESS
 * 27: BOT KNOB R
 * 28: BOT KNOB G
 * 29: BOT KNOB B
 * 30: TOP CLICKS
 * 31: BOT CLICKS
 * 32: TOP PRESSES
 * 33: BOT PRESSES
 * 34: TOP SETTING
 * 35: BOT SETTING
 * 36: ENABLE AUTOSET
 * 37: KICK WDT + STORE
 * 38: FIRMWARE VERSION
 */

uint8_t register_backing [39];

uint8_t *status_led_color       = &register_backing[0];
uint8_t *status_led_mode        = &register_backing[3];
uint8_t *top_dial_colors        = &register_backing[4];
uint8_t *top_dial_brightness    = &register_backing[13];
uint8_t *top_knob_color         = &register_backing[14];
uint8_t *bottom_dial_colors     = &register_backing[17];
uint8_t *bottom_dial_brightness = &register_backing[26];
uint8_t *bottom_knob_color      = &register_backing[27];
uint8_t *top_presses            = &register_backing[32];
uint8_t *bottom_presses         = &register_backing[33];
int8_t  *top_clicks             = (int8_t*) &register_backing[30];
int8_t  *bottom_clicks          = (int8_t*) &register_backing[31];
int8_t  *top_setting            = (int8_t*) &register_backing[34];
int8_t  *bottom_setting         = (int8_t*) &register_backing[35];
uint8_t *enable_autoset         = &register_backing[36];
uint8_t *wdt_number             = &register_backing[37];
uint8_t *firmware_version       = &register_backing[38];

bool I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS status) {

    static uint8_t data;
    static uint8_t address;
    static bool first;
    
    switch (status) {
        case I2C1_SLAVE_TRANSMIT_REQUEST_DETECTED:
            // set up the slave driver buffer transmit pointer
            I2C1_ReadPointerSet(&register_backing[address]);
            address++;
            break;

        case I2C1_SLAVE_RECEIVE_REQUEST_DETECTED:
            first = true;
            // set up the slave driver buffer receive pointer
            I2C1_WritePointerSet(&data);
            break;

        case I2C1_SLAVE_RECEIVED_DATA_DETECTED:
            if (first) 
            {
                address = data;
                first = false;
                if (data == 37)
                {
                    (*wdt_number) ++;
                    __builtin_clrwdt();
                }
            }
            else
            {
                register_backing[address] = data;
                address++;
            }
            break;
        case I2C1_SLAVE_10BIT_RECEIVE_REQUEST_DETECTED:
            // do something here when 10-bit address is detected
            // 10-bit address is detected
            break;
        default:
            break;

    }
    return true;
}

void register_tasks()
{
    *firmware_version = 0x12;
    static int8_t last_top_clicks = 0;
    static int8_t last_bottom_clicks = 0;
    static uint8_t last_top_presses = 0;
    static uint8_t last_bottom_presses = 0;
    if(*top_clicks - last_top_clicks < 0)
        *top_setting -= 25;
    if(*top_clicks - last_top_clicks > 0)
        *top_setting += 25;
    if(*bottom_clicks - last_bottom_clicks < 0)
        *bottom_setting -= 25;
    if(*bottom_clicks - last_bottom_clicks > 0)
        *bottom_setting += 25;
    last_top_clicks = *top_clicks;
    last_bottom_clicks = *bottom_clicks;
    if(*top_presses != last_top_presses)
        *top_setting = 0;
    if(*bottom_presses != last_bottom_presses)
        *bottom_setting = 0;
    last_top_presses = *top_presses;
    last_bottom_presses = *bottom_presses;
    if (*top_setting < -100) *top_setting = -100;
    if (*top_setting > 100) *top_setting = 100;
    if (*bottom_setting < -100) *bottom_setting = -100;
    if (*bottom_setting > 100) *bottom_setting = 100;
    if(*enable_autoset)
    {
        top_dial_colors[0] = (*top_setting <= -100) ? COLOR_Rgb : COLOR_rgb;
        top_dial_colors[1] = (*top_setting <= -70) ? COLOR_Rgb : COLOR_rgb;
        top_dial_colors[2] = (*top_setting <= -50) ? COLOR_Rgb : COLOR_rgb;
        top_dial_colors[3] = (*top_setting <= -25) ? COLOR_Rgb : COLOR_rgb;
        top_dial_colors[4] = COLOR_rGb;
        top_dial_colors[5] = (*top_setting >= 25) ? COLOR_rgB : COLOR_rgb;
        top_dial_colors[6] = (*top_setting >= 50) ? COLOR_rgB : COLOR_rgb;
        top_dial_colors[7] = (*top_setting >= 75) ? COLOR_rgB : COLOR_rgb;
        top_dial_colors[8] = (*top_setting >= 100) ? COLOR_rgB : COLOR_rgb;
        bottom_dial_colors[0] = (*bottom_setting <= -100) ? COLOR_Rgb : COLOR_rgb;
        bottom_dial_colors[1] = (*bottom_setting <= -70) ? COLOR_Rgb : COLOR_rgb;
        bottom_dial_colors[2] = (*bottom_setting <= -50) ? COLOR_Rgb : COLOR_rgb;
        bottom_dial_colors[3] = (*bottom_setting <= -25) ? COLOR_Rgb : COLOR_rgb;
        bottom_dial_colors[4] = COLOR_rGb;
        bottom_dial_colors[5] = (*bottom_setting >= 25) ? COLOR_rgB : COLOR_rgb;
        bottom_dial_colors[6] = (*bottom_setting >= 50) ? COLOR_rgB : COLOR_rgb;
        bottom_dial_colors[7] = (*bottom_setting >= 75) ? COLOR_rgB : COLOR_rgb;
        bottom_dial_colors[8] = (*bottom_setting >= 100) ? COLOR_rgB : COLOR_rgb;
    }
}
