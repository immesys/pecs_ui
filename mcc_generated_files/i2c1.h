/**
  I2C1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1.h

  @Summary
    This is the generated header file for the I2C1 driver using MPLAB� Code Configurator

  @Description
    This header file provides APIs for driver for I2C1.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25.2
        Device            :  PIC24FJ128GA310
        Driver Version    :  1.0
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.24
        MPLAB 	          :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#ifndef _I2C1_H
#define _I2C1_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <xc.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    /**
      I2C Slave Driver Status

      @Summary
        Defines the different status that the slave driver has
        detected over the i2c bus.

      @Description
        This defines the different status that the slave driver has
        detected over the i2c bus. The status is passed to the
        I2C1_StatusCallback() callback function that is implemented by
        the user of the slave driver as a parameter to inform the user
        that there was a change in the status of the driver due to
        transactions on the i2c bus. User of the slave driver can use these
        to manage the read or write buffers.

     */

    typedef enum {
        /* This state indicates that the slave driver has detected a transmit request from the master.
           The next transaction will be a read transaction. Application should prime the transmit
           buffer with the valid data to be sent to the master using the: I2C1_ReadPointerSet()
       
         */
        I2C1_SLAVE_TRANSMIT_REQUEST_DETECTED,

        /* This state indicates that the slave driver has detected a reception request from the master.
           The next transaction will be a write transaction. Application should set up the receive 
           buffer by setting the location of the receive buffer using the: I2C1_WritePointerSet()
         */
        I2C1_SLAVE_RECEIVE_REQUEST_DETECTED,

        /* This state indicates that the slave driver has received data from the master.
           Application can use this status to process the received data set up the receive
           buffer in anticipation of next reception in case the master sends more data. 
           See I2C1_SLAVE_RECEIVE_REQUEST_DETECTED.
         */
        I2C1_SLAVE_RECEIVED_DATA_DETECTED,

        /* This state indicates that the slave driver has detected the most significant
           byte of the 10-bit slave address. Another transaction with the least 
           significant byte of the 10-bit address with a read/write request will
           be detected next. This second detection is automatically done by the 
           driver which may return one of the following:
               a. I2C1_SLAVE_RECEIVE_REQUEST_DETECTED
               b. I2C1_SLAVE_TRANSMIT_REQUEST_DETECTED
               c. I2C1_SLAVE_10BIT_RECEIVE_REQUEST_DETECTED
           a or b is detected depending on the read/write bit of the received 
           control data. If c is detected next, the master decided to resend
           the most significant address.  
         */
        I2C1_SLAVE_10BIT_RECEIVE_REQUEST_DETECTED,

    } I2C1_SLAVE_DRIVER_STATUS;

    /**
      This will be removed in future MCC releases. 
      Use I2C1_SLAVE_DRIVER_STATUS instead.
     */
    typedef enum {
        DRV_I2C1_SLAVE_TRANSMIT_REQUEST_DETECTED,
        DRV_I2C1_SLAVE_RECEIVE_REQUEST_DETECTED,
        DRV_I2C1_SLAVE_RECEIVED_DATA_DETECTED,
        DRV_I2C1_SLAVE_10BIT_RECEIVE_REQUEST_DETECTED,

    } DRV_I2C1_SLAVE_DRIVER_STATUS;

#define I2C1_SLAVE_DEFAULT_ADDRESS          0

    /**
        @Summary
            Initializes and enables the i2c slave instance : 1

        @Description
            This routine initializes the i2c slave driver instance for : 1
            index, making it ready for clients to open and use it.

        @Preconditions
            None

        @Param
            None

        @Returns
            None

        @Example
            <code>
            
                uint8_t SlaveReadBuffer;
                uint8_t SlaveWriteBuffer;

                // initialize the i2c slave driver    
                I2C1_Initialize();
    
                // set up the slave driver
 
                // initialize the location of the read buffer
                I2C1_ReadPointerSet(SlaveReadBuffer);
                // initialize the location of the write buffer
                I2C1_WritePointerSet(SlaveWriteBuffer);
  
            </code>
     */

    void I2C1_Initialize(void);

    /**
        void DRV_I2C1_Initialize(void)
     */
    void DRV_I2C1_Initialize(void) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse I2C1_Initialize instead. ")));


    /**
        @Summary
            This function sets the slave address mask.

        @Description
            This function sets the 10-bit slave address mask to be able to
            respond to multiple addresses. This function should be called
            after the initialization of the module.

        @Preconditions
            None

        @Param
            mask - The address mask to be used when filtering
                addresses from the i2c master transactions.

        @Returns
            None

        @Example
            <code>
                Refer to I2C1_SlaveAddressSet() for an example	
            </code>

     */

    void I2C1_SlaveAddressMaskSet(
            uint16_t mask);

    /**
        void DRV_I2C1_SlaveAddressMaskSet(uint16_t mask)
     */
    void DRV_I2C1_SlaveAddressMaskSet(uint16_t mask) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse I2C1_SlaveAddressMaskSet instead. ")));

    /**
        @Summary
            This function sets the slave address.

        @Description
            This function sets the 10-bit slave address to be used by the
            module when filtering transactions from the i2c masters in the
            bus. The function analyzes the given address and decides if
            the 10-bit or 7-bit mode will be enabled. Once the function
            returns, the given address is set for the slave module.

            This function should be called after the initialization of
            the module.

            When changing the slave address the module must be idle.

        @Preconditions
            None

        @Param
            address - The address to be used to determine if the transaction
                is intended for this slave module.

        @Returns
            None

        @Example
            <code>
                // initialize the i2c slave driver    
                I2C1_Initialize();
 
                // set the slave address and address mask if the default
                // values set in the initialize is not the desired values.
                I2C1_SlaveAddressMaskSet(0x0xF);
                I2C1_SlaveAddressSet(0x3C);
 
            </code>

     */

    void I2C1_SlaveAddressSet(
            uint16_t address);

    /**
        void DRV_I2C1_SlaveAddressSet(uint16_t address)
     */
    void DRV_I2C1_SlaveAddressSet(uint16_t address) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse I2C1_SlaveAddressSet instead. ")));

    /**
        @Summary
            This function sets the read pointer for the slave driver.

        @Description
            This function sets the read pointer that the driver will
            need to retrieve data that will be transmitted to the master
            whenever the master requests a read.

        @Preconditions
            None

        @Param
     *p - The pointer to the read buffer, that will be used to transmit
                 data to the requesting i2c master.

        @Returns
            None

        @Example
            <code>
                Refer to I2C1_Initialize() for an example	
            </code>

     */

    void I2C1_ReadPointerSet(uint8_t *p);

    /**
        void DRV_I2C1_ReadPointerSet(uint8_t *p)
     */
    void DRV_I2C1_ReadPointerSet(uint8_t *p) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse I2C1_ReadPointerSet instead. ")));

    /**
        @Summary
            This function sets the write pointer for the slave driver.

        @Description
            This function sets the write pointer that the driver will
            need to save data that will be received from the master
            whenever the master requests a write.

        @Preconditions
            None

        @Param
     *p - The pointer to the read buffer, that will be used to transmit
                 data to the requesting i2c master.

        @Returns
            None

        @Example
            <code>
                Refer to I2C1_Initialize() for an example	
            </code>

     */

    void I2C1_WritePointerSet(uint8_t *p);

    /**
        void DRV_I2C1_WritePointerSet(uint8_t *p)
     */
    void DRV_I2C1_WritePointerSet(uint8_t *p) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse I2C1_WritePointerSet instead. ")));

    /**
        @Summary
            This function returns the current read pointer used by the
            slave driver.

        @Description
            This function returns the current read pointer used by the
            slave driver. As the operation executes, the pointer is
            incremented. User of the slave driver can use this function
            to check on the current address that the pointer is pointing to.

        @Preconditions
            None

        @Param
            None

        @Returns
            The current pointer used to transmit data to the requesting
            i2c master

        @Example
            <code>
                uint8_t *pReadBuffer;
 
                pReadBuffer = I2C1_ReadPointerGet();
            </code>

     */

    uint8_t *I2C1_ReadPointerGet(void);

    /**
        uint8_t *DRV_I2C1_ReadPointerGet(void)
     */
    uint8_t *DRV_I2C1_ReadPointerGet(void) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse I2C1_ReadPointerGet instead. ")));

    /**
        @Summary
            This function returns the current write pointer used by the
            slave driver.

        @Description
            This function returns the current write pointer used by the
            slave driver. As the operation executes, the pointer is
            incremented. User of the slave driver can use this function
            to check on the current address that the pointer is pointing to.

        @Preconditions
            None

        @Param
            None

        @Returns
            The current pointer used to save received data from the requesting
            i2c master

        @Example
            <code>
                uint8_t *pWriteBuffer;
 
                pWriteBuffer = I2C1_WritePointerGet();
 
            </code>

     */

    uint8_t *I2C1_WritePointerGet(void);

    /**
        uint8_t *DRV_I2C1_WritePointerGet(void)
     */
    uint8_t *DRV_I2C1_WritePointerGet(void) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse I2C1_WritePointerGet instead. ")));

    /**
       @Summary
            This application implemented function passes the
            status of the i2c slave driver.

        @Description
            This application implemented function passes the
            status of the i2c slave driver. The status passed
            can be used by the application to manage the read and
            write buffers. This function is called by the slave
            driver everytime there is an event in the i2c bus that caused
            an interrupt in the i2c slave module to be asserted.

            The function will return boolean. The value of the return
            will determine if the next received byte will be ack'ed or 
            nack'ed. By doing that, the application can have the 
            ability to delay incoming transactions. When a false is
            returned, the next transactions will be nack'ed forcing the 
            master to restart the transactions. 
 
            Returning a false will give the application a chance to
            prepare for the next transactions (for example: a read
            requests from the master) or process the recently received
            data.

        @Preconditions
            None

        @Param
            status - The latest status of the slave driver due
                to an event in the i2c bus.

        @Returns
            True, if the application is ready for the next transaction.
            False, if the application is not ready for the next transaction.

        @Example
            <code>

                // Example implementation of the callback

                static uint8_t i2c1_slaveWriteData = 0xAA;

                bool I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS status)
                {

                    // this emulates the slave device memory where data written to slave
                    // is placed and data read from slave is taken
                    static uint8_t EMULATE_EEPROM_Memory[64] =
                            {
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
                    static bool     addressState = true;

                    switch (status)
                    {
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

                            if (addressState == true)
                            {
                                // get the address of the memory being written
                                if (addrByteCount == 0)
                                {
                                    address = (i2c1_slaveWriteData << 8) & 0xFF00;
                                    addrByteCount++;
                                }
                                else if (addrByteCount == 1)
                                {
                                    address = address | i2c1_slaveWriteData;
                                    addrByteCount = 0;
                                    addressState = false;
                                }
                            }
                            else // if (addressState == false)
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
   
            </code>

     */
    bool I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS status);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif  // _I2C1_H