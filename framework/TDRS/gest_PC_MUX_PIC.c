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
#include <time.h>

#include "app.h"
#include "system/reset/sys_reset.h"

#ifdef PIC_RF
#include "tcpip/icmp.h"
int ping_ok = 0, mux_waiting, nbMiss = 0, cpt_pc_restart = 0;
void MyICMPCallbackFunction(TCPIP_NET_HANDLE hNetIf, IPV4_ADDR * remoteIP, void * data);

enum 
{
    PC_OFF, PC_ON, PC_PULSE, PC_RESTART, PC_TEL_RESTART
}PC_state, PC_state_TimeStamp;
enum 
{
    DSP_OFF, DSP_ON, MUX_STARTING_BOUQUET, MUX_CHANGING_BOUQUET
}MUX_state, MUX_state_TimeStamp;
#endif
enum 
{
    PIC_ON, PIC_RESET, PIC_WAITING_FOR_RESET
}PIC_state, PIC_state_TimeStamp;
int PC_pulse_cpt, PC_RESTART_state, PC_TEL_RESTART_state;

void statementTask(void)
{
#ifdef PIC_RF
    switch(PC_state)
    {
        extern char Alim_PC_Txt[5];
        
        case PC_ON:
        {
            static int PC_cpt_ON = 0;
            sprintf(Alim_PC_Txt,"ON");
            
            if(Alim_PC == 0)
            {
                if(PC_cpt_ON++ >= 40)
                {   // Changer par ping
                    PC_cpt_ON = 0;
                    PC_state = PC_OFF;
                }
            }
            else
            {
                PC_cpt_ON = 0;
            }
        }break;
        case PC_OFF:
        {
            static int PC_cpt_OFF = 0, cptPC_Alim = 0;
            static int cptPing = 0, nbPing = 0;
            sprintf(Alim_PC_Txt,"OFF");
            
            ICMP_HANDLE test_ping;
            ICMP_ECHO_RESULT Valeur_Echo;
            uint16_t mySequenceNumber = 19;
            TCPIP_NET_HANDLE ping;
            IPV4_ADDR remoteIP;
            extern char Adresse_IP_PC[17];
            
            TCPIP_Helper_StringToIPAddress(Adresse_IP_PC, &remoteIP);
            if(Alim_PC == 1)
            {
                cptPing++;
            }
            if(cptPing >= 200)
            {
                cptPing = 0;
                
                if(ping_ok == 0)
                {
                    TCPIP_ICMP_CallbackDeregister(test_ping);
                    nbPing = 0;
                    if(nbMiss++ >= 12)
                    {
                        nbMiss = 0;
                        PC_Restart();
                        PC_RESTART_state = 1;
                    }
                }
                else
                {
                    ping_ok = 0;
                    nbPing++;
                }
                if(nbPing == 0)
                {
                    Valeur_Echo = TCPIP_ICMP_EchoRequestSend(ping,&remoteIP, mySequenceNumber, 0x840);
                    test_ping = (ICMP_HANDLE)TCPIP_ICMP_CallbackRegister(&MyICMPCallbackFunction);
                }
                else
                {
                    nbMiss = 0;
                    PC_state = PC_ON;
                    nbPing = 0;
                }
            }
            
            cptPC_Alim ++;
            if(cptPC_Alim == 1 && Alim_PC == 0)
            {
                PC_state = PC_PULSE;
                PC_pulse_cpt = PC_PULSE_ON_TIME;
            }
            else if(cptPC_Alim >= 3600)
            {
                cptPC_Alim = 0;
            }

        }break;
        case PC_PULSE:
        {   // Use define for timing
            Pulse_BTN_PC = 1;
            PC_pulse_cpt--;
            if(PC_pulse_cpt <= 0)
            {
                Pulse_BTN_PC = 0;
                PC_state = PC_OFF;
            }
        }break;
        case PC_RESTART:
        {
            static int restart_timer;
            switch(PC_RESTART_state)
            {
                case 1:
                {
                    restart_timer = PC_PULSE_OFF_TIME;
                    Pulse_BTN_PC = 1;
                    PC_RESTART_state ++;
                }break;
                case 2:
                {
                    if(restart_timer-- <= 0)
                    {
                        if(Mux_Alarme == 0)
                        {
                            Pulse_BTN_PC = 0;
                            PC_RESTART_state ++;
                        }
                    }
                }break;
                case 3:
                {
                    restart_timer = PC_PULSE_ON_TIME;
                    PC_RESTART_state ++;
                }break;
                case 4:
                {
                    Pulse_BTN_PC = 1;
                    if(restart_timer-- <= 0)
                    {
                        Pulse_BTN_PC = 0;
                        PC_RESTART_state ++;
                        PC_state = PC_OFF;
                    }
                }break;
            }
        }break;
        case PC_TEL_RESTART:
        {
            switch(PC_TEL_RESTART_state)
            {
                case 1:
                {
                    if(CMDTEL_Ready() == true)
                    {
                        CMDTEL_Start(CMDTEL_RESTART);
                        PC_TEL_RESTART_state++;
                    }
                }break;
                case 2:
                {
                    if(CMDTEL_Ready() == true)
                    {
                        PC_state = PC_OFF;
                    }
                }break;
            }
        }break;
    }
    switch(MUX_state)
    {
        static int nbFailed = 0;
        
        case DSP_OFF:
        {
            if(Mux_Alarme == 1)
            {
                MUX_state = DSP_ON;
            }
            else if(PC_state == PC_ON)
            {
                if(CMDTEL_Ready() == true)
                {
                    CMDTEL_Start(CMDTEL_STARTUP_BOUQUET);
                    MUX_state = MUX_STARTING_BOUQUET;
                }
            }
        }break;
        case MUX_STARTING_BOUQUET:
        {
            static int MUX_Starting_cpt = 0;
            static int cpt_mux_fail = 0;
            nbFailed = 0;
            if(CMDTEL_IsConected() == 0)
            {   // L'envoi TelNet se fait
                if(Mux_Alarme == 1)
                {
                    if(MUX_Starting_cpt++ > 40)
                    {
                        MUX_state = DSP_ON;
                        MUX_Starting_cpt = 0;
                        cpt_pc_restart = 0;
                    }
                }
                else if(cpt_mux_fail++ > 1200)
                {   // Si le mux n'est pas allumé après une minute on recommence
                    cpt_mux_fail = 0;
                    MUX_state = DSP_OFF;
                    if(cpt_pc_restart++ >= 1)
                    {   // Si le mux n'est pas allumé après 2 fois, on restart le PC
                        cpt_pc_restart = 0;
                        PC_Restart();
                        static int cpt_pic_restart = 0;
                        if(cpt_pic_restart++ >= 2)
                        {// Si rien ne passe on redemmare le PIC
                            cpt_pic_restart = 0;
                            PIC_state = PIC_RESET;
                        }
                    }
                }
            }
        }break;
        case MUX_CHANGING_BOUQUET:
        {
            mux_waiting--;
            if(mux_waiting <= 0)
            {
                if(Mux_Alarme == 0)
                {
                    extern int Choix_Channel_In;
                    EEPROM_SaveData(&Choix_Channel_In);
                    MUX_state = DSP_OFF;
                }
                else
                {
                    PC_state = PC_RESTART;
                    PC_RESTART_state = 1;
                }
            }
        }break;
        case DSP_ON:
        {
            static int MUX_ON_cpt = 0;
            if(Mux_Alarme == 0)
            {
                if(MUX_ON_cpt++ > 40)
                {
                    MUX_ON_cpt = 0;
                    MUX_state = DSP_OFF;
                }
            }
            else
            {
                MUX_ON_cpt = 0;
            }
        }break;
    }
#endif
    switch(PIC_state)
    {
        case PIC_ON:
            // Nothing to do
        break;
        case PIC_WAITING_FOR_RESET:
        {
            static int PIC_waitingForceResetCpt = 0;
            if(EEPROM_IsAllSaved() == true 
#ifdef PIC_RF
                    && CMDTEL_Ready() == true
#endif
                                             )  // Permet de terminer la condition dans tous les cas (ifdef)
            {
                static int PIC_waitingCpt = 0;
                PIC_waitingCpt++;
                
                if(PIC_waitingCpt >= PIC_RESET_TIME)
                {
                    PIC_waitingCpt = 0;
                    PIC_state = PIC_RESET;
                }
                #if defined(PIC_RF) || defined(PIC_COMB) || defined(PIC_AMPLI)
                else if(PIC_waitingCpt == 1 && BCKUP_Ready())
                {
                    BCKUP_Popup("Backup successfull, restarting device...");
                }
                #endif
            }
            else if(PIC_waitingForceResetCpt++ > 2400)
            {   // Si après deux minutes le PIC est bloqué, redemmarage
                PIC_state = PIC_RESET;
            }
        }        
        break;
        case PIC_RESET:
            SYS_RESET_SoftwareReset();
        break;
        
    }
}
#ifdef PIC_RF
bool PC_IsOk(void)
{
    if(PC_state == PC_ON)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void PC_Shutdown(void)
{
    if(PC_state == PC_ON)
    {
        PC_state = PC_PULSE;
        PC_pulse_cpt = PC_PULSE_OFF_TIME;
    }
}
void PC_Boot(void)
{
    if(PC_state == PC_OFF)
    {
        PC_state = PC_PULSE;
        PC_pulse_cpt = PC_PULSE_ON_TIME;
    }
}
void PC_Restart(void)
{
    if(PC_state == PC_ON)
    {
        PC_RESTART_state = 1;
    }
    else
    {
        PC_RESTART_state = 3;
    }
    PC_state = PC_RESTART;
}

void PC_TELNET_Restart(void)
{
    PC_state = PC_TEL_RESTART;
    PC_TEL_RESTART_state = 1;
}

bool MUX_IsOn(void)
{
    if(MUX_state == DSP_ON)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void MUX_ChangeBouquet(void)
{
    if(MUX_state == DSP_ON)
    {
        PC_state = PC_TEL_RESTART;
        PC_TEL_RESTART_state = 1;
    }
    mux_waiting = MUX_WAITING_CHANGE;
    MUX_state = MUX_CHANGING_BOUQUET;
}

void MyICMPCallbackFunction(TCPIP_NET_HANDLE hNetIf, IPV4_ADDR * remoteIP, void * data)
{
    // process request from interface hNetIf and remoteIP address

    uint16_t* pReply = (uint16_t*)data;
    uint16_t myRecvId = *pReply;
    uint16_t myRecvSequenceNumber = *(pReply + 1);
    
    ping_ok = 1;

//    TCPIP_ICMP_CallbackDeregister(test_ping);



    // check that the sequence number, ID and IP address match, etc.
}
#endif

void PIC_reset(void)
{
    PIC_state = PIC_WAITING_FOR_RESET;
}

void PIC_ForceReset(void)
{
    PIC_state = PIC_RESET;
}

char* createTime(char* msg, bool forCSV)
{
    extern char Time_Now[20];
    static char strTime[30];
    if(forCSV == 1)
    {
        strTime[0] = ';';
        strcpy(strTime+1, Time_Now);
        strcat(strTime, "\r\n");
    }
    else
    {
        strcpy(strTime, Time_Now);
    }
    strcpy(msg, strTime);
    return strTime;
}

#ifdef PIC_MONITORING_ENABLE
unsigned int timeForMonitoring = 0;
void PC_MUX_PIC_TimeStampChanges(void)
{
    char timeString[30];
    static int start = 1;
    if(start == 1)
    {
        start = 0;
//        strcpy(PC_MUX_PIC_timestamp, "PIC;ON\r\nPC;OFF;day:00 00:00:00\r\nMUX;OFF;day:00 00:00:00\r\n")        
        EEPROM_Maintenance_csv_Write("\r\n\r\nPIC;REBOOT");
        EEPROM_Maintenance_csv_Write(createTime(timeString, 1));
        PC_state_TimeStamp = PC_OFF;
        MUX_state_TimeStamp = DSP_OFF;
    }
    if(PC_state_TimeStamp != PC_state)
    {
        createTime(timeString, 1);
        PC_state_TimeStamp = PC_state;
        switch(PC_state)
        {
            case PC_OFF:
            {
                EEPROM_Maintenance_csv_Write("PC;OFF");
            }break;
            case PC_ON:
            {
                EEPROM_Maintenance_csv_Write("PC;ON");
            }break;
            case PC_PULSE: 
            {
                EEPROM_Maintenance_csv_Write("PC;PULSE");
            }break;
            case PC_RESTART: 
            {
                EEPROM_Maintenance_csv_Write("PC;RESTART");
            }break;
            case PC_TEL_RESTART:
            {
                EEPROM_Maintenance_csv_Write("PC;TEL RESTART");
            }break;
        }
        EEPROM_Maintenance_csv_Write(timeString);
    }
    if(MUX_state_TimeStamp != MUX_state)
    {
        createTime(timeString, 1);
        MUX_state_TimeStamp = MUX_state;
        switch(MUX_state)
        {
            case DSP_OFF:
            {
                EEPROM_Maintenance_csv_Write("MUX;OFF");
            }break;
            case DSP_ON:
            {
                EEPROM_Maintenance_csv_Write("MUX;ON");
            }break;
            case MUX_STARTING_BOUQUET: 
            {
                EEPROM_Maintenance_csv_Write("MUX;START");
            }break;
            case MUX_CHANGING_BOUQUET: 
            {
                EEPROM_Maintenance_csv_Write("MUX;CHANGING");
            }break;
        }
        EEPROM_Maintenance_csv_Write(timeString);
    }
    char telnetmsg[100], *tel;
    tel = CMDTEL_PrintStatement(telnetmsg);
    if(tel != 0)
    {
        createTime(timeString, 1);
        EEPROM_Maintenance_csv_Write("TELNET;");
        EEPROM_Maintenance_csv_Write(telnetmsg);
        EEPROM_Maintenance_csv_Write(timeString);
    }
}
char* PC_MUX_PIC_PrintTimeStamp(void)
{
    return EEPROM_Maintenance_csv_Read();
}
#endif

/* *****************************************************************************
 End of File
 */
