/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "EEPROM_Driver.h"
#include "app.h"
#include "tcpip/tcpip.h"
extern APP_DATA appData;

bool processeurAudio[I2C_NB_PT2314] ={1,1,1,1,1,1,0,0,0,0,0,0,0};//PT2314 ou TDA7439

I2C_Devices_States I2C_TCA9548A_state   = I2C_DEVICE_WRITE;
I2C_Devices_States I2C_AD5593_state     = I2C_DEVICE_WRITE;
I2C_Devices_States I2C_PT2314_state     = I2C_DEVICE_WRITE;
I2C_Devices_States I2C_EEPROM_state     = I2C_DEVICE_WRITE;



I2C_Msg_Expander    I2C_Msg_Expanders   [I2C_NB_AD5593 + I2C_NB_PT2314] = 
{{.size = 2, .msg = {DEACTIVATE_EXPANDER, EXP_ADC_FADER},       .add = {I2C_EXPANDER2_ADD, I2C_EXPANDER0_ADD}},
 {.size = 1, .msg = {EXP_ADC_POT_ROT},                          .add = {I2C_EXPANDER0_ADD}},
 {.size = 2, .msg = {DEACTIVATE_EXPANDER, EXP_DAC_ADC_FADER},   .add = {I2C_EXPANDER0_ADD, I2C_EXPANDER1_ADD}},
 {.size = 2, .msg = {DEACTIVATE_EXPANDER, EXP_ON_AIR},          .add = {I2C_EXPANDER1_ADD, I2C_EXPANDER2_ADD}},
 
 {.size = 2, .msg = {DEACTIVATE_EXPANDER, EXP_PT_MIC1},         .add = {I2C_EXPANDER2_ADD, I2C_EXPANDER1_ADD}},
 {.size = 1, .msg = {EXP_PT_MIC2},                              .add = {I2C_EXPANDER1_ADD}},
 {.size = 1, .msg = {EXP_PT_MIC3},                              .add = {I2C_EXPANDER1_ADD}},
 {.size = 1, .msg = {EXP_PT_MIC4},                              .add = {I2C_EXPANDER1_ADD}},
 {.size = 1, .msg = {EXP_PT_LIGNE1},                            .add = {I2C_EXPANDER1_ADD}},
 {.size = 1, .msg = {EXP_PT_LIGNE2},                            .add = {I2C_EXPANDER1_ADD}},
 {.size = 2, .msg = {DEACTIVATE_EXPANDER, EXP_STUDIO},          .add = {I2C_EXPANDER1_ADD, I2C_EXPANDER2_ADD}},
 {.size = 1, .msg = {EXP_MASTER},                               .add = {I2C_EXPANDER2_ADD}},
 {.size = 1, .msg = {EXP_PHONE1},                               .add = {I2C_EXPANDER2_ADD}},
 {.size = 1, .msg = {EXP_PHONE2},                               .add = {I2C_EXPANDER2_ADD}},
 {.size = 1, .msg = {EXP_PHONE3},                               .add = {I2C_EXPANDER2_ADD}},
 {.size = 1, .msg = {EXP_PHONE4},                               .add = {I2C_EXPANDER2_ADD}},
 {.size = 1, .msg = {EXP_PHONE_DJ},                             .add = {I2C_EXPANDER2_ADD}}};

I2C_PT2314 I2C_Msgs_PT2314[I2C_NB_PT2314]=
{{.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
 {.msgWrite=I2C_PT2314_WRITE, .size=6, .add = I2C_PT2314_ADD},
};

I2C_EEPROM I2C_eeprom =
{.add=I2C_EEPROM_ADD, .read.toRead=false, .write.toWrite=false};

I2C_Msg_AD5593      I2C_Msg_AD5593s[I2C_NB_AD5593] =
        //                           ADC            DAC            IN          OUT         OPEN DRAIN
{{.Init.msgInit = I2C_AD5593_INIT(0, 0b00111111, 0, 0b00000000, 0, 0b00000000, 0b00000000, 0b00000000), .ADC.msgRead = I2C_AD5593_START_READ, .add = I2C_AD5593_ADD},
 {.Init.msgInit = I2C_AD5593_INIT(0, 0b01111111, 0, 0b00000000, 0, 0b00000000, 0b00000000, 0b00000000), .ADC.msgRead = I2C_AD5593_START_READ, .add = I2C_AD5593_ADD},
 {.Init.msgInit = I2C_AD5593_INIT(1, 0b00001010, 1, 0b11110101, 1, 0b00000000, 0b00000000, 0b00000000), .ADC.msgRead = I2C_AD5593_START_READ, .add = I2C_AD5593_ADD},
 {.Init.msgInit = I2C_AD5593_INIT(1, 0b00000011, 0, 0b00000000, 1, 0b00000000, 0b00000100, 0b00000000), .ADC.msgRead = I2C_AD5593_START_READ, .add = I2C_AD5593_ADD},
};

I2C_Error I2C_error[2 * (I2C_NB_AD5593 + I2C_NB_PT2314) + 1] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0};

Parametre_AD faders, pot_rots;
typedef enum {ACT_FADERS, ACT_POT_ROT, ACT_FADERS_OUT} ActiveDevice;
ActiveDevice activeDevice = 0, activeExpander = 0;
typedef enum {GROUP_AD5593, GROUP_PT2314, GROUP_EEPROM}I2C_Groups;
I2C_Groups activeGroup = GROUP_AD5593;
int writeptr = 0, isRead = false;
bool APP_Write_Tasks(void)
{
    switch(I2C_state)
    {
        static int deactiveExpander = 0;
        case I2C_EXPANDER_HANDLE:
        {
            if(I2C_TCA9548A_state == I2C_DEVICE_WRITE)
            {
                if ( (appData.drvI2CTxRxBufferHandle[0] == (DRV_I2C_BUFFER_HANDLE) NULL) || 
                        (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[0]) == DRV_I2C_BUFFER_EVENT_COMPLETE) || 
                            (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[0]) == DRV_I2C_BUFFER_EVENT_ERROR) )
                {
                    appData.drvI2CTxRxBufferHandle[0] = DRV_I2C_Transmit (  appData.drvI2CHandle_Master,
                                                                            I2C_Msg_Expanders[activeExpander].add[deactiveExpander],
                                                                            &I2C_Msg_Expanders[activeExpander].msg[deactiveExpander], 
                                                                            1, 
                                                                            NULL);
                    I2C_TCA9548A_state = I2C_DEVICE_WAIT;
                }
            }
            else if(I2C_TCA9548A_state == I2C_DEVICE_WAIT)
            {
                if(I2C_error[activeExpander*2].time ++ < 10000)
                {
                    if ((APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[0]) == DRV_I2C_BUFFER_EVENT_COMPLETE ) ||
                        (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[0]) == DRV_I2C_BUFFER_EVENT_ERROR) )
                    {
                        I2C_error[activeExpander*2].time = 0;
                        I2C_TCA9548A_state = I2C_DEVICE_WRITE;
                        if(I2C_Msg_Expanders[activeExpander].size == 1 || deactiveExpander == 1)
                        {
                            deactiveExpander = 0;
                            activeExpander++;
                            switch(activeGroup)
                            {
                                case GROUP_AD5593:
                                {
//                                    PLIB_I2C_BaudRateSet(I2C_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 400000);
                                    I2C_state = I2C_AD5593_HANDLE;
                                }break;
                                case GROUP_PT2314:
                                {
                                    if(I2C_Msgs_PT2314[activeDevice].isConfigurate == false)
                                    {
                                        I2C_state = I2C_PT2314_HANDLE;
                                    }
                                    else
                                    {
                                        I2C_state = I2C_HANDLE;
                                    }
                                }break;
                                default:
                                {
                                    I2C_state = I2C_HANDLE;
                                }break;
                            }
                        }
                        else
                        {   // tout les device de l'expander traités, desactivation
                            deactiveExpander = 1;
                        }
                    }
                }
                else
                {
                    I2C_error[activeExpander*2].time = 0;
                    I2C_error[activeExpander*2].error++;
                    I2C_state = I2C_ERROR;
                }
            }
        }break;
        case I2C_AD5593_HANDLE:
        {
            if(I2C_AD5593_state == I2C_DEVICE_WRITE)
            {
                if(I2C_Msg_AD5593s[activeDevice].Init.isInit == false)
                {
                    if ( (appData.drvI2CTxRxBufferHandle[1] == (DRV_I2C_BUFFER_HANDLE) NULL) || 
                            (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[1]) == DRV_I2C_BUFFER_EVENT_COMPLETE) || 
                                (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[1]) == DRV_I2C_BUFFER_EVENT_ERROR) )
                    {
                        appData.drvI2CTxRxBufferHandle[1] = DRV_I2C_Transmit (  appData.drvI2CHandle_Master,
                                                                                I2C_Msg_AD5593s[activeDevice].add,
                                                                                &I2C_Msg_AD5593s[activeDevice].Init.msgInit[I2C_Msg_AD5593s[activeDevice].Init.initPtr*3], 
                                                                                3, 
                                                                                NULL);
                        I2C_AD5593_state = I2C_DEVICE_WAIT;
                    }
                }
                else
                {
                    if ( (appData.drvI2CTxRxBufferHandle[1] == (DRV_I2C_BUFFER_HANDLE) NULL) || 
                            (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[1]) == DRV_I2C_BUFFER_EVENT_COMPLETE) ||
                                (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[1]) == DRV_I2C_BUFFER_EVENT_ERROR) )
                    {
                        if(I2C_Msg_AD5593s[activeDevice].DAC.nbDAC > writeptr)
                        {
                            appData.drvI2CTxRxBufferHandle[1] = DRV_I2C_Transmit (  appData.drvI2CHandle_Master,
                                                                                I2C_Msg_AD5593s[activeDevice].add,
                                                                                &I2C_Msg_AD5593s[activeDevice].DAC.msgWrite[0 + 3*writeptr], 
                                                                                3, 
                                                                                NULL);
                            I2C_AD5593_state = I2C_DEVICE_WAIT;
                        }
                        else if(I2C_Msg_AD5593s[activeDevice].GPIO.writeAsked == true)
                        {
                            appData.drvI2CTxRxBufferHandle[1] = DRV_I2C_Transmit (  appData.drvI2CHandle_Master,
                                                                                I2C_Msg_AD5593s[activeDevice].add,
                                                                                &I2C_Msg_AD5593s[activeDevice].GPIO.msgWrite[0], 
                                                                                3, 
                                                                                NULL);
                            I2C_Msg_AD5593s[activeDevice].GPIO.writeAsked = false;
                            I2C_AD5593_state = I2C_DEVICE_WAIT;
                        }
                        else if(I2C_Msg_AD5593s[activeDevice].ADC.nbADC > 0)
                        {
                            isRead = true;
                            appData.drvI2CTxRxBufferHandle[1] = DRV_I2C_TransmitThenReceive (   appData.drvI2CHandle_Master,
                                                                                                I2C_Msg_AD5593s[activeDevice].add,
                                                                                                &I2C_Msg_AD5593s[activeDevice].ADC.msgRead[0], 
                                                                                                1,  
                                                                                                &I2C_Msg_AD5593s[activeDevice].ADC.msgRead[1], 
                                                                                                I2C_Msg_AD5593s[activeDevice].ADC.nbADC*2, 
                                                                                                NULL);
                            I2C_AD5593_state = I2C_DEVICE_WAIT;
                        }
                    }
                }
            }
            else if(I2C_AD5593_state == I2C_DEVICE_WAIT)
            {
                if(I2C_error[(activeDevice*2) + 1].time++ < 10000)
                {
                    if ((APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[1]) == DRV_I2C_BUFFER_EVENT_COMPLETE ) ||
                        (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[1]) == DRV_I2C_BUFFER_EVENT_ERROR) )
                    {
                        I2C_error[(activeDevice*2) + 1].time = 0;
                        I2C_AD5593_state = I2C_DEVICE_WRITE;
                        if(APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[1]) == DRV_I2C_BUFFER_EVENT_COMPLETE)
                        {
                            if(I2C_Msg_AD5593s[activeDevice].Init.isInit == false)
                            {
                                I2C_Msg_AD5593s[activeDevice].Init.initPtr++;
                                if(I2C_Msg_AD5593s[activeDevice].Init.initPtr >= I2C_AD5593_INIT_SIZE/3)
                                {
                                    I2C_Msg_AD5593s[activeDevice].Init.isInit = true;
                                }
                            }
                            else
                            {
                                writeptr ++;
                                if(writeptr >= I2C_Msg_AD5593s[activeDevice].DAC.nbDAC)
                                {
                                    if(I2C_Msg_AD5593s[activeDevice].ADC.nbADC == 0 || isRead == true)
                                    {
                                        isRead = false;
                                        writeptr = 0;
                                        I2C_state = I2C_HANDLE;
                                        StateAck.ACK_AD5532[activeDevice] = true;
                                    }
                                    else
                                    {
                                        StateAck.ACK_AD5532[activeDevice] = false;
                                    }
                                }
                            }
                        }
                        else
                        {
                            I2C_state = I2C_HANDLE;
                        }
                    }
                }
                else
                {
                    I2C_error[(activeDevice*2) + 1].time = 0;
                    I2C_error[(activeDevice*2) + 1].error++;
                    I2C_state = I2C_ERROR;
                }
            }
        }break;
        case I2C_PT2314_HANDLE:
        {
            if(I2C_PT2314_state == I2C_DEVICE_WRITE)
            {
                if ( (appData.drvI2CTxRxBufferHandle[2] == (DRV_I2C_BUFFER_HANDLE) NULL) || 
                        (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[2]) == DRV_I2C_BUFFER_EVENT_COMPLETE) || 
                            (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[2]) == DRV_I2C_BUFFER_EVENT_ERROR) )
                {
                    appData.drvI2CTxRxBufferHandle[2] = DRV_I2C_Transmit (  appData.drvI2CHandle_Master,
                                                                            I2C_Msgs_PT2314[activeDevice].add,
                                                                            I2C_Msgs_PT2314[activeDevice].msgWrite, 
                                                                            I2C_Msgs_PT2314[activeDevice].size,                                                                             
                                                                            NULL);
//                    appData.drvI2CTxRxBufferHandle[2] = DRV_I2C_TransmitForced (  appData.drvI2CHandle_Master,
//                                                                            I2C_Msgs_PT2314[activeDevice].add,
//                                                                            I2C_Msgs_PT2314[activeDevice].msgWrite, 
//                                                                            I2C_Msgs_PT2314[activeDevice].size, 
//                                                                            DRV_I2C_BUS_IGNORE_OVERFLOW_ERROR,
//                                                                            NULL);                    
                    I2C_PT2314_state = I2C_DEVICE_WAIT;
                }
            }
            else if(I2C_PT2314_state == I2C_DEVICE_WAIT)
            {
                if(I2C_error[((activeDevice+I2C_NB_AD5593)*2) + 1].time++ < 10000)
                {
                    if ((APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[2]) == DRV_I2C_BUFFER_EVENT_COMPLETE ) ||
                        (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[2]) == DRV_I2C_BUFFER_EVENT_ERROR) )
                    {
                        I2C_error[((activeDevice+I2C_NB_AD5593)*2) + 1].time = 0;
                        I2C_PT2314_state = I2C_DEVICE_WRITE;

                        if(APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[2]) == DRV_I2C_BUFFER_EVENT_COMPLETE)
                        {
                            I2C_Msgs_PT2314[activeDevice].isConfigurate = true;
                            StateAck.ACK_PT2314[activeDevice] = true;

                        }
                        else
                        {
                            StateAck.ACK_PT2314[activeDevice] = false;
                        }

                        I2C_state = I2C_HANDLE;
                    }
                }
                else
                {
                    I2C_error[((activeDevice+I2C_NB_AD5593)*2) + 1].time = 0;
                    I2C_error[((activeDevice+I2C_NB_AD5593)*2) + 1].error++;
                    I2C_state = I2C_ERROR;
                }
            }
        }break;
        case I2C_EEPROM_HANDLE:
        {
            if(I2C_EEPROM_state == I2C_DEVICE_WRITE)
            {
                
                if ( (appData.drvI2CTxRxBufferHandle[3] == (DRV_I2C_BUFFER_HANDLE) NULL) || 
                        (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[3]) == DRV_I2C_BUFFER_EVENT_COMPLETE) || 
                            (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[3]) == DRV_I2C_BUFFER_EVENT_ERROR) )
                {
                    if(I2C_eeprom.write.toWrite == true)
                    {
                        appData.drvI2CTxRxBufferHandle[3] = DRV_I2C_Transmit (  appData.drvI2CHandle_Master,
                                                                                I2C_eeprom.add,
                                                                                I2C_eeprom.write.msgWrite, 
                                                                                I2C_eeprom.write.size, 
                                                                                NULL);
                        I2C_EEPROM_state = I2C_DEVICE_WAIT;
                    }
                    else if(I2C_eeprom.read.toRead == true)
                    {
                        appData.drvI2CTxRxBufferHandle[3] = DRV_I2C_TransmitThenReceive (   appData.drvI2CHandle_Master,
                                                                                            I2C_eeprom.add,
                                                                                            I2C_eeprom.read.startAddress, 
                                                                                            2,  
                                                                                            I2C_eeprom.read.msgRead, 
                                                                                            I2C_eeprom.read.size, 
                                                                                            NULL);
                        I2C_EEPROM_state = I2C_DEVICE_WAIT;
                    }
                }
            }
            else if(I2C_EEPROM_state == I2C_DEVICE_WAIT)
            {
                if(I2C_error[2 * (I2C_NB_AD5593 + I2C_NB_PT2314)].time++ < 10000)
                {
                    if ((APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[3]) == DRV_I2C_BUFFER_EVENT_COMPLETE ) ||
                        (APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[3]) == DRV_I2C_BUFFER_EVENT_ERROR) )
                    {
                        I2C_error[2 * (I2C_NB_AD5593 + I2C_NB_PT2314)].time = 0;
                        I2C_EEPROM_state = I2C_DEVICE_WRITE;
                        I2C_state = I2C_HANDLE;

                        if(APP_Check_Transfer_Status(appData.drvI2CHandle_Master, appData.drvI2CTxRxBufferHandle[3]) == DRV_I2C_BUFFER_EVENT_COMPLETE )
                        {
                            I2C_eeprom.read.toRead = false;
                            I2C_eeprom.write.toWrite = false;
                        }

                    }
                }
                else
                {
                    I2C_error[2 * (I2C_NB_AD5593 + I2C_NB_PT2314)].time = 0;
                    I2C_error[2 * (I2C_NB_AD5593 + I2C_NB_PT2314)].error++;
                }
            }
        }break;
        case I2C_HANDLE:
        {
            // Pré-traitement
            PLIB_I2C_BaudRateSet(I2C_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 100000);
            if(activeGroup == GROUP_AD5593)
            {
                int i;
                for(i = 0; i < I2C_Msg_AD5593s[activeDevice].ADC.nbADC*2; i+=2)
                {
                    uint8_t add = (I2C_Msg_AD5593s[activeDevice].ADC.msgRead[i + 1] & 0b01110000) >> 4;
                    uint16_t val = (uint16_t)(((I2C_Msg_AD5593s[activeDevice].ADC.msgRead[i + 1] & 0b00001111) << 8) | (I2C_Msg_AD5593s[activeDevice].ADC.msgRead[i + 2] & 0xFF));
                    I2C_Msg_AD5593s[activeDevice].ADC.valeur[add] = val;
                }
                PLIB_I2C_BaudRateSet(I2C_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 100000);
            }
            
            I2C_state = I2C_EXPANDER_HANDLE;
            activeDevice++;
            switch(activeGroup)
            {
                case GROUP_AD5593:
                {
                    if(activeDevice >= I2C_NB_AD5593)
                    {
                        activeGroup ++;
                        activeDevice = 0;
//                        APP_UpdateState2(APP_STATE2_MESURE_AD);
                        Gestion_Line();
//                        PLIB_I2C_BaudRateSet(I2C_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 100000);
                    }
                }break;
                case GROUP_PT2314:
                {
                    if(activeDevice >= I2C_NB_PT2314)
                    {
                        activeGroup++;
                        activeDevice = 0;
//                        PLIB_I2C_BaudRateSet(I2C_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 400000);
                        I2C_state = I2C_EEPROM_HANDLE;
                    }
                }break;
                case GROUP_EEPROM:
                {
                    extern int I2C_cpt;
                    if(I2C_cpt > 100)
                    {
                        I2C_cpt = 0;
                        activeGroup = 0;
                        activeDevice = 0;
                        activeExpander = 0;
                    }
                }break;
            }
            
            
            // Post traitement
            if(activeGroup == GROUP_PT2314)
            {
//                if(I2C_Msgs_PT2314[activeDevice].isConfigurate == true)
//                {
//                    I2C_state = I2C_HANDLE;
//                }
//                else if(I2C_Msgs_PT2314[0].isConfigurate == false)
//                {
//                    Nop();
//                }
            }
            else if(activeGroup == GROUP_EEPROM)
            {
                if(I2C_eeprom.read.toRead == false && I2C_eeprom.write.toWrite == false)
                {
                    I2C_state = I2C_HANDLE;
                }
            }
        }break;
        case I2C_ERROR:
        {
            PLIB_I2C_MasterStop (I2C_ID_2);
            DRV_I2C0_DeInitialize();
            DRV_I2C_Close(appData.drvI2CHandle_Master);
//            TRISAbits.TRISA2 = 0;
//            TRISAbits.TRISA3 = 0;
//            LATAbits.LATA2 = 0;
//            LATAbits.LATA3 = 0;
//            delay_us(5);
//            LATAbits.LATA2 = 1;
//            LATAbits.LATA3 = 1;      
//            delay_us(5);
//            LATAbits.LATA2 = 0;
//            LATAbits.LATA3 = 0;   
            
//            DRV_I2C_Close(appData.drvI2CHandle_Master);
            
            DRV_I2C0_Initialize();
            
            
            I2C_TCA9548A_state   = I2C_DEVICE_WRITE;
            I2C_AD5593_state     = I2C_DEVICE_WRITE;
            I2C_PT2314_state     = I2C_DEVICE_WRITE;
            I2C_EEPROM_state     = I2C_DEVICE_WRITE;
            appData.drvI2CTxRxBufferHandle[0] = 0;
            appData.drvI2CTxRxBufferHandle[1] = 0;
            appData.drvI2CTxRxBufferHandle[2] = 0;
            I2C_state = I2C_HANDLE;
        }break;
    }   
    return false;
}
                            // Fonctionne
//                            static bool testSpeed = false;
//                            if(testSpeed == false)
//                            {
//                                testSpeed = true;
//                                PLIB_I2C_BaudRateSet(I2C_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 100000);
//                            }
//                            else
//                            {
//                                testSpeed = false;
//                                PLIB_I2C_BaudRateSet(I2C_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 400000);
//                            }

//****************************************************************************/
//  Function: APP_Check_Transfer_Status
//
//  Returns the status of Buffer operation from the driver; The application
//  can probe this function to see if the status of a particular I2C
//  transfer is in its execution
//****************************************************************************/
DRV_I2C_BUFFER_EVENT APP_Check_Transfer_Status(DRV_HANDLE drvOpenHandle, DRV_I2C_BUFFER_HANDLE drvBufferHandle)
{
    return (DRV_I2C_TransferStatusGet  (appData.drvI2CHandle_Master, drvBufferHandle));
}

//****************************************************************************/
//  Function: Master Callback Function 
//
//  Callback from DRV_I2C_Tasks when I2C is configured in Master mode     
//****************************************************************************/

void I2CMasterOpStatusCb ( DRV_I2C_BUFFER_EVENT event,
                           DRV_I2C_BUFFER_HANDLE bufferHandle,
                           uintptr_t context)
{
    static uint32_t successCount = 0;
    
    switch (event)
    {
        case DRV_I2C_BUFFER_EVENT_COMPLETE:
            successCount++;
            Nop();
            break;
        case DRV_I2C_BUFFER_EVENT_ERROR:
            successCount--;
            break;
        default:
            break;
    }
}


/***********************************************************
 *   Millisecond Delay function using the Count register
 *   in coprocessor 0 in the MIPS core.
 *   When running 200 MHz, CoreTimer frequency is 100 MHz
 *   CoreTimer increments every 2 SYS_CLK, CoreTimer period = 10ns
 *   1 ms = N x CoreTimer_period;
 *   To count 1ms, N = 100000 counts of CoreTimer
 *   1 ms = 10 ns * 100000 = 10e6 ns = 1 ms
 *   When running 80 MHz, CoreTimer frequency is 40 MHz 
 *   CoreTimer increments every 2 SYS_CLK, CoreTimer period = 25ns
 *   To count 1ms, N = 40000 counts of CoreTimer
 *   1ms = 25 ns * 40000 = 10e6 ns = 1 ms
 *   ms_SCALE = (GetSystemClock()/2000) @ 200 MHz = 200e6/2e3 = 100e3 = 100000
 *   ms_SCLAE = (GetSystemClock()/2000) @ = 80e6/2e3 = 40e3 = 40000 
 */
 
void DelayMs(unsigned long int msDelay )
{
      register unsigned int startCntms = ReadCoreTimer();
      register unsigned int waitCntms = msDelay * ms_SCALE;
 
      while( ReadCoreTimer() - startCntms < waitCntms );
}

/***********************************************************
 *   Microsecond Delay function using the Count register
 *   in coprocessor 0 in the MIPS core.
 *   When running 200 MHz, CoreTimer frequency is 100 MHz
 *   CoreTimer increments every 2 SYS_CLK, CoreTimer period = 10ns
 *   1 us = N x CoreTimer_period;
 *   To count 1us, N = 100 counts of CoreTimer
 *   1 us = 10 ns * 100 = 1000 ns  = 1us
 *   When running 80 MHz, CoreTimer frequency is 40 MHz 
 *   CoreTimer increments every 2 SYS_CLK, CoreTimer period = 25ns
 *   To count 1us, N = 40 counts of CoreTimer
 *   1us = 25 ns * 40 = 1000 ns = 1 us
 *   us_SCALE = (GetSystemClock()/2000) @ 200 MHz = 200e6/2e6 = 100 
 *   us_SCLAE = (GetSystemClock()/2000) @ 80 MHz = 80e6/2e6 = 40 
 */
 
void DelayUs(unsigned long int usDelay )
{
      register unsigned int startCnt = ReadCoreTimer();
      register unsigned int waitCnt = usDelay * us_SCALE;
 
      while( ReadCoreTimer() - startCnt < waitCnt );
}

void I2C_AD5593_Init_Buffer(void)
{
    int i;
    for(i = 0; i < I2C_NB_AD5593; i++)
    {
        if(I2C_Msg_AD5593s[i].Init.msgInit[0] == 3)
        {
            int j;
            for(j = 0; j < 8; j++)
            {
                if(I2C_Msg_AD5593s[i].ADC.port & (1 << j))
                {
                    I2C_Msg_AD5593s[i].ADC.nbADC++;
                }
                if(I2C_Msg_AD5593s[i].DAC.port & (1 << j))
                {
                    I2C_Msg_AD5593s[i].DAC.msgWrite[I2C_Msg_AD5593s[i].DAC.nbDAC*3] = 0x10 + j;
                    I2C_Msg_AD5593s[i].DAC.msgWrite[I2C_Msg_AD5593s[i].DAC.nbDAC*3 + 1] = 0x80 + (j << 4) + 0x0F;
                    I2C_Msg_AD5593s[i].DAC.msgWrite[I2C_Msg_AD5593s[i].DAC.nbDAC*3 + 2] = 0xFF;
                    I2C_Msg_AD5593s[i].DAC.nbDAC++;
                }
            }
        }
    }
}

uint16_t I2C_Read_Buffer(AD_DEVICES device, int port)
{
    return I2C_Msg_AD5593s[device].ADC.valeur[port];
}
void I2C_Write_Buffer(AD_DEVICES device, int port, int value)
{
    int i;
    for(i = 0; i < 8; i++)
    {
        if((I2C_Msg_AD5593s[device].DAC.msgWrite[i*3] & 0x0F) == port)
        {
            I2C_Msg_AD5593s[device].DAC.msgWrite[i*3 + 1] = 0x80 + (port << 4) + ((value & 0x0F00) >> 8);
            I2C_Msg_AD5593s[device].DAC.msgWrite[i*3 + 2]  = (value & 0xFF);
        }
    }
}

void I2C_Write_GPIO(AD_DEVICES device, int port, bool value)
{
    if(value == false)
    {   // Mise à zéro
        I2C_Msg_AD5593s[device].GPIO.msgWrite[2] &= ~(1<<port);
    }
    else
    {   // Mise à 1
        I2C_Msg_AD5593s[device].GPIO.msgWrite[2] |=  (1<<port);
    }
    I2C_Msg_AD5593s[device].GPIO.writeAsked = true;
}


// Gauche droite volume float, loudness bool
void  I2C_PT_Volume( PT_DEVICES d, float volume)
{
    if(processeurAudio[d] == 0)//PT2314
    {
        I2C_Msgs_PT2314[d].size=6;
        unsigned int dizVol = volume / -10.;
        unsigned int vol = (volume - (dizVol * -10.)) / -1.25;
        unsigned int Valeur = 0 | (vol & 0b111) | ((dizVol & 0b111) << 3);      

        I2C_Msgs_PT2314[d].msgWrite[0] = Valeur;      
    }
    else
    {
        I2C_Msgs_PT2314[d].size=9;
        
        if(volume < -30)
        {
            volume = -56;

        }
        I2C_Msgs_PT2314[d].msgWrite[3] = (int)(-volume);

    }
    I2C_Msgs_PT2314[d].isConfigurate = false;
}

// !!!!!!!!!!!!! Modifs sans attenuation !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void I2C_PT_Speak_Att(PT_DEVICES d, float attenuation, T_LR lr)
{
    if(processeurAudio[d] == 0)//PT2314
    {
        I2C_Msgs_PT2314[d].size=6;
        unsigned int dizAtt = attenuation / -10.;
        unsigned int att = (attenuation - (dizAtt * -10.)) / -1.25;

        if(lr == LEFT)
        {
            I2C_Msgs_PT2314[d].msgWrite[1] = (0b110 << 5) | (att & 0b111) | ((dizAtt & 0b11) << 3);
        }
        else
        {
            I2C_Msgs_PT2314[d].msgWrite[2] = (0b111 << 5) | (att & 0b111) | ((dizAtt & 0b11) << 3);
        }
    }
    else
    {
        I2C_Msgs_PT2314[d].size=9;
//        if(lr == LEFT)
//        {
//            I2C_Msgs_PT2314[d].msgWrite[7] = 120;
//        }
//        else
//        {
//            I2C_Msgs_PT2314[d].msgWrite[8] = 120;
//        }
        I2C_Msgs_PT2314[d].msgWrite[7] = 0;
        I2C_Msgs_PT2314[d].msgWrite[8] = 0;        
    }
    I2C_Msgs_PT2314[d].isConfigurate = false;
}

void I2C_PT_AudioSwitch(PT_DEVICES d, float gain, bool loodness, Stereo stereo)
{
    if(processeurAudio[d] == 0)//PT2314
    {
        I2C_Msgs_PT2314[d].size=6;
        unsigned int g = gain / 3.75;
    
        g = 0b11 - (g & 0b11);
        I2C_Msgs_PT2314[d].msgWrite[3] = (0b010 << 5) | (loodness << 2) | (g << 3) | stereo;
    }
    else
    {
        if(gain < 0){gain = 0;}
        if(gain > 30){gain = 30;}
        
        I2C_Msgs_PT2314[d].size=9;
        I2C_Msgs_PT2314[d].msgWrite[0] = 0b00010000 ;//select canal + incremente
        I2C_Msgs_PT2314[d].msgWrite[1] = 0b00000011;//entree 1
        I2C_Msgs_PT2314[d].msgWrite[2] = (int)(gain/2);//Gain 0 
        
    }
    I2C_Msgs_PT2314[d].isConfigurate = false;
}

void I2C_PT_BASS_TREBLE(PT_DEVICES d, int attenuation, PT_BT choice)
{
    unsigned int att;
    if(attenuation < 0)
    {
        att = (attenuation + 14) / 2;
    }
    else
    {
        att = 0b1111 - (attenuation / 2);
    }
    if(processeurAudio[d] == 0)//PT2314
    {
        I2C_Msgs_PT2314[d].size=6;
        if(choice == PT_BASS)
        {
            I2C_Msgs_PT2314[d].msgWrite[4] = (0b0110 << 4) | att;
        }
        else if(choice == PT_TREBLE)
        {
            I2C_Msgs_PT2314[d].msgWrite[5] = (0b0111 << 4) | att;
        }
    }
    else
    {
        I2C_Msgs_PT2314[d].size=9;
        if(choice == PT_BASS)
        {
            I2C_Msgs_PT2314[d].msgWrite[4] = att;
        }
        else if(choice == TDA_MIDDLE)
        {
            I2C_Msgs_PT2314[d].msgWrite[5] = att;
        }   
        else if(choice == PT_TREBLE)
        {
            I2C_Msgs_PT2314[d].msgWrite[6] = att;
        }  
    }
    
    I2C_Msgs_PT2314[d].isConfigurate = false;
}

bool I2C_EEPROM_write(char* w, size_t size, uint16_t add)
{
    if(I2C_eeprom.write.toWrite == false && I2C_eeprom.read.toRead == false)
    {
        I2C_eeprom.write.toWrite = true;
        I2C_eeprom.write.size = size + 2;
        memcpy(I2C_eeprom.write.msgWrite+2, w, size);
        I2C_eeprom.write.msgWrite[1] = add & 0xFF;
        I2C_eeprom.write.msgWrite[0] = (add >> 8) & 0xFF;
        return true;
    }
    return false;
}

bool I2C_EEPROM_read(char* r, size_t size, uint16_t add)
{
    if(I2C_eeprom.write.toWrite == false && I2C_eeprom.read.toRead == false)
    {
        I2C_eeprom.read.toRead = true;
        I2C_eeprom.read.size = size;
        I2C_eeprom.read.msgRead = r;
        I2C_eeprom.read.startAddress[1] = add & 0xFF;
        I2C_eeprom.read.startAddress[0] = (add >> 8) & 0xFF;
        return true;
    }
    return false;
}

bool I2C_EEPROM_isReady(void)
{
    return !I2C_eeprom.read.toRead && !I2C_eeprom.write.toWrite;
}

PT_DEVICES Select_Input(int i)//Jo (13.02.2018)
{
    PT_DEVICES Device;
    switch(i)
    {
        case 0:
        {
            Device = PT_LIGNE1;
        }
        break;

        case 1:
        {
            Device = PT_LIGNE2;
        }
        break;

        case 2:
        {
            Device = PT_MIC1;
        }
        break;

        case 3:
        {
            Device = PT_MIC2;
        }
        break;

        case 4:
        {
            Device = PT_MIC3;
        }
        break;

        case 5:
        {
            Device = PT_MIC4;
        }
        break;
    }
    
    return Device;
}
PT_DEVICES Select_Output(int i)//Jo (13.02.2018
{
    PT_DEVICES Device;
    switch(i)
    {
        case 0:
        {
            Device = PT_STUDIO;
        }
        break;

        case 1:
        {
            Device = PT_MASTER;
        }
        break;

        case 2:
        {
            Device = PT_PHONE1;
        }
        break;

        case 3:
        {
            Device = PT_PHONE2;
        }
        break;

        case 4:
        {
            Device = PT_PHONE3;
        }
        break;

        case 5:
        {
            Device = PT_PHONE4;
        }
        break;

        case 6:
        {
            Device = PT_PHONE_DJ;
        }
        break;
    }
    
    return Device;
}

void ResetConfig(int N)
{

/******Config Usine*******************/
    float Somm_Volume;
    int Somm_VolumeIN;
    float Perte;
    int i;
    /********Audio In*************************/
    /********Line1****************/
    Nconfig[N].Device_IN[0].Loudness = 0;
    Nconfig[N].Device_IN[0].Aigue = 0;
    Nconfig[N].Device_IN[0].Middle = 0;
    Nconfig[N].Device_IN[0].Basse= 0;
    Nconfig[N].Device_IN[0].Volume = 0;
    Nconfig[N].Device_IN[0].ReductionMax = 10.;
    Nconfig[N].Device_IN[0].Niveau_Overload = 250;
    Nconfig[N].Device_IN[0].Niveau_Stop_Overload = 200;
    Nconfig[N].Device_IN[0].Time_Mute = 1000;

    /********Line2****************/
    Nconfig[N].Device_IN[1].Loudness = 0;
    Nconfig[N].Device_IN[1].Aigue = 0;
    Nconfig[N].Device_IN[1].Middle = 0;
    Nconfig[N].Device_IN[1].Basse= 0;
    Nconfig[N].Device_IN[1].Volume = 0;
    Nconfig[N].Device_IN[1].ReductionMax = 10.;
    Nconfig[N].Device_IN[1].Niveau_Overload = 250;
    Nconfig[N].Device_IN[1].Niveau_Stop_Overload = 200;
    Nconfig[N].Device_IN[1].Time_Mute = 1000;    

    /********Micro1****************/
    Nconfig[N].Device_IN[2].Loudness = 0;
    Nconfig[N].Device_IN[2].Aigue = 2;
    Nconfig[N].Device_IN[2].Middle = 6;
    Nconfig[N].Device_IN[2].Basse= 2;
    Nconfig[N].Device_IN[2].Volume = 10;

    /********Micro2****************/
    Nconfig[N].Device_IN[3].Loudness = 0;
    Nconfig[N].Device_IN[3].Aigue = 2;
    Nconfig[N].Device_IN[3].Middle = 6;
    Nconfig[N].Device_IN[3].Basse= 2;
    Nconfig[N].Device_IN[3].Volume = 10;

    /********Micro3****************/
    Nconfig[N].Device_IN[4].Loudness = 0;
    Nconfig[N].Device_IN[4].Aigue = 2;
    Nconfig[N].Device_IN[4].Middle = 6;
    Nconfig[N].Device_IN[4].Basse= 2;
    Nconfig[N].Device_IN[4].Volume = 10;


    /********Micro4****************/
    Nconfig[N].Device_IN[5].Loudness = 0;
    Nconfig[N].Device_IN[5].Aigue = 2;
    Nconfig[N].Device_IN[5].Middle = 6;
    Nconfig[N].Device_IN[5].Basse= 2;
    Nconfig[N].Device_IN[5].Volume = 10;
    
    
   

        
    /*************Audio OUT*********************/
        
    /*******Studio***************/             
    Nconfig[N].Device_OUT[0].Loudness = 0;
    Nconfig[N].Device_OUT[0].Aigue = 0;
    Nconfig[N].Device_OUT[0].Basse = -8;
    Nconfig[N].Device_OUT[0].Volume = -78.75;
    Nconfig[N].Device_OUT[0].L= 0;
    Nconfig[N].Device_OUT[0].R= 0;

    /*******Master***************/             
    Nconfig[N].Device_OUT[1].Loudness = 0;
    Nconfig[N].Device_OUT[1].Aigue = 0;
    Nconfig[N].Device_OUT[1].Basse = 0;
    Nconfig[N].Device_OUT[1].Volume = 11.25;
    Nconfig[N].Device_OUT[1].L= 0;
    Nconfig[N].Device_OUT[1].R= 0;
    Nconfig[N].Master_Gain = 0;


    /*******Phone1***************/             
    Nconfig[N].Device_OUT[2].Loudness = 0;
    Nconfig[N].Device_OUT[2].Aigue = 0;
    Nconfig[N].Device_OUT[2].Basse = 0;
    Nconfig[N].Device_OUT[2].Volume = 11.25;
    Nconfig[N].Device_OUT[2].L= 0;
    Nconfig[N].Device_OUT[2].R= 0;
    /*******Phone2***************/             
    Nconfig[N].Device_OUT[3].Loudness = 0;
    Nconfig[N].Device_OUT[3].Aigue = 0;
    Nconfig[N].Device_OUT[3].Basse = 0;
    Nconfig[N].Device_OUT[3].Volume = 11.25;
    Nconfig[N].Device_OUT[3].L= 0;
    Nconfig[N].Device_OUT[3].R= 0;
    /*******Phone3***************/             
    Nconfig[N].Device_OUT[4].Loudness = 0;
    Nconfig[N].Device_OUT[4].Aigue = 0;
    Nconfig[N].Device_OUT[4].Basse = 0;
    Nconfig[N].Device_OUT[4].Volume = 11.25;
    Nconfig[N].Device_OUT[4].L= 0;
    Nconfig[N].Device_OUT[4].R= 0;
    /*******Phone4***************/             
    Nconfig[N].Device_OUT[5].Loudness = 0;
    Nconfig[N].Device_OUT[5].Aigue = 0;
    Nconfig[N].Device_OUT[5].Basse = 0;
    Nconfig[N].Device_OUT[5].Volume = 11.25;
    Nconfig[N].Device_OUT[5].L= 0;
    Nconfig[N].Device_OUT[5].R= 0;
    /*******PhoneDJ***************/             
    Nconfig[N].Device_OUT[6].Loudness = 0;
    Nconfig[N].Device_OUT[6].Aigue = 0;
    Nconfig[N].Device_OUT[6].Basse = 0;
    Nconfig[N].Device_OUT[6].Volume = 11.25;
    Nconfig[N].Device_OUT[6].L= 0;
    Nconfig[N].Device_OUT[6].R= 0;
               
    for(i =0; i < 6;i++)
    {
        Somm_VolumeIN = (int)Nconfig[N].Device_IN[i].Volume;

        if(Somm_VolumeIN > 0)
        {
            if(Somm_VolumeIN%2 == 0)//si gain chiffre paire
            {
                Nconfig[N].Device_IN[i].Volume = 0;
                Nconfig[N].Device_IN[i].Gain = Somm_VolumeIN;
            }
            else//si gain chiffre impaire
            {
                Nconfig[N].Device_IN[i].Volume = -1;
                Nconfig[N].Device_IN[i].Gain = Somm_VolumeIN+1;
            }
        }
        else
        {
            Nconfig[N].Device_IN[i].Volume = Somm_VolumeIN;
            Nconfig[N].Device_IN[i].Gain = 0;                   
        }
        if(Nconfig[N].Device_IN[i].Volume < -30)
        {
            Nconfig[N].Device_IN[i].Volume = -56;//corespond a MUTE pour TDA7439
        }            
    }
    
    
    for(i=0;i<7;i++)
    {
        Somm_Volume = Nconfig[N].Device_OUT[i].Volume; 
        
        if((Somm_Volume > 0)&&(Somm_Volume <= 3.75))
        {
            Nconfig[N].Device_OUT[i].Gain = 3.75;            
        }
        else if((Somm_Volume > 3.75)&&(Somm_Volume <= 7.5))
        {
            Nconfig[N].Device_OUT[i].Gain = 7.5;               
        }
        else if((Somm_Volume > 7.5)&&(Somm_Volume <= 11.25))
        {
            Nconfig[N].Device_OUT[i].Gain = 11.25;               
        }
        else if(Somm_Volume <= 0)
        {
            Nconfig[N].Device_OUT[i].Gain = 0;
        }
        else
        {
            return;
        }
        Perte = Nconfig[N].Device_OUT[i].Gain - Somm_Volume;

        Nconfig[N].Device_OUT[i].Volume = -Perte; 
        if(Nconfig[N].Device_OUT[i].Volume < -30)
        {
            Nconfig[N].Device_OUT[i].Volume = -78.75;
        }       
    }
        
    sprintf(Nconfig[N].Name_Config,"Config Usine%d",N);

        
        
        /******Config Usine*******************/
//    int i;
//    char Config_Usine[1024];
//    char CRLF[2];
//    CRLF[0] = 0x0D;
//    CRLF[1] = 0x0A;
//    float Somm_Volume;
//    float Perte;
//
//    sprintf(Config_Usine,"Name:base;;;;;;;%s;;;;;;;%sInput;Line1;Line2;Micro1;Micro2;Micro3;Micro4;%sGain;6.25;0;11.25;11.25;11.25;11.25;%sBass;2;2;10;10;10;10;%sTreble;8;8;14;14;14;14;%sLoudness;0;0;0;0;0;0;%s;;;;;;;%sOutput;Studio;Master;Phone1;Phone2;Phone3;Phone4;PhoneDJ%sMax Gain;-78.75;-7.50;11.25;11.25;11.25;11.25;11.25%sLeft;0;0;0;0;0;0;0%sRight;0;0;0;0;0;0;0%sBass;2;0;4;4;4;4;2%sTreble;14;0;4;4;4;4;8%sLoudness;0;0;0;0;0;0;0%sMaster Gain;;0;;;;;%s;;;;;;;%s/FinCSV;;;;;;;%s",CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF,CRLF );
//
//    Upload_Audio_CSV(Config_Usine);  
//
//    for(i =0; i < 6;i++)
//    {
//        Somm_Volume = Nconfig[N].Device_IN[i].Volume;
//
//        if((Somm_Volume > 0)&&(Somm_Volume <= 3.75))
//        {
//            Nconfig[N].Device_IN[i].Gain = 3.75;            
//        }
//        else if((Somm_Volume > 3.75)&&(Somm_Volume <= 7.5))
//        {
//            Nconfig[N].Device_IN[i].Gain = 7.5;               
//        }
//        else if((Somm_Volume > 7.5)&&(Somm_Volume <= 11.25))
//        {
//            Nconfig[N].Device_IN[i].Gain = 11.25;               
//        }
//        else if(Somm_Volume <= 0)
//        {
//            Nconfig[N].Device_IN[i].Gain = 0;
//        }
//        else
//        {
//            return;
//        }
//        Perte = Nconfig[N].Device_IN[i].Gain - Somm_Volume;
//
//        Nconfig[N].Device_IN[i].Volume = -Perte; 
//        if(Nconfig[N].Device_IN[i].Volume < -30)
//        {
//            Nconfig[N].Device_IN[i].Volume = -78.75;
//        }   
//    }
//    
//    for(i=0;i<7;i++)
//    {
//        Somm_Volume = Nconfig[N].Device_OUT[i].Volume; 
//        
//        if((Somm_Volume > 0)&&(Somm_Volume <= 3.75))
//        {
//            Nconfig[N].Device_OUT[i].Gain = 3.75;            
//        }
//        else if((Somm_Volume > 3.75)&&(Somm_Volume <= 7.5))
//        {
//            Nconfig[N].Device_OUT[i].Gain = 7.5;               
//        }
//        else if((Somm_Volume > 7.5)&&(Somm_Volume <= 11.25))
//        {
//            Nconfig[N].Device_OUT[i].Gain = 11.25;               
//        }
//        else if(Somm_Volume <= 0)
//        {
//            Nconfig[N].Device_OUT[i].Gain = 0;
//        }
//        else
//        {
//            return;
//        }
//        Perte = Nconfig[N].Device_OUT[i].Gain - Somm_Volume;
//
//        Nconfig[N].Device_OUT[i].Volume = -Perte; 
//        if(Nconfig[N].Device_OUT[i].Volume < -30)
//        {
//            Nconfig[N].Device_OUT[i].Volume = -78.75;
//        }       
//    }
//
//    sprintf(Nconfig[N].Name_Config,"Config Defaut%d",N);

}
char ConfigCSV[1000];

void DownloadCSV(int N)
{    
    char TxtTitreAD[15];
    char ChaineADD[100];
       
    ConfigCSV[0] = 0;//Recommence l'ecriture du fichier CSV
//    sprintf(ConfigCSV,"");//Recommence l'ecriture du fichier CSV
    sprintf(ChaineADD,"Name:%s;\r\n\r\n",Nconfig[N].Name_Config);
    strcat(ConfigCSV,ChaineADD);
    sprintf(ChaineADD,"Input;Line1;Line2;Micro1;Micro2;Micro3;Micro4;\r\n");// Ligne 1 Titre Tableau
    strcat(ConfigCSV,ChaineADD); 
    int i;
    for(i = 0; i < 9;i++)
    {
        float Volume;
        int Valeur;
        
        
        switch(i)
        {
            int ii;
            case 0:
            {
                sprintf(TxtTitreAD,"Gain;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 6;ii++)
                {
                    Volume = Nconfig[N].Device_IN[ii].Volume+Nconfig[N].Device_IN[ii].Gain;
                    sprintf(ChaineADD,"%0.2f;",Volume);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }  
            }
            break;

            case 1:
            {
                sprintf(TxtTitreAD,"Bass;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 6;ii++)
                {
                    Valeur = Nconfig[N].Device_IN[ii].Basse;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }  
            }
            break;
            
            case 2:
            {
                sprintf(TxtTitreAD,"Middle;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 6;ii++)
                {
                    Valeur = Nconfig[N].Device_IN[ii].Middle;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }  
            }
            break;

            case 3:
            {
                sprintf(TxtTitreAD,"Treble;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 6;ii++)
                {
                    Valeur = Nconfig[N].Device_IN[ii].Aigue;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }  
            }
            break;

            case 4:
            {
                sprintf(TxtTitreAD,"Loudness;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 6;ii++)
                {
                    Valeur = Nconfig[N].Device_IN[ii].Loudness;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }                  
            }
            break;
            
            case 5:
            {
                sprintf(TxtTitreAD,"ReductionMax;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 2;ii++)
                {
                    Volume = Nconfig[N].Device_IN[ii].ReductionMax;
                    sprintf(ChaineADD,"%2.2f;",Volume);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }                  
            }
            break;
            
            case 6:
            {
                sprintf(TxtTitreAD,"Niveau Overload;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 2;ii++)
                {
                    Valeur = Nconfig[N].Device_IN[ii].Niveau_Overload;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }                  
            }
            break;
            
            case 7:
            {
                sprintf(TxtTitreAD,"Detection Mute;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 2;ii++)
                {
                    Valeur = Nconfig[N].Device_IN[ii].Niveau_Stop_Overload;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }                  
            }
            break;
            
            case 8:
            {
                sprintf(TxtTitreAD,"Time Muting;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 2;ii++)
                {
                    Valeur = Nconfig[N].Device_IN[ii].Time_Mute;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }                  
            }
            break;
        }  
        strcat(ConfigCSV,"\r\n");
    }
    sprintf(TxtTitreAD,"\r\n");
    strcat(ConfigCSV,TxtTitreAD);
    sprintf(ChaineADD,"Output;Studio;Master;Phone1;Phone2;Phone3;Phone4;PhoneDJ;\r\n");// Ligne 1 Titre Tableau
    strcat(ConfigCSV,ChaineADD); 
    
    for(i = 0; i < 7;i++)
    {
        float Volume;
        int Valeur;
        int ii;
        
        switch(i)
        {
            case 0:
            {
                sprintf(TxtTitreAD,"Max Gain;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 7;ii++)
                {
                    Volume = Nconfig[N].Device_OUT[ii].Volume+Nconfig[N].Device_OUT[ii].Gain;
                    sprintf(ChaineADD,"%0.2f;",Volume);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }  

            }
            break;

            case 1:
            {
                sprintf(TxtTitreAD,"Left;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 7;ii++)
                {
                    Volume = Nconfig[N].Device_OUT[ii].L;
                    sprintf(ChaineADD,"%0.2f;",Volume);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }                  
            }
            break;

            case 2:
            {
                sprintf(TxtTitreAD,"Right;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 7;ii++)
                {
                    Volume = Nconfig[N].Device_OUT[ii].R;
                    sprintf(ChaineADD,"%0.2f;",Volume);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }  
            }
            break;

            case 3:
            {
                sprintf(TxtTitreAD,"Bass;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 7;ii++)
                {
                    Valeur = Nconfig[N].Device_OUT[ii].Basse;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }  
            }
            break;

            case 4:
            {
                sprintf(TxtTitreAD,"Treble;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 7;ii++)
                {
                    Valeur = Nconfig[N].Device_OUT[ii].Aigue;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }  
            }
            break;

            case 5:
            {
                sprintf(TxtTitreAD,"Loudness;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 7;ii++)
                {
                    Valeur = Nconfig[N].Device_OUT[ii].Loudness;
                    sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    strcat(ConfigCSV,ChaineADD);
                }  
            }
            break;
            case 6:
            {
                sprintf(TxtTitreAD,"Master Gain;");
                strcat(ConfigCSV,TxtTitreAD);
                for(ii = 0; ii < 7;ii++)
                {
                    Valeur = Nconfig[N].Master_Gain;
                    if(ii == 1)
                    {
                        sprintf(ChaineADD,"%d;",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    }
                    else
                    {
                        sprintf(ChaineADD,";",Valeur);// Gain Line1 Line2 Micro1.... etc 
                    }
                    strcat(ConfigCSV,ChaineADD);
                }
            }
            break;            
        }
        strcat(ConfigCSV,"\r\n");        
    }  
    sprintf(TxtTitreAD,"\r\n/FinCSV");
    strcat(ConfigCSV,TxtTitreAD);
    static int Cpt_csv = 0;
    extern char FichierCSV[20];
    extern char DossierCSV[30];
    
    Cpt_csv++;
    if(Cpt_csv > 10)
    {
        Cpt_csv = 0;
    }  
    sprintf(FichierCSV,"Config%d.csv",Cpt_csv);
//    TCPIP_HTTP_Print_ConfigCSV(1);
//    char httpDataBuff[20];
//    strcpy(httpDataBuff, "/Save_Config.htm");
//    TCPIP_HTTP_CurrentConnectionStatusSet((HTTP_CONN_HANDLE)0xA0017F30, HTTP_REDIRECT);
    
}

char *InputTxt (int N)
{ 
//    char Txt[30];
    switch(N)
    {
        case 0:
        {
            return "Line1:";
        }
        break;
        
//        case 1:
//        {
//            sprintf(Txt,"Line2:");
//        }
//        break;
//        
//        case 2:
//        {
//            sprintf(Txt,"Micro1:");
//        }
//        break;
//        
//        case 3:
//        {
//            sprintf(Txt,"Micro2:");
//        }
//        break;
//        
//        case 4:
//        {
//            sprintf(Txt,"Micro3:");
//        }
//        break;
//        
//        case 5:
//        {
//            sprintf(Txt,"Micro4:");
//        }
//        break;        
    }
//    return Txt;
    
    
}

/* *****************************************************************************
 End of File
 */

void Upload_Audio_CSV(char* csv)
{

    char debugInfo[1024];

    int i;
    char TxtCompare[10];
    memcpy(debugInfo, csv, 1024);
    char c;
    int Cpt_Match = 0;
    int Param = 0;
    
    
    char* TableParamtre[] = {"Name:","Gain;","Bass;","Middle;","Treble;","Loudness;","ReductionMax;","Niveau Overload;","Detection Mute;","Time Muting;",
                             "Max Gain;","Left;","Right;","Bass;","Treble;","Loudness;","Master Gain;"};
    
    int pp;

    for(i=0;i < sizeof debugInfo;i++)        
    {       
//        sprintf(TxtCompare,"%s",TableParamtre[Param]);
        if(Param <= 16)
        {
            strcpy(TxtCompare,TableParamtre[Param]);
            if(debugInfo[i] == TxtCompare[0])//si premier caracter correspond
            {
                int ii;
                for(ii=0; ii < strlen(TxtCompare);ii++)
                {
                    if(debugInfo[i+ii] == TxtCompare[ii])
                    {
                        Cpt_Match++;//icremente pour chaque caractere consecutif coresspondant a TxtCompare
                    }
                }
                if(Cpt_Match == strlen(TxtCompare))//si autant de caractere correspondant que longueur TxtCompare.
                {
                    Nop();
                    int j = 0;
                    static int jj = 0;  
                    char str[25];
                    jj = 0;
                    pp = 0;
                    do
                    {
                        memset (str, 0, sizeof (str));
                        int p = 0;
                        do
                        {
                            str[p] = debugInfo[i+ Cpt_Match +j+pp];
                            j++;
                            p++;
                        }
                        while(debugInfo[i+ Cpt_Match +j] != 0x3B);
                            switch(Param)
                            {
                                case 0:
                                {
                                    strcpy(Nconfig[Config_Used].Name_Config,str);
                                }
                                break;

                                case 1:
                                {
                                    Nconfig[Config_Used].Device_IN[jj].Volume = atoi(str);
                                    
                                    int Somm_Volume = Nconfig[Config_Used].Device_IN[jj].Volume;
                                    
                                    if(Somm_Volume > 0)
                                    {
                                        if(Somm_Volume%2 == 0)//si gain chiffre paire
                                        {
                                            Nconfig[Config_Used].Device_IN[jj].Volume = 0;
                                            Nconfig[Config_Used].Device_IN[jj].Gain = Somm_Volume;
                                        }
                                        else//si gain chiffre impaire
                                        {
                                            Nconfig[Config_Used].Device_IN[jj].Volume = -1;
                                            Nconfig[Config_Used].Device_IN[jj].Gain = Somm_Volume+1;
                                        }
                                    }
                                    else
                                    {
                                        Nconfig[Config_Used].Device_IN[jj].Volume = Somm_Volume;
                                        Nconfig[Config_Used].Device_IN[jj].Gain = 0;                   
                                    }
                                    if(Nconfig[Config_Used].Device_IN[jj].Volume < -30)
                                    {
                                        Nconfig[Config_Used].Device_IN[jj].Volume = -56;//corespond a MUTE pour TDA7439
                                    }            
                                    pp = 1;
                                }
                                break;

                                case 2:
                                {
                                    Nconfig[Config_Used].Device_IN[jj].Basse = atoi(str);
                                    pp = 1;
                                }
                                break;
                                
                                case 3:
                                {
                                    Nconfig[Config_Used].Device_IN[jj].Middle = atoi(str);
                                    pp = 1;
                                }
                                break;

                                case 4://Treble Input
                                {
                                    Nconfig[Config_Used].Device_IN[jj].Aigue = atoi(str);
                                    pp = 1;
                                }
                                break;

                                case 5://Loudness input
                                {
                                    Nconfig[Config_Used].Device_IN[jj].Loudness = atoi(str);
                                    pp = 1;
                                }
                                break;  
                                
                                case 6://ReductionMaxinput
                                {
                                    Nconfig[Config_Used].Device_IN[jj].ReductionMax = atof(str);
                                    pp = 1;
                                }
                                break; 
                                
                                case 7://Niveau Overload
                                {
                                    Nconfig[Config_Used].Device_IN[jj].Niveau_Overload = atof(str);
                                    pp = 1;
                                }
                                break;    
                                
                                case 8://Detection_Mute
                                {
                                    Nconfig[Config_Used].Device_IN[jj].Niveau_Stop_Overload = atof(str);
                                    pp = 1;
                                }
                                break; 
                                
                                case 9://ReductionMaxinput
                                {
                                    Nconfig[Config_Used].Device_IN[jj].Time_Mute = atof(str);
                                    pp = 1;
                                }
                                break;     
                                
                                case 10://Gain Max
                                {
                                    Nconfig[Config_Used].Device_OUT[jj].Volume = atof(str);
                                    
                                    float Perte;
                                    float Somm_Volume = Nconfig[Config_Used].Device_OUT[jj].Volume; 

                                    if((Somm_Volume > 0)&&(Somm_Volume <= 3.75))
                                    {
                                        Nconfig[Config_Used].Device_OUT[jj].Gain = 3.75;            
                                    }
                                    else if((Somm_Volume > 3.75)&&(Somm_Volume <= 7.5))
                                    {
                                        Nconfig[Config_Used].Device_OUT[jj].Gain = 7.5;               
                                    }
                                    else if((Somm_Volume > 7.5)&&(Somm_Volume <= 11.25))
                                    {
                                        Nconfig[Config_Used].Device_OUT[jj].Gain = 11.25;               
                                    }
                                    else if(Somm_Volume <= 0)
                                    {
                                        Nconfig[Config_Used].Device_OUT[jj].Gain = 0;
                                    }
                                    else
                                    {
                                        return;
                                    }
                                    Perte = Nconfig[Config_Used].Device_OUT[jj].Gain - Somm_Volume;

                                    Nconfig[Config_Used].Device_OUT[jj].Volume = -Perte; 
                                    if(Nconfig[Config_Used].Device_OUT[jj].Volume < -30)
                                    {
                                        Nconfig[Config_Used].Device_OUT[jj].Volume = -78.75;
                                    }                                           
                                    pp = 1;
                                }
                                break;

                                case 11://Left
                                {
                                    Nconfig[Config_Used].Device_OUT[jj].L = atof(str);
                                    pp = 1;
                                }
                                break;

                                case 12://Right
                                {
                                    Nconfig[Config_Used].Device_OUT[jj].R = atof(str);
                                    pp = 1;
                                }
                                break;

                                case 13://Basse
                                {
                                    Nconfig[Config_Used].Device_OUT[jj].Basse = atoi(str);
                                    pp = 1;
                                }
                                break;   
                                
                                case 14://aigue
                                {
                                    Nconfig[Config_Used].Device_OUT[jj].Aigue = atoi(str);
                                    pp = 1;
                                }
                                break;

                                case 15:
                                {
                                    Nconfig[Config_Used].Device_OUT[jj].Loudness = atoi(str);
                                    pp = 1;
                                }
                                break;  

                                case 16:
                                {
                                    Nconfig[Config_Used].Master_Gain = atoi(str);
                                    pp = 1;
                                }
                                break;           
                                
                                default:
                                    
                                break; 
                            }

                            jj++;
                        }
                        while(debugInfo[i+ Cpt_Match +j +1] != 0x0d);
                        j = 0;



    //                while(debugInfo[i+ Cpt_Match +j] != 0x0d);
    //                Nconfig[Config_Used].Name_Config[j] = 0x00;
                    Param++;

                }
                Cpt_Match = 0;
            }
        }
    }
    


}