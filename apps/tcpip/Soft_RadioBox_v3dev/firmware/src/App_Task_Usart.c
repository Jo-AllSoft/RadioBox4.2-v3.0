/*******************************************************************************
  USART Driver Demo Application Soure File.

  File Name:
    app.c

  Summary:
    USART driver echo demo application.

  Description:
    This file contains the USART driver echo demo application's implementation.
 ******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 ******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "app.h"
//#include <proc/p32mx795f512l.h>
//"C:\Program Files (x86)\Microchip\xc32\v1.42\pic32mx\include\proc\p32mx795f512l.h"
//#include "drv_usart.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************
/* USART Driver Demo Banner Message */
//char appMsg[APP_NUM_LINES][APP_BUFFER_SIZE] = {
//        {"*******************************************************\r\n"},
//        {"Welcome to Microchip USART Driver Demo Application.\r\n"},
//        {"Press any character, the character will be echoed back.\r\n"},
//        {"Press 'ESC' key to exit the Demo Application.\r\n"},
//        {"*******************************************************\r\n"},
//        {"\n"},
//        {"\r\n\r\n****** End of USART Driver Demo Application. *****"},};


char appMsg[APP_NUM_LINES][APP_BUFFER_SIZE] = {
        {"*******************************************************\r\n"},
        {"Welcome to Microchip USART Driver Demo Application.\r\n"},
        {"Press any character, the character will be echoed back.\r\n"},
        {"Press 'ESC' key to exit the Demo Application.\r\n"},
        {"*******************************************************\r\n"},
        {"\n"},
        {"\r\n\r\n****** End of USART Driver Demo Application. *****"},};     

char Table_Midi[]={0x80,0x39,0x00,0x90,0x39,0x3F,0};
int Ok_Send = 0;
/* User Application Data Structure */
APP_DATA_USART appDataUart;


extern SYSTEM_OBJECTS sysObj;

#define min(a,b) (((a) < (b)) ? (a) : (b))
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data.

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/
// *****************************************************************************
// *****************************************************************************
// Section: Application Data Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize_Usart( void )
{
    U1STAbits.UTXINV = 1;
    /* Set the App. previous state to its initial state. */
    appDataUart.prevState         = APP_DRV_OPEN;
    /* Set the App. current state to its initial state. */
    appDataUart.currentState      = APP_DRV_OPEN;
    /* Initialise buffer Size */
    appDataUart.bufferSize        = 0;
    /* Demo App. message index */
    appDataUart.usrMsgIndex       = 0;
    /* Set the USART Clent Statud to error */
    appDataUart.usartStatus       = DRV_USART_CLIENT_STATUS_ERROR;
    /* Set the USART buffer handler to invalid */
    appDataUart.usartBufferHandle = DRV_HANDLE_INVALID;
    /* Set the USART handler to invalid */
    appDataUart.usartHandle       = DRV_HANDLE_INVALID;
    /* Set the USART buffer event to invalid */
    appDataUart.usartBufferEvent  = DRV_USART_BUFFER_EVENT_ERROR;
    /* Set the initial state of event flags for driver messages */
    appDataUart.drvBufferEventComplete = false;
    /* Set the initial state of event flags for user messages */
    appDataUart.usrBufferEventComplete = false;
    /* Clear Application Buffer */
    strcpy(appDataUart.buffer, "");
    
//    U2STAbits.UTXINV = 1;
//    /* Set the App. previous state to its initial state. */
//    appDataUart.prevState         = APP_DRV_OPEN;
//    /* Set the App. current state to its initial state. */
//    appDataUart.currentState      = APP_DRV_OPEN;
//    /* Initialise buffer Size */
//    appDataUart.bufferSize        = 0;
//    /* Demo App. message index */
//    appDataUart.usrMsgIndex       = 0;
//    /* Set the USART Clent Statud to error */
//    appDataUart.usartStatus       = DRV_USART_CLIENT_STATUS_ERROR;
//    /* Set the USART buffer handler to invalid */
//    appDataUart.usartBufferHandle = DRV_HANDLE_INVALID;
//    /* Set the USART handler to invalid */
//    appDataUart.usartHandle       = DRV_HANDLE_INVALID;
//    /* Set the USART buffer event to invalid */
//    appDataUart.usartBufferEvent  = DRV_USART_BUFFER_EVENT_ERROR;
//    /* Set the initial state of event flags for driver messages */
//    appDataUart.drvBufferEventComplete = false;
//    /* Set the initial state of event flags for user messages */
//    appDataUart.usrBufferEventComplete = false;
//    /* Clear Application Buffer */
//    strcpy(appDataUart.buffer, "");
}




void APP_BufferEventHandler(DRV_USART_BUFFER_EVENT buffEvent,
                            DRV_USART_BUFFER_HANDLE hBufferEvent,
                            uintptr_t context )
{
    switch(buffEvent)
    {
        /* Buffer event is completed successfully */
        case DRV_USART_BUFFER_EVENT_COMPLETE:
        {
            if(context == APP_DRV_CONTEXT)
            {
                /* Update buffer event status */
                appDataUart.drvBufferEventComplete = true;
            }
            else if (context == APP_USR_CONTEXT)
            {
                /* if user has pressed 'ESC' key, exit the app */
                if(appDataUart.buffer[0] == APP_USR_ESC_KEY)
                {
                    appDataUart.currentState = APP_DRV_DEMO_COMPLETE;
                    appDataUart.usrBufferEventComplete = false;
                }
                /* if user has pressed 'enter' key, add newline character */
                else if(appDataUart.buffer[0] == APP_USR_RETURN_KEY)
                {
                    strcpy(appDataUart.buffer, "\r\n");
                    /* Update Buffer Size */
                    appDataUart.bufferSize = min(APP_BUFFER_SIZE,
                                                       strlen(appDataUart.buffer));
                    /* Update buffer event status */
                    appDataUart.usrBufferEventComplete = true;
                }
                else
                {
                    /* Update buffer event status */
                    appDataUart.usrBufferEventComplete = true;
                }
            }
        }
            break;

        /* Buffer event has some error */
        case DRV_USART_BUFFER_EVENT_ERROR:
            break;

        /* Buffer event has aborted */
        case DRV_USART_BUFFER_EVENT_ABORT:
            break;
    }
}


/*******************************************************************************
  Function:
    void APP_Tasks_Usart( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks_Usart(int N_Usart)
{
    extern int Config_UsartON;
    /* Check the Application State*/
    switch ( appDataUart.currentState )
    {
        /* Open USART Driver and set the Buffer Event Handling */
        case APP_DRV_OPEN:
        {
            /* Open an instance of USART driver */

            DRV_USART_Close (appDataUart.usartHandle);
            Config_UsartON = 1;
            
            
            appDataUart.usartHandle = DRV_USART_Open(N_Usart,(DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_NONBLOCKING));
            

            /* Check the USART driver handler */
            if (appDataUart.usartHandle != DRV_HANDLE_INVALID )
            {
                DRV_USART_BufferEventHandlerSet(appDataUart.usartHandle,
                                       APP_BufferEventHandler, APP_DRV_CONTEXT);
                /* Set the app state to Ready */

                appDataUart.prevState    = APP_DRV_OPEN;
                appDataUart.currentState = APP_DRV_READY;

            }
            else
            {
                /* If handler is not ready, set the App. state to error */
                appDataUart.currentState = APP_ERROR;
            }
        }
        break;

        /* When the driver is ready, add Data Buffer to queue */
        case APP_DRV_READY:
        {
            /* Get the USART driver status */
            appDataUart.usartStatus = DRV_USART_ClientStatus( appDataUart.usartHandle );

            if ( appDataUart.usartStatus == DRV_USART_CLIENT_STATUS_READY )
            {
                /* To begin with, Send the newline character to buffer */
//                strcpy(appDataUart.buffer, "/r/n");
                 memcpy(appDataUart.buffer, Table_Midi,3);
                /* Update Buffer Size */
                appDataUart.bufferSize = min(APP_BUFFER_SIZE,
                                                3);
                /* Submit buffer to USART */
                DRV_USART_BufferAddWrite( appDataUart.usartHandle,
                                          &(appDataUart.usartBufferHandle),
                                          appDataUart.buffer, appDataUart.bufferSize );

                /* check buffer handler */
                if ( appDataUart.usartBufferHandle == DRV_HANDLE_INVALID )
                {
                    /* Terminate the Demo, if add to buffer is failed */
                    appDataUart.currentState = APP_ERROR;
                }
                else
                {
                    /* If handle is valid, Set the app state to next state */
                    appDataUart.prevState    = APP_IDLE;
                    appDataUart.currentState = APP_WAIT_FOR_DONE;
                }
            }
            else
            {
                /* If client is not ready, set App. state to error */
                appDataUart.currentState = APP_ERROR;
            }
        }
        break;

        case APP_WAIT_FOR_DONE:
        {
            /* check if the driver buffer event is complete or not */
            if(appDataUart.drvBufferEventComplete)
            {
                appDataUart.drvBufferEventComplete = false;
                /* Get next Demo App. state */
                App_GetNextTaskState(appDataUart.prevState);
            }
            /* check if the user buffer event is complete or not */
            else if(appDataUart.usrBufferEventComplete)
            {
                appDataUart.usrBufferEventComplete = false;
                /* Get next Demo App. state */
                App_GetNextTaskState(appDataUart.prevState);
            }
        }
        break;

        case APP_DRV_MSG_WRITE:
        {
            /* Get the USART Driver Status */
            appDataUart.usartStatus = DRV_USART_ClientStatus( appDataUart.usartHandle );
//            char Table_Midi[]={(~0x90)&0xFF,(~0x39)&0xFF,(~0x3F)&0xFF,0};
            if (( appDataUart.usartStatus == DRV_USART_CLIENT_STATUS_READY )&&(Ok_Send == 1))
            {
               
//                char Table_Midi[]={(~0x90)&0xFF,(~0x3C)&0xFF,(~0x40)&0xFF,0};
                

                memcpy(appDataUart.buffer, Table_Midi,3);
//                strcpy( appDataUart.buffer, Table_Midi);
                /* Update Buffer Size */
                appDataUart.bufferSize = min(APP_BUFFER_SIZE,3);
                /* Submit buffer to USART */
                
                DRV_USART_BufferAddWrite( appDataUart.usartHandle,
                                          &(appDataUart.usartBufferHandle),
                                          appDataUart.buffer, appDataUart.bufferSize);

                if ( appDataUart.usartBufferHandle == DRV_HANDLE_INVALID )
                {
                    /* Set the App. state to error */
                    appDataUart.currentState = APP_ERROR;
                }
                else
                {
                    /* Set the App. state to wait for done */
                    appDataUart.prevState    = APP_DRV_MSG_WRITE;
                    appDataUart.currentState = APP_WAIT_FOR_DONE;
                }
                Ok_Send = 0;
            }
        }
        break;

        case APP_USR_MSG_READ:
        {
            /* Get the USART driver status */
            appDataUart.usartStatus = DRV_USART_ClientStatus( appDataUart.usartHandle );
            /* Check if the client is ready or not */
            if ( appDataUart.usartStatus == DRV_USART_CLIENT_STATUS_READY )
            {
                strcpy( appDataUart.buffer, appMsg[appDataUart.usrMsgIndex] );
                /* Update Buffer Size */
                appDataUart.bufferSize = min(APP_BUFFER_SIZE,
                                                       strlen(appDataUart.buffer));
                /* Submit buffer to USART */
                DRV_USART_BufferAddRead( appDataUart.usartHandle,
                                         &(appDataUart.usartBufferHandle),
                                         appDataUart.buffer, appDataUart.bufferSize);

                if ( appDataUart.usartBufferHandle == DRV_HANDLE_INVALID )
                {
                    /* Set the app state to invalid */
                    appDataUart.currentState = APP_ERROR;
                }
                else
                {
                    /* Set the App. state to wait for done */
                    appDataUart.prevState    = APP_USR_MSG_READ;
                    appDataUart.currentState = APP_WAIT_FOR_DONE;
                }
            }
        }
        break;

        case APP_USR_MSG_WRITE:
        {
            /* Get the USART driver status */
            appDataUart.usartStatus = DRV_USART_ClientStatus( appDataUart.usartHandle );

            if ( appDataUart.usartStatus == DRV_USART_CLIENT_STATUS_READY )
            {
                /* Submit buffer to USART */
                DRV_USART_BufferAddWrite( appDataUart.usartHandle,
                                          &(appDataUart.usartBufferHandle),
                                          appDataUart.buffer, appDataUart.bufferSize);

                if ( appDataUart.usartBufferHandle == DRV_HANDLE_INVALID )
                {
                    /* Set the App. state to error */
                    appDataUart.currentState = APP_ERROR;
                }
                else
                {
                    /* Set the App. state to wait for done */
                    appDataUart.prevState    = APP_IDLE;
                    appDataUart.currentState = APP_WAIT_FOR_DONE;
                }
            }
        }
        break;

        case APP_DRV_DEMO_COMPLETE:
        {
            /* Get the USART driver status */
            appDataUart.usartStatus = DRV_USART_ClientStatus( appDataUart.usartHandle );

            if ( appDataUart.usartStatus == DRV_USART_CLIENT_STATUS_READY )
            {

                appDataUart.usrMsgIndex++;
                /* Get the exit message from the user data buffer */
                strcpy( appDataUart.buffer, appMsg[appDataUart.usrMsgIndex] );
                /* Update Buffer Size */
                appDataUart.bufferSize = min(APP_BUFFER_SIZE,
                                                   strlen(appDataUart.buffer));
                /* Submit buffer to USART */
                DRV_USART_BufferAddWrite( appDataUart.usartHandle,
                                          &(appDataUart.usartBufferHandle),
                                          appDataUart.buffer, appDataUart.bufferSize);

                if ( appDataUart.usartBufferHandle == DRV_HANDLE_INVALID )
                {
                    /* Set the app state to invalid */
                    appDataUart.currentState = APP_ERROR;
                }
                else
                {
                    /* Set the app state to Wait for done */
                    appDataUart.prevState    = APP_DRV_DEMO_COMPLETE;
                    appDataUart.currentState = APP_WAIT_FOR_DONE;
                }
            }
        }
        break;

        case APP_IDLE:
        {
            /* Close USART Driver */
            DRV_USART_Close( appDataUart.usartHandle );
            /* Deinitialize the driver */
            DRV_USART_Deinitialize( sysObj.drvUsart0 );
            DRV_USART_Deinitialize( sysObj.drvUsart1 );
            /* The appliction comes here when the demo has completed
             * successfully. Switch on LED D5. */

        }
        break;

        case APP_ERROR:
        {
            /* The appliction comes here when the demo
             * has failed. Switch on the LED D9.*/
            
        }
        break;
        // perso
        
        case APP_MIDI_OPEN:
            DRV_USART_Close (appDataUart.usartHandle);
            Config_UsartON = 1;
            
            
            appDataUart.usartHandle = DRV_USART_Open(N_Usart,(DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_NONBLOCKING));
            

            /* Check the USART driver handler */
            if (appDataUart.usartHandle != DRV_HANDLE_INVALID )
            {
                DRV_USART_BufferEventHandlerSet(appDataUart.usartHandle,
                                       APP_BufferEventHandler, APP_DRV_CONTEXT);
                /* Set the app state to Ready */

                appDataUart.usrMsgIndex = 0;
                appDataUart.currentState = APP_DRV_MSG_WRITE;

            }
            else
            {
                /* If handler is not ready, set the App. state to error */
                appDataUart.currentState = APP_ERROR;
            }
        break;

        default:
            break;
    }
}

/*******************************************************************************
  Function:
    void App_UpdateTaskState( void )

  Remarks:
    See prototype in app.h.
 */

void App_GetNextTaskState(uint32_t appState)
{
    switch ( appState )
    {
        case APP_DRV_READY:
            /* Set the next Demo App. State */
            appDataUart.currentState = APP_USR_MSG_READ;
            break;

        case APP_DRV_MSG_WRITE:
        {
            if(appDataUart.usrMsgIndex < 0)
            {
                /* Get the next message from App. banner */
                appDataUart.usrMsgIndex++;
                /* Set the next Demo App. State */
                appDataUart.currentState = APP_DRV_MSG_WRITE;
            }
            else
            {
                /* Insert newline character, before accepting data from user */
                strcpy(appDataUart.buffer, appMsg[appDataUart.usrMsgIndex]);
                appDataUart.bufferSize = APP_NO_OF_BYTES_TO_READ;
                /* Set the buffer event for user data */
                DRV_USART_BufferEventHandlerSet(appDataUart.usartHandle,
                                  APP_BufferEventHandler, APP_USR_CONTEXT);
                /* Set the next Demo App. State */
                appDataUart.currentState = APP_USR_MSG_READ;
            }
        }
        break;

        case APP_USR_MSG_READ:
            /* Set the next Demo App. State */
            appDataUart.currentState = APP_USR_MSG_WRITE;
            break;

        case APP_USR_MSG_WRITE:
            /* Set the next Demo App. State */
            appDataUart.currentState = APP_USR_MSG_READ;
            break;

        case APP_DRV_DEMO_COMPLETE:
            /* Set the next Demo App. State */
            appDataUart.currentState = APP_IDLE;
            break;
    }
}


/*******************************************************************************
 End of File
*/

