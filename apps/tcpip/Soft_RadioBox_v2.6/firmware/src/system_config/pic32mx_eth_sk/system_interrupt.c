/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

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

#include <xc.h>
#include <sys/attribs.h>
#include "app.h"
#include "system_definitions.h"
#include "peripheral/int/plib_int.h"
//#include "peripheral/usart/plib_usart.h"
#include "EEPROM_Driver.h"




extern int Test_Ethernet;
extern int Mode_Calibration;
// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
int I2C_cpt = 0;
void __ISR(_TIMER_1_VECTOR, ipl2AUTO) _IntHandlerDrvTmrInstance1(void)//modification interuption de 1m � 100us 31.03.2017
{
    static int attente, waitEEPROM,CptLectureAD;
    
    CptLectureAD++;
    if(CptLectureAD >= 500)
    {
//        APP_UpdateState2(APP_STATE2_MESURE_AD);
        CptLectureAD = 0;
    }
    attente++;
    if(attente > 20000)
    {
        if(Mode_Calibration == 0)
        {
            APP_UpdateState2(APP_STATE2_EXEC);
        }
        else
        {
            APP_UpdateState2(APP_STATE2_Calibration);
        }
//        APP_UpdateState2(APP_STATE2_EXEC);
        
        attente = 19500;
    }
    if(waitEEPROM++ >= 50 && I2C_EEPROM_isReady())
    {
        EEPROM_Task();
        waitEEPROM = 0;
    }
    
    
    
    I2C_cpt++;
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_1);
}

    
void __ISR(_TIMER_2_VECTOR, ipl4AUTO) IntHandlerDrvTmrInstance0(void)
{
    DRV_TMR_Tasks(sysObj.drvTmr0);
}
 
 void __ISR(_FCE_VECTOR, ipl4AUTO) _IntHandlerDrvNvm (void)
{
    DRV_NVM_Tasks(sysObj.drvNvm);

}

void __ISR(_ETH_VECTOR, ipl5AUTO) _IntHandler_ETHMAC(void)
{
    DRV_ETHMAC_Tasks_ISR((SYS_MODULE_OBJ)0);
}

/* This function is used by ETHMAC driver */
bool SYS_INT_SourceRestore(INT_SOURCE src, int level)
{
    if(level)
    {
        SYS_INT_SourceEnable(src);
    }

    return level;
}

void __ISR(_I2C_2_VECTOR, ipl4AUTO) _IntHandlerDrvI2CInstance0(void)
{
    DRV_I2C0_Tasks();
}

 void __ISR(_UART_2_VECTOR, ipl1AUTO) _IntHandlerDrvUsartInstance0(void)
{
    DRV_USART_TasksTransmit(sysObj.drvUsart0);
    DRV_USART_TasksReceive(sysObj.drvUsart0);
    DRV_USART_TasksError(sysObj.drvUsart0);
}
 
 void __ISR(_UART_1_VECTOR, ipl1AUTO) _IntHandlerDrvUsartInstance1(void)
{
    DRV_USART_TasksTransmit(sysObj.drvUsart1);
    DRV_USART_TasksReceive(sysObj.drvUsart1);
    DRV_USART_TasksError(sysObj.drvUsart1);
}
/*******************************************************************************
 End of File
*/

