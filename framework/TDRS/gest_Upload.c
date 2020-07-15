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

#if defined(PIC_RF) || defined(PIC_COMB) || defined(PIC_AMPLI)
#define Nb_Route 4
    typedef struct tROUTE_CONFIG
    {
        IPV4_ADDR IP_Route;    
        IPV4_ADDR IP_Mask;
        IPV4_ADDR IP_Net;

    } ROUTE_CONFIG;

    extern ROUTE_CONFIG routeconfig[Nb_Route];

typedef enum {
    BCKUP_NAME, BCKUP_IP_ADD, BCKUP_IP_MASK, BCKUP_IP_GAT, BCKUP_IP_DNS, BCKUP_IP_NTP,
    BCKUP_RT1_NET, BCKUP_RT1_MASK, BCKUP_RT1_GAT,  
    BCKUP_RT2_NET, BCKUP_RT2_MASK, BCKUP_RT2_GAT, 
    BCKUP_RT3_NET, BCKUP_RT3_MASK, BCKUP_RT3_GAT, 
    BCKUP_RT4_NET, BCKUP_RT4_MASK, BCKUP_RT4_GAT,
#ifdef PIC_RF
    BCKUP_BOUQUET, BCKUP_CHAN, BCKUP_IP_NUC, BCKUP_INFO_TRAFFIC, BCKUP_TA, BCKUP_OPT_IN_LOW, 
#endif
#ifdef PIC_AMPLI
    BCKUP_OPT_OUT_LOW,         
#endif
#if defined(PIC_RF) || defined(PIC_AMPLI)
    BCKUP_ATT, 
#endif
    BCKUP_ACT_MAIL, BCKUP_ACT_SNMP, BCKUP_ACT_NMS,
    BCKUP_MAIL_ACT, BCKUP_MAIL_FROM, BCKUP_MAIL_TO,
    BCKUP_SNMP_ACT, BCKUP_NMS, BCKUP_SNMP1, BCKUP_SNMP2, BCKUP_SNMP3, BCKUP_SNMP4,
    BCKUP_USER, BCKUP_PASS, BCKUP_SIZE}BCKUP_Elem;
    
uint8_t backUp[2000];                       // Backup file, csv format
bool backUpIsOk[BCKUP_SIZE];                // 1 bool per element
bool UploadStatePopUp = 0;                  // Show a pop up when new message incoming
bool backupReady = 0;                       // inform that backup is launched
char UploadState[200] = "No backup file";   // Info for web page
    
const char* BCKUP_NameElem[BCKUP_SIZE]={
    "name;%s\r\n", "ip address;%s\r\n", "ip mask;%s\r\n", "ip gateway;%s\r\n", "ip dns;%s\r\n", "ntp server;%s\r\n",
    "route1.net;%s\r\n", "route1.mask;%s\r\n", "route1.gat;%s\r\n", "route2.net;%s\r\n", "route2.mask;%s\r\n", "route2.gat;%s\r\n", 
    "route3.net;%s\r\n", "route3.mask;%s\r\n", "route3.gat;%s\r\n", "route4.net;%s\r\n", "route4.mask;%s\r\n", "route4.gat;%s\r\n", 
#ifdef PIC_RF
    "bouquet;%s\r\n", "channel;%s\r\n", "ip nuc;%s\r\n", "info traffic;%s\r\n", "ta;%s\r\n", "option in low;%s\r\n", 
#endif
#ifdef PIC_AMPLI
    "option out low;%s\r\n", 
#endif
#if defined(PIC_RF) | defined(PIC_AMPLI)
    "attenuation;%s\r\n",
#endif
    "act mail;%s\r\n", "act snmp;%s\r\n", "act nms;%s\r\n", "mail enable;%s\r\n", "mail from;%s\r\n", "mail to;%s\r\n",
    "snmp enable;%s\r\n","nms;%s\r\n", "snmp1;%s\r\n", "snmp2;%s\r\n", "snmp3;%s\r\n", "snmp4;%s\r\n", "user;%s\r\n", "pass;%s\r\n"};

bool controleBackUp(void)
{
    BCKUP_Elem i;
    for(i = 0; i < BCKUP_SIZE; i++)
    {
        if(backUpIsOk[i] == false)
        {
            return false;
        }
    }
    return true;
}

bool controleNetwork(char* add_ip, char* add_mask, char* add_gateway, char* add_nuc, char* add_nuc_gat)
{
    IPV4_ADDR ip, mask, gateway, nuc, nuc_gat;
    TCPIP_Helper_StringToIPAddress(add_ip, &ip);
    TCPIP_Helper_StringToIPAddress(add_mask, &mask);
    TCPIP_Helper_StringToIPAddress(add_gateway, &gateway);
    TCPIP_Helper_StringToIPAddress(add_nuc, &nuc);
    TCPIP_Helper_StringToIPAddress(add_nuc_gat, &nuc_gat);
    
    if(((ip.Val & mask.Val) == (gateway.Val & mask.Val)) // ip pic dans son lan
#ifdef PIC_RF
            && ((nuc.Val & mask.Val) == (nuc_gat.Val & mask.Val)) // ip nuc dans son lan
            && ((gateway.Val & mask.Val) == (nuc_gat.Val & mask.Val)) // nuc et pic dans le meme lan
#endif
                                                                    ) // Termine la condiction dans tous les cas (ifdef))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void uploadAndSave(char* csv)
{
    extern char Save_Gateway_IP[17], Save_Adresse_IP[17], Save_Mask_IP[17];
    memset(backUpIsOk, 0, sizeof(backUpIsOk));
#ifdef __DEBUG    // Pour contrôler le fichier de backup
    memcpy(debugInfo, csv, 3000);
#endif
    do
    {
        while(*csv != 'E'){csv++;}
    }while(memcmp(csv, "EEPROM", 6));
    // Arrivé au début de fichier csv
    while(*csv != '\n'){csv++;}
    while(*csv == '\n'){csv++;}
    
    do
    {
        int i = 0;
        char name[20];
        while(*csv != ',' && *csv != ';')
        {
            name[i] = *csv;
            csv++;
            i++;
        }
        csv++;
        name[i] = 0;
        
        if(!memcmp(name, "act", 3))
        {
            extern ActInfo act_MAIL, act_SNMP, act_NMS;
            ActInfo *act;
            if(!strcmp(name, "act mail"))       {act=&act_MAIL;}
            else if(!strcmp(name, "act snmp"))  {act=&act_SNMP;}
            else if(!strcmp(name, "act nms"))   {act=&act_NMS;}
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                int n;
#ifdef PIC_RF
                if(!memcmp(csv, "audio", 5))        {n=1<<0; csv += 5;}
                else if(!memcmp(csv, "input", 5))   {n=1<<1; csv += 5;}
                else if(!memcmp(csv, "mux", 3))     {n=1<<2; csv += 3;}
#endif
#ifdef PIC_AMPLI
                if      (!memcmp(csv, "fanar", 5))  {n=1<<0; csv += 5;}
                else if (!memcmp(csv, "fanav", 5))  {n=1<<1; csv += 5;}
                else if (!memcmp(csv, "in", 2))     {n=1<<2; csv += 2;}
                else if (!memcmp(csv, "outlow", 6)) {n=1<<3; csv += 6;}
                else if (!memcmp(csv, "outovr", 6)) {n=1<<4; csv += 6;}
                else if (!memcmp(csv, "swr", 3))    {n=1<<5; csv += 3;}
                else if (!memcmp(csv, "warswr", 6)) {n=1<<6; csv += 6;}
                else if (!memcmp(csv, "temp", 4))   {n=1<<7; csv += 4;}
#endif
                if(*csv == '=')
                {
                    csv++;
                    if(*csv - '0' == 1)
                    {
                        act->global = (act->global | (n));
                        j |= n; // Pour vérification
                    }
                    else if(*csv - '0' == 0)
                    {
                        act->global = (act->global & (~n));
                        j |= n; // Pour vérification
                    }
                }                  
                csv++;
            }
#ifdef PIC_RF
            if(j == 7)
#endif
#ifdef PIC_AMPLI
            if(j == 255) 
#endif
            {
                if(act == &act_MAIL)        {backUpIsOk[BCKUP_ACT_MAIL] = true;}
                else if(act == &act_SNMP)   {backUpIsOk[BCKUP_ACT_SNMP] = true;}
                else if(act == &act_NMS)    {backUpIsOk[BCKUP_ACT_NMS] = true;}
            }
        }
        else if(!strcmp(name, "mail enable"))
        {
            extern unsigned int mail_activation;
            mail_activation = *csv - '0';
            if(mail_activation == 1 || mail_activation == 0)
            {
                backUpIsOk[BCKUP_MAIL_ACT] = true;
            }
        }
        else if(!strcmp(name, "mail from"))
        {
            extern char from_mail[60];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                from_mail[j] = *csv;
                csv++;
                j++;
            }
            from_mail[j] = 0;
            backUpIsOk[BCKUP_MAIL_FROM] = true;
        }
        else if(!strcmp(name, "mail to"))
        {
            extern char to_mail[60];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                to_mail[j] = *csv;
                csv++;
                j++;
            }
            to_mail[j] = 0;
            backUpIsOk[BCKUP_MAIL_TO] = true;
        }
        else if(!strcmp(name, "name"))
        {// Change le nom du pic
            extern char unique_name[50];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                unique_name[j] = *csv;
                csv++;
                j++;
            }
            unique_name[j] = 0;
            backUpIsOk[BCKUP_NAME] = true;
        }
        else if(!strcmp(name, "ip address"))
        {// Change l'adresse du pic, effectif au redemmarage
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Save_Adresse_IP[j] = *csv;
                csv++;
                j++;
            }
            Save_Adresse_IP[j] = 0;
            backUpIsOk[BCKUP_IP_ADD] = true;
        }
        else if(!strcmp(name, "ip mask"))
        {// Change le mask du pic, effectif au redemmarage
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Save_Mask_IP[j] = *csv;
                csv++;
                j++;
            }
            Save_Mask_IP[j] = 0;
            backUpIsOk[BCKUP_IP_MASK] = true;
        }
        else if(!strcmp(name, "ip gateway"))
        {// Change la passerelle du pic, effectif au redemmarage
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Save_Gateway_IP[j] = *csv;
                csv++;
                j++;
            }
            Save_Gateway_IP[j] = 0;
            backUpIsOk[BCKUP_IP_GAT] = true;
        }
        else if(!strcmp(name, "ip dns"))
        {// Change le dns du pic, effectif au redemmarage
            extern char Save_DNS_IP[17];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Save_DNS_IP[j] = *csv;
                csv++;
                j++;
            }
            Save_DNS_IP[j] = 0;
            backUpIsOk[BCKUP_IP_DNS] = true;
        }
        else if(!strcmp(name, "ntp server"))
        {// Change le dns du pic, effectif au redemmarage
            extern char Save_NTP1[30];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Save_NTP1[j] = *csv;
                csv++;
                j++;
            }
            Save_NTP1[j] = 0;
            backUpIsOk[BCKUP_IP_NTP] = true;
        }
        else if(!strcmp(name, "route1.net"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[0].IP_Net))
            {
                routeconfig[0].IP_Net.v[0] = 0;
            }
            backUpIsOk[BCKUP_RT1_NET] = true;
        }
        else if(!strcmp(name, "route1.mask"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[0].IP_Mask))
            {
                routeconfig[0].IP_Mask.v[0] = 0;
            }
            backUpIsOk[BCKUP_RT1_MASK] = true;
        }
        else if(!strcmp(name, "route1.gat"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[0].IP_Route))
            {
                routeconfig[0].IP_Route.v[0] = 0;
            } // !!!!!!!!!!!!!!!!!
            backUpIsOk[BCKUP_RT1_GAT] = true;
        }
        else if(!strcmp(name, "route2.net"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[1].IP_Net))
            {
                routeconfig[1].IP_Net.v[0] = 0;
            }
            backUpIsOk[BCKUP_RT2_NET] = true;
        }
        else if(!strcmp(name, "route2.mask"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[1].IP_Mask))
            {
                routeconfig[1].IP_Mask.v[0] = 0;
            }
            backUpIsOk[BCKUP_RT2_MASK] = true;
        }
        else if(!strcmp(name, "route2.gat"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[1].IP_Route))
            {
                routeconfig[1].IP_Route.v[0] = 0;
            } // !!!!!!!!!!!!!!!!!
            backUpIsOk[BCKUP_RT2_GAT] = true;
        }
        else if(!strcmp(name, "route3.net"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[2].IP_Net))
            {
                routeconfig[2].IP_Net.v[0] = 0;
            }
            backUpIsOk[BCKUP_RT3_NET] = true;
        }
        else if(!strcmp(name, "route3.mask"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[2].IP_Mask))
            {
                routeconfig[2].IP_Mask.v[0] = 0;
            }
            backUpIsOk[BCKUP_RT3_MASK] = true;
        }
        else if(!strcmp(name, "route3.gat"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[2].IP_Route))
            {
                routeconfig[2].IP_Route.v[0] = 0;
            } // !!!!!!!!!!!!!!!!!
            backUpIsOk[BCKUP_RT3_GAT] = true;
        }
        else if(!strcmp(name, "route4.net"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[3].IP_Net))
            {
                routeconfig[3].IP_Net.v[0] = 0;
            }
            backUpIsOk[BCKUP_RT4_NET] = true;
        }
        else if(!strcmp(name, "route4.mask"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[3].IP_Mask))
            {
                routeconfig[3].IP_Mask.v[0] = 0;
            }
            backUpIsOk[BCKUP_RT4_MASK] = true;
        }
        else if(!strcmp(name, "route4.gat"))
        {
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &routeconfig[3].IP_Route))
            {
                routeconfig[3].IP_Route.v[0] = 0;
            } // !!!!!!!!!!!!!!!!!
            backUpIsOk[BCKUP_RT4_GAT] = true;
        }
        else if(!strcmp(name, "snmp enable"))
        {
            extern unsigned int snmp_activation;
            snmp_activation = *csv - '0';
            if(snmp_activation == 1 || snmp_activation == 0)
            {
                backUpIsOk[BCKUP_SNMP_ACT] = true;
            }
        }
        else if(!strcmp(name, "snmp1"))
        {// Change le serveur snmp
            extern SNMP_TRAP_INFO trapInfo;
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            trapInfo.table[0].Flags.bEnabled = true;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &trapInfo.table[0].IPAddress))
            {
                trapInfo.table[0].Flags.bEnabled = false;
                trapInfo.table[0].IPAddress.v[0] = 0;
            }
            backUpIsOk[BCKUP_SNMP1] = true;
        }
        else if(!strcmp(name, "snmp2"))
        {// Change le serveur snmp
            extern SNMP_TRAP_INFO trapInfo;
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            trapInfo.table[1].Flags.bEnabled = true;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &trapInfo.table[1].IPAddress))
            {
                trapInfo.table[1].Flags.bEnabled = false;
                trapInfo.table[1].IPAddress.v[0] = 0;
            }
            backUpIsOk[BCKUP_SNMP2] = true;
        }
        else if(!strcmp(name, "snmp3"))
        {// Change le serveur snmp
            extern SNMP_TRAP_INFO trapInfo;
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            trapInfo.table[2].Flags.bEnabled = true;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &trapInfo.table[2].IPAddress))
            {
                trapInfo.table[2].Flags.bEnabled = false;
                trapInfo.table[2].IPAddress.v[0] = 0;
            }
            backUpIsOk[BCKUP_SNMP3] = true;
        }
        else if(!strcmp(name, "snmp4"))
        {// Change le serveur snmp
            extern SNMP_TRAP_INFO trapInfo;
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            trapInfo.table[3].Flags.bEnabled = true;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &trapInfo.table[3].IPAddress))
            {
                trapInfo.table[3].Flags.bEnabled = false;
                trapInfo.table[3].IPAddress.v[0] = 0;
            }
            backUpIsOk[BCKUP_SNMP4] = true;
        }
        else if(!strcmp(name, "nms"))
        {// Change le serveur nms
            extern SNMP_TRAP_INFO trapInfo;
            int j = 0;
            char ip[17];
            while(*csv != '\r' && *csv != ';')
            {
                ip[j] = *csv;
                csv++;
                j++;
            }
            ip[j] = 0;
            trapInfo.table[4].Flags.bEnabled = true;
            if(!TCPIP_Helper_StringToIPAddress((char*)(ip), &trapInfo.table[4].IPAddress))
            {
                trapInfo.table[4].Flags.bEnabled = false;
                trapInfo.table[4].IPAddress.v[0] = 0;
            }
            backUpIsOk[BCKUP_NMS] = true;
        }
        else if(!strcmp(name, "ntp server"))
        {
            extern char Save_NTP1[30];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Save_NTP1[j] = *csv;
                csv++;
                j++;
            }
            Save_NTP1[j] = 0;
            backUpIsOk[BCKUP_IP_NTP] = true;
        }
        else if(!strcmp(name, "user"))
        {
            extern char User_x[40];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                User_x[j] = *csv;
                csv++;
                j++;
            }
            User_x[j] = 0;
            backUpIsOk[BCKUP_USER] = true;
        }
        else if(!strcmp(name, "pass"))
        {
            extern char Pass_x[40];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Pass_x[j] = *csv;
                csv++;
                j++;
            }
            Pass_x[j] = 0;
            backUpIsOk[BCKUP_PASS] = true;
        }
#ifdef PIC_AMPLI
        else if(!strcmp(name, "option out low"))
        {
            extern int Option_Out_Low;
            Option_Out_Low = *csv - '0';
            if(Option_Out_Low == 1 || Option_Out_Low == 0)
            {
                backUpIsOk[BCKUP_OPT_OUT_LOW] = true;
            }
        }
#endif
#ifdef PIC_RF
        else if(!strcmp(name, "option in low"))
        {
            extern int Option_In_Low;
            Option_In_Low = *csv - '0';
            if(Option_In_Low == 1 || Option_In_Low == 0)
            {
                backUpIsOk[BCKUP_OPT_IN_LOW] = true;
            }
        }

        else if(!strcmp(name, "ip nuc"))
        {
            extern char Adresse_IP_PC[17];
            CMDTEL_ChangeIpNuc(Adresse_IP_PC);
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Adresse_IP_PC[j] = *csv;
                csv++;
                j++;
            }
            Adresse_IP_PC[j] = 0;
            backUpIsOk[BCKUP_IP_NUC] = true;
        }
        else if(!strcmp(name, "bouquet"))
        {// Change le bouquet
            extern char Bouquet[10];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Bouquet[j] = *csv;
                csv++;
                j++;
            }
            Bouquet[j] = 0;
            backUpIsOk[BCKUP_BOUQUET] = true;
        }
        else if(!strcmp(name, "channel"))
        {// Change le canal, effectif au redemmarage
            extern int Choix_Channel_In;
            char tmp[10];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                tmp[j] = *csv;
                csv++;
                j++;
            }
            tmp[j] = 0;
            Choix_Channel_In = DAB_channel_stringToNum(tmp);
            if(Choix_Channel_In > 0)
            {
                backUpIsOk[BCKUP_CHAN] = true;
            }
        }
        else if(!strcmp(name, "ta"))
        {
            extern int Option_TAON;
            Option_TAON = *csv - '0';
            if(Option_TAON == 1 || Option_TAON == 0)
            {
                backUpIsOk[BCKUP_TA] = true;
            }
        }
        else if(!strcmp(name, "info traffic"))
        {
            extern char Text_info_Traffic[100];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                Text_info_Traffic[j] = *csv;
                csv++;
                j++;
            }
            Text_info_Traffic[j] = 0;
            backUpIsOk[BCKUP_INFO_TRAFFIC] = true;
        }
#endif
#if defined(PIC_RF) | defined(PIC_AMPLI)
        else if(!strcmp(name, "attenuation"))
        {// Change le canal, effectif au redemmarage
            extern int Valeur_ATT_Save;
            char tmp[10];
            int j = 0;
            while(*csv != '\r' && *csv != ';')
            {
                tmp[j] = *csv;
                csv++;
                j++;
            }
            tmp[j] = 0;
            Valeur_ATT_Save = (int)strtol(tmp, NULL, 10);
            tmp[0] = Valeur_ATT_Save % 5;
            if(Valeur_ATT_Save <= 250 && Valeur_ATT_Save % 5 == 0)
            {
                backUpIsOk[BCKUP_ATT] = true;
            }
        }
#endif        
        while(*csv != '\n'){csv++;}
        while(*csv == '\n'){csv++;}
    }while(memcmp(csv, "/EEPROM", 7));
#ifndef PIC_RF
    char Adresse_IP_PC[17];
#else
    extern char Adresse_IP_PC[17];
#endif
    if(controleBackUp() == true && controleNetwork(Save_Adresse_IP, Save_Mask_IP, Save_Gateway_IP, Adresse_IP_PC, Save_Gateway_IP) == true)
    {
        extern int Save_IP_NUC;
        strcpy(UploadState, "backup file processing successfull, device configuration modifying");
#ifdef PIC_RF
        Save_IP_NUC = 1;
#endif
        backupReady = 1;
        PIC_reset();
    }
    else
    {
        BCKUP_Popup("backup file processing canceled, backup file incorect or bad transaction, device restarting...");
        PIC_reset();
        backupReady = 0;
    }
}

void createBackup(void)
{
    extern char unique_name[50], Save_Adresse_IP[17], Save_Mask_IP[17], Save_Gateway_IP[17],
                Save_DNS_IP[17], Save_NTP1[30];
    extern char User_x[40], Pass_x[40];
    extern char to_mail[60], from_mail[60];
    extern char Adresse_IP_PC[17], Text_info_Traffic[100], Bouquet[10], Channel_In[4];
    extern ActInfo act_MAIL, act_SNMP, act_NMS;
    extern char unique_name[50];
    extern int Valeur_ATT_Save, Choix_Channel_In, Option_In_Low, Option_Out_Low;
    extern SNMP_TRAP_INFO trapInfo;
    extern int Jour_Reset1, Hour_Reset1, Minute_Reset1, Jour_Reset2, Hour_Reset2, Minute_Reset2;
    extern int Option_TAON;
    extern unsigned int snmp_activation;
    extern unsigned int mail_activation;
    int cpt = 0;
    char temp[100];
    
    backUp[0] = 0;
    strcat(backUp, "EEPROM,\r\n");
    for(cpt = 0; cpt < BCKUP_SIZE; cpt++)
    {
        char elem[100];
        switch(cpt)
        {   // Elements système
            case BCKUP_NAME:    strcpy(elem, unique_name); break;
            case BCKUP_IP_ADD:  strcpy(elem, Save_Adresse_IP); break;
            case BCKUP_IP_MASK: strcpy(elem, Save_Mask_IP); break; 
            case BCKUP_IP_GAT:  strcpy(elem, Save_Gateway_IP); break;
            case BCKUP_IP_DNS:  strcpy(elem, Save_DNS_IP); break;
            case BCKUP_IP_NTP:  strcpy(elem, Save_NTP1); break;
            // Routes
            case BCKUP_RT1_NET: TCPIP_Helper_IPAddressToString(&routeconfig[0].IP_Net, elem, sizeof(elem)); break;
            case BCKUP_RT1_MASK:TCPIP_Helper_IPAddressToString(&routeconfig[0].IP_Mask, elem, sizeof(elem)); break;
            case BCKUP_RT1_GAT: TCPIP_Helper_IPAddressToString(&routeconfig[0].IP_Route, elem, sizeof(elem)); break;
            case BCKUP_RT2_NET: TCPIP_Helper_IPAddressToString(&routeconfig[1].IP_Net, elem, sizeof(elem)); break;
            case BCKUP_RT2_MASK:TCPIP_Helper_IPAddressToString(&routeconfig[1].IP_Mask, elem, sizeof(elem)); break;
            case BCKUP_RT2_GAT: TCPIP_Helper_IPAddressToString(&routeconfig[1].IP_Route, elem, sizeof(elem)); break;  
            case BCKUP_RT3_NET: TCPIP_Helper_IPAddressToString(&routeconfig[2].IP_Net, elem, sizeof(elem)); break;
            case BCKUP_RT3_MASK:TCPIP_Helper_IPAddressToString(&routeconfig[2].IP_Mask, elem, sizeof(elem)); break;
            case BCKUP_RT3_GAT: TCPIP_Helper_IPAddressToString(&routeconfig[2].IP_Route, elem, sizeof(elem)); break;  
            case BCKUP_RT4_NET: TCPIP_Helper_IPAddressToString(&routeconfig[3].IP_Net, elem, sizeof(elem)); break;
            case BCKUP_RT4_MASK:TCPIP_Helper_IPAddressToString(&routeconfig[3].IP_Mask, elem, sizeof(elem)); break;
            case BCKUP_RT4_GAT: TCPIP_Helper_IPAddressToString(&routeconfig[3].IP_Route, elem, sizeof(elem)); break;  
            // NUC
#ifdef PIC_AMPLI
            case BCKUP_OPT_OUT_LOW:  sprintf(elem, "%1d", Option_Out_Low); break;
#endif
#ifdef PIC_RF
            case BCKUP_BOUQUET:     strcpy(elem, Bouquet); break;
            case BCKUP_CHAN:        strcpy(elem, Channel_In); break;
            case BCKUP_IP_NUC:      strcpy(elem, Adresse_IP_PC); break;
            case BCKUP_INFO_TRAFFIC:strcpy(elem, Text_info_Traffic); break;
            case BCKUP_OPT_IN_LOW:  sprintf(elem, "%1d", Option_In_Low); break;
            case BCKUP_TA:      sprintf(elem, "%1d", Option_TAON); break;
#endif
#if defined(PIC_RF) | defined(PIC_AMPLI)
            case BCKUP_ATT:     sprintf(elem, "%3d", Valeur_ATT_Save); break;
#endif
            // Activations
            ActInfo act;
            case BCKUP_ACT_MAIL: case BCKUP_ACT_SNMP: case BCKUP_ACT_NMS: 
                if      (cpt == BCKUP_ACT_MAIL) act = act_MAIL;
                else if (cpt == BCKUP_ACT_SNMP) act = act_SNMP;
                else if (cpt == BCKUP_ACT_NMS)  act = act_NMS;
#ifdef PIC_RF
                sprintf(elem, "audio=%1d|input=%1d|mux=%1d", act.flags.audio, act.flags.input, act.flags.mux);
#endif
#ifdef PIC_AMPLI
                sprintf(elem, "fanar=%1d|fanav=%1d|in=%1d|outlow=%1d|outovr=%1d|swr=%1d|warswr=%1d|temp=%1d", 
                        act.flags.FanAr, act.flags.FanAv, act.flags.In, act.flags.Output_Low, act.flags.Output_Over, act.flags.SWR, act.flags.War_SWR, act.flags.T);    
#endif
                
            break;
            case BCKUP_MAIL_ACT:    sprintf(elem, "%1d", mail_activation); break;
            case BCKUP_MAIL_FROM:   strcpy(elem, from_mail); break; 
            case BCKUP_MAIL_TO:     strcpy(elem, to_mail); break;
            // SNMP
            case BCKUP_SNMP_ACT:sprintf(elem, "%1d", snmp_activation); break;
            case BCKUP_SNMP1:   TCPIP_Helper_IPAddressToString(&trapInfo.table[0].IPAddress, elem, sizeof(elem)); break;
            case BCKUP_SNMP2:   TCPIP_Helper_IPAddressToString(&trapInfo.table[1].IPAddress, elem, sizeof(elem)); break;
            case BCKUP_SNMP3:   TCPIP_Helper_IPAddressToString(&trapInfo.table[2].IPAddress, elem, sizeof(elem)); break;
            case BCKUP_SNMP4:   TCPIP_Helper_IPAddressToString(&trapInfo.table[3].IPAddress, elem, sizeof(elem)); break;
            case BCKUP_NMS:     TCPIP_Helper_IPAddressToString(&trapInfo.table[4].IPAddress, elem, sizeof(elem)); break;
            // 
            case BCKUP_USER:    strcpy(elem, User_x); break;
            case BCKUP_PASS:    strcpy(elem, Pass_x); break;
        }
        
        sprintf(temp, BCKUP_NameElem[cpt], elem);
        strcat(backUp, temp);
    }
    strcat(backUp, "/EEPROM");
}

void BCKUP_Popup(char* msg)
{
    UploadStatePopUp = 1;
    strcpy(UploadState, msg);
}

bool BCKUP_Ready(void)
{
    return backupReady;
}
#endif
/* *****************************************************************************
 End of File
 */
