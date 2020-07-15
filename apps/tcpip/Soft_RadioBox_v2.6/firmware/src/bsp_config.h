/*******************************************************************************
  Board Support Package Header File.

  Company:
    Microchip Technology Inc.

  File Name:
    bsp_config.h

  Autor / modifications :
    J. Jeanneret  adaptation carte PIC Rouge
 *

  Summary:
    Board Support Package Header file for Starter Kit PIC32MX795F512L ETML ES.
    + Touch Screen FT800
 *
  Description:
    This file contains constants, macros, type defintions and function
    declarations required by the PIC32MX USB Starter Kit II BSP.
 *
 *  Adaptation Code  JJ 24.02.2017

 *
*******************************************************************************/


#ifndef _BSP_CONFIG_H
#define _BSP_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "peripheral/ports/plib_ports.h"
#include "peripheral/tmr/plib_tmr.h"


// *****************************************************************************
// *****************************************************************************
// Section: Constants and Type Definitions.
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Oscillator Frequency

  Summary:
    Defines frequency value of crystal/oscillator used on the board

  Description:
    Defines frequency value of crystal/oscillator used on the board
*/

#define BSP_OSC_FREQUENCY 8000000      // 8 MHz

/*********************** New RF-UNIT (sans Team Cast) carte rouge RF-unit v2.1****************************/

//Born Pull-Up

/******SMB**********/
#define Etat_Mux_Alarme         TRISBbits.TRISB8 //Mux alarm (AN8/RB8)
#define Mux_Alarme              PORTBbits.RB8 //Mux Alarm <-- Entrée
/********************/

/********** Relais ***********************/
#define Etat_Relai1       TRISBbits.TRISB14 
#define Relai1Out         LATBbits.LATB14  
#define Etat_Relai2       TRISBbits.TRISB15 
#define Relai2Out         LATBbits.LATB15  

#define Etat_Alim_PC           TRISDbits.TRISD2  //-----(OC3/RD2)
#define Alim_PC                PORTDbits.RD2   //Alim_PC<-- Entrée
/***********************************************************/

/**************************SMB************************/
#define Etat_Mesure_Audio       TRISDbits.TRISD1  //Tone-Police     (OC2/RD1)
#define Mesure_Audio            PORTDbits.RD1   //Tone-Police<-- Entrée SMB

#define Etat_Lecture_Police     TRISAbits.TRISA1
#define Lecture_Police          PORTAbits.RA1

#define Etat_Sommation       TRISAbits.TRISA15  //
#define Relais_Sommation      LATAbits.LATA15   //


/****************************************************/

/*************SMB*******************/
//UART2 --> Sortie pour ID                               //-----(OC4/RD3) SMB
/*************SMB*******************/


//Connecteur 26p
//GND                                              //pin1
//VCC                                              //pin2
#define Etat_IN_Lock_1          TRISGbits.TRISG6  //D15 pin 10                 //pin3 New
#define Etat_IN_Lock_2          TRISGbits.TRISG7  //D14 pin 11                 //pin4 New
//#define Etat_IN_LOCK            TRISDbits.TRISD3  //pin5
#define Etat_Enable_PLL_1       TRISDbits.TRISD3   //pin5
#define Etat_Enable_PLL_2       TRISCbits.TRISC13  //pin6
//#define Etat_PLL_2              TRISCbits.TRISC13  //pin6
#define Etat_PIC_RX             TRISDbits.TRISD13   //pin7
#define Etat_DIV0               TRISDbits.TRISD12  //pin8
#define Etat_DIV1               TRISCbits.TRISC14  //pin9
#define Etat_DIV2               TRISDbits.TRISD4   //pin10
#define Etat_DIV3               TRISDbits.TRISD5   //pin11
#define Etat_DIV4               TRISDbits.TRISD7   //pin12
#define Etat_DIV5               TRISCbits.TRISC3   //pin13
#define Etat_DIV6               TRISCbits.TRISC2   //pin14
#define Etat_DIV7               TRISAbits.TRISA7   //pin15
#define Etat_DIV8               TRISEbits.TRISE0   //pin16
#define Etat_DIV9               TRISEbits.TRISE1   //pin17
#define Etat_DIV10              TRISFbits.TRISF3   //pin18
#define Etat_DIV11              TRISGbits.TRISG13  //pin19
#define Etat_DIV12              TRISEbits.TRISE2   //pin20
#define Etat_DIV13              TRISEbits.TRISE3   //pin21
#define Etat_DIV14              TRISEbits.TRISE4   //pin22
#define Etat_DIV15              TRISEbits.TRISE5   //pin23
#define Etat_DIV16              TRISEbits.TRISE6   //pin24
#define Etat_DIV17              TRISEbits.TRISE7   //pin25
#define Etat_DIV18              TRISCbits.TRISC1   //pin26

/********Conn Rectangle 10p**************************/

// GND //Mute RF2                                            //pin1
#define Etat_RF_Step4           TRISBbits.TRISB2  //pin2
#define Etat_RF_Step0_5         TRISBbits.TRISB4  //pin3
#define Etat_RF_Step8           TRISBbits.TRISB3  //pin4
#define Etat_RF_Step1           TRISAbits.TRISA9  //pin5
#define Etat_RF_Step16          TRISAbits.TRISA10 //pin6
//RF Level   AN9                                  //pin7
//AN10/RB10 nc                                    //pin8
#define Etat_RF_Step2           TRISBbits.TRISB0  //pin9
#define Etat_Mute_RF            TRISBbits.TRISB1  //pin10

//GND
#define RF_Step4           LATBbits.LATB2
#define RF_Step0_5         LATBbits.LATB4
#define RF_Step8           LATBbits.LATB3
#define RF_Step1           LATAbits.LATA9
#define RF_Step16          LATAbits.LATA10
//RF Level   AN9
//AN10/RB10 nc
#define RF_Step2          LATBbits.LATB0
#define Mute_RF           LATBbits.LATB1

#define IN_Lock_1          PORTGbits.RG6   //pin3
#define IN_Lock_2          PORTGbits.RG7   //pin4
#define Enable_PLL_1       LATDbits.LATD3   //pin5
#define Enable_PLL_2       LATCbits.LATC13   //pin6
//#define IN_LOCK            PORTDbits.RD3
//#define PLL_2              LATCbits.LATC13
#define PIC_RX             LATDbits.LATD13
#define DIV0               LATDbits.LATD12
#define DIV1               LATCbits.LATC14
#define DIV2               LATDbits.LATD4
#define DIV3               LATDbits.LATD5
#define DIV4               LATDbits.LATD7
#define DIV5               LATCbits.LATC3
#define DIV6               LATCbits.LATC2
#define DIV7               LATAbits.LATA7
#define DIV8               LATEbits.LATE0
#define DIV9               LATEbits.LATE1
#define DIV10              LATFbits.LATF3
#define DIV11              LATGbits.LATG13
#define DIV12              LATEbits.LATE2
#define DIV13              LATEbits.LATE3
#define DIV14              LATEbits.LATE4
#define DIV15              LATEbits.LATE5
#define DIV16              LATEbits.LATE6
#define DIV17              LATEbits.LATE7
#define DIV18              LATCbits.LATC1



















/***********************Ecran FT800****************************/
#define FT800_INT  PORTAbits.RA5    //  COLONNE1   dir ?
#define FT800_PD_W   LATAbits.LATA4  //  COLONNE3 OUT
#define FT800_PD_R   PORTAbits.RA4   //  COLONNE3 OUT
#define FT800_CS_W   LATAbits.LATA6  //  COLONNE4   OUT
#define FT800_CS_R   PORTAbits.RA6   //  COLONNE4   OUT



typedef enum
{
    /* SWITCH 1 */
     BSP_SWITCH_1 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_12/*DOM-IGNORE-END*/,

    /* SWITCH 2 */
     BSP_SWITCH_2 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_13/*DOM-IGNORE-END*/,

//    /* SWITCH 3 */
//     BSP_SWITCH_3 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_14/*DOM-IGNORE-END*/,

     BSP_SWITCH_4 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_15/*DOM-IGNORE-END*/

} BSP_SWITCH;

// *****************************************************************************
/* BSP Switch state.

  Summary:
    Defines possible states of the switches on this board.

  Description:
    This enumeration defines the possible states of the switches on this board.

  Remarks:
    None.
*/

typedef enum
{
    /* Switch pressed */
    BSP_SWITCH_STATE_PRESSED = /*DOM-IGNORE-BEGIN*/0/*DOM-IGNORE-END*/,

   /* Switch not pressed */
    BSP_SWITCH_STATE_RELEASED = /*DOM-IGNORE-BEGIN*/1/*DOM-IGNORE-END*/

} BSP_SWITCH_STATE;

// *****************************************************************************
/* LED Number.

  Summary:
    Defines the LEDs available on this board.

  Description:
    This enumeration defines the LEDs available on this board.

  Remarks:
    None.
*/

// CHR introduction des 8 led du kit ES

// #define LED0_W       LATAbits.LATA0  //Led0
// #define LED1_W       LATAbits.LATA1  //Led1
// #define LED2_W       LATAbits.LATA4  //Led2
// #define LED3_W       LATAbits.LATA5  //Led3
// #define LED4_W       LATAbits.LATA6  //Led4
// #define LED5_W       LATAbits.LATA7  //Led5
// #define LED6_W       LATAbits.LATA15 //Led6
// #define LED7_W       LATBbits.LATB10 //Led7

typedef enum
{
    BSP_LED_0 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_0/*DOM-IGNORE-END*/,
    BSP_LED_1 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_1/*DOM-IGNORE-END*/,
    BSP_LED_2 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_4/*DOM-IGNORE-END*/,
    BSP_LED_3 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_5/*DOM-IGNORE-END*/,
    BSP_LED_4 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_6/*DOM-IGNORE-END*/,
    BSP_LED_5 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_7/*DOM-IGNORE-END*/,
    BSP_LED_6 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_15/*DOM-IGNORE-END*/,
    // Attention port B
    BSP_LED_7 = /*DOM-IGNORE-BEGIN*/PORTS_BIT_POS_10/*DOM-IGNORE-END*/,

} BSP_LED;

// *****************************************************************************
/* LED State

  Summary:
    Enumerates the supported LED states.

  Description:
    This enumeration defines the supported LED states.

  Remarks:
    None.
*/

typedef enum
{
    /* LED State is on */
    BSP_LED_STATE_OFF = /*DOM-IGNORE-BEGIN*/0,/*DOM-IGNORE-END*/

    /* LED State is off */
    BSP_LED_STATE_ON = /*DOM-IGNORE-BEGIN*/1,/*DOM-IGNORE-END*/

} BSP_LED_STATE;


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void BSP_Initialize(void)

  Summary:
    Performs the necessary actions to initialize a board

  Description:
    This function initializes the LED and Switch ports on the board.  This
    function must be called by the user before using any APIs present on this
    BSP.

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Example:
    <code>
    //Initialize the BSP
    BSP_Initialize();
    </code>

  Remarks:
    None
*/

void BSP_Initialize(void);

// *****************************************************************************
/* Function:
    void BSP_LEDStateSet(BSP_LED led, BSP_LED_STATE state);

  Summary:
    Controls the state of the LED.

  Description:
    This function allows the application to specify the state of the LED.

  Precondition:
    BSP_Initialize() should have been called.

  Parameters:
    led     - The LED to operate on.
    state   - The state to be set.

  Returns:
    None.

  Example:
    <code>

    // Initialize the BSP
    BSP_Initialize();

    // Switch on LED1 on the board
    BSP_LEDStateSet(BSP_LED_1, BSP_LED_STATE_ON);

    // Switch off LED2 on the board
    BSP_LEDStateSet(BSP_LED_2, BSP_LED_STATE_OFF);

    </code>

  Remarks:
    None
*/

void BSP_LEDStateSet(BSP_LED led, BSP_LED_STATE state);

// *****************************************************************************
/* Function:
    BSP_LED_STATE BSP_LEDStateGet(BSP_LED led);

  Summary:
    Returns the present state of the LED.

  Description:
    This function returns the present state of the LED.

  Precondition:
    BSP_Initialize() should have been called.

  Parameters:
    led - The LED to whose status needs to be obtained.

  Returns:
    The ON/OFF state of the LED.

  Example:
    <code>

    // Initialize the BSP
    BSP_Initialize();

    // Check if LED2 is off
    if(BSP_LED_STATE_OFF == BSP_LEDStateGet(BSP_LED_2)
    {
        // Switch on the LED.
        BSP_LEDStateSet(BSP_LED_2, BSP_LED_STATE_ON);
    }

    </code>

  Remarks:
    None
*/

BSP_LED_STATE BSP_LEDStateGet(BSP_LED led);

// *****************************************************************************
/* Function:
    void BSP_LEDToggle(BSP_LED led);

  Summary:
    Toggles the state of the LED between BSP_LED_STATE_ON and BSP_LED_STATE_OFF.

  Description:
    This function toggles the state of the LED between BSP_LED_STATE_ON and
    BSP_LED_STATE_OFF.

  Precondition:
    BSP_Initialize() should have been called.

  Parameters:
    led - The LED to toggle.

  Returns:
    None.

  Example:
    <code>

    // Initialize the BSP
    BSP_Initialize();

    // Switch on LED1 on the board
    BSP_LEDStateSet(BSP_LED_1, BSP_LED_STATE_ON);

    // Switch off LED2 on the board
    BSP_LEDStateSet(BSP_LED_2, BSP_LED_STATE_OFF);

    // Toggle state of LED3
    BSP_LEDToggle(BSP_LED_3);
    </code>

  Remarks:
    None
*/

void BSP_LEDToggle(BSP_LED led);

// *****************************************************************************
/* Function:
    void BSP_LEDOn(BSP_LED led);

  Summary:
    Switches ON the specified LED.

  Description:
    This function switches ON the specified LED.

  Precondition:
    BSP_Initialize() should have been called.

  Parameters:
    led - The LED to switch on.

  Returns:
    None.

  Example:
    <code>

    // Initialize the BSP
    BSP_Initialize();

    // Switch on LED1 on the board
    BSP_LEDOn(BSP_LED_1);

    </code>

  Remarks:
    None
*/

void BSP_LEDOn(BSP_LED led);

// *****************************************************************************
/* Function:
    void BSP_LEDOff(BSP_LED led);

  Summary:
    Switches OFF the specified LED.

  Description:
    This function switches OFF the specified LED.

  Precondition:
    BSP_Initialize() should have been called.

  Parameters:
    led - The LED to switch off.

  Returns:
    None.

  Example:
    <code>

    // Initialize the BSP
    BSP_Initialize();

    // Switch off LED1 on the board
    BSP_LEDOff(BSP_LED_1);

    </code>

  Remarks:
    None
*/

void BSP_LEDOff(BSP_LED led);

// *****************************************************************************
/* Function:
    BSP_SWITCH_STATE BSP_SwitchStateGet(BSP_SWITCH switch);

  Summary:
    Returns the present state (pressed or not pressed) of the specified switch.

  Description:
    This function returns the present state (pressed or not pressed) of the
    specified switch.

  Precondition:
    BSP_Initialize() should have been called.

  Parameters:
    switch  - The switch whose state needs to be obtained.

  Returns:
    The pressed released state of the switch.

  Example:
    <code>

    // Initialize the BSP
    BSP_Initialize();

    // Check the state of the switch.
    if(BSP_SWITCH_STATE_PRESSED == BSP_SwitchStateGet(BSP_SWITCH_1))
    {
        // This means that Switch 1 on the board is pressed.
    }

    </code>

  Remarks:
    None
*/

BSP_SWITCH_STATE BSP_SwitchStateGet(BSP_SWITCH bspSwitch);


// Ajout CHR 09.12.2014
void BSP_EnableHbrige(void);

#endif //_BSP_CONFIG_H

/*******************************************************************************
 End of File
*/
