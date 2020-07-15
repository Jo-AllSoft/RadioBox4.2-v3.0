/*******************************************************************************
  Application to Demo HTTP Server

  Summary:
    Support for HTTP module in Microchip TCP/IP Stack

  Description:
    -Implements the application
    -Reference: RFC 1002ersionPIC
*******************************************************************************/

/***********************************poste********************************************
File Name: custom_http_app.c
Copyright (C) 2012 released Microchip Technology Inc.  All rights
reserved.

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

#define __CUSTOMHTTPAPP_C

#include "system_config.h"

#if defined(TCPIP_STACK_USE_HTTP_SERVER)

#include "tcpip/tcpip.h"
#include "system/tmr/sys_tmr.h"
#include "system/random/sys_random.h"
#include "crypto/crypto.h"
#include "tcpip/src/common/helpers.h"
#include "app.h"
//#include "tcpip.h"
#include "EEPROM_24LC256.h"
#include "time.h"

//#include "Mc32NVMUtil.h"
#include "Mc32SpiUtil.h"
#include"Mc32Delays.h"
#include "custom_snmp_app.h"
#include "EEPROM_Driver.h"
//#include "system_interrupt.c"

int Num_Mot_Pass;


/****************************************************************************
  Section:
    Definitions
  ***************************************************************************/

// Use the web page in the Demo App (~2.5kb ROM, ~0b RAM)
#define HTTP_APP_USE_RECONFIG

// Use the MD5 Demo web page (~5kb ROM, ~160b RAM)
#define HTTP_APP_USE_MD5

/****************************************************************************
  Section:
    Function Prototypes and Memory Globalizers
  ***************************************************************************/
#if defined(TCPIP_HTTP_USE_POST)
    static HTTP_IO_RESULT HTTPPostSNMP(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostMAIL(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostAlarms(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostSaveAudioConfig(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostUploadAudio(HTTP_CONN_HANDLE connHandle, int SelectPost);

    #if defined(PIC_RF) || defined(PIC_COMB) || defined(PIC_AMPLI)
    static HTTP_IO_RESULT HTTPPostBackup(HTTP_CONN_HANDLE connHandle);
    #endif
    static HTTP_IO_RESULT HTTPPostConfig(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostRouteConfig(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostNMS(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostChannel(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostAttenuation(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostPassword(HTTP_CONN_HANDLE connHandle);
    static HTTP_IO_RESULT HTTPPostDisplay(HTTP_CONN_HANDLE connHandle);
#endif


// RAM allocated for DDNS parameters
#if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    static uint8_t DDNSData[100];
#endif

// Sticky status message variable.
// This is used to indicated whether or not the previous POST operation was
// successful.  The application uses these to store status messages when a
// POST operation redirects.  This lets the application provide status messages
// after a redirect, when connection instance data has already been lost.
static bool lastSuccess = false;

// Stick status message variable.  See lastSuccess for details.
static bool lastFailure = false;

/****************************************************************************
  Section:
    Authorization Handlers
  ***************************************************************************/

/*****************************************************************************
  Function:
    uint8_t TCPIP_HTTP_FileAuthenticate(HTTP_CONN_HANDLE connHandle, uint8_t* cFile)

  Internal:
    See documentation in the TCP/IP Stack API or HTTP.h for details.
  ***************************************************************************/
#if defined(TCPIP_HTTP_USE_AUTHENTICATION)
uint8_t TCPIP_HTTP_FileAuthenticate(HTTP_CONN_HANDLE connHandle, uint8_t* cFile)
{
    if(memcmp(cFile, (const void*)"maintenance/boot.htm", 20) == 0) // Dossier maintenance
    {   // !!!!! ajouter backup avec mot de passe spécial
        Num_Mot_Pass = 3;
        return 0x00;        // Authentication will be needed later
    }
    if(memcmp(cFile, (const void*)"maintenance/Calibration.htm", 28) == 0) // Dossier maintenance
    {   // !!!!! ajouter backup avec mot de passe spécial
        Num_Mot_Pass = 3;
        return 0x00;        // Authentication will be needed later
    }

    // You can match additional strings here to password protect other files.
    // You could switch this and exclude files from authentication.
    // You could also always return 0x00 to require auth for all files.
    // You can return different values (0x00 to 0x79) to track "realms" for below.

    return 0x80; // No authentication required
}
#endif

/*****************************************************************************
  Function:
    uint8_t TCPIP_HTTP_UserAuthenticate(uint8_t* cUser, uint8_t* cPass)

  Internal:
    See documentation in the TCP/IP Stack API or HTTP.h for details.
  ***************************************************************************/
#if defined(TCPIP_HTTP_USE_AUTHENTICATION)
uint8_t TCPIP_HTTP_UserAuthenticate(HTTP_CONN_HANDLE connHandle, uint8_t* cUser, uint8_t* cPass)
{
    extern char User_x[40];
    extern char Pass_x[40];
    
    if(Num_Mot_Pass == 2)
    {
        if(strcmp((char *)cUser,(const char *)"admin") == 0 && strcmp((char *)cPass, (const char *)"aumix22") == 0)
            return 0x80;        // We accept this combination
    }
    else
    {
        if(Num_Mot_Pass == 3)
        {
            if(strcmp((char *)cUser,(const char *)"admin") == 0 && strcmp((char *)cPass, (const char *)"boot") == 0)
                return 0x80;        // We accept this combination
            if(strcmp((char *)cUser,(const char *)"admin") == 0 && strcmp((char *)cPass, (const char *)"aumix22") == 0)
                return 0x80;        // We accept this combination
        }
        else
        {
            if(strcmp((char *)cUser,(const char *)"admin") == 0 && strcmp((char *)cPass, (const char *)"aumix22") == 0)
                return 0x80;        // We accept this combination
            if(strcmp((char *)cUser,(const char *)User_x) == 0 && strcmp((char *)cPass, (const char *)Pass_x) == 0)
                return 0x80;        // We accept this combination
        }
    }



    // You can add additional user/pass combos here.
    // If you return specific "realm" values above, you can base this
    //   decision on what specific file or folder is being accessed.
    // You could return different values (0x80 to 0xff) to indicate
    //   various users or groups, and base future processing decisions
    //   in TCPIP_HTTP_GetExecute/Post or HTTPPrint callbacks on this value.

    return 0x00;            // Provided user/pass is invalid
}
#endif

/****************************************************************************
  Section:
    GET Form Handlers
  ***************************************************************************/
//float Valeur_Volume = 0;
//float Valeur_R = 0;
//float Valeur_L = 0;
//int Valeur_Basse = 0;
//int Valeur_Aigue = 0;

int In_Audio = 0;
int Out_Audio = 0;
int Option_Loudness;
extern int Config_Used;
//int Gain_Master = 0;


int Max_Fader = 2900;
int Min_Fader = 4400;
int Fader_OFF = 4095;//4095 == 5V
int Aff_Fader_OFF = 5000;
int Statut_Mode = 0;
char Txt_MIDI_ON[20];
char Txt_MIDI_OFF[20];
char FichierCSV[20] = "Config0.csv";
char DossierCSV[30] = "CSV_Config/Config0.csv";

char Midi1 = 144;
char Midi2 = 57;
char Midi3 = 63;

char MidiOFF1 = 128;
char MidiOFF2 = 57;
char MidiOFF3 = 0;

int SelectPost = 0;

float Niveau_Overload = 200;
float Niveau_Stop_Overload = 20;
int Ndet = 500;

/*****************************************************************************
  Function:
    HTTP_IO_RESULT TCPIP_HTTP_GetExecute(HTTP_CONN_HANDLE connHandle)

  Internal:
    See documentation in the TCP/IP Stack API or HTTP.h for details.
  ***************************************************************************/
HTTP_IO_RESULT TCPIP_HTTP_GetExecute(HTTP_CONN_HANDLE connHandle)
{
    const uint8_t *ptr;
    uint8_t filename[30];
    uint8_t* httpDataBuff;


    // Load the file name
    // Make sure uint8_t filename[] above is large enough for your longest name
    SYS_FS_FileNameGet(TCPIP_HTTP_CurrentConnectionFileGet(connHandle), filename, sizeof(filename));

    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);

    if(!memcmp(filename, "Input_Audio.htm", 15))
    {
        if(Config_Used != 0)
        {
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Redu") != 0)
            {
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Redu");
                Nconfig[Config_Used].Device_IN[In_Audio].ReductionMax = atof(ptr);
            }
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"RefV") != 0)
            {
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"ValV");

                int Somm_Volume;
                Somm_Volume = atoi(ptr);
                calculGainTDA(Somm_Volume, In_Audio); 
                
                I2C_PT_AudioSwitch(Select_Input(In_Audio), Nconfig[Config_Used].Device_IN[In_Audio].Gain,0,Stereo1);
                I2C_PT_Volume(Select_Input(In_Audio), Nconfig[Config_Used].Device_IN[In_Audio].Volume);
            }

            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"RefB") != 0)
            {
                static char tmp[20];
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"ValB");
                memcpy(tmp, ptr, 20);
                Nconfig[Config_Used].Device_IN[In_Audio].Basse = atoi(ptr);
                I2C_PT_BASS_TREBLE(Select_Input(In_Audio), Nconfig[Config_Used].Device_IN[In_Audio].Basse,PT_BASS);
            }
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"RefA") != 0)
            {
                static char tmp[20];
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"ValA");
                memcpy(tmp, ptr, 20);
                Nconfig[Config_Used].Device_IN[In_Audio].Aigue = atoi(ptr);
                I2C_PT_BASS_TREBLE(Select_Input(In_Audio), Nconfig[Config_Used].Device_IN[In_Audio].Aigue,PT_TREBLE);
            }
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"RefC") != 0)
            {
                static char tmp[20];
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"ValC");
                memcpy(tmp, ptr, 20);
                Nconfig[Config_Used].Device_IN[In_Audio].Middle = atoi(ptr);
                I2C_PT_BASS_TREBLE(Select_Input(In_Audio), Nconfig[Config_Used].Device_IN[In_Audio].Middle,TDA_MIDDLE);
            }
        }

        if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"OKIN") != 0)            
        {
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"InA") != 0)
            {
                static char tmp[20];
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"InA");
                memcpy(tmp, ptr, 20);
                In_Audio = atoi(ptr);
            }            
        } 
        
    }
    
    if(!memcmp(filename, "Output_Audio.htm", 16))
    {
        if(Config_Used != 0)
        {
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"outl") != 0)
            {
    //            Gain_Master = !Gain_Master;
                Nconfig[Config_Used].Master_Gain = !Nconfig[Config_Used].Master_Gain;
            }

            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"RefV") != 0)
            {
                static char tmp[20];
                float Somm_Volume_Out;
                float Perte;
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"ValV");
                memcpy(tmp, ptr, 20);
                Somm_Volume_Out = atof(ptr);

                // <editor-fold defaultstate="collapsed" desc="Gestion Volume et Gain">            
                if((Somm_Volume_Out > 0)&&(Somm_Volume_Out <= 3.75))
                {
                    Nconfig[Config_Used].Device_OUT[Out_Audio].Gain = 3.75;            
                }
                else if((Somm_Volume_Out > 3.75)&&(Somm_Volume_Out <= 7.5))
                {
                    Nconfig[Config_Used].Device_OUT[Out_Audio].Gain = 7.5;               
                }
                else if((Somm_Volume_Out > 7.5)&&(Somm_Volume_Out <= 11.25))
                {
                    Nconfig[Config_Used].Device_OUT[Out_Audio].Gain = 11.25;               
                }
                else if(Somm_Volume_Out <= 0)
                {
                    Nconfig[Config_Used].Device_OUT[Out_Audio].Gain = 0;
                }
                else
                {
                    return;
                }
                Perte = Nconfig[Config_Used].Device_OUT[Out_Audio].Gain - Somm_Volume_Out;

                Nconfig[Config_Used].Device_OUT[Out_Audio].Volume = -Perte; 
                if(Nconfig[Config_Used].Device_OUT[Out_Audio].Volume < -30)
                {
                    Nconfig[Config_Used].Device_OUT[Out_Audio].Volume = -78.75;
                }       
                // </editor-fold>

                if((Statut_Mode == MODE_ON_AIR)&&(Out_Audio == 0))
                {
                    I2C_PT_AudioSwitch(Select_Output(Out_Audio), Nconfig[Config_Used].Device_OUT[Out_Audio].Gain,0,Stereo1);
                    I2C_PT_Volume(Select_Output(Out_Audio), Nconfig[Config_Used].Device_OUT[Out_Audio].Volume);
                }

    //            if((Nconfig[Config_Used].Master_Gain == GAIN_WEB_ACTIF)&&(Out_Audio == 1))
    //            {
    //                I2C_PT_AudioSwitch(Select_Output(Out_Audio), Nconfig[Config_Used].Device_OUT[Out_Audio].Gain,Nconfig[Config_Used].Device_OUT[Out_Audio].Loudness,Stereo1);
    //                I2C_PT_Volume(Select_Output(Out_Audio), Nconfig[Config_Used].Device_OUT[Out_Audio].Volume);
    //            }




            }
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"BaRL") != 0)
            {
                static char tmp[20];
                static float VBalance;

                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Bal");
                memcpy(tmp, ptr, 20);
                VBalance = atof(ptr);
                if(VBalance ==  0)
                {
                    Nconfig[Config_Used].Device_OUT[Out_Audio].L = 0;
                    Nconfig[Config_Used].Device_OUT[Out_Audio].R = 0;                
                }
                else if(VBalance > 0)
                {
                    Nconfig[Config_Used].Device_OUT[Out_Audio].L = 0;
                    Nconfig[Config_Used].Device_OUT[Out_Audio].R = VBalance*(-1);
                }
                else if(VBalance < 0)
                {
                    Nconfig[Config_Used].Device_OUT[Out_Audio].L = VBalance;
                    Nconfig[Config_Used].Device_OUT[Out_Audio].R = 0;               
                }
                I2C_PT_Speak_Att(Select_Output(Out_Audio), Nconfig[Config_Used].Device_OUT[Out_Audio].L,LEFT);
                I2C_PT_Speak_Att(Select_Output(Out_Audio), Nconfig[Config_Used].Device_OUT[Out_Audio].R,RIGHT);           
            }
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"RefB") != 0)
            {
                static char tmp[20];
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"ValB");
                memcpy(tmp, ptr, 20);
                Nconfig[Config_Used].Device_OUT[Out_Audio].Basse = atof(ptr);
                I2C_PT_BASS_TREBLE(Select_Output(Out_Audio), Nconfig[Config_Used].Device_OUT[Out_Audio].Basse,PT_BASS);

            }
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"RefA") != 0)
            {
                static char tmp[20];
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"ValA");
                memcpy(tmp, ptr, 20);
                Nconfig[Config_Used].Device_OUT[Out_Audio].Aigue = atof(ptr);
                I2C_PT_BASS_TREBLE(Select_Output(Out_Audio), Nconfig[Config_Used].Device_OUT[Out_Audio].Aigue,PT_TREBLE);

            }
        }

        if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"OK") != 0)            
        {
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Outs") != 0)
            {
                static char tmp[20];
                ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Outs");
                memcpy(tmp, ptr, 20);
                Out_Audio = atoi(ptr);
            }            
        } 
        
    }
    
    if(!memcmp(filename, "maintenance/Calibration.htm", 27))
    {
        if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"ok") != 0)            
        {
            extern int Mode_Calibration;
            Mode_Calibration = 1;
        }

    }
    
    if(!memcmp(filename, "Options.htm", 12))
    {

        if(Config_Used != 0)
        {
            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"OK1") != 0)            
            {
                if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"OV1") != 0)            
                {
                    static char tmp[20];
                    ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"OV1");
                    memcpy(tmp, ptr, 20); 
                    Nconfig[Config_Used].Device_IN[0].Niveau_Overload = atof(ptr);

                }

                if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"STO1") != 0)            
                {
                    static char tmp[20];
                    ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"STO1");
                    memcpy(tmp, ptr, 20); 
                     Nconfig[Config_Used].Device_IN[0].Niveau_Stop_Overload = atof(ptr);

                }
                if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Nde1") != 0)            
                {
                    ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Nde1");
                    Nconfig[Config_Used].Device_IN[0].Time_Mute = atoi(ptr);

                }   
            }

            if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"OK2") != 0)            
            {
                if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"OV2") != 0)            
                {
                    static char tmp[20];
                    ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"OV2");
                    memcpy(tmp, ptr, 20); 

                    Nconfig[Config_Used].Device_IN[1].Niveau_Overload = atof(ptr);
                }

                if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"STO2") != 0)            
                {
                    static char tmp[20];
                    ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"STO2");
                    memcpy(tmp, ptr, 20); 

                     Nconfig[Config_Used].Device_IN[1].Niveau_Stop_Overload = atof(ptr);
                }
                if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Nde2") != 0)            
                {
                    ptr = TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Nde2");

                    Nconfig[Config_Used].Device_IN[1].Time_Mute = atoi(ptr);
                }   
            }
        }
    }
    
    if(!memcmp(filename, "Test_Upload.htm", 15))
    {
        if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Sel") != 0)            
        {
            SelectPost = 1;
        }
    }
            
    


    if(!memcmp(filename, "maintenance/boot.htm", 20))//14.08.2017
    {
        if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"Start_Boot") !=0)
        {
            extern int Stop_Boot;
            Stop_Boot = 22;
            EEPROM_SaveData(&Stop_Boot); 
            PIC_reset();
        }
        if(TCPIP_HTTP_ArgGet(httpDataBuff,(uint8_t*)"erase") !=0)
        {
            EEPROM_EraseAll();  
        }
    }
    else if(!memcmp(filename, "maintenance/monitoring.htm", 26))
    {
        EEPROM_Maintenance_csv_Reset();
    }
    return HTTP_IO_DONE;
}

/****************************************************************************
  Section:
    POST Form Handlers
  ***************************************************************************/
#if defined(TCPIP_HTTP_USE_POST)

#define Nb_Route 4
typedef struct tROUTE_CONFIG
{
    IPV4_ADDR IP_Route;    
    IPV4_ADDR IP_Mask;
    IPV4_ADDR IP_Net;

} ROUTE_CONFIG;

extern ROUTE_CONFIG routeconfig[Nb_Route];

/*****************************************************************************
  Function:
    HTTP_IO_RESULT TCPIP_HTTP_PostExecute(HTTP_CONN_HANDLE connHandle)

  Internal:
    See documentation in the TCP/IP Stack API or HTTP.h for details.
  ***************************************************************************/
HTTP_IO_RESULT TCPIP_HTTP_PostExecute(HTTP_CONN_HANDLE connHandle)
{
    // Resolve which function to use and pass along
    uint8_t filename[30];
    
    // Load the file name
    // Make sure uint8_t filename[] above is large enough for your longest name
    SYS_FS_FileNameGet(TCPIP_HTTP_CurrentConnectionFileGet(connHandle), filename, sizeof(filename));
    
    if(!memcmp(filename, "maintenance/network.htm", 23))
        return HTTPPostConfig(connHandle);
    else if(!memcmp(filename, "maintenance/routes.htm", 22))
        return HTTPPostRouteConfig(connHandle);
    else if(!memcmp(filename, "display.htm", 11))
        return HTTPPostDisplay(connHandle);
    else if(!memcmp(filename, "Save_Config.htm", 15))
        return HTTPPostSaveAudioConfig(connHandle);
    else if(!memcmp(filename, "Test_Upload1.htm", 16))
        return HTTPPostUploadAudio(connHandle, 1);
    else if(!memcmp(filename, "Test_Upload.htm", 15))
        return HTTPPostUploadAudio(connHandle, 0);
    

    #if defined(PIC_RF) || defined(PIC_COMB) || defined(PIC_AMPLI)
    else if(!memcmp(filename, "device/backup.htm", 17))
        return HTTPPostBackup(connHandle);
    #endif  
    return HTTP_IO_DONE;
}

static HTTP_IO_RESULT HTTPPostDisplay(HTTP_CONN_HANDLE connHandle)
{

    uint8_t i;
    IPV4_ADDR newIPAddress, newMask;
    TCPIP_MAC_ADDR    newMACAddr;
    uint32_t byteCount;
    TCP_SOCKET sktHTTP;
    uint8_t* httpDataBuff = 0;
    bool bConfigFailure = false;

    // Check to see if the browser is attempting to submit more data than we
    // can parse at once.  This function needs to receive all updated
    // parameters and validate them all before committing them to memory so that
    // orphaned configuration parameters do not get written (for example, if a
    // static IP address is given, but the subnet mask fails parsing, we
    // should not use the static IP address).  Everything needs to be processed
    // in a single transaction.  If this is impossible, fail and notify the user.
    // As a web devloper, if you add parameters to the network info and run into this
    // problem, you could fix this by to splitting your update web page into two
    // seperate web pages (causing two transactional writes).  Alternatively,
    // you could fix it by storing a static shadow copy of network info someplace
    // in memory and using it when info is complete.
    // Lastly, you could increase the TCP RX FIFO size for the HTTP server.
    // This will allow more data to be POSTed by the web browser before hitting this limit.
    byteCount = TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle);
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(byteCount > TCPIP_TCP_GetIsReady(sktHTTP) + TCPIP_TCP_FifoRxFreeGet(sktHTTP))
    {   // Configuration Failure
        lastFailure = true;
        TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
        return HTTP_IO_DONE;
    }

    // Ensure that all data is waiting to be parsed.  If not, keep waiting for
    // all of it to arrive.
    if(TCPIP_TCP_GetIsReady(sktHTTP) < byteCount)
        return HTTP_IO_NEED_DATA;

    // Use current config in non-volatile memory as defaults
    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);

    // Read all browser POST data
    while(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle))
    {
        // Read a form field name
        if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, 6) != HTTP_READ_OK)
        {
            bConfigFailure = true;
            break;
        }

        // Read a form field value
        if(TCPIP_HTTP_PostValueRead(connHandle, httpDataBuff + 6, TCPIP_HTTP_MAX_DATA_LEN-6-2) != HTTP_READ_OK)
        {
            bConfigFailure = true;
            break;
        }
        

    }
    return HTTP_IO_DONE;
}

static HTTP_IO_RESULT HTTPPostSaveAudioConfig(HTTP_CONN_HANDLE connHandle)
{
//    static int TestForceUpload = 0;
//    
//    if(TestForceUpload == 0)
//    {
//            
//        uint8_t i;
//        uint32_t byteCount;
//        TCP_SOCKET sktHTTP;
//        uint8_t* httpDataBuff = 0;
//        bool bConfigFailure = false;
//    
//        byteCount = TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle);
//        sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
//        if(byteCount > TCPIP_TCP_GetIsReady(sktHTTP) + TCPIP_TCP_FifoRxFreeGet(sktHTTP))
//        {   // Configuration Failure
//            lastFailure = true;
//            TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
//            return HTTP_IO_DONE;
//        }
//
//        // Ensure that all data is waiting to be parsed.  If not, keep waiting for
//        // all of it to arrive.
//        if(TCPIP_TCP_GetIsReady(sktHTTP) < byteCount)
//            return HTTP_IO_NEED_DATA;
//
//        // Use current config in non-volatile memory as defaults
//        httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);
//
//        // Read all browser POST data
//
//        while(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle))
//        {
//            // Read a form field name
//            if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, 6) != HTTP_READ_OK)
//            {
//                bConfigFailure = true;
//                break;
//            }
//
//            // Read a form field value
//            if(TCPIP_HTTP_PostValueRead(connHandle, httpDataBuff + 6, TCPIP_HTTP_MAX_DATA_LEN-6-2) != HTTP_READ_OK)
//            {
//                bConfigFailure = true;
//                break;
//            }
//
//
//
//
//                if(!strcmp((char*)httpDataBuff, (const char*)"ch"))
//                {
//                    char Test_Txt[2];
//                    memcpy(Test_Txt, (char*)(httpDataBuff + 6),sizeof Test_Txt);
//                    Config_Used = atoi(Test_Txt);
//
//                    EEPROM_SaveData(&Config_Used);
//
//                    for(i=0; i < 6;i++)
//                    {
//                        I2C_PT_Volume(Select_Input(i),  Nconfig[Config_Used].Device_IN[i].Volume);
//                        I2C_PT_Speak_Att(Select_Input(i),Nconfig[Config_Used].Device_IN[i].L,LEFT );
//                        I2C_PT_Speak_Att(Select_Input(i), Nconfig[Config_Used].Device_IN[i].R,RIGHT);
//                        I2C_PT_AudioSwitch(Select_Input(i), 0,Nconfig[Config_Used].Device_IN[i].Loudness,Stereo1);
//                        I2C_PT_BASS_TREBLE(Select_Input(i), Nconfig[Config_Used].Device_IN[i].Basse,PT_BASS);
//                        I2C_PT_BASS_TREBLE(Select_Input(i), Nconfig[Config_Used].Device_IN[i].Aigue,PT_TREBLE);
//                    }
//
//                    for(i=0; i < 7;i++)
//                    {
//                        I2C_PT_Volume(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Volume);
//                        I2C_PT_Speak_Att(Select_Output(i),Nconfig[Config_Used].Device_OUT[i].L,LEFT );
//                        I2C_PT_Speak_Att(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].R,RIGHT);
//                        I2C_PT_AudioSwitch(Select_Output(i), 0,Nconfig[Config_Used].Device_OUT[i].Loudness,Stereo1);
//                        I2C_PT_BASS_TREBLE(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Basse,PT_BASS);
//                        I2C_PT_BASS_TREBLE(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Aigue,PT_TREBLE);
//                    }
//                    Nop();
//                }
//
//                else if(!strcmp((char*)httpDataBuff, (const char*)"txt1"))
//                {           
//                    strcpy(Nconfig[Config_Used].Name_Config, (char*)(httpDataBuff + 6));
//                }  
//                else if(!strcmp((char*)httpDataBuff, (const char*)"txt2"))
//                {          
//                    strcpy(Nconfig[1].Name_Config, (char*)(httpDataBuff + 6));
//                }  
//                else if(!strcmp((char*)httpDataBuff, (const char*)"txt3"))
//                {          
//                    strcpy(Nconfig[2].Name_Config, (char*)(httpDataBuff + 6));
//                }
//                else if(!strcmp((char*)httpDataBuff, (const char*)"txt4"))
//                {          
//                    strcpy(Nconfig[3].Name_Config, (char*)(httpDataBuff + 6));
//                }  
//                else if(!strcmp((char*)httpDataBuff, (const char*)"txt5"))
//                {          
//                    strcpy(Nconfig[4].Name_Config, (char*)(httpDataBuff + 6));
//                }  
//                else if(!strcmp((char*)httpDataBuff, (const char*)"SV"))
//                {
//                    EEPROM_SaveData(&Nconfig[Config_Used]);
//                }
//                else if(!strcmp((char*)httpDataBuff, (const char*)"RST"))
//                {
//                    ResetConfig(Config_Used);
//                    
//                }
//                else if(!strcmp((char*)httpDataBuff, (const char*)"Dow"))
//                {
//
//
//                }
//            }
//            return HTTP_IO_DONE; 
//        }
//        
//        if(TestForceUpload == 1)
//        {
//            uint16_t lenA, lenB;
//            static uint16_t start, stop;
//            static CRYPT_MD5_CTX md5;            // Assume only one simultaneous MD5
//            TCP_SOCKET sktHTTP;
//            uint8_t* httpDataBuff;
//
//            #define UPLOAD_INIT_DATA   (0)
//            #define UPLOAD_WAIT_DATA   (1)
//            #define UPLOAD_PARSE_DATA     (2)
//
//        //    extern char UploadState[200];
//            static char temp[1024] = "Start csv    ";
//            char tmp[1024] = "tmp";
//            static int state = 0;
//            static int len = 0;
//            sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
//            switch(state)
//            {
//                case UPLOAD_INIT_DATA:
//                {
//
//        //            strcpy(UploadState, "backup file processing");                                  
//                    lenA = TCPIP_TCP_ArrayFind(sktHTTP, (const uint8_t*)"Name:", 5, 0, 0, false);
//
//                    if(lenA == 0xffff)
//                    {//if not, ask for more data
//                        return HTTP_IO_NEED_DATA;
//                    }
//                    else if(lenA == 0)
//                    {
//                        state = 0;
//                        Nop();
//        //                strcpy(UploadState, "backup file processing failed");
//                        return HTTP_IO_DONE;
//                    }
//                    state = 1;
//                }
//                case UPLOAD_WAIT_DATA:
//                {
//                    // See if a CRLF is in the buffer
//
//                    lenA = TCPIP_TCP_ArrayFind(sktHTTP, (const uint8_t*)"/FinCSV", 7, 0, 0, true);
//
//                    if(lenA != 0xffff)
//                    {// Found it, so remove all data up to and including
//                        lenA = TCPIP_TCP_ArrayGet(sktHTTP, tmp, lenA+7);
//                        TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenA);
//                        state = 2;
//                        strcat(temp, tmp);
//                    }
//                    else
//                    {// Otherwise, remove as much as possible
//                        lenA = TCPIP_TCP_ArrayGet(sktHTTP, tmp, TCPIP_TCP_GetIsReady(sktHTTP) - 7);
//                        if(lenA == 0)
//                        {
//                            state = 0;
//        //                    strcpy(UploadState, "backup file processing failed");
//                            return HTTP_IO_DONE;
//                        }
//                        TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenA);
//                        strcat(temp, tmp);
//                        return HTTP_IO_NEED_DATA;
//                    }
//                }
//                case UPLOAD_PARSE_DATA:
//                {
//
//        //            uploadAndSave(temp);
//                    Upload_Audio_CSV(temp);
//                    memset (temp, 0, sizeof (temp));
//                    state = 0;
//                    Nop();
//                }
//            }
//            return HTTP_IO_DONE;
//        }
//    return HTTP_IO_DONE;  
}




static HTTP_IO_RESULT HTTPPostUploadAudio(HTTP_CONN_HANDLE connHandle, int SelectPost)
{
    int SV = 0;
    if(SelectPost == 0)
    {
        uint8_t i;
        uint32_t byteCount;
        TCP_SOCKET sktHTTP;
        uint8_t* httpDataBuff = 0;
        bool bConfigFailure = false;
    
        byteCount = TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle);
        sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
        if(byteCount > TCPIP_TCP_GetIsReady(sktHTTP) + TCPIP_TCP_FifoRxFreeGet(sktHTTP))
        {   // Configuration Failure
            lastFailure = true;
            TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
            return HTTP_IO_DONE;
        }

        // Ensure that all data is waiting to be parsed.  If not, keep waiting for
        // all of it to arrive.
        if(TCPIP_TCP_GetIsReady(sktHTTP) < byteCount)
            return HTTP_IO_NEED_DATA;

        // Use current config in non-volatile memory as defaults
        httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);

        // Read all browser POST data

        while(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle))
        {
            // Read a form field name
            if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, 6) != HTTP_READ_OK)
            {
                bConfigFailure = true;
                break;
            }

            // Read a form field value
            if(TCPIP_HTTP_PostValueRead(connHandle, httpDataBuff + 6, TCPIP_HTTP_MAX_DATA_LEN-6-2) != HTTP_READ_OK)
            {
                bConfigFailure = true;
                break;
            }




            if(!strcmp((char*)httpDataBuff, (const char*)"ch"))
            {
                char Test_Txt[2];
                int Compare_Config_Used = Config_Used;
                memcpy(Test_Txt, (char*)(httpDataBuff + 6),sizeof Test_Txt);
                Config_Used = atoi(Test_Txt);

                if(Compare_Config_Used != Config_Used)
                {                      
                    EEPROM_SaveData(&Config_Used);
                    memcpy(Nconfig,NconfigDefaut,sizeof(NconfigDefaut));
                    for(i=0; i < 6;i++)
                    {
                        I2C_PT_Volume(Select_Input(i),  Nconfig[Config_Used].Device_IN[i].Volume);
                        I2C_PT_Speak_Att(Select_Input(i),Nconfig[Config_Used].Device_IN[i].L,LEFT );
                        I2C_PT_Speak_Att(Select_Input(i), Nconfig[Config_Used].Device_IN[i].R,RIGHT);
                        I2C_PT_AudioSwitch(Select_Input(i), Nconfig[Config_Used].Device_IN[i].Gain,0,Stereo1);
                        I2C_PT_BASS_TREBLE(Select_Input(i), Nconfig[Config_Used].Device_IN[i].Basse,PT_BASS);
                        I2C_PT_BASS_TREBLE(Select_Input(i), Nconfig[Config_Used].Device_IN[i].Aigue,PT_TREBLE);
                    }

                    for(i=0; i < 7;i++)
                    {
                        I2C_PT_Volume(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Volume);
                        I2C_PT_Speak_Att(Select_Output(i),Nconfig[Config_Used].Device_OUT[i].L,LEFT );
                        I2C_PT_Speak_Att(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].R,RIGHT);
                        I2C_PT_AudioSwitch(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Gain,0,Stereo1);
                        I2C_PT_BASS_TREBLE(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Basse,PT_BASS);
                        I2C_PT_BASS_TREBLE(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Aigue,PT_TREBLE);
                    }
                }
            }

            else if(!strcmp((char*)httpDataBuff, (const char*)"txt1"))
            {           
                strcpy(Nconfig[Config_Used].Name_Config, (char*)(httpDataBuff + 6));
                SV = 1;
            }  
            else if(!strcmp((char*)httpDataBuff, (const char*)"txt2"))
            {          
                strcpy(Nconfig[1].Name_Config, (char*)(httpDataBuff + 6));
                SV = 1;
            }  
            else if(!strcmp((char*)httpDataBuff, (const char*)"txt3"))
            {          
                strcpy(Nconfig[2].Name_Config, (char*)(httpDataBuff + 6));
                SV = 1;
            }
            else if(!strcmp((char*)httpDataBuff, (const char*)"txt4"))
            {          
                strcpy(Nconfig[3].Name_Config, (char*)(httpDataBuff + 6));
                SV = 1;
            }  
            else if(!strcmp((char*)httpDataBuff, (const char*)"txt5"))
            {          
                strcpy(Nconfig[4].Name_Config, (char*)(httpDataBuff + 6));
                SV = 1;
            }  
//            else if(!strcmp((char*)httpDataBuff, (const char*)"SV"))
//            {
////                EEPROM_SaveData(&Nconfig[Config_Used]);
//                SV = 1;
//                
//            }
            else if(!strcmp((char*)httpDataBuff, (const char*)"RST"))
            {
                ResetConfig(Config_Used);
            }
            else if(!strcmp((char*)httpDataBuff, (const char*)"Sel"))
            {
                Nop();
            }
            else if(!strcmp((char*)httpDataBuff, (const char*)"UPL"))
            {
                Nop();
            }
            else if(!strcmp((char*)httpDataBuff, (const char*)"UP"))
            {
                Nop();
            }
        }
        if(SV == 1)
        {
            EEPROM_SaveData(&Nconfig[Config_Used]);
            memcpy(NconfigDefaut,Nconfig,sizeof(Nconfig));
            SV = 0;
        }
            
        return HTTP_IO_DONE; 
    }
    
    if(SelectPost == 1)
    {
        uint16_t lenA, lenB;
        static uint16_t start, stop;
        static CRYPT_MD5_CTX md5;            // Assume only one simultaneous MD5
        TCP_SOCKET sktHTTP;
        uint8_t* httpDataBuff;

        #define UPLOAD_INIT_DATA   (0)
        #define UPLOAD_WAIT_DATA   (1)
        #define UPLOAD_PARSE_DATA     (2)

    //    extern char UploadState[200];
        static char temp[1024] = "Start csv    ";
        char tmp[1024] = "tmp";
        static int state = 0;
        static int len = 0;
        sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
        switch(state)
        {
            case UPLOAD_INIT_DATA:
            {

    //            strcpy(UploadState, "backup file processing");                                  
                lenA = TCPIP_TCP_ArrayFind(sktHTTP, (const uint8_t*)"Name:", 5, 0, 0, false);

                if(lenA == 0xffff)
                {//if not, ask for more data
                    return HTTP_IO_NEED_DATA;
                }
                else if(lenA == 0)
                {
                    state = 0;
                    Nop();
    //                strcpy(UploadState, "backup file processing failed");
                    return HTTP_IO_DONE;
                }
                state = 1;
            }
            case UPLOAD_WAIT_DATA:
            {
                // See if a CRLF is in the buffer

                lenA = TCPIP_TCP_ArrayFind(sktHTTP, (const uint8_t*)"/FinCSV", 7, 0, 0, true);

                if(lenA != 0xffff)
                {// Found it, so remove all data up to and including
                    lenA = TCPIP_TCP_ArrayGet(sktHTTP, tmp, lenA+7);
                    TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenA);
                    state = 2;
                    strcat(temp, tmp);
                }
                else
                {// Otherwise, remove as much as possible
                    lenA = TCPIP_TCP_ArrayGet(sktHTTP, tmp, TCPIP_TCP_GetIsReady(sktHTTP) - 7);
                    if(lenA == 0)
                    {
                        state = 0;
    //                    strcpy(UploadState, "backup file processing failed");
                        return HTTP_IO_DONE;
                    }
                    TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenA);
                    strcat(temp, tmp);
                    return HTTP_IO_NEED_DATA;
                }
            }
            case UPLOAD_PARSE_DATA:
            {

    //            uploadAndSave(temp);
                Upload_Audio_CSV(temp);
                memset (temp, 0, sizeof (temp));
                state = 0;
                Nop();

            }
        }
        return HTTP_IO_DONE;
    }
}


static HTTP_IO_RESULT HTTPPostRouteConfig(HTTP_CONN_HANDLE connHandle)
{

    uint8_t i;
    IPV4_ADDR newIPAddress, newMask;
    TCPIP_MAC_ADDR    newMACAddr;
    uint32_t byteCount;
    TCP_SOCKET sktHTTP;
    uint8_t* httpDataBuff = 0;
    bool bConfigFailure = false;

    // Check to see if the browser is attempting to submit more data than we
    // can parse at once.  This function needs to receive all updated
    // parameters and validate them all before committing them to memory so that
    // orphaned configuration parameters do not get written (for example, if a
    // static IP address is given, but the subnet mask fails parsing, we
    // should not use the static IP address).  Everything needs to be processed
    // in a single transaction.  If this is impossible, fail and notify the user.
    // As a web devloper, if you add parameters to the network info and run into this
    // problem, you could fix this by to splitting your update web page into two
    // seperate web pages (causing two transactional writes).  Alternatively,
    // you could fix it by storing a static shadow copy of network info someplace
    // in memory and using it when info is complete.
    // Lastly, you could increase the TCP RX FIFO size for the HTTP server.
    // This will allow more data to be POSTed by the web browser before hitting this limit.
    byteCount = TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle);
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(byteCount > TCPIP_TCP_GetIsReady(sktHTTP) + TCPIP_TCP_FifoRxFreeGet(sktHTTP))
    {   // Configuration Failure
        lastFailure = true;
        TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
        return HTTP_IO_DONE;
    }

    // Ensure that all data is waiting to be parsed.  If not, keep waiting for
    // all of it to arrive.
    if(TCPIP_TCP_GetIsReady(sktHTTP) < byteCount)
        return HTTP_IO_NEED_DATA;

    // Use current config in non-volatile memory as defaults
    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);

    // Read all browser POST data
    while(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle))
    {
        // Read a form field name
        if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, 6) != HTTP_READ_OK)
        {
            bConfigFailure = true;
            break;
        }

        // Read a form field value
        if(TCPIP_HTTP_PostValueRead(connHandle, httpDataBuff + 6, TCPIP_HTTP_MAX_DATA_LEN-6-2) != HTTP_READ_OK)
        {
            bConfigFailure = true;
            break;
        }
        

        if(!strcmp((char*)httpDataBuff, (const char*)"Dst1"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[0].IP_Route))
            {
                routeconfig[0].IP_Route.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Mas1"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[0].IP_Mask))
            {
                routeconfig[0].IP_Mask.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Net1"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[0].IP_Net))
            {
                routeconfig[0].IP_Net.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Dst2"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[1].IP_Route))
            {
                routeconfig[1].IP_Route.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Mas2"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[1].IP_Mask))
            {
                routeconfig[1].IP_Mask.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Net2"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[1].IP_Net))
            {
                routeconfig[1].IP_Net.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Dst3"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[2].IP_Route))
            {
                routeconfig[2].IP_Route.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Mas3"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[2].IP_Mask))
            {
                routeconfig[2].IP_Mask.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Net3"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[2].IP_Net))
            {
                routeconfig[2].IP_Net.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Dst4"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[3].IP_Route))
            {
                routeconfig[3].IP_Route.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Mas4"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[3].IP_Mask))
            {
                routeconfig[3].IP_Mask.Val = 0;
                bConfigFailure = true;
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"Net4"))
        {// Save new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &routeconfig[3].IP_Net))
            {
                routeconfig[3].IP_Net.Val = 0;
                bConfigFailure = true;
            }
        }
    }
    
    EEPROM_SaveData(&routeconfig[0].IP_Route.v);
    EEPROM_SaveData(&routeconfig[0].IP_Mask.v);
    EEPROM_SaveData(&routeconfig[0].IP_Net.v);
    
    EEPROM_SaveData(&routeconfig[1].IP_Route.v);
    EEPROM_SaveData(&routeconfig[1].IP_Mask.v);
    EEPROM_SaveData(&routeconfig[1].IP_Net.v);
    
    EEPROM_SaveData(&routeconfig[2].IP_Route.v);
    EEPROM_SaveData(&routeconfig[2].IP_Mask.v);
    EEPROM_SaveData(&routeconfig[2].IP_Net.v);
    
    EEPROM_SaveData(&routeconfig[3].IP_Route.v);
    EEPROM_SaveData(&routeconfig[3].IP_Mask.v);
    EEPROM_SaveData(&routeconfig[3].IP_Net.v);

        // Parse the value that was read
    
    //TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);

    return HTTP_IO_DONE;
}

static struct
{
    TCPIP_NET_HANDLE    currNet;              // current working interface + valid flag
    char                ifName[10 + 1];       // interface name
    char                nbnsName[16 + 1];     // host name
    char                ifMacAddr[17 + 1];    // MAC address
    char                ipAddr[15 +1];        // IP address
    char                ipMask[15 + 1];       // mask
    char                gwIP[15 + 1];         // gateway IP address
    char                dns1IP[15 + 1];       // DNS IP address
    char                dns2IP[15 + 1];       // DNS IP address

    TCPIP_NETWORK_CONFIG   netConfig;  // configuration in the interface requested format
}httpNetData;
static HTTP_IO_RESULT HTTPPostConfig(HTTP_CONN_HANDLE connHandle)
{

    uint8_t i;
    IPV4_ADDR newIPAddress, newMask;
    TCPIP_MAC_ADDR    newMACAddr;
    uint32_t byteCount;
    TCP_SOCKET sktHTTP;
    uint8_t* httpDataBuff = 0;
    bool bConfigFailure = false;

    extern char Save_Adresse_IP[17];
    extern char Save_Mask_IP[17];
    extern char Save_Gateway_IP[17];
    extern char Save_DNS_IP[17];
    
    int SNMP_htm = 0;

    httpNetData.currNet = 0; // forget the old settings

    // Check to see if the browser is attempting to submit more data than we
    // can parse at once.  This function needs to receive all updated
    // parameters and validate them all before committing them to memory so that
    // orphaned configuration parameters do not get written (for example, if a
    // static IP address is given, but the subnet mask fails parsing, we
    // should not use the static IP address).  Everything needs to be processed
    // in a single transaction.  If this is impossible, fail and notify the user.
    // As a web devloper, if you add parameters to the network info and run into this
    // problem, you could fix this by to splitting your update web page into two
    // seperate web pages (causing two transactional writes).  Alternatively,
    // you could fix it by storing a static shadow copy of network info someplace
    // in memory and using it when info is complete.
    // Lastly, you could increase the TCP RX FIFO size for the HTTP server.
    // This will allow more data to be POSTed by the web browser before hitting this limit.
    byteCount = TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle);
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(byteCount > TCPIP_TCP_GetIsReady(sktHTTP) + TCPIP_TCP_FifoRxFreeGet(sktHTTP))
    {   // Configuration Failure
        lastFailure = true;
        TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
        return HTTP_IO_DONE;
    }

    // Ensure that all data is waiting to be parsed.  If not, keep waiting for
    // all of it to arrive.
    if(TCPIP_TCP_GetIsReady(sktHTTP) < byteCount)
        return HTTP_IO_NEED_DATA;

    // Use current config in non-volatile memory as defaults
    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);

    // Read all browser POST data
    while(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle))
    {
        // Read a form field name
        if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, 6) != HTTP_READ_OK)
        {
            bConfigFailure = true;
            break;
        }

        // Read a form field value
        if(TCPIP_HTTP_PostValueRead(connHandle, httpDataBuff + 6, TCPIP_HTTP_MAX_DATA_LEN-6-2) != HTTP_READ_OK)
        {
            bConfigFailure = true;
            break;
        }

        // Parse the value that was read
        if(!strcmp((char*)httpDataBuff, (const char*)"name"))
        {
            extern char unique_name[50], SNMP_msg[50];
            int i = 0;
            strcpy(unique_name, (char*)(httpDataBuff+6));
            int j = strlen(unique_name), k = 0;
            while(j >= k)
            {
                SNMP_msg[k] = unique_name[j - k];
                k++;
            }
            EEPROM_SaveData(unique_name);
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"ip"))
        {// Save new static IP Address
            if(TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &newIPAddress) != 0)
            {
                char tmp[30];
                strcpy(tmp, (char*)(httpDataBuff+6));
                if(strcmp(tmp, Save_Adresse_IP) != 0)
                {
                    bConfigFailure = true;
                    strcpy(Save_Adresse_IP, tmp);
                    EEPROM_SaveData(Save_Adresse_IP);
                }
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"gw"))
        {// Read new gateway address
            if(TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &newIPAddress) != 0)
            {
                char tmp[30];
                strcpy(tmp, (char*)(httpDataBuff+6));
                if(strcmp(tmp, Save_Gateway_IP) != 0)
                {
                    bConfigFailure = true;
                    strcpy(Save_Gateway_IP, tmp);
                    EEPROM_SaveData(Save_Gateway_IP);
                }
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"sub"))
        {// Read new static subnet
            if(TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &newIPAddress) != 0)
            {
                char tmp[30];
                strcpy(tmp, (char*)(httpDataBuff+6));
                if(strcmp(tmp, Save_Mask_IP) != 0)
                {
                    bConfigFailure = true;
                    strcpy(Save_Mask_IP, tmp);
                    EEPROM_SaveData(Save_Mask_IP);
                }
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"dns1"))
        {// Read new primary DNS server
            if(TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &newIPAddress) != 0)
            {
                char tmp[30];
                strcpy(tmp, (char*)(httpDataBuff+6));
                if(strcmp(tmp, Save_DNS_IP) != 0)
                {
                    bConfigFailure = true;
                    strcpy(Save_DNS_IP, tmp);
                    EEPROM_SaveData(Save_DNS_IP);
                }
            }
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"ntp"))
        {
            extern char Save_NTP1[30];
            char tmp[30];
            strcpy(tmp, (char*)(httpDataBuff+6));
            if(strcmp(tmp, Save_NTP1) != 0)
            {
                bConfigFailure = true;
                strcpy(Save_NTP1, tmp);
                EEPROM_SaveData(Save_NTP1);
            }
        }
    }

    if(bConfigFailure == true)
    {
        // All parsing complete!  Save new settings and force an interface restart
        // Set the interface to restart and display reconnecting information
        strcpy((char*)httpDataBuff, "/maintenance/reboot.htm?");
        TCPIP_Helper_FormatNetBIOSName((uint8_t*)httpNetData.nbnsName);
        memcpy((void*)(httpDataBuff+30), httpNetData.nbnsName, 16);
        httpDataBuff[30+16] = 0x00; // Force null termination
        for(i = 30; i < 30u+16u; i++)
        {
            if(httpDataBuff[i] == ' ')
                httpDataBuff[i] = 0x00;
        }
        httpNetData.currNet = TCPIP_TCP_SocketNetGet(sktHTTP);   // save current interface and mark as valid
        strncpy(httpNetData.ifName, TCPIP_STACK_NetNameGet(httpNetData.currNet), sizeof(httpNetData.ifName));
        PIC_reset();
    }
    else
    {   // Configuration don't need reboot
        if(httpDataBuff)
        {
            strcpy((char*)httpDataBuff, "/maintenance/network.htm");
        }
    }
    
    TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);

    return HTTP_IO_DONE;
}

/*****************************************************************************
  Function:
    static HTTP_IO_RESULT HTTPPostBackup(HTTP_CONN_HANDLE connHandle)

  Summary:
    Processes the file upload form on upload.htm

  Description:
    This function demonstrates the processing of file uploads.  First, the
    function locates the file data, skipping over any headers that arrive.
    Second, it reads the file 64 bytes at a time and hashes that data.  Once
    all data has been received, the function calculates the MD5 sum and
    stores it in current connection data buffer.

    After the headers, the first line from the form will be the MIME
    separator.  Following that is more headers about the file, which we
    discard.  After another CRLFCRLF, the file data begins, and we read
    it 16 bytes at a time and add that to the MD5 calculation.  The reading
    terminates when the separator string is encountered again on its own
    line.  Notice that the actual file data is trashed in this process,
    allowing us to accept files of arbitrary size, not limited by RAM.
    Also notice that the data buffer is used as an arbitrary storage array
    for the result.  The ~uploadedmd5~ callback reads this data later to
    send back to the client.

  Precondition:
    None

  Parameters:
    connHandle  - HTTP connection handle

  Return Values:
    HTTP_IO_DONE - all parameters have been processed
    HTTP_IO_WAITING - the function is pausing to continue later
    HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/
#if defined(PIC_RF) || defined(PIC_COMB) || defined(PIC_AMPLI)
static HTTP_IO_RESULT HTTPPostBackup(HTTP_CONN_HANDLE connHandle)
{
    uint16_t lenA, lenB;
    static uint16_t start, stop;
    static CRYPT_MD5_CTX md5;            // Assume only one simultaneous MD5
    TCP_SOCKET sktHTTP;
    uint8_t* httpDataBuff;
    
    #define UPLOAD_INIT_DATA   (0)
    #define UPLOAD_WAIT_DATA   (1)
    #define UPLOAD_PARSE_DATA     (2)
    
    extern char UploadState[200];
    static char temp[3000] = "Start csv    ";
    char tmp[1000] = "tmp";
    static int state = 0;
    static int len = 0;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    switch(state)
    {
        case UPLOAD_INIT_DATA:
        {
            strcpy(UploadState, "backup file processing");
            lenA = TCPIP_TCP_ArrayFind(sktHTTP, (const uint8_t*)"\r\n", 2, 0, 0, false);
            if(lenA == 0xffff)
            {//if not, ask for more data
                return HTTP_IO_NEED_DATA;
            }
            else if(lenA == 0)
            {
                state = 0;
                strcpy(UploadState, "backup file processing failed");
                return HTTP_IO_DONE;
            }
            state = 1;
        }
        case UPLOAD_WAIT_DATA:
        {
            // See if a CRLF is in the buffer
            
            lenA = TCPIP_TCP_ArrayFind(sktHTTP, (const uint8_t*)"/EEPROM", 7, 0, 0, true);

            if(lenA != 0xffff)
            {// Found it, so remove all data up to and including
                lenA = TCPIP_TCP_ArrayGet(sktHTTP, tmp, lenA+7);
                TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenA);
                state = 2;
                strcat(temp, tmp);
            }
            else
            {// Otherwise, remove as much as possible
                lenA = TCPIP_TCP_ArrayGet(sktHTTP, tmp, TCPIP_TCP_GetIsReady(sktHTTP) - 7);
                if(lenA == 0)
                {
                    state = 0;
                    strcpy(UploadState, "backup file processing failed");
                    return HTTP_IO_DONE;
                }
                TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenA);
                strcat(temp, tmp);
                return HTTP_IO_NEED_DATA;
            }
        }
        case UPLOAD_PARSE_DATA:
        {

            uploadAndSave(temp);
        }
    }
    return HTTP_IO_DONE;
}
#endif
#endif //(use_post)

/****************************************************************************
  Section:
    Dynamic Variable Callback Functions
  ***************************************************************************/

/*****************************************************************************
  Function:
    void TCPIP_HTTP_Print_varname(void)

  Internal:
    See documentation in the TCP/IP Stack API or HTTP.h for details.
  ***************************************************************************/

void TCPIP_HTTP_Print_builddate(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x01);
    if(TCPIP_TCP_PutIsReady(sktHTTP) < strlen((const char*)__DATE__" "__TIME__))
        return;

    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x00);
    TCPIP_TCP_StringPut(sktHTTP, (const void*)__DATE__" "__TIME__);
}

void TCPIP_HTTP_Print_version(HTTP_CONN_HANDLE connHandle)
{
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (const void*)TCPIP_STACK_VERSION_STR);
}

const uint8_t HTML_UP_ARROW[] = "up";
const uint8_t HTML_DOWN_ARROW[] = "dn";

void TCPIP_HTTP_Print_drive(HTTP_CONN_HANDLE connHandle)
{
 TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (const void*)SYS_FS_DRIVE);
}

void TCPIP_HTTP_Print_fstype(HTTP_CONN_HANDLE connHandle)
{
 TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (const void*)SYS_FS_MPFS_STRING);
}

void TCPIP_HTTP_Print_cookiename(HTTP_CONN_HANDLE connHandle)
{
    const uint8_t *ptr;
    TCP_SOCKET sktHTTP;

    ptr = TCPIP_HTTP_ArgGet(TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle), (const uint8_t*)"name");

    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(ptr)
        TCPIP_TCP_StringPut(sktHTTP, ptr);
    else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"not set");
}

void TCPIP_HTTP_Print_cookiefav(HTTP_CONN_HANDLE connHandle)
{
    const uint8_t *ptr;
    TCP_SOCKET sktHTTP;

    ptr = TCPIP_HTTP_ArgGet(TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle), (const uint8_t*)"fav");

    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(ptr)
        TCPIP_TCP_StringPut(sktHTTP, ptr);
    else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"not set");
}

void TCPIP_HTTP_Print_uploadedmd5(HTTP_CONN_HANDLE connHandle)
{
    uint8_t i;
    uint8_t* httpDataBuff;
    TCP_SOCKET sktHTTP;

    // Set a flag to indicate not finished
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 1);

    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    // Make sure there's enough output space
    if(TCPIP_TCP_PutIsReady(sktHTTP) < 32u + 37u + 5u)
        return;

    {// No file uploaded, so just return
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"<b>Upload a File</b>");
        TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0);
        return;
    }

    TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"<b>Uploaded File's MD5 was:</b><br />");
    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);

    // Write a byte of the md5 sum at a time
    for(i = 0; i < 16u; i++)
    {
        TCPIP_TCP_Put(sktHTTP, btohexa_high(httpDataBuff[i]));
        TCPIP_TCP_Put(sktHTTP, btohexa_low(httpDataBuff[i]));
        if((i & 0x03) == 3u)
            TCPIP_TCP_Put(sktHTTP, ' ');
    }

    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x00);
}

void HTTPPrintIP(HTTP_CONN_HANDLE connHandle, IPV4_ADDR ip)
{
    uint8_t digits[4];
    uint8_t i;
    TCP_SOCKET sktHTTP;

    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    for(i = 0; i < 4u; i++)
    {
        if(i)
            TCPIP_TCP_Put(sktHTTP, '.');
        uitoa(ip.v[i], digits);
        TCPIP_TCP_StringPut(sktHTTP, digits);
    }
}

void TCPIP_HTTP_Print_config_hostname(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_TCP_StringPut(sktHTTP, (uint8_t*)TCPIP_STACK_NetBIOSName(TCPIP_TCP_SocketNetGet(sktHTTP)));
}

void TCPIP_HTTP_Print_config_dhcpchecked(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(TCPIP_DHCP_IsEnabled(TCPIP_TCP_SocketNetGet(sktHTTP)))
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"checked");
    }
}

void TCPIP_HTTP_Print_config_ip(HTTP_CONN_HANDLE connHandle)
{
    extern char Save_Adresse_IP[17];
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t *)Save_Adresse_IP);
}

void TCPIP_HTTP_Print_config_gw(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_NET_HANDLE netH = TCPIP_TCP_SocketNetGet(sktHTTP);
    IPV4_ADDR gwAddress;

    gwAddress.Val = TCPIP_STACK_NetAddressGateway(netH);

    HTTPPrintIP(connHandle, gwAddress);
}

void TCPIP_HTTP_Print_config_subnet(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_NET_HANDLE netH = TCPIP_TCP_SocketNetGet(sktHTTP);
    IPV4_ADDR ipMask;

    ipMask.Val = TCPIP_STACK_NetMask(netH);
    HTTPPrintIP(connHandle, ipMask);
}

void TCPIP_HTTP_Print_config_dns1(HTTP_CONN_HANDLE connHandle)
{
    extern char Save_DNS_IP[17];
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t *)Save_DNS_IP);
}

void TCPIP_HTTP_Print_config_dns2(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_NET_HANDLE netH = TCPIP_TCP_SocketNetGet(sktHTTP);
    IPV4_ADDR secondDnsAddr;

    secondDnsAddr.Val = TCPIP_STACK_NetAddressDnsSecond(netH);

    HTTPPrintIP(connHandle, secondDnsAddr);
}

void TCPIP_HTTP_Print_config_mac(HTTP_CONN_HANDLE connHandle)
{
    uint8_t i;
    TCP_SOCKET sktHTTP;
    TCPIP_NET_HANDLE hNet;
    const uint8_t* pMacAdd;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    if(TCPIP_TCP_PutIsReady(sktHTTP) < 18u)
    {//need 17 bytes to write a MAC
        TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x01);
        return;
    }

    hNet = TCPIP_TCP_SocketNetGet(sktHTTP);
    pMacAdd = TCPIP_STACK_NetAddressMac(hNet);
    // Write each byte
    for(i = 0; i < 6u; i++)
    {
        if(i)
            TCPIP_TCP_Put(sktHTTP, ':');
        TCPIP_TCP_Put(sktHTTP, btohexa_high(pMacAdd[i]));
        TCPIP_TCP_Put(sktHTTP, btohexa_low(pMacAdd[i]));
    }

    // Indicate that we're done
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x00);
    return;
}

// SNMP Read communities configuration page
void TCPIP_HTTP_Print_read_comm(HTTP_CONN_HANDLE connHandle, uint16_t num)
{
#if defined(TCPIP_STACK_USE_SNMP_SERVER)
    uint8_t dest[TCPIP_SNMP_COMMUNITY_MAX_LEN+1];
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    // Ensure no one tries to read illegal memory addresses by specifying
    // illegal num values.
    if(num >= TCPIP_SNMP_MAX_COMMUNITY_SUPPORT)
        return;
    memset(dest,0,sizeof(dest));
    if(TCPIP_SNMP_ReadCommunityGet(num,TCPIP_SNMP_COMMUNITY_MAX_LEN,dest) != true)
        return;
    // Send proper string
    TCPIP_TCP_StringPut(sktHTTP,dest);
#endif
}

// SNMP Write communities configuration page
void TCPIP_HTTP_Print_write_comm(HTTP_CONN_HANDLE connHandle, uint16_t num)
{
#if defined(TCPIP_STACK_USE_SNMP_SERVER)
    uint8_t dest[TCPIP_SNMP_COMMUNITY_MAX_LEN+1];
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    // Ensure no one tries to read illegal memory addresses by specifying
    // illegal num values.
    if(num >= TCPIP_SNMP_MAX_COMMUNITY_SUPPORT)
        return;
    memset(dest,0,sizeof(dest));
    // Send proper string
    if(TCPIP_SNMP_WriteCommunityGet(num,TCPIP_SNMP_COMMUNITY_MAX_LEN,dest) != true)
        return;
    TCPIP_TCP_StringPut(sktHTTP,dest);
#endif
}

void TCPIP_HTTP_Print_reboot(HTTP_CONN_HANDLE connHandle)
{
    // This is not so much a print function, but causes the interface to restart
    // when the configuration is changed.  If called via an AJAX call, this
    // will gracefully restart the interface and bring it back online immediately
    if(httpNetData.currNet != 0)
    {   // valid data
        httpNetData.netConfig.interface = httpNetData.ifName;
        httpNetData.netConfig.hostName = httpNetData.nbnsName;
        httpNetData.netConfig.macAddr = httpNetData.ifMacAddr;
        httpNetData.netConfig.ipAddr = httpNetData.ipAddr;
        httpNetData.netConfig.ipMask = httpNetData.ipMask;
        httpNetData.netConfig.gateway = httpNetData.gwIP;
        httpNetData.netConfig.priDNS = httpNetData.dns1IP;
        httpNetData.netConfig.secondDNS = httpNetData.dns2IP;
        httpNetData.netConfig.powerMode = TCPIP_STACK_IF_POWER_FULL;
        // httpNetData.netConfig.startFlags should be already set;
        //
        TCPIP_STACK_NetDown(httpNetData.currNet);
        TCPIP_STACK_NetUp(httpNetData.currNet, &httpNetData.netConfig);
    }
}

void TCPIP_HTTP_Print_rebootaddr(HTTP_CONN_HANDLE connHandle)
{// This is the expected address of the board upon rebooting
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle));
}

void TCPIP_HTTP_Print_ddns_user(HTTP_CONN_HANDLE connHandle)
{
    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    uint32_t callbackPos;

    if(DDNSClient.ROMPointers.Username || !DDNSClient.Username.szRAM)
        return;

    callbackPos = TCPIP_HTTP_CurrentConnectionCallbackPosGet(connHandle);
    if(callbackPos == 0x00u)
        callbackPos = (uint32_t)DDNSClient.Username.szRAM;
    callbackPos = (uint32_t)TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (uint8_t*)callbackPos);
    if(*(uint8_t*)callbackPos == '\0')
        callbackPos = 0x00;
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, callbackPos);
    #endif
}

void TCPIP_HTTP_Print_ddns_pass(HTTP_CONN_HANDLE connHandle)
{
    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    uint32_t callbackPos;
    if(DDNSClient.ROMPointers.Password || !DDNSClient.Password.szRAM)
        return;

    callbackPos = TCPIP_HTTP_CurrentConnectionCallbackPosGet(connHandle);

    if(callbackPos == 0x00u)
        callbackPos = (uint32_t)DDNSClient.Password.szRAM;
    callbackPos = (uint32_t)TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (uint8_t*)callbackPos);
    if(*(uint8_t*)callbackPos == '\0')
        callbackPos = 0x00;
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, callbackPos);
    #endif
}

void TCPIP_HTTP_Print_ddns_host(HTTP_CONN_HANDLE connHandle)
{
    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    uint32_t callbackPos;
    if(DDNSClient.ROMPointers.Host || !DDNSClient.Host.szRAM)
        return;
    callbackPos = TCPIP_HTTP_CurrentConnectionCallbackPosGet(connHandle);
    if(callbackPos == 0x00u)
        callbackPos = (uint32_t)DDNSClient.Host.szRAM;
    callbackPos = (uint32_t)TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (uint8_t*)callbackPos);
    if(*(uint8_t*)callbackPos == '\0')
        callbackPos = 0x00;
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, callbackPos);
    #endif
}

extern const char * const ddnsServiceHosts[];
void TCPIP_HTTP_Print_ddns_service(HTTP_CONN_HANDLE connHandle, uint16_t i)
{
    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    if(!DDNSClient.ROMPointers.UpdateServer || !DDNSClient.UpdateServer.szROM)
        return;
    if((const char*)DDNSClient.UpdateServer.szROM == ddnsServiceHosts[i])
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (const uint8_t*)"selected");
    #endif
}

void TCPIP_HTTP_Print_ddns_status(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    DDNS_STATUS s;
    s = TCPIP_DDNS_LastStatusGet();
    if(s == DDNS_STATUS_GOOD || s == DDNS_STATUS_UNCHANGED || s == DDNS_STATUS_NOCHG)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"ok");
    else if(s == DDNS_STATUS_UNKNOWN)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"unk");
    else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"fail");
    #else
    TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"fail");
    #endif
}

void TCPIP_HTTP_Print_ddns_status_msg(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(TCPIP_TCP_PutIsReady(sktHTTP) < 75u)
    {
        TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x01);
        return;
    }

    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    switch(TCPIP_DDNS_LastStatusGet())
    {
        case DDNS_STATUS_GOOD:
        case DDNS_STATUS_NOCHG:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The last update was successful.");
            break;
        case DDNS_STATUS_UNCHANGED:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The IP has not changed since the last update.");
            break;
        case DDNS_STATUS_UPDATE_ERROR:
        case DDNS_STATUS_CHECKIP_ERROR:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"Could not communicate with DDNS server.");
            break;
        case DDNS_STATUS_INVALID:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The current configuration is not valid.");
            break;
        case DDNS_STATUS_UNKNOWN:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The Dynamic DNS client is pending an update.");
            break;
        default:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"An error occurred during the update.<br />The DDNS Client is suspended.");
            break;
    }
    #else
    TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The Dynamic DNS Client is not enabled.");
    #endif

    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0);
}

void TCPIP_HTTP_Print_smtps_en(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"none");
}

void TCPIP_HTTP_Print_snmp_en(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    #if defined(TCPIP_STACK_USE_SNMP_SERVER)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"none");
    #else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"block");
    #endif
}

void TCPIP_HTTP_Print_status_ok(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(lastSuccess)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"block");
    else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"none");
    lastSuccess = false;
}

void TCPIP_HTTP_Print_status_fail(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(lastFailure)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"block");
    else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"none");
    lastFailure = false;
}

void TCPIP_HTTP_Print_Version(HTTP_CONN_HANDLE connHandle)
{
    extern  char Version[30];


    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t *)Version);
}



TCPIP_HTTP_Print_config_name(HTTP_CONN_HANDLE connHandle)
{
    extern char unique_name[50];
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)unique_name);
}
TCPIP_HTTP_Print_config_NTP(HTTP_CONN_HANDLE connHandle)
{
    extern char Save_NTP1[30];
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)Save_NTP1);
}
TCPIP_HTTP_Print_config_ver(HTTP_CONN_HANDLE connHandle)
{
    char chaine[40];
    sprintf(chaine,"%s",VERSION_PROG_WEB);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);
}
TCPIP_HTTP_Print_EEPROM(HTTP_CONN_HANDLE connHandle)
{
    if(EEPROM_IsAllSaved())
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"Saved");
    else
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"Saving");
}
//TCPIP_HTTP_Print_versionPIC(HTTP_CONN_HANDLE connHandle)
//{
//    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)VERSION);
//}
TCPIP_HTTP_Print_stateBackupPopup(HTTP_CONN_HANDLE connHandle)
{
    #if defined(PIC_RF) || defined(PIC_COMB) || defined(PIC_AMPLI)
    extern bool UploadStatePopUp;
    if(UploadStatePopUp == 1)
    {
        UploadStatePopUp = 0;
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"1");
    }
    else
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"0");
    }
    #endif
        
}
TCPIP_HTTP_Print_stateBackup(HTTP_CONN_HANDLE connHandle)
{
    #if defined(PIC_RF) || defined(PIC_COMB) || defined(PIC_AMPLI)
    extern char UploadState[200];
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)UploadState);
    #endif
}

void TCPIP_HTTP_Print_Config_rte_dst1(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[0].IP_Route,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);    
}
void TCPIP_HTTP_Print_Config_rte_mask1(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[0].IP_Mask,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);        
}   
void TCPIP_HTTP_Print_Config_rte_interface1(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[0].IP_Net,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);        
}


void TCPIP_HTTP_Print_Config_rte_dst2(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[1].IP_Route,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);    
}    
void TCPIP_HTTP_Print_Config_rte_mask2(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[1].IP_Mask,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);     
}
void TCPIP_HTTP_Print_Config_rte_interface2(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[1].IP_Net,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);     
}
   


void TCPIP_HTTP_Print_Config_rte_dst3(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[2].IP_Route,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);    
}
void TCPIP_HTTP_Print_Config_rte_mask3(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[2].IP_Mask,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);     
}
    
void TCPIP_HTTP_Print_Config_rte_interface3(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[2].IP_Net,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);     
}



void TCPIP_HTTP_Print_Config_rte_dst4(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[3].IP_Route,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);    
}
void TCPIP_HTTP_Print_Config_rte_mask4(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[3].IP_Mask,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);     
}
void TCPIP_HTTP_Print_Config_rte_interface4(HTTP_CONN_HANDLE connHandle)
{
    uint8_t tmp[17];
    TCPIP_Helper_IPAddressToString(&routeconfig[3].IP_Net,(char*) tmp, 17);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),tmp);     
}

void TCPIP_HTTP_Print_EEPROM_Saved(HTTP_CONN_HANDLE connHandle)
{
    if(EEPROM_IsAllSaved() == true)
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*) "1");     
    else
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*) "0");     
}



void TCPIP_HTTP_Print_BCKUP_Ready(HTTP_CONN_HANDLE connHandle)
{
    #if defined(PIC_RF) || defined(PIC_COMB) || defined(PIC_AMPLI)
    if(BCKUP_Ready() == true)
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*) "1");     
    else
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*) "0");  
    #endif
}






//Input
void TCPIP_HTTP_Print_ValV(HTTP_CONN_HANDLE connHandle)
{
    char Defaut_Volume[10];
    
    if(Nconfig[Config_Used].Device_IN[In_Audio].Volume >= -30)
    {
        sprintf(Defaut_Volume,"%0.2f",Nconfig[Config_Used].Device_IN[In_Audio].Volume+Nconfig[Config_Used].Device_IN[In_Audio].Gain);
    }
    else
    {
        sprintf(Defaut_Volume,"-31.25");
    }
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Defaut_Volume);     
}
    
void TCPIP_HTTP_Print_ValB(HTTP_CONN_HANDLE connHandle)
{
    char Defaut_Basse[10];
    
    sprintf(Defaut_Basse,"%d",Nconfig[Config_Used].Device_IN[In_Audio].Basse);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Defaut_Basse); 
}

void TCPIP_HTTP_Print_ValA(HTTP_CONN_HANDLE connHandle)
{
    char Defaut_Aigue[10];
    sprintf(Defaut_Aigue,"%d",Nconfig[Config_Used].Device_IN[In_Audio].Aigue);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Defaut_Aigue); 
}
void TCPIP_HTTP_Print_ValC(HTTP_CONN_HANDLE connHandle)
{
    char Defaut[10];
    sprintf(Defaut,"%d",Nconfig[Config_Used].Device_IN[In_Audio].Middle);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Defaut);     
}




void TCPIP_HTTP_Print_InA(HTTP_CONN_HANDLE connHandle)
{
//    char Audio[5];
//    sprintf(Audio,"%d",In_Audio);
//    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Audio);     
}
void TCPIP_HTTP_Print_Select(HTTP_CONN_HANDLE connHandle,uint16_t ShapeNr)
{
    char chaine[20];
    sprintf(chaine,"selected");
    if(In_Audio == 3)
    {
        if (ShapeNr == In_Audio+3 )//Correction Bug Microchip
        {
            TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine); 
        }
    }
    else if (ShapeNr == In_Audio )
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine); 
    }
}



//Output
void TCPIP_HTTP_Print_VolO(HTTP_CONN_HANDLE connHandle)
{
    char Defaut_Volume[10];
    
    if(Nconfig[Config_Used].Device_OUT[Out_Audio].Volume >= -30)
    {
        sprintf(Defaut_Volume,"%0.2f",Nconfig[Config_Used].Device_OUT[Out_Audio].Volume+Nconfig[Config_Used].Device_OUT[Out_Audio].Gain);
    }
    else
    {
        sprintf(Defaut_Volume,"-31.25");
    }    
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Defaut_Volume); 
//    char Defaut_Volume[10];
//    
////    sprintf(Defaut_Volume,"%0.2f",Nconfig[Config_Used].Device_OUT[Out_Audio].Volume);
//    sprintf(Defaut_Volume,"%0.2f",Nconfig[Config_Used].Device_OUT[Out_Audio].Volume+Nconfig[Config_Used].Device_OUT[Out_Audio].Gain);
//    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Defaut_Volume);     
}
void TCPIP_HTTP_Print_Balance(HTTP_CONN_HANDLE connHandle)
{
    char Defaut_Balance[10];
    static float Defaut_Valeur;
    
    if((Nconfig[Config_Used].Device_OUT[Out_Audio].R == 0)&&(Nconfig[Config_Used].Device_OUT[Out_Audio].L == 0))
    {
        Defaut_Valeur = 0;
    }
    else if((Nconfig[Config_Used].Device_OUT[Out_Audio].L == 0)&&(Nconfig[Config_Used].Device_OUT[Out_Audio].R < 0))
    {
        Defaut_Valeur = Nconfig[Config_Used].Device_OUT[Out_Audio].R *(-1);
    }
    else if((Nconfig[Config_Used].Device_OUT[Out_Audio].R == 0)&&(Nconfig[Config_Used].Device_OUT[Out_Audio].L < 0))
    {
        Defaut_Valeur = Nconfig[Config_Used].Device_OUT[Out_Audio].L;   
    }
    else
    {
        Defaut_Valeur = 0;
    }
    sprintf(Defaut_Balance,"%0.2f",Defaut_Valeur);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Defaut_Balance);
    
}

void TCPIP_HTTP_Print_OVB(HTTP_CONN_HANDLE connHandle)
{
    char Defaut_Basse[10];   
    sprintf(Defaut_Basse,"%d",Nconfig[Config_Used].Device_OUT[Out_Audio].Basse);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Defaut_Basse);     
}
void TCPIP_HTTP_Print_OVA(HTTP_CONN_HANDLE connHandle)
{
    char Defaut_Aigue[10];
    sprintf(Defaut_Aigue,"%d",Nconfig[Config_Used].Device_OUT[Out_Audio].Aigue);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Defaut_Aigue);     
}


void TCPIP_HTTP_Print_LoudnessChecked(HTTP_CONN_HANDLE connHandle)
{   
    if(Nconfig[Config_Used].Device_IN[In_Audio].Loudness == true)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"checked");
    }
    else
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"");
    }    
}
void TCPIP_HTTP_Print_LoudnessTxtin(HTTP_CONN_HANDLE connHandle)
{
    if(Nconfig[Config_Used].Device_IN[In_Audio].Loudness == true)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"ON");
    }
    else
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"OFF");
    }       
}


void TCPIP_HTTP_Print_AudioOutSelect(HTTP_CONN_HANDLE connHandle,uint16_t ShapeNr)
{
    if(Out_Audio == 3)
    {
        if(ShapeNr == Out_Audio +4)//Correction Bug Microchip
        {

            TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"selected");
        }    
    }
    else if(ShapeNr == Out_Audio)
    {

        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"selected");
    }    
}
    


void TCPIP_HTTP_Print_MasterGainChecked(HTTP_CONN_HANDLE connHandle)
{
    if(Nconfig[Config_Used].Master_Gain == GAIN_WEB_ACTIF)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"checked");
    }
    else
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"");
    }      
}
void TCPIP_HTTP_Print_MasterGainTxt(HTTP_CONN_HANDLE connHandle)
{
    if(Out_Audio != 1)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)" ");
    }
    else if(Nconfig[Config_Used].Master_Gain == GAIN_WEB_ACTIF)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"Web Fader actif");
    }
    else
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),(uint8_t*)"Pot Master actif");
    }       
}












void TCPIP_HTTP_Print_AD(HTTP_CONN_HANDLE connHandle,int N_AD)
{
    if(StateAck.ACK_AD5532[N_AD] == true)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"ON");
    }
    else if(StateAck.ACK_AD5532[N_AD] == false)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"!!!!!!");
    }
    else
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"--");  
    }
}


void TCPIP_HTTP_Print_PT(HTTP_CONN_HANDLE connHandle,int N_PT)
{
    if(StateAck.ACK_PT2314[N_PT] == true)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"ON");
    }
    else if(StateAck.ACK_PT2314[N_PT] == false)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"!!!!!!");
    }
    else
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"--");  
    }
     
}


void TCPIP_HTTP_Print_hiddenMasterGain(HTTP_CONN_HANDLE connHandle)
{
    char Cache[10];
    if(Out_Audio != 1)
    {
        sprintf(Cache,"hidden");
    }
    else
    {
        sprintf(Cache," ");
    }
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Cache); 
    
}


void TCPIP_HTTP_Print_Config_Defaut(HTTP_CONN_HANDLE connHandle,uint16_t ShapeNr)
{    
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
   
    TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)Nconfig[ShapeNr].Name_Config);
    
    //    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Nconfig[ShapeNr].Name_Config); 
}


void TCPIP_HTTP_Print_disabled(HTTP_CONN_HANDLE connHandle,uint16_t ShapeNr)
{
    if (ShapeNr != Config_Used )
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"disabled"); 
    }    
}

void TCPIP_HTTP_Print_Name_Config(HTTP_CONN_HANDLE connHandle)
{
    char Txt_Name_Config[30];
    sprintf(Txt_Name_Config,"%s",Nconfig[Config_Used].Name_Config);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Txt_Name_Config);     
}


void TCPIP_HTTP_Print_Checked(HTTP_CONN_HANDLE connHandle,uint16_t ShapeNr)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    
    if (ShapeNr == Config_Used)
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"checked");
    }
    
}




void TCPIP_HTTP_Print_value_But_Fader(HTTP_CONN_HANDLE connHandle)
{
    char chaine[20];
    
    sprintf(chaine,"%d",Aff_Fader_OFF);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);    
}

void TCPIP_HTTP_Print_Txt_MIDI_ON(HTTP_CONN_HANDLE connHandle)
{
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Txt_MIDI_ON);   
}

void TCPIP_HTTP_Print_Txt_MIDI_OFF(HTTP_CONN_HANDLE connHandle)
{
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),Txt_MIDI_OFF);   
}
    

void TCPIP_HTTP_Print_Number_Midi1(HTTP_CONN_HANDLE connHandle)
{
    char chaine[5];
    sprintf(chaine,"%d",Midi1);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);
}
void TCPIP_HTTP_Print_Number_Midi2(HTTP_CONN_HANDLE connHandle)
{
    char chaine[5];
    sprintf(chaine,"%d",Midi2);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);
}
void TCPIP_HTTP_Print_Number_Midi3(HTTP_CONN_HANDLE connHandle)
{
    char chaine[5];
    sprintf(chaine,"%d",Midi3);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);
}

void TCPIP_HTTP_Print_Number_Midi_OFF1(HTTP_CONN_HANDLE connHandle)
{
    char chaine[5];
    sprintf(chaine,"%d",MidiOFF1);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);    
}
void TCPIP_HTTP_Print_Number_Midi_OFF2(HTTP_CONN_HANDLE connHandle)
{
    char chaine[5];
    sprintf(chaine,"%d",MidiOFF2);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);      
}
    
void TCPIP_HTTP_Print_Number_Midi_OFF3(HTTP_CONN_HANDLE connHandle)
{
    char chaine[5];
    sprintf(chaine,"%d",MidiOFF3);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);      
}
void TCPIP_HTTP_Print_value_TOV(HTTP_CONN_HANDLE connHandle)
{
    char chaine[5];
    extern int Time_Over;
    sprintf(chaine,"%d",Time_Over);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);   
    
}
    
 

void TCPIP_HTTP_Print_ConfigCSV(HTTP_CONN_HANDLE connHandle)
{
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),FichierCSV);    
}

void TCPIP_HTTP_Print_TxtGainOut(HTTP_CONN_HANDLE connHandle)
{
    if((Out_Audio == 0)||(Out_Audio == 1))//Studio ou Master
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"Gain"); 
    }
    else   
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"Max Gain");    
    }
} 

void TCPIP_HTTP_Print_CacheModeUsine(HTTP_CONN_HANDLE connHandle)
{
    //cache les sauvegardes en Mode Usine
    if(Config_Used == 0)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"hidden"); 
    }
    else
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle)," "); 
    }
    
}

void TCPIP_HTTP_Print_hiddenReduction(HTTP_CONN_HANDLE connHandle)
{
    if((In_Audio == 0)||(In_Audio == 1))
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),""); 
    }
    else
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"hidden"); 
    }    
}
void TCPIP_HTTP_Print_ReduSelect(HTTP_CONN_HANDLE connHandle,uint16_t num)
{
    if(num == Nconfig[Config_Used].Device_IN[In_Audio].ReductionMax/1.25)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"selected");
    }      
}

void TCPIP_HTTP_Print_value_Overload1(HTTP_CONN_HANDLE connHandle)
{
    char chaine[20];

    sprintf(chaine,"%.0f", Nconfig[Config_Used].Device_IN[0].Niveau_Overload);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);
}
void TCPIP_HTTP_Print_Detection_Muting1(HTTP_CONN_HANDLE connHandle)
{
    char chaine[20];
    
    sprintf(chaine,"%.0f", Nconfig[Config_Used].Device_IN[0].Niveau_Stop_Overload);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);    
}
void TCPIP_HTTP_Print_Time_Muting1(HTTP_CONN_HANDLE connHandle)
{
    char chaine[20];
    
    sprintf(chaine,"%d", Nconfig[Config_Used].Device_IN[0].Time_Mute);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);        
}
    
    
void TCPIP_HTTP_Print_value_Overload2(HTTP_CONN_HANDLE connHandle)
{
    char chaine[20];

    sprintf(chaine,"%.0f", Nconfig[Config_Used].Device_IN[1].Niveau_Overload);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);
}
void TCPIP_HTTP_Print_Detection_Muting2(HTTP_CONN_HANDLE connHandle)
{
    char chaine[20];
    
    sprintf(chaine,"%.0f", Nconfig[Config_Used].Device_IN[1].Niveau_Stop_Overload);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);    
}
void TCPIP_HTTP_Print_Time_Muting2(HTTP_CONN_HANDLE connHandle)
{
    char chaine[20];
    
    sprintf(chaine,"%d", Nconfig[Config_Used].Device_IN[1].Time_Mute);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);        
}

    
void TCPIP_HTTP_Print_cacheMiddle(HTTP_CONN_HANDLE connHandle)
{
    if(In_Audio < 2)
    {
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),"hidden");  
    }    
}

void TCPIP_HTTP_Print_ValueReduction(HTTP_CONN_HANDLE connHandle)
{
    char chaine[10];
    if(In_Audio < 2)
    {
        sprintf(chaine,"%.0f",Nconfig[Config_Used].Device_IN[In_Audio].ReductionMax);


        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);
    }
}

void TCPIP_HTTP_Print_footer(HTTP_CONN_HANDLE connHandle)
{
    char chaine[250];
    sprintf(chaine,"<div class=\"spacer\">&nbsp;</div><left> %s <div id=\"footer\">Swoxtelecom Copyright &copy </div></div></div></div></div></div></body></html>",VERSION_PROG);
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle),chaine);
}
    
#endif

