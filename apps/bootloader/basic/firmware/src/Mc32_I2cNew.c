/*--------------------------------------------------------*/
//     Mc32_I2cUtilCCS.c

//	Description :	utilitaire I2C compatible syntaxe CCS
//                      Obtenu par modification du PIC32MX I2C Example
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.0
//	Compilateur	:	XC32 V1.31
//
//      MODIFICATIONS   :
//
//
//
/*--------------------------------------------------------*/

/*********************************************************************
 *
 *      PIC32MX I2C Example
 *
 *********************************************************************
 * FileName:        i2c_master.c
 * Dependencies:    plib.h
 *
 * Processor:       PIC32MX
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the �Company�) for its PIC32MX Microcontroller is intended
 * and supplied to you, the Company�s customer, for use solely and
 * exclusively on Microchip Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *********************************************************************
 * Change History:
 * Name        Date            Changes
 * A Rafiq     2/7/07          Initial Version
 * JM          2/7/09          Updated
 *
 * $Id: i2c_master.c 9558 2008-07-04 10:08:49Z deshmukha $
 *
 * Demo Code Description:
 * This example interfaces with a 24LC256 serial eeprom on
 * I2C channel 1. The code writes to a location and then
 * verifies the contents of the eeprom. I2C Channel 1 is
 * hooked up to 24LC256, while the address lines of the
 * eeprom are all tied to Vss.
 ********************************************************************/


#include "Mc32_I2cNew.h"
#include "SK32MX795F512L_V18.h"







// KIT 32MX795F512L Constants
#define KIT_I2C_BUS   I2C2
#define I2C_CLOCK_FAST 400000
#define I2C_CLOCK_SLOW 100000

//------------------------------------------------------------------------------
// i2c_init
//
// Initialisationde l'I2c
//      si BOOL Fast = FALSE   LOW speed  100 KHz
//      si BOOL Fast = TRUE   HIGH speed  400 KHz
//------------------------------------------------------------------------------

void i2c_init(void)
{
    #define MY_I2C_ID I2C_ID_2
    
    PLIB_I2C_Disable(MY_I2C_ID);
    PLIB_I2C_GeneralCallEnable (MY_I2C_ID);
    PLIB_I2C_HighFrequencyDisable(MY_I2C_ID);
    PLIB_I2C_SlaveClockStretchingEnable(MY_I2C_ID);
    PLIB_I2C_SMBDisable(MY_I2C_ID);
    PLIB_I2C_BaudRateSet(MY_I2C_ID,80000000,400000);
    PLIB_I2C_Enable(MY_I2C_ID);
}

void i2c_start(void)
{
    
    #define MY_I2C_ID I2C_ID_2

    if(PLIB_I2C_BusIsIdle (MY_I2C_ID))
    {
        PLIB_I2C_MasterStart(MY_I2C_ID);
        //I2C1CONbits.SEN = 1;
    }
    while(I2C2CONbits.SEN); 

}// end i2c_start

void i2c_reStart(void)
{
    #define MY_I2C_ID I2C_ID_2

    PLIB_I2C_MasterStartRepeat(MY_I2C_ID);
    //I2C1CONbits.RSEN = 1;
    
    while(I2C2CONbits.RSEN);   
}

void i2c_write( uint8_t data )
{
    //bool AckBit;
    #define MY_I2C_ID I2C_ID_2
 
    while(!PLIB_I2C_TransmitterIsReady(MY_I2C_ID));
    
    PLIB_I2C_TransmitterByteSend(MY_I2C_ID,data);

    while(!PLIB_I2C_TransmitterByteHasCompleted(MY_I2C_ID));
//    
    //AckBit = PLIB_I2C_TransmitterByteWasAcknowledged(I2C_ID_2);
    
    //return AckBit;
}// end i2c_write

void i2c_stop( void )
{
    #define MY_I2C_ID I2C_ID_2

    PLIB_I2C_MasterStop(MY_I2C_ID);
    //I2C1CONbits.PEN = 1;
    while(I2C2CONbits.PEN);   
}

uint8_t i2c_read(void)
{
    #define MY_I2C_ID I2C_ID_2
    uint8_t i2cByte;
    I2C2CONbits.RCEN = 1;
    
    while ( !PLIB_I2C_ReceivedByteIsAvailable(MY_I2C_ID) );
    
    //PLIB_I2C_ReceivedByteAcknowledge ( MY_I2C_ID, true );
    
     i2cByte = PLIB_I2C_ReceivedByteGet(MY_I2C_ID);
    
    while(PLIB_I2C_ReceiverByteAcknowledgeHasCompleted (MY_I2C_ID) == 0);
    
    return i2cByte;
}