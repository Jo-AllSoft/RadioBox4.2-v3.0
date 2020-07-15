/*******************************************************************************
  File Name:
    app.c

  Summary:


  Description:

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
#include "app.h"

#include "FT_GPU.h"


#include "math.h"
#include "sntp.h"
#include "time.h"
#include "peripheral\I2C\plib_i2c.h"
#include "Mc32SpiUtil.h"
#include "peripheral/spi/plib_spi.h"
#include "peripheral/usart/plib_usart.h"

#include "Mc32DriverAdc.h"

#include "tcpip/icmp.h"
#include "Mux_gestSpiFT800.h"
#include "Audio_PT2314.h"
#include "Expender_i2c_TCA9548A.h"
#include "ADC_DAC_AD5593.h"
#include "Fct_Ecran.h"
#include "EEPROM_Driver.h"


double APP_MoyGliTemp(double ValEch);
int APP_MoyGli(int n, int PrevMoy, int ValEch);
void calculGainTDA(int Somm_Volume, int Audio);
void calculGainPT(float Somm_Volume, int Audio);

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
int Overload_Ligne[2];
bool ClickNext[2] = {0,0};
int Cpt_Affichage_Overload[2];
float ReducteurGain[2] = {0,0};

int Config_UsartON = 0;
int Config_UsartOFF = 0;

int N_Midi = 1;

// PIC
char Save_Adresse_IP[17];
char Save_Mask_IP[17];
char Save_Gateway_IP[17];
char Save_DNS_IP[17];
char Save_NTP1[25];

char User_x[40];
char Pass_x[40];
char unique_name[50];
char SNMP_msg[50];
// Permet d'éviter la config par défaut lors de redemmarage software par bouton
int Reset_Software; 
int Stop_Boot;

int Mode_Calibration = 0;//Permet de se mettre en mode calibration.
int Time_Over = 1;
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
APP_DATA appData;
DRV_I2C_BUFFER_EVENT i2cOpStatus;
static const bool s_app_wifi = false;

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary local functions.
*/

#if defined(TCPIP_IF_MRF24W) || defined(TCPIP_IF_MRF24WN)
extern void APP_WIFI_Initialize(void);
extern void APP_WIFI_Tasks(void);
#else /* !defined(TCPIP_IF_MRF24W) && !defined(TCPIP_IF_MRF24WN) */
#define APP_WIFI_Initialize() do { } while (0)
#define APP_WIFI_Tasks() do { } while (0)
#endif /* defined(TCPIP_IF_MRF24W) || defined(TCPIP_IF_MRF24WN) */

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
    if(s_app_wifi)
        APP_WIFI_Initialize();

    /* Place the application state machine in its initial state. */
    appData.state = APP_MOUNT_DISK;
    appData.state2 = APP_STATE2_INIT;
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    // <editor-fold defaultstate="collapsed" desc="Gestion Ethernet">    
    SYS_STATUS          tcpipStat;
    TCPIP_NET_HANDLE    netH;
    int                 nNets;
    static IPV4_ADDR    dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;
    int                 i;
    const char          *netName, *netBiosName;
    static uint32_t     startTick = 0;

    if(s_app_wifi) {
        APP_WIFI_Tasks();
        return;
    }

    switch(appData.state)
    {
        case APP_MOUNT_DISK:
            if(SYS_FS_Mount(SYS_FS_NVM_VOL, LOCAL_WEBSITE_PATH_FS, MPFS2, 0, NULL) == 0)
            {
                SYS_CONSOLE_PRINT("SYS_Initialize: The %s File System is mounted\r\n", SYS_FS_MPFS_STRING);
                appData.state = APP_TCPIP_WAIT_INIT;
            }
            else
            {
                //SYS_CONSOLE_PRINT("SYS_Initialize: Mount the %s File System, pending\r\n", SYS_FS_MPFS_STRING);
            }
            break;

        case APP_TCPIP_WAIT_INIT:
            tcpipStat = TCPIP_STACK_Status(sysObj.tcpip);
            if(tcpipStat < 0)
            {   // some error occurred
                SYS_CONSOLE_MESSAGE("APP: TCP/IP stack initialization failed!\r\n");
                appData.state = APP_TCPIP_ERROR;
            }
            else if(tcpipStat == SYS_STATUS_READY)
            {
                // now that the stack is ready we can check the
                // available interfaces and register
                // a Bonjour service

                nNets = TCPIP_STACK_NumberOfNetworksGet();

                for(i = 0; i < nNets; i++)
                {
                    netH = TCPIP_STACK_IndexToNet(i);
                    netName = TCPIP_STACK_NetNameGet(netH);
                    netBiosName = TCPIP_STACK_NetBIOSName(netH);

#if defined(TCPIP_STACK_USE_NBNS)
                    SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS enabled\r\n", netName, netBiosName);
#else
                    SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS disabled\r\n", netName, netBiosName);
#endif // defined(TCPIP_STACK_USE_NBNS)

#if defined(TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
                    // base name of the service Must not exceed 16 bytes long
                    // the last digit will be incremented by interface
                    char mDNSServiceName[] = "MyWebServiceNameX "; 

                    mDNSServiceName[sizeof(mDNSServiceName) - 2] = '1' + i;
                    TCPIP_MDNS_ServiceRegister(netH
                            , mDNSServiceName                     // name of the service
                            ,"_http._tcp.local"                   // type of the service
                            ,80                                   // TCP or UDP port, at which this service is available
                            ,((const uint8_t *)"path=/index.htm") // TXT info
                            ,1                                    // auto rename the service when if needed
                            ,NULL                                 // no callback function
                            ,NULL);                               // no application context
#endif // defined(TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
                }

                appData.state = APP_TCPIP_TRANSACT;
            }

            break;

        case APP_TCPIP_TRANSACT:

            if(SYS_TMR_TickCountGet() - startTick >= SYS_TMR_TickCounterFrequencyGet()/2ul)
            {
                startTick = SYS_TMR_TickCountGet();
            }

            // if the IP address of an interface has changed
            // display the new value on the system console
            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for(i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if(dwLastIP[i].Val != ipAddr.Val)
                {
                    dwLastIP[i].Val = ipAddr.Val;
                    SYS_CONSOLE_PRINT("%s IP Address: %d.%d.%d.%d \r\n",
                            TCPIP_STACK_NetNameGet(netH),
                            ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                }
            }

            SYS_CMD_READY_TO_READ();

            break;

        default:
            break;
    }
    // </editor-fold>
    
    
    
    switch ( appData.state2)
    {
        // <editor-fold defaultstate="collapsed" desc="Initialisation"> 
         case APP_STATE2_INIT:

            WDTCONbits.WDTCLR = 1;
            delay_ms(100);
            // I2C
            I2C_AD5593_Init_Buffer();
            int i;
            for(i=0; i < 6;i++)// audio IN
            {
                    I2C_PT_Volume(Select_Input(i),  Nconfig[Config_Used].Device_IN[i].Volume);
                    I2C_PT_Speak_Att(Select_Input(i),Nconfig[Config_Used].Device_IN[i].L,LEFT );
                    I2C_PT_Speak_Att(Select_Input(i), Nconfig[Config_Used].Device_IN[i].R,RIGHT);
                    I2C_PT_AudioSwitch(Select_Input(i),  Nconfig[Config_Used].Device_IN[i].Gain,0,Stereo1);
                    I2C_PT_BASS_TREBLE(Select_Input(i), Nconfig[Config_Used].Device_IN[i].Basse,PT_BASS);
                    I2C_PT_BASS_TREBLE(Select_Input(i), Nconfig[Config_Used].Device_IN[i].Aigue,PT_TREBLE);         
                    I2C_PT_BASS_TREBLE(Select_Input(i), Nconfig[Config_Used].Device_IN[i].Middle,TDA_MIDDLE);
                   
            }
            
            for(i=0; i < 7;i++)
            {
                //I2C_PT_Volume(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Volume);
                I2C_PT_Speak_Att(Select_Output(i),Nconfig[Config_Used].Device_OUT[i].L,LEFT );
                I2C_PT_Speak_Att(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].R,RIGHT);
                I2C_PT_AudioSwitch(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Gain,0,Stereo1);
                I2C_PT_BASS_TREBLE(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Basse,PT_BASS);
                I2C_PT_BASS_TREBLE(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Aigue,PT_TREBLE);
            }
            
            appData.drvI2CHandle_Master = DRV_I2C_Open(DRV_I2C_INDEX_0, DRV_IO_INTENT_READWRITE);
            
            /* event-handler set up receive callback from DRV_I2C_Tasks */
            DRV_I2C_BufferEventHandlerSet(appData.drvI2CHandle_Master, I2CMasterOpStatusCb, i2cOpStatus );
            // /I2C
            change_ecran(0);
            Init_Ecran();
            
            cmd(CMD_DLSTART);
            cmd_gradient(0,0,0x66CCFF, 0, 240, 0xFFFFFF);
            cmd(COLOR_RGB(0,0,0));
            cmd_text(30,60,31,0,"Swoxtelecom");
            
            cmd(DISPLAY());                     // Affichage sur l'écran
            cmd(CMD_SWAP);
            cmd_exec();
            cmd_wait();
            
            for(i =0;i< 6;i++)//Lecture Calibration 1eme ecran
            {
                wr32(REG_TOUCH_TRANSFORM_A+4*i,Valeur_Calibration[i].Calibration_32);                      
            }
            
            
            change_ecran(1);
            Init2_Ecran();
            cmd(CMD_DLSTART);
            cmd_gradient(0,0,0x66CCFF, 0, 240, 0xFFFFFF);
            cmd(COLOR_RGB(0,0,0));
            cmd_text(30,60,31,0,"Swoxtelecom");          
           

           
            cmd(DISPLAY());                     // Affichage sur l'écran
            cmd(CMD_SWAP);
            cmd_exec();
            cmd_wait2();

            for(i =0;i< 6;i++)//Lecture Calibration 2eme ecran
            {
                wr32(REG_TOUCH_TRANSFORM_A+4*i,Valeur_Calibration2[i].Calibration_32);                      
            }
                    
            

            Fct_Bar_Init(0,1000,500,6500,500);
            Fct_Bar_Init(1,1000,1500,6500,500);

            
            Fct_BTN_Init(1,0xFF0000,0x00FF00,0x000000,16,25,448,100,25,"ALL MUTE");
            Fct_BTN_Init(2,0xFF0000,0x00FF00,0x000000,16,160,100,100,23,"Mute");
            Fct_BTN_Init(3,0xFF0000,0x00FF00,0x000000,132,160,100,100,23,"Mute");
            Fct_BTN_Init(4,0xFF0000,0x00FF00,0x000000,248,160,100,100,23,"Mute");
            Fct_BTN_Init(5,0xFF0000,0x00FF00,0x000000,364,160,100,100,23,"Mute");

            Fct_BTN_Init(6,0xFF0000,0x00FF00,0x000000,16,160,100,100,23,"Start");
            Fct_BTN_Init(7,0xFF0000,0x00FF00,0x000000,132,160,100,100,23,"Start");
            
            for(i=1; i<= 7;i++)
            {
                Mem_BTN[i] = 1;//met les valeur a 0 des bouton pour eviter de presser 2 fois a la premiere utilisation
            }
            Mem_BTN[1] = 1;//test depar ON

            
            
            Reset_Software = 1;
            EEPROM_SaveData(&Reset_Software);
            
            Load_Image();
            APP_UpdateState2(APP_STATE2_WAIT);


         break;
         
        // </editor-fold>

         case APP_STATE2_WAIT:
            //Ne fait rien

         break; 

         case APP_STATE2_EXEC:
         {
            WDTCONbits.WDTCLR = 1; //remet a zero le WTDPS a 0
            
            statementTask();
/******************************   Gestion I2C *********************************/       
            const int Seuil_Fader = 50, Hyst = 5;//hyst = hystérèse
            static int schmidt[6];
            static double Valeur_DAC_OUT[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
            
            static int Valeur_Fader[6];
            static const SONG_INPUT_ADC Port_Song_IN[]={SONG_MICRO1_ADC,SONG_MICRO2_ADC,SONG_MICRO3_ADC,SONG_MICRO4_ADC,SONG_LIGNE1_ADC,SONG_LIGNE2_ADC};  
            static const SONG_INPUT_DAC Port_Song_OUT[]={SONG_MICRO1_DAC,SONG_MICRO2_DAC,SONG_MICRO3_DAC,SONG_MICRO4_DAC,SONG_LIGNE1_DAC,SONG_LIGNE2_DAC};
            extern int Max_Fader;
            extern int Min_Fader;
            extern int Fader_OFF;
            static float PT_Muting = -78.75;
            static float TDA_Muting = -56;
            for(i=0; i<6 ;i++)
            {  
                Valeur_DAC_OUT[i] = 0xFFF - I2C_Read_Buffer(AD_FADERS_IN,Port_Song_IN[i]);
                Valeur_Fader[i] = I2C_Read_Buffer(AD_FADERS_IN,Port_Song_IN[i]);
                Valeur_DAC_OUT[i] = (Valeur_DAC_OUT[i]*3300)/4095;
                
                Valeur_DAC_OUT[i] = (((Min_Fader-Max_Fader)/3300.)*Valeur_DAC_OUT[i])+Max_Fader;
                Valeur_DAC_OUT[i] = (Valeur_DAC_OUT[i]*4095)/5000;
            }
          
            static int i = 0;
            static const SONG_OUTPUT Port_Song_OUT_PT[]={SONG_STUDIO,SONG_MASTER,SONG_PHONE1,SONG_PHONE2,SONG_PHONE3,SONG_PHONE4,SONG_PHONEDJ};  
            static float Valeur_Volume_IN[7];
            static float Volume_IN[7];
            static float Volume_IN_Old[7];
            static float Hyst_Volume_IN[7] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
            static float Volume_IN_Check[7];
            static float Volume_IN_Change_Check[7];
            static bool Muting_PT[6];
            extern int Statut_Mode;
            int Max_Valeur;
            float Max_Attenuation;
            int N_Div;
            int N_Soustraction;
            for(i=0; i<7; i++)
            {

                
                if(i == 0)//Studio
                {
                    Max_Valeur = 42;
                    Max_Attenuation = -52.50;
                    N_Div = 95;
                    N_Soustraction = 11;
                }
                else //Phone & Master
                {
                    Max_Valeur = 72;
                    Max_Attenuation = -78.75;
                    N_Div = 56;
                    N_Soustraction = 8;   
                }
                Volume_IN_Check[i] = I2C_Read_Buffer(AD_POTROT_IN,Port_Song_OUT_PT[i]);

                
                Valeur_Volume_IN[i] = (I2C_Read_Buffer(AD_POTROT_IN,Port_Song_OUT_PT[i]));//Volume valeur AD 12bit             
                Valeur_Volume_IN[i] = (int)((Valeur_Volume_IN[i] - N_Soustraction) / N_Div);//Volume valeur AD 0 a 73 ou 0 a 43

                
                if((Valeur_Volume_IN[i] - Hyst_Volume_IN[i]  > Volume_IN_Old[i])||(Valeur_Volume_IN[i] == Max_Valeur))
                { 
                    Volume_IN[i] = (Valeur_Volume_IN[i] * 1.25) + Max_Attenuation;
                    Volume_IN_Old[i] = Valeur_Volume_IN[i]; 
                    Hyst_Volume_IN[i] = -1;
                }
                if((Valeur_Volume_IN[i] + Hyst_Volume_IN[i]  <  Volume_IN_Old[i])||(Valeur_Volume_IN[i] == 0))
                {
                    Volume_IN[i] = (Valeur_Volume_IN[i] * 1.25) + Max_Attenuation;
                    Volume_IN_Old[i] = Valeur_Volume_IN[i];
                    Hyst_Volume_IN[i] = +1;
                }

                if((Statut_Mode == MODE_ON_AIR)&&(i == 0))
                {
                    I2C_PT_Volume(Select_Output(i),Nconfig[Config_Used].Device_OUT[i].Volume);
                    I2C_PT_AudioSwitch(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Gain,0,Stereo1);
                }
                else if((Nconfig[Config_Used].Master_Gain == GAIN_WEB_ACTIF )&&(i == 1))
                {
                    I2C_PT_Volume(Select_Output(i),Nconfig[Config_Used].Device_OUT[i].Volume);
                    I2C_PT_AudioSwitch(Select_Output(i), Nconfig[Config_Used].Device_OUT[i].Gain,0,Stereo1);
                }
                else
                {
                    float Gain;
                    if((Volume_IN[i] > Nconfig[Config_Used].Device_OUT[i].Volume+ Nconfig[Config_Used].Device_OUT[i].Gain)&&(i > 1))//Ajout de l'ouput Max
                    {
                        Volume_IN[i] = Nconfig[Config_Used].Device_OUT[i].Volume +Nconfig[Config_Used].Device_OUT[i].Gain;
                    }
                    
                    if((Volume_IN[i] > 0)&&(Volume_IN[i] <= 3.75))
                    {
                        Gain = 3.75;            
                    }
                    else if((Volume_IN[i] > 3.75)&&(Volume_IN[i] <= 7.5))
                    {
                        Gain = 7.5;               
                    }
                    else if((Volume_IN[i] > 7.5)&&(Volume_IN[i] <= 11.25))
                    {
                        Gain = 11.25;               
                    }
                    else if(Volume_IN[i] <= 0)
                    {
                        Gain = 0;
                    }
       
                    if((Volume_IN[i] > Volume_IN_Old[i])||(Volume_IN[i] < Volume_IN_Old[i]))
                    {
                        I2C_PT_AudioSwitch(Select_Output(i), Gain,0,Stereo1);
                        if(Volume_IN[i] == Max_Attenuation)
                        {
                             I2C_PT_Volume(Select_Output(i),-78.75);
                        }
                        else
                        {
                            I2C_PT_Volume(Select_Output(i),Volume_IN[i] - Gain);
                        }
                    }
                }               
            }

            change_ecran(0);                      
            cmd(CMD_DLSTART);                   // Effacement de l'écran
            cmd(CLEAR_COLOR_RGB(0,0,0));
            cmd(CLEAR(1,1,1));   

            for(i=0; i<4 ;i++)
            {  
                cmd(COLOR_RGB(0,0,0));
                
                if(Mem_BTN[1] == 0 || Mem_BTN[2] == 0 || Mem_BTN[3] == 0 || Mem_BTN[4] == 0 || Mem_BTN[5] == 0)
                {
                    Affichage_BTN(i+2,TOGGLE);
                    if((Mem_BTN[2] == 0 || Valeur_Fader[0] < Seuil_Fader)&&(Mem_BTN[3] == 0|| Valeur_Fader[1] < Seuil_Fader)&&(Mem_BTN[4] == 0|| Valeur_Fader[2] < Seuil_Fader)&&(Mem_BTN[5] == 0|| Valeur_Fader[3] < Seuil_Fader))
                    {
                        Change_Text_BTN(1,"ALL MUTE");
                        Change_Color_ON_BTN(1,0x00FF00);
                        Change_Color_OFF_BTN(1,0x00FF00);
                        Change_Text_BTN(i+2,"MUTE");
                        Affichage_BTN(i+2,MODE_OFF);
                        Mem_BTN[i+2] = 0;
                        I2C_Write_Buffer(AD_PT_OUT,Port_Song_OUT[i],Fader_OFF);
                        ON_AIR(0);
                        Statut_Mode = MODE_MUTE;
                        if( Muting_PT[i] == 1)
                        {
                            I2C_PT_Volume(Select_Input(i+2),TDA_Muting);
                            Muting_PT[i] = 0;                       
                        }
                        
                    }
                    else
                    {                            
                        Change_Text_BTN(1,"ON-AIR");                            
                        Change_Color_ON_BTN(1,0xFF0000);
                        Change_Color_OFF_BTN(1,0xFF0000);
                        ON_AIR(1);
                        Statut_Mode = MODE_ON_AIR;

                        if((Mem_BTN[i+2] == 0)||(Valeur_Fader[i] < Seuil_Fader))
                        {                                   
                            Change_Text_BTN(i+2,"MUTE");
                            Mem_BTN[i+2] = 0;
                            Affichage_BTN(i+2,MODE_OFF);
                            I2C_Write_Buffer(AD_PT_OUT,Port_Song_OUT[i],Fader_OFF);
                            if( Muting_PT[i] == 1)
                            {
                                I2C_PT_Volume(Select_Input(i+2),TDA_Muting);
                                Muting_PT[i] = 0;
                            }
                        }
                        else
                        {
                            Change_Text_BTN(i+2,"ON-AIR"); 
                            Affichage_BTN(i+2,MODE_ON);
                            I2C_Write_Buffer(AD_PT_OUT,Port_Song_OUT[i],(int)Valeur_DAC_OUT[i]);
                            if( Muting_PT[i] == 0)
                            {
                                I2C_PT_Volume(Select_Input(i+2),Nconfig[Config_Used].Device_IN[i].Volume);
                                Muting_PT[i] = 1;
                            }
                        }

                    }                       
                }
                else
                {      
                    static int allOff;
                    Affichage_BTN(i+2,TOGGLE);
                    if((Valeur_Fader[0] < Seuil_Fader+schmidt[0])&&(Valeur_Fader[1] < Seuil_Fader+schmidt[1])&&(Valeur_Fader[2] < Seuil_Fader+schmidt[2])&&(Valeur_Fader[3] < Seuil_Fader+schmidt[3]))
                    {
                        schmidt[0] = Hyst;
                        schmidt[1] = Hyst;
                        schmidt[2] = Hyst;
                        schmidt[3] = Hyst;
                        Affichage_BTN(i+2,MODE_OFF);
                        Change_Color_OFF_BTN(1,0x00FF00);
                        Change_Color_ON_BTN(1,0x00FF00);
                        Change_Text_BTN(i+2,"MUTE");
                        Change_Text_BTN(1,"ALL OFF");
                        I2C_Write_Buffer(AD_PT_OUT,Port_Song_OUT[i],Fader_OFF);
                        Statut_Mode = MODE_MUTE;
                        ON_AIR(0);
                        if( Muting_PT[i] == 1)
                        {
                            I2C_PT_Volume(Select_Input(i+2),TDA_Muting);
                            Muting_PT[i] = 0;
                        }
                    }
                    else if(Mem_BTN[i+2] != 0)
                    {

                        Change_Color_OFF_BTN(1,0x00FF00);
                        Change_Color_ON_BTN(1,0xFF0000);
                        Change_Text_BTN(1,"ON-AIR");
                        ON_AIR(1);
                        Statut_Mode = MODE_ON_AIR;

                        if(Valeur_Fader[i] < (Seuil_Fader+schmidt[i]))
                        {
                            schmidt[i] = Hyst;
                            Affichage_BTN(i+2,MODE_OFF);
                            Change_Text_BTN(i+2,"MUTE");
                            I2C_Write_Buffer(AD_PT_OUT,Port_Song_OUT[i],Fader_OFF);
                            if( Muting_PT[i] == 1)
                            {
                                I2C_PT_Volume(Select_Input(i+2),TDA_Muting);
                                Muting_PT[i] = 0;
                            }
                        }
                        else
                        {
                            Affichage_BTN(i+2,TOGGLE); 
                            schmidt[i] = -Hyst;
                            Change_Text_BTN(i+2,"ON-AIR");
                            I2C_Write_Buffer(AD_PT_OUT,Port_Song_OUT[i],(int)Valeur_DAC_OUT[i]);
                            if( Muting_PT[i] == 0)
                            {
                                I2C_PT_Volume(Select_Input(i+2),Nconfig[Config_Used].Device_IN[i].Volume);
                                Muting_PT[i] = 1;
                            }
                        }                       
                    }
                }
            }
            Affichage_BTN(1,TOGGLE);
            static int Rebond_BTN = 0;
            if((Mem_BTN[1] == 0)&&(Rebond_BTN == 0))//remet tout en Mode Mute
            {
                for(i=2;i<2+4;i++)
                {
                    Mem_BTN[i] = 0;
                    Change_Text_BTN(i,"MUTE");
                }
                Rebond_BTN = 1;
            }
            if((Mem_BTN[1] == 1)&&(Rebond_BTN == 1))
            {
                for(i=2;i<2+4;i++)
                {
                    Mem_BTN[i] = 1;
                    Change_Text_BTN(i,"ON-AIR");
                }
                Rebond_BTN = 0;
            }

            cmd(DISPLAY());                     // Affichage sur l'écran
            cmd(CMD_SWAP);
            cmd_exec();
            cmd_wait();

            //deuxieme ecran
            change_ecran(1);
            cmd(CMD_DLSTART);                   // Effacement de l'écran
            cmd(CLEAR_COLOR_RGB(0,0,0));
            cmd(CLEAR(1,1,1));
                                
            cmd(BITMAP_HANDLE(0));
            cmd(BITMAP_SOURCE(RAM_G+20280));
            cmd(BITMAP_LAYOUT(ARGB1555, 418, 39));
            cmd(BITMAP_SIZE(NEAREST, BORDER, BORDER, 209, 39));
                            
            cmd(BITMAP_HANDLE(1));
            cmd(BITMAP_SOURCE(RAM_G+20280+16302));
            cmd(BITMAP_LAYOUT(ARGB1555, 90, 45));
            cmd(BITMAP_SIZE(NEAREST, BORDER, BORDER, 45, 45));
            
            cmd(BITMAP_HANDLE(2));
            cmd(BITMAP_SOURCE(RAM_G+20280+16302+4050));
            cmd(BITMAP_LAYOUT(ARGB1555, 108, 48));
            cmd(BITMAP_SIZE(NEAREST, BORDER, BORDER, 54, 48));
            
            cmd(BEGIN(BITMAPS));
            
            cmd(VERTEX2II(255, 175, 0, 0));//affiche Logo RADIOBOX

            cmd(END());
            

            cmd(COLOR_RGB(255,255,255));
            cmd_text(25,31,25,0,"L");           
            cmd_text(25,93,25,0,"R");
            
            static int Valeur_L = 0;
            static int Valeur_R = 0;


            Valeur_R = I2C_Read_Buffer(AD_ON_AIR,0);
            Valeur_L = I2C_Read_Buffer(AD_ON_AIR,1);
            Fct_Bar(0,(Valeur_L*100)/184);//1V bar graphe au max ==> 4095/5 =819
            Fct_Bar(1,(Valeur_R*100)/184);//1V bar graphe au max ==> 4095/5 =819

            extern char Midi1;
            extern char Midi2;
            extern char Midi3;

            extern char MidiOFF1;
            extern char MidiOFF2;
            extern char MidiOFF3;

            for(i=6; i<=7;i++)
            {     
                extern APP_DATA_USART appDataUart;
                
                extern char Table_Midi[];
                extern int Ok_Send;
                static int OneX[2];
                int Mode_Son = 0;

                if(Valeur_Fader[i-2] < Seuil_Fader+schmidt[i-2])
                {
                    schmidt[i-2] = Hyst;
                    Change_Text_BTN(i,"Stop");
                    Affichage_BTN(i,MODE_OFF);
                    ReducteurGain[i-6] = 0;

                    I2C_Write_Buffer(AD_PT_OUT,Port_Song_OUT[i-2],Fader_OFF);
                    if(Muting_PT[i-1] == 0)
                    {
                        Muting_PT[i-1] = 1;
                        I2C_PT_Volume(Select_Input(i-6),TDA_Muting);
                    }
                    if(OneX[i-6] == 1)//Pour envoyer une seul fois
                    {
//                        if(i==6)
//                        {
//                            Ok_Send = 1;
//
//                            Table_Midi[0]=MidiOFF1;//envoie MIDI OFF
//                            Table_Midi[1]=MidiOFF2; 
//                            Table_Midi[2]=MidiOFF3; 
//
//                            N_Midi = 1;
//                            Config_UsartOFF = 1;
//                            appDataUart.currentState = APP_DRV_OPEN;
//                        }
                        OneX[i-6] = 0;//
                    }
                    else
                    {
                        if(Config_UsartOFF == 1)
                        {
                            appDataUart.usrMsgIndex = 0;
                            appDataUart.currentState = APP_DRV_MSG_WRITE;     
                            Config_UsartOFF = 0;
                        }                                                       
                    }
                    
                }
                else
                {
                    static int Time_next[2];
                    
                    OneX[i-6] = 1;
                    if((Affichage_BTN(i,ONE_CLICK) == 1)&&(Time_next[i-6] < 50))
                    {
                        Time_next[i-6] = 60;//maintien 3s le bouton rouge apres avoir ete relache
                        ClickNext[i-6] = 1;//detect un click pour stopper la reduction

                        if(i==6)
                        {     
                            Ok_Send = 1;
                            
                            Table_Midi[0]=Midi1;//envoie MIDI ON
                            Table_Midi[1]=Midi2; 
                            Table_Midi[2]=Midi3;  

                            N_Midi = 1;
                            
                            appDataUart.currentState = APP_MIDI_OPEN; 
                        }
                              
                         

                        
                    }
                    else
                    {
                        if(Config_UsartON == 1)
                        {
                            appDataUart.usrMsgIndex = 0;
                            appDataUart.currentState = APP_DRV_MSG_WRITE;     
                            Config_UsartON = 0;
                        }                                                       
                    }
                    if(Time_next[i-6] != 0)
                    {
                        schmidt[i-2] = -Hyst;
                        Change_Text_BTN(i,"ON-AIR"); 
                        Change_Color_ON_BTN(i,0xFF0000);                       
                        Time_next[i-6]--;
                    }
                    else
                    {
                        schmidt[i-2] = -Hyst;
                        Change_Text_BTN(i,"Next"); 
                        Change_Color_ON_BTN(i,0x0000FF);
                    }
                    Affichage_BTN(i,MODE_ON);
                    I2C_Write_Buffer(AD_PT_OUT,Port_Song_OUT[i-2],(int)Valeur_DAC_OUT[i-2]);
                    if( Muting_PT[i-1] == 1)
                    {
                        Muting_PT[i-1] = 0;
                        I2C_PT_Volume(Select_Input(i-6),Nconfig[Config_Used].Device_IN[i-6].Volume);
                    }

                }
            }
            static int Affiche_Phone[7];
            static float Volume_IN_Change[7];
            static int Cpt_Affiche;
            static int Hyts_Pot[7];
            int j;
            static char Txt_Phone[20];
            static bool Start_Pot = true;
            
            for(j=0; j<7;j++)
            {
                if((Volume_IN[j] != Volume_IN_Change_Check[j])&&(Start_Pot != true))
                {
                    Affiche_Phone[j] = j; 
                    Cpt_Affiche = 40;
                    Volume_IN_Change_Check[j]= Volume_IN[j];
                }
                else
                {
                    Affiche_Phone[j] = 10; 
                }
                
                if(Start_Pot == true)//pour ne pas afficher valeur Phones au demarrage
                {
//                    Volume_IN_Change_Check[j]= Volume_IN_Check[j];
                    Volume_IN_Change_Check[j]= Volume_IN[j];
                    if(j == 6)
                    {
                        Start_Pot = false;  
                    }
                }

                if(Affiche_Phone[j] != 10)
                {
                    char Txt_Limit[5];
                    if((Volume_IN[j] == Nconfig[Config_Used].Device_OUT[j].Volume+ Nconfig[Config_Used].Device_OUT[j].Gain)&&(j > 1))
                    {
                        sprintf(Txt_Limit,"max");                       
                    }
                    else
                    {
                        sprintf(Txt_Limit,"");   
                    }
                    switch(Affiche_Phone[j])
                    {
                        case 0:
                        {
                            if(Statut_Mode == MODE_ON_AIR)
                            {
//                                sprintf(Txt_Phone,"Studio: %0.0f dB",(Nconfig[Config_Used].Device_OUT[i].Volume));
                                sprintf(Txt_Phone,"Studio Fixe");
                            }
                            else
                            {
                                
                                sprintf(Txt_Phone,"Studio %0.0f%s",((100*(Volume_IN[j]+52.5))/52.5),Txt_Limit);
                            }
                                                       
                        }
                        break;
                        
                        case 1:
                        {
                            if(Nconfig[Config_Used].Master_Gain == GAIN_WEB_ACTIF)
                            {
                                sprintf(Txt_Phone,"Master Fixe");
                            }
                            else
                            {
                                sprintf(Txt_Phone,"Master %0.0f%s",((100*(Volume_IN[j]+78.75))/90),Txt_Limit);
                            }
                        }
                        break;
                        
                        case 2:
                        {

                            sprintf(Txt_Phone,"Phone 1 %0.0f%s",((100*(Volume_IN[j]+78.75))/90),Txt_Limit);
                        }
                        break;
                        
                        case 3:
                        {
                            sprintf(Txt_Phone,"Phone 2 %0.0f%s",((100*(Volume_IN[j]+78.75))/90),Txt_Limit);
                        }
                        break;
                        
                        case 4:
                        {
                            sprintf(Txt_Phone,"Phone 3 %0.0f%s",((100*(Volume_IN[j]+78.75))/90),Txt_Limit);
                        }
                        break;
                        
                        case 5:
                        {
                            
                            sprintf(Txt_Phone,"Phone 4 %0.0f%s",((100*(Volume_IN[j]+78.75))/90),Txt_Limit);
                        }
                        break;
                        
                        case 6:
                        {
                            sprintf(Txt_Phone,"Phone DJ %0.0f%s",((100*(Volume_IN[j]+78.75))/90),Txt_Limit);
                        }   
                        break;
                    }
                }
            }
            

            
            if(Cpt_Affiche > 0)
            {
                Cpt_Affiche--;
                cmd_fgcolor(0xFFFFFF);
                cmd_button(245, 174, 220, 52, 22, 0, "");
                cmd(COLOR_RGB(0,0,0));
                cmd_text(305, 190, 23, 0,Txt_Phone);
                cmd(COLOR_RGB(255,255,255));                      
                cmd(BEGIN(BITMAPS));
                cmd(VERTEX2II(255, 179, 1, 0));//affiche Image HANDLE 0           
                cmd(END());   
            }
            
            cmd(COLOR_RGB(255,0,0));

            char TxtAdj[20];
            sprintf(TxtAdj,"Adj%2.2f",ReducteurGain[0]);
            
            if(ReducteurGain[0] > 0)
            {
                if(ReducteurGain[0] >= Nconfig[Config_Used].Device_IN[0].ReductionMax)
                {
                    sprintf(TxtAdj,"%2.2f Max",ReducteurGain[0]);                       
                }
                else
                {
                    cmd(COLOR_RGB(255,153,0));
                    sprintf(TxtAdj,"%2.2f",ReducteurGain[0]);
                }
                cmd_text(16, 133, 23, 0,TxtAdj);
            }            
            if(ReducteurGain[1] > 0)
            {
                if(ReducteurGain[1] >= Nconfig[Config_Used].Device_IN[1].ReductionMax)
                {
                    sprintf(TxtAdj,"%2.2f Max",ReducteurGain[1]);
                }
                else
                {
                    cmd(COLOR_RGB(255,153,0));
                    sprintf(TxtAdj,"%2.2f",ReducteurGain[1]);
                }
                cmd_text(132, 133, 23, 0,TxtAdj);
            }

            /*********************************/
            
            // <editor-fold defaultstate="collapsed" desc="Affichage IP et Version"> 
            static char Adresse_IP[25];
            sprintf(Adresse_IP, "IP : %d.%d.%d.%d", ipAddr.v[0],ipAddr.v[1],ipAddr.v[2],ipAddr.v[3]);                     
            cmd(COLOR_RGB(255,255,255)); //Utilisation d'une ancre noire pour tout les prochain textes
            
            cmd_text(245,240,21,0,Adresse_IP);
            cmd_text(395, 240, 21, 0, VERSION_PROG);
            
            
            
            
            // </editor-fold>

          

            cmd(DISPLAY());                     // Affichage sur l'écran
            cmd(CMD_SWAP);
            cmd_exec();
            cmd_wait2();

            
            
            
            APP_UpdateState2(APP_STATE2_WAIT);  
         }break; 
         
         case APP_STATE2_Calibration:
         {
            
            Mode_Calibration = 0;
            
            change_ecran(0);      
            cmd(CMD_DLSTART);
            cmd(CLEAR_COLOR_RGB(0,0,0));
            cmd(CLEAR(1,1,1));
            cmd_gradient(0,0,0xAD5593, 0, 240, 0xFFFFFF);
            cmd(COLOR_RGB(0,0,0));
            cmd_text(30,60,31,0,"Calibration Touch point");            
            cmd_calibrate(); 
            cmd(DISPLAY());                     // Affichage sur l'écran
            cmd(CMD_SWAP);
            cmd_exec();
            
            
            
            
            cmd_offset=rd16(REG_CMD_WRITE);
            while(rd16(REG_CMD_READ) != cmd_offset)
            {
                WDTCONbits.WDTCLR = 1; //remet a zero le WTDPS(Watch dog) a 0 pendant la ca calibration
            }
            for(i = 0; i< 6; i++)
            {                  
                Valeur_Calibration[i].Calibration_32 = rd32(REG_TOUCH_TRANSFORM_A+4*i); 
            }
            EEPROM_SaveData(Valeur_Calibration);
                

            change_ecran(1);
  
            cmd(CMD_DLSTART);
            cmd(CLEAR_COLOR_RGB(0,0,0));
            cmd(CLEAR(1,1,1));
            cmd_gradient(0,0,0xAD5593, 0, 240, 0xFFFFFF);
            cmd(COLOR_RGB(0,0,0));
            cmd_text(30,60,31,0,"Calibration Touch point");
            cmd_calibrate2();
            cmd(DISPLAY());                     // Affichage sur l'écran
            cmd(CMD_SWAP);
            cmd_exec();
            
            
            cmd_offset=rd16(REG_CMD_WRITE);
            while(rd16(REG_CMD_READ) != cmd_offset)
            {
                WDTCONbits.WDTCLR = 1; //remet a zero le WTDPS(Watch dog) a 0 pendant la ca calibration              
            }

            for(i = 0; i< 6; i++)
            {                  
                Valeur_Calibration2[i].Calibration_32 = rd32(REG_TOUCH_TRANSFORM_A+4*i); 
            }
            EEPROM_SaveData(Valeur_Calibration2);
                    
         }
         break;
         
    }
    APP_Write_Tasks();  // Gestion de l'I2C
}
void APP_UpdateState2 ( APP_STATES2 NewState )
{
    appData.state2 = NewState;
}
void APP_UpdateState ( APP_STATE NewState )
{
    appData.state = NewState;
}

/*******************************************************************************
 End of File
 */



int APP_MoyGli(int n, int PrevMoy, int ValEch)
{
    int Moy;
    Moy = ((n-1) *PrevMoy + ValEch)/n ;

    return Moy;
}

void Gestion_Line(void)
{
    extern float Niveau_Overload;
    extern float Niveau_Stop_Overload;
    Overload_Ligne[0] = APP_MoyGli(1,Overload_Ligne[0],I2C_Read_Buffer(AD_PT_OUT,1));
    Overload_Ligne[1] = APP_MoyGli(1,Overload_Ligne[1],I2C_Read_Buffer(AD_PT_OUT,3));
    int i;
    for(i=0;i<2;i++)
    {
        float Volume_Reduction = 0;
        float NOverload = 0.0;
        NOverload = (Nconfig[Config_Used].Device_IN[i].Niveau_Overload *1000)/1220.703;
        if(Overload_Ligne[i] > NOverload)//0.2V
        {
            
            ReducteurGain[i] = ReducteurGain[i]+1;
            if(ReducteurGain[i] > Nconfig[Config_Used].Device_IN[i].ReductionMax)
            {
                ReducteurGain[i] = Nconfig[Config_Used].Device_IN[i].ReductionMax;
                Cpt_Affichage_Overload[i] = 1;
            }
            Volume_Reduction = (Nconfig[Config_Used].Device_IN[i].Volume) - (ReducteurGain[i]);
            I2C_PT_Volume(Select_Input(i),Volume_Reduction);
        }
        
        static float NSO = 0.0;
        NSO = (Nconfig[Config_Used].Device_IN[i].Niveau_Stop_Overload *1000)/1220.703;

        static int Cpt_ReductionGain[2] = {0,0};//Detection changement de titre
        if((Overload_Ligne[i] <= NSO)&&(ClickNext[i] == 1))//0.2V
        {
            Cpt_ReductionGain[i]++;
            if(Cpt_ReductionGain[i] >= Nconfig[Config_Used].Device_IN[i].Time_Mute/ 10)
            {
                ReducteurGain[i] = 0;
                ClickNext[i] = 0;
                Volume_Reduction = (Nconfig[Config_Used].Device_IN[i].Volume) - ReducteurGain[i];
                I2C_PT_Volume(Select_Input(i),Volume_Reduction);
            }
        }
        else
        {
            Cpt_ReductionGain[i] = 0;
        }

    }    
}

 void calculGainTDA(int Somm_Volume, int Audio)
{
    if(Somm_Volume > 0)
    {
        if(Somm_Volume%2 == 0)//si gain chiffre paire
        {
            Nconfig[Config_Used].Device_IN[Audio].Volume = 0;
            Nconfig[Config_Used].Device_IN[Audio].Gain = Somm_Volume;
        }
        else//si gain chiffre impaire
        {
            Nconfig[Config_Used].Device_IN[Audio].Volume = -1;
            Nconfig[Config_Used].Device_IN[Audio].Gain = Somm_Volume+1;
        }
    }
    else
    {
        Nconfig[Config_Used].Device_IN[Audio].Volume = Somm_Volume;
        Nconfig[Config_Used].Device_IN[Audio].Gain = 0;                   
    }
    if(Nconfig[Config_Used].Device_IN[Audio].Volume < -30)
    {
        Nconfig[Config_Used].Device_IN[Audio].Volume = -56;//corespond a MUTE pour TDA7439
        Nconfig[Config_Used].Device_IN[Audio].Gain = 0; 
    }    
}
 
void calculGainPT(float Somm_Volume, int Audio)
{
    float Perte;

    if((Somm_Volume > 0)&&(Somm_Volume <= 3.75))
    {
        Nconfig[Config_Used].Device_OUT[Audio].Gain = 3.75;            
    }
    else if((Somm_Volume > 3.75)&&(Somm_Volume <= 7.5))
    {
        Nconfig[Config_Used].Device_OUT[Audio].Gain = 7.5;               
    }
    else if((Somm_Volume > 7.5)&&(Somm_Volume <= 11.25))
    {
        Nconfig[Config_Used].Device_OUT[Audio].Gain = 11.25;               
    }
    else if(Somm_Volume <= 0)
    {
        Nconfig[Config_Used].Device_OUT[Audio].Gain = 0;
    }
    else
    {
        return;
    }
    Perte = Nconfig[Config_Used].Device_OUT[Audio].Gain - Somm_Volume;

    Nconfig[Config_Used].Device_OUT[Audio].Volume = -Perte; 
    if(Nconfig[Config_Used].Device_OUT[Audio].Volume < -30)
    {
        Nconfig[Config_Used].Device_OUT[Audio].Volume = -78.75;
    }       
}


