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

#include "app.h"
#include "gest_TELNET.h"
#include "string.h"
#include "bsp_config.h"

typedef enum {  TEL_CONNECT, TEL_WAIT_CONNECT, TEL_OPEN, 
                TEL_WAIT_RESPONSE, TEL_PROCESS_RESPONSE, TEL_TEMPO,
                TEL_STARTUP_BOUQUET, TEL_WAIT_MUX_OFF,
                TEL_RESTART, 
                TEL_REMOVE_LOGS, 
                TEL_CHANGE_DLS,
                TEL_CHANGE_IP_NUC,
                TEL_TUNNEL_TA,
                TEL_END, TEL_DISCONNECT, TEL_STANDBY, TEL_ERROR} TEL_Cmd;
                
IP_MULTI_ADDRESS TELNET_ClientIP;
char new_IP_NUC[17], IP_TELNET[17], TEL_subMask[17], TEL_gateway[17];
int nb_fail = 1;

bool isOpen = false;

TEL_Cmd telnetState                 = TEL_STANDBY;
TEL_Cmd telnetState_afterTempo      = TEL_STANDBY;
TEL_Cmd telnetState_afterOpen       = TEL_STANDBY;
TEL_Cmd telnetState_afterWait       = TEL_STANDBY;
TEL_Cmd telnetState_ifNoResponse    = TEL_STANDBY;
TEL_Cmd telnetState_print           = TEL_STANDBY;
int telnetOpenState = 0;
int telnetStartUpBouquetState = 0;
int telnetRemoveLogsState = 0;
int telnetChangeDlsState = 0;
int telnetChangeIpNuc = 0;
int telnetTunnelTA = 0;

bool TELNET_RouteIsOk(char* rep, char* ad, char* gat)
{  
    char temp[1000] = "temp";
    char ad_ip[20], gat_ip[20];
    strcpy(temp, rep);
    do
    {
        if(*rep == 'i'){rep++;}
        while(*rep != 'i'){rep++;}
    }while(memcmp(rep, "ipv4.routes:", 12));
    rep += 12;
    do
    {
        if(!memcmp(rep, "dst = ", 6))
        {
            int i = 0;
            rep += 6;
            while(*rep != '/' && *rep != ',')
            {
                ad_ip[i] = *rep;
                i++;
                rep++;
            }
            ad_ip[i] = 0;
        }
        else if(!memcmp(rep, "nh = ", 5))
        {
            int i = 0;
            rep += 5;
            while(*rep != ',')
            {
                gat_ip[i] = *rep;
                i++;
                rep++;
            }
            gat_ip[i] = 0;
        }
        rep++;
    }while(memcmp(rep, "ipv4", 4));
    if(strcmp(ad_ip, ad) == 0 && strcmp(gat_ip, gat) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }   
}

void TELNET_Task(void)
{
    static TCP_SOCKET telnetSocket;
    static int timeToWait;
    
    static uint8_t reponse[1000];
    static char rep[1000];
            
    switch(telnetState)
    {
        case TEL_CONNECT:
        {
            IP_MULTI_ADDRESS ip;
            TCPIP_Helper_StringToIPAddress(IP_TELNET, &ip.v4Add);
            telnetSocket = TCPIP_TCP_ClientOpen(IP_ADDRESS_TYPE_IPV4, 23, &ip);
            telnetState = TEL_WAIT_CONNECT;
        }break;
        case TEL_WAIT_CONNECT:
        {
            static int nbPC_fail = 0;
            static int tempo = 0;
            if(TCPIP_TCP_IsConnected(telnetSocket))
            {
                telnetState = TEL_WAIT_RESPONSE;
                tempo = 0;
                nb_fail = 0;
                nbPC_fail = 0;
            }
            else
            {
                if(tempo++ >= 40) // * 50ms
                {
                    nb_fail++;
                    telnetState = TEL_CONNECT;
                    TCPIP_TCP_Disconnect(telnetSocket);
                    tempo = 0;
                    if(nb_fail >= 5)
                    {
                        nb_fail = 0;
                        PC_Restart();
                        if(nbPC_fail++ >= 4)
                        {
                            nbPC_fail = 0;
                            PIC_reset();
                            telnetState = TEL_STANDBY;
                        }
                    }
                }
            }
        }break;
        case TEL_WAIT_RESPONSE:
        {
            static int waitResponseCpt = 0, noResponseCpt = 0;
            if(TCPIP_TCP_GetIsReady(telnetSocket) > 0)
            {
                noResponseCpt = 0;
                telnetState = TEL_PROCESS_RESPONSE;
            }
            else if(waitResponseCpt++ >= 1200)
            {
                uint16_t nbByteToRead = TCPIP_TCP_GetIsReady(telnetSocket);
                TCPIP_TCP_ArrayGet(telnetSocket, reponse, nbByteToRead);
                telnetState_ifNoResponse = telnetState_afterWait;
                telnetState = TEL_END;
                if(noResponseCpt++ > 3)
                {
                    PC_Restart();
                }
                waitResponseCpt = 0;
            }
        }break;
        case TEL_PROCESS_RESPONSE:
        {
            uint8_t tmp;
            uint16_t nbByteToRead = TCPIP_TCP_GetIsReady(telnetSocket);
            TCPIP_TCP_ArrayGet(telnetSocket, reponse, nbByteToRead);
            if(TCPIP_TCP_ArrayGet(telnetSocket, &tmp, 1) == 0)
            {
                if(isOpen == false)
                {
                    isOpen = true;
                    telnetState = TEL_OPEN;
                }
                else
                {
                    telnetState = telnetState_afterWait;
                }
            }
            memcpy(rep, reponse, nbByteToRead);
            memcpy(rep, reponse, nbByteToRead);
            
        }break;
        case TEL_TEMPO:
        {
            static int tempo = 0;
            if(tempo++ >= timeToWait)
            {
                telnetState = telnetState_afterTempo;
                tempo = 0;
            }
        }break;
        case TEL_OPEN:
        {
            switch(telnetOpenState++)
            {
                case 0:
                {
                    // Will Terminal Type + Will Negotiate About windows Size
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "\xff\xfb\x18\xff\xfb\x1f");
                }break;
                case 1:
                {
                    // won't Terminal Speed + won't X Display Location + 
                    // won't New Environment Option
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "\xff\xfc\x20\xff\xfc\x23\xff\xfc\x27");
                }break;
                case 2:
                {
                    // Suboption Begin: Terminal Type
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "\xff\xfa\x18");
                    // Command : suboption End
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "\xff\xf0");
                }break;
                case 3:
                {
                    // Do supress go ahead
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "\xff\xfd\03");
                    // will Echo + Don't Echo + won't Remote flow ctr
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "\xff\xfb\x01\xff\xfe\x05\xff\xfc\x21");
                }break;
                case 4:
                {
                    // will Echo don't status
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "odr\r\n");
                }break;
                case 5:
                {
                    // will Echo don't status
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "AUMIX1\r\n");
                    telnetState = TEL_WAIT_RESPONSE;     // att réponse
                    telnetState_afterWait = TEL_TEMPO;   // tempo après réponse 
                    telnetState_afterTempo = telnetState_afterOpen; // action définie
                    timeToWait = 5; // *50ms
                    telnetOpenState = 0;
                    return; // permet de terminer la communication et de pas attendre de réponse
                }break;
            }
            // Attente d'une réponse du NUC après chaque envoi 
            telnetState = TEL_WAIT_RESPONSE;
            telnetState_afterWait = TEL_OPEN;
        }break;
        case TEL_STARTUP_BOUQUET:
        {
            switch(telnetStartUpBouquetState++)
            {
                case 0:
                {
                    extern char Channel_In[4];
                    char tmp[30];
                    sprintf(tmp, "cd /home/odr/%s\r\n", Channel_In);
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) tmp);
                    timeToWait = 3; // *50ms
                }break;
                case 1:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "nohup bash dab-startup.sh &\r\n");
                    timeToWait = 8; // *50ms
                }break;
                case 2:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "\r\n");
                    timeToWait = 3; // *50ms
                }break;
                case 3:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "rm nohup.out\r\n");
                    telnetStartUpBouquetState = 0;
                    timeToWait = 3; // *50ms
                    telnetState = TEL_END;
                    return; // permet de terminer la communication et de pas attendre de réponse
                }break;
            }
            // Attente d'une réponse du NUC après chaque envoi et tempo 
            telnetState = TEL_WAIT_RESPONSE;
            telnetState_afterWait = TEL_TEMPO;
            telnetState_afterTempo = TEL_STARTUP_BOUQUET;
        }break;
        case TEL_REMOVE_LOGS:
        {
            switch(telnetRemoveLogsState++)
            {
                case 0:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "su\r\n");
                }break;
                case 1:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "AUMIX1\r\n");
                }break;
                case 2:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "rm /var/log/messages\r\n");
                }break;
                case 3:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "rm /var/log/messages.1\r\n");
                    telnetRemoveLogsState = 0;
                    telnetState = TEL_END;
                    return; // permet de terminer la communication et de pas attendre de réponse
                }break;
            }
            // Attente d'une réponse du NUC après chaque envoi 
            telnetState = TEL_WAIT_RESPONSE;
            telnetState_afterWait = TEL_REMOVE_LOGS;
        }break;
        case TEL_CHANGE_DLS:
        {
            switch(telnetChangeDlsState++)
            {
                case 0:
                {
                    extern char Channel_In[4];
                    char tmp[30];
                    sprintf(tmp, "cd /home/odr/%s/site\r\n", Channel_In);
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) tmp);
                }break;
                case 1:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "rm dls.txt\r\n");
                }break;
                case 2:
                {
                    extern char Text_info_Traffic[100];
                    char tmp[100];
                    sprintf(tmp,"echo %s > dls.txt\r\n", Text_info_Traffic);
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) tmp);
                    telnetChangeDlsState = 0;
                    EEPROM_SaveData(Text_info_Traffic);
                    telnetState = TEL_END;
                    return;
                }break;
            }
            // Attente d'une réponse du NUC après chaque envoi 
            telnetState = TEL_WAIT_RESPONSE;
            telnetState_afterWait = TEL_CHANGE_DLS;
        }break;
        case TEL_CHANGE_IP_NUC:
        {
            switch(telnetChangeIpNuc++)
            {
                case 0:
                {
                    char tmp[100];
                    sprintf(tmp,"sudo nmcli con mod \"Wired connection 1\" ipv4.addresses \"%s/%s\"\r\n", new_IP_NUC, TEL_subMask);
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) tmp);
                }break;
                case 1:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "sudo nmcli connection edit \"Wired connection 1\"\r\n");
                }break;
                case 2:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "goto ipv4\r\n");
                }break;
                case 3:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "remove routes\r\n");
                }break;
                case 4:
                {
                    char tmp[100];
                    sprintf(tmp,"set routes %s/8 %s\r\n", new_IP_NUC, TEL_gateway);
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) tmp);
                }break;
                case 5:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "print\r\n");
                }break;
                case 6:
                {
                    extern char UploadState[200];
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "save\r\nquit\r\n");
                    telnetChangeIpNuc = 0;
                    
                    // Vérification de la configuration
                    if(TELNET_RouteIsOk(rep, new_IP_NUC, TEL_gateway) == false)
                    {
                        strcpy(UploadState, "Device configuration failed, wrong NUC network");
                        telnetState = TEL_END;
                    }
                    else
                    {
                        strcpy(UploadState, "Device configuration successful, saving parameters, device will reboot after that");
                        EEPROM_SaveAll();
                        strcpy(IP_TELNET, new_IP_NUC);
                        telnetState = TEL_RESTART;
                    }
                    return; // permet de terminer la communication et de pas attendre de réponse
                }break;
            }
            // Attente d'une réponse du NUC après chaque envoi 
            telnetState = TEL_WAIT_RESPONSE;
            telnetState_afterWait = TEL_CHANGE_IP_NUC;
        }break;
        case TEL_TUNNEL_TA:
        {
            switch(telnetTunnelTA++)
            {
                case 0:
                {
                    extern char Channel_In[4];
                    char tmp[30];
                    sprintf(tmp, "cd /home/odr/%s/site\r\n", Channel_In);
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) tmp);
                    timeToWait = 299; // *50ms
                    telnetState = TEL_WAIT_RESPONSE;
                    telnetState_afterWait = TEL_TEMPO;
                    telnetState_afterTempo = TEL_TUNNEL_TA;
                }break;
                case 1:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "bash TAOFF.sh\r\n");
                    timeToWait = 39; // *50ms
                    telnetState = TEL_WAIT_RESPONSE;
                    telnetState_afterWait = TEL_TEMPO;
                    telnetState_afterTempo = TEL_TUNNEL_TA;
                }break;
                case 2:
                {
                    TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "bash TAON.sh\r\n");
                    telnetTunnelTA = 0;
                    telnetState = TEL_END;
                }break;
            }
        }break;
        case TEL_RESTART:
        {
            TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "sleep 10; sudo shutdown -r now\r\n");
            telnetState = TEL_END;
        }break;   
        case TEL_END:
        {
            TCPIP_TCP_StringPut(telnetSocket, (uint8_t*) "exit\r\n");
            telnetState = TEL_DISCONNECT;
        }break;
        case TEL_DISCONNECT:
        {
            TCPIP_TCP_Disconnect(telnetSocket);
            if(telnetState_ifNoResponse == TEL_STANDBY)
            {
                telnetState = TEL_STANDBY;
            }
            else
            {   // Seulement en cas de non réponse du NUC
                telnetState_print = TEL_ERROR;
                telnetState = TEL_CONNECT;
                telnetState_afterOpen = telnetState_ifNoResponse;
                switch(telnetState_ifNoResponse)
                {
                    case TEL_OPEN:              telnetOpenState = 0;            break;
                    case TEL_STARTUP_BOUQUET:   telnetStartUpBouquetState = 0;  break;
                    case TEL_REMOVE_LOGS:       telnetRemoveLogsState = 0;      break;
                    case TEL_CHANGE_DLS:        telnetChangeDlsState = 0;       break;
                    case TEL_CHANGE_IP_NUC:     telnetChangeIpNuc = 0;          break;
                    case TEL_TUNNEL_TA:         telnetTunnelTA = 0;             break;
                }
                telnetState_ifNoResponse = TEL_STANDBY;
            }
        }break;
        case TEL_STANDBY:
        {
            // Ne sert pas à grand chose, état d'attente d'une nouvelle transaction
        }break; 
    }
}



void CMDTEL_Start(TELNET_COMMANDS cmd)
{
    if(telnetState == TEL_STANDBY)
    {
        telnetState_print = cmd;
        telnetState = TEL_CONNECT;
        isOpen = false;
        nb_fail = 1;
        switch(cmd)
        {
            case CMDTEL_STARTUP_BOUQUET:
            {
                telnetState_afterOpen = TEL_STARTUP_BOUQUET;
            }break;
            case CMDTEL_RESTART:
            {
                telnetState_afterOpen = TEL_RESTART;
            }break;
            case CMDTEL_CHANGE_DLS:
            {
                telnetState_afterOpen = TEL_CHANGE_DLS;
            }break;
            case CMDTEL_REMOVE_LOGS:
            {
                telnetState_afterOpen = TEL_REMOVE_LOGS;
            }break;
            case CMDTEL_CHANGE_IP_NUC:
            {
                telnetState_afterOpen = TEL_CHANGE_IP_NUC;
            }break;
            case CMDTEL_TUNNEL_TA:
            {
                telnetState_afterOpen = TEL_TUNNEL_TA;
            }break;
            case CMDTEL_STANDBY:
            {
                telnetState = TEL_STANDBY;
            }break;
            default:
            {
                telnetState = TEL_STANDBY;
            }break;
        }
    }
}

bool CMDTEL_Ready(void)
{
    return (telnetState == TEL_STANDBY);
}

char* maskToSubmask(char* submask, char* mask)
{
    int submask_int = 0, b = 0x80;
    IPV4_ADDR ip;
    TCPIP_Helper_StringToIPAddress(mask, &ip);
    while((ip.Val & b) > 0)
    {
        submask_int++;
        b = b >> 1;
        if(b == 0)
        {
            ip.Val = ip.Val >> 8;
            b = 0x80;
        }
    }
    itoa(submask, submask_int, 10);
    return submask;
}

void CMDTEL_NewIpNuc(char* ip, char* mask, char* gateway)
{
    char submask[10];
    strcpy(new_IP_NUC, ip);
    strcpy(TEL_subMask, maskToSubmask(submask, mask));
    strcpy(TEL_gateway, gateway);
}

void CMDTEL_ChangeIpNuc(char* ip)
{
    strcpy(IP_TELNET, ip);
}

int CMDTEL_IsConected(void)
{   // Return 0 if success, or nb fail if failed
    return nb_fail;
}
// Pour la page WEB
char* CMDTEL_PrintState(char* msg)
{
    switch(telnetState)
    {
        case TEL_CONNECT:
        {
            strcpy(msg, "Connect");
        }break;
        case TEL_WAIT_CONNECT:
        {
            strcpy(msg, "Waiting connect");
        }break;
        case TEL_WAIT_RESPONSE:
        {
            strcpy(msg, "Waiting response");
        }break;
        case TEL_PROCESS_RESPONSE:
        {
            strcpy(msg, "Processing response");
        }break;
        case TEL_TEMPO:
        {
            strcpy(msg, "Tempo waiting");
        }break;
        case TEL_OPEN:
        {
            extern int telnetOpenState;
            switch(telnetOpenState)
            {
                case 0:
                {
                    strcpy(msg, "TELNET Opening: state 0");
                }break;
                case 1:
                {
                    strcpy(msg, "TELNET Opening: state 1");
                }break;
                case 2:
                {
                    strcpy(msg, "TELNET Opening: state 2");
                }break;
                case 3:
                {
                    strcpy(msg, "TELNET Opening: state 3");
                }break;
                case 4:
                {
                    strcpy(msg, "TELNET Opening: state 4");
                }break;
                case 5:
                {
                    strcpy(msg, "TELNET Opening: state 5");
                }break;
            }
        }break;
        case TEL_STARTUP_BOUQUET:
        {
            extern int telnetStartUpBouquetState;
            switch(telnetStartUpBouquetState)
            {
                case 0:
                {
                    strcpy(msg, "TELNET Starting bouquet: state 0");
                }break;
                case 1:
                {
                    strcpy(msg, "TELNET Starting bouquet: state 1");
                }break;
                case 2:
                {
                    strcpy(msg, "TELNET Starting bouquet: state 2");
                }break;
                case 3:
                {
                    strcpy(msg, "TELNET Starting bouquet: state 3");
                }break;
            }
        }break;
        case TEL_REMOVE_LOGS:
        {
            extern int telnetRemoveLogsState;
            switch(telnetRemoveLogsState)
            {
                case 0:
                {
                    strcpy(msg, "TELNET removing logs: state 0");
                }break;
                case 1:
                {
                    strcpy(msg, "TELNET Starting bouquet: state 1");
                }break;
                case 2:
                {
                    strcpy(msg, "TELNET Starting bouquet: state 2");
                }break;
                case 3:
                {
                    strcpy(msg, "TELNET Starting bouquet: state 3");
                }break;
            }
        }break;
        case TEL_CHANGE_DLS:
        {
            extern int telnetChangeDlsState;
            switch(telnetChangeDlsState)
            {
                case 0:
                {
                    strcpy(msg, "TELNET Changing DLS: state 0");
                }break;
                case 1:
                {
                    strcpy(msg, "TELNET Changing DLS: state 1");
                }break;
                case 2:
                {
                    strcpy(msg, "TELNET Changing DLS: state 2");
                }break;
            }
        }break;
        case TEL_CHANGE_IP_NUC:
        {
            extern int telnetChangeIpNuc;
            switch(telnetChangeIpNuc)
            {
                case 0:
                {
                    strcpy(msg, "TELNET Changing IP and routes: state 0");
                }break;
                case 1:
                {
                    strcpy(msg, "TELNET Changing IP and routes: state 1");
                }break;
                case 2:
                {
                    strcpy(msg, "TELNET Changing IP and routes: state 2");
                }break;
                case 3:
                {
                    strcpy(msg, "TELNET Changing IP and routes: state 3");
                }break;
                case 4:
                {
                    strcpy(msg, "TELNET Changing IP and routes: state 4");
                }break;
                case 5:
                {
                    strcpy(msg, "TELNET Changing IP and routes: state 5");
                }break;
                case 6:
                {
                    strcpy(msg, "TELNET Changing IP and routes: state 6");
                }break;
            }
        }break;
        case TEL_TUNNEL_TA:
        {
            extern int telnetTunnelTA;
            switch(telnetTunnelTA)
            {
                case 0:
                {
                    strcpy(msg, "TELNET TA: state 0");
                }break;
                case 1:
                {
                    strcpy(msg, "TELNET TA: state 1");
                }break;
                case 2:
                {
                    strcpy(msg, "TELNET TA: state 2");
                }break;
            }
        }break;
        case TEL_RESTART:
        {
            strcpy(msg, "TELNET Restart");
        }break;   
        case TEL_END:
        {
            strcpy(msg, "TELNET End");
        }break;
        case TEL_DISCONNECT:
        {
            strcpy(msg, "TELNET Disconnect");
        }break;
        case TEL_STANDBY:
        {
            strcpy(msg, "TELNET Standby");
        }break; 
    }
    return msg;
}
// Pour fichier de maintenance
char* CMDTEL_PrintStatement(char* msg)
{
    if(telnetState_print != TEL_STANDBY)
    {
        switch(telnetState_print)
        {
            case CMDTEL_STARTUP_BOUQUET:
            {
                strcpy(msg, "start bouquet");
            }break;
            case CMDTEL_RESTART:
            {
                strcpy(msg, "start restart");
            }break;
            case CMDTEL_CHANGE_DLS:
            {
                strcpy(msg, "change DLS");
            }break;
            case CMDTEL_REMOVE_LOGS:
            {
                strcpy(msg, "remove logs");
            }break;
            case CMDTEL_CHANGE_IP_NUC:
            {
                strcpy(msg, "change IP");
            }break;
            case CMDTEL_TUNNEL_TA:
            {
                strcpy(msg, "tunnel TA");
            }break;
            case CMDTEL_STANDBY:
            {
                strcpy(msg, "standby");
            }break;
            case TEL_ERROR:
            {
                strcpy(msg, "error");
            }break;
            default:
            {
                strcpy(msg, "default");
            }break;
        }
        telnetState_print = TEL_STANDBY;
    }
    else
        return 0;
}

/* *****************************************************************************
 End of File
 */
