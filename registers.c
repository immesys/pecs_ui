
/* Note: This is an example of the I2C1_StatusCallback()
         implementation. This is an emulated EEPROM Memory
         configured to act as a I2C Slave Device.
         For specific slave device implementation, remove
         or modify this function to the specific slave device
         behavior.
 */

#define MODE_OFF    0x0
#define MODE_DIM    0x1
#define MODE_MED    0x2
#define MODE_BRIGHT 0x3
#define MODE_SOLID  0x0
#define MODE_BLINK  0x4

struct __attribute__((packed))
{
    int8_t top_dial;
    int8_t bottom_dial;
    uint8_t top_clicks;
    uint8_t bottom_clicks;
    uint8_t pow_rg;
    uint8_t pow_bm;
    uint8_t pow_b;
    uint8_t top_color;
    uint8_t bottom_color;
    
} register_map;
static uint8_t i2c1_slaveWriteData = 0xAA;

bool I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS status) {

    // this emulates the slave device memory where data written to slave
    // is placed and data read from slave is taken
    static uint8_t EMULATE_EEPROM_Memory[64] ={
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    };

    static uint16_t address, addrByteCount;
    static bool addressState = true;

    switch (status) {
        case I2C1_SLAVE_TRANSMIT_REQUEST_DETECTED:

            // set up the slave driver buffer transmit pointer
            I2C1_ReadPointerSet(&EMULATE_EEPROM_Memory[address]);
            address++;

            break;

        case I2C1_SLAVE_RECEIVE_REQUEST_DETECTED:

            addrByteCount = 0;
            addressState = true;

            // set up the slave driver buffer receive pointer
            I2C1_WritePointerSet(&i2c1_slaveWriteData);

            break;

        case I2C1_SLAVE_RECEIVED_DATA_DETECTED:

            if (addressState == true) {
                // get the address of the memory being written
                if (addrByteCount == 0) {
                    address = (i2c1_slaveWriteData << 8) & 0xFF00;
                    addrByteCount++;
                } else if (addrByteCount == 1) {
                    address = address | i2c1_slaveWriteData;
                    addrByteCount = 0;
                    addressState = false;
                }
            } else // if (addressState == false)
            {
                // set the memory with the received data
                EMULATE_EEPROM_Memory[address] = i2c1_slaveWriteData;
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
