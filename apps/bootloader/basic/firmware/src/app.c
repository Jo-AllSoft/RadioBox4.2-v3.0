/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

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
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

//#include "bsp_config.h"
#include "app.h"
#include "system/system.h"
#include "bootloader/src/bootloader.h"
//#include "bootloader/src/nvm.h"
#include "peripheral/nvm/plib_nvm.h"
#include <sys/kmem.h> 

#include "system_config.h"
#include "system_definitions.h"
#include "Mc32Delays.h"

#include "FT_GPU.h"
#include "Mc32gestSpiFT800.h"
#include "Mc32SpiUtil.h"
#include "peripheral/spi/plib_spi.h"
#include "Mc32_I2cNew.h"
#include "EEPROM_24LC256.h"


void Affichage_Bootloader(int num, int Button,int *Cpt_Presse);


//#include "plib.h"
//#define _SUPPRESS_PLIB_WARNING
#define BTN PORTBbits.RB1

char AdresseIP[30];
char Save_Adresse_IP[30];
char Save_Mask_IP[17];
char Save_Gateway_IP[17];
char Save_DNS_IP[17];
int Start_Bootloader;
int Time_Bootloader;
int Cpt_Presse_BTN;

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */




//unsigned char nvmBufferData[NVM_ROW_SIZE] __attribute__((coherent));

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

int APP_ForceBootloaderCheck(void)//officiel
{
    // For most of the basic bootloaders, the check of the switch (S3) and
    // the memory location will decide the question.
//    if (BSP_SWITCH_STATE_PRESSED == BSP_SwitchStateGet(BSP_SWITCH_3))
//        return (1);
    
    return (1);
}
//int APP_ForceBootloaderCheck(void)
//{
//    TRISBbits.TRISB1 = 1;
//    AD1PCFG = 0xFFFF;
//    
//    if(PORTBbits.RB1 == 1)
//    {
//        return (1);
//    }
//   
//    return (0);
//}


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Initialize ( void )
{
    AD1PCFG = 0xFFFF;
    
    Start_Bootloader = Read_EEPROM(1999);
    
    if(Start_Bootloader != 25)
    {
        InitFT800();

        cmd(CMD_DLSTART);
        cmd_gradient(0,0,0xFFAC00, 0, 240, 0xACACAC);
        wr8(REG_PWM_DUTY,40); //Réglage du retro éclairage (0 à 128)
    }
    
    
    delay_ms(50);
    if((Start_Bootloader == 22)||(Start_Bootloader == 23)||(Start_Bootloader == 24)||(Start_Bootloader == 25))
    {
        if(Start_Bootloader == 22)
        {
            Etat_Sommation = 0;
        }
        if(Start_Bootloader == 23)
        {
            Etat_Bouton_Veille_Ampli = 1;
            Etat_Alarme_RF = 0;
            Etat_Ctr_Ampli = 0;
        }
        if(Start_Bootloader == 24)
        {
            Etat_Sommation_Alarme = 0;
        }
        BOOTLOADER_ForceBootloadRegister(APP_ForceBootloaderCheck);
    }
}

/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks (void)
{
    WDTCONbits.WDTCLR = 1;

    if(Start_Bootloader == 23)
    {
        Affichage_Bootloader(Start_Bootloader,Bouton_Veille_Ampli,&Cpt_Presse_BTN);
    }
    if((Start_Bootloader == 22)||(Start_Bootloader == 24)||(Start_Bootloader == 25))
    {
        Affichage_Bootloader(Start_Bootloader,Bouton_Veille,&Cpt_Presse_BTN);
    }
    Start_Bootloader = 0;
    if(Cpt_Presse_BTN >= 400 )
    {
        SYS_RESET_SoftwareReset();//version compilateur XC32 1.40
    }
}

void Affichage_Bootloader(int num, int Button,int *Cpt_Presse)
{
    if(num != 25)
    {
        delay_ms(5);
        cmd(CMD_DLSTART);
        cmd_gradient(0,0,0xFFAC00, 0, 240, 0xACACAC);
        cmd(COLOR_RGB(0,0,0));
        wr8(REG_PWM_DUTY,40); //Réglage du retro éclairage (0 à 128)
        
        char* msg;
        
        char m22[]  = "Bootloader RF Unit";
        char m23[]  = "Bootloader Ampli";
        char m24[]  = "Bootloader Comb";
        if(num == 22)
        {
            msg = m22;
            Relais_Sommation = 1;
        }
        if(num == 23)
        {
            msg = m23;
            Alarme_RF = 1;
            
            Ctr_Ampli = 1;//eteint l'ampli(l'étage final)
        }
        if(num == 24)
        {
            msg = m24;
            Sommation_Alarme = 1;
        }
        cmd_text(20,60,30,0, msg);

        sprintf(AdresseIP,"IP : %s",Save_Adresse_IP);
        cmd_text(20,130,23,0,AdresseIP);
        cmd_text(20,170,23,0,"UDP Port : 6234");

        cmd(DISPLAY());                     // Affichage sur l'écran
        cmd(CMD_SWAP);
        cmd_exec();
        cmd_wait();
    }
    
    if(num == 25)
    {
        delay_us(12500);
    }  
}

/*******************************************************************************
 End of File
 */

