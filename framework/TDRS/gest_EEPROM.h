/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _GEST_EEPROM_H    /* Guard against multiple inclusion */
#define _GEST_EEPROM_H

#include "app.h"
#include "EEPROM_24LC256.h"

typedef struct 
{
    char* data;
    bool change;
}EEPROM_Data;
typedef enum {CHAR_TYPE,CHAR_TAB_TYPE, STRING_TYPE, IP_STRING_TYPE, IP_NUM_TYPE, IP_NUM_MASK_TYPE, MAINTENANCE_TYPE, CALIBRATION_TYPE} EEPROM_Type;
typedef struct EEPROM_Element EEPROM_Element;
struct EEPROM_Element
{
    EEPROM_Data mem;
    int start;
    int size;
    int byteToChange;
    EEPROM_Type type;
    EEPROM_Element* nextElm;
};

void EEPROM_Maintenance_csv_Write(char* msgToAdd);
char* EEPROM_Maintenance_csv_Read(void);
void EEPROM_Maintenance_csv_Reset(void);
void EEPROM_Start_List(void);


void EEPROM_Task(void);

#define EEPROM_AddAndRead(d,start,end,type,def) EEPROM_AddAndRead_1((char*)d,start,end,type,(char*)def)
#define EEPROM_SaveData(d) EEPROM_SaveData_1((char*)d)
#define EEPROM_IsSaved(d) EEPROM_IsSaved_1((char*)d)
#define EEPROM_ReadData(d,def) EEPROM_ReadData_1((char*)d, (char*)def)

void EEPROM_SaveAll(void);
bool EEPROM_IsAllSaved(void);
void EEPROM_EraseAll(void);
void EEPROM_SaveNow(void);

EEPROM_Data* EE_rst_soft;
// Lecture des activations, toutes activées par défaut
EEPROM_Data* EE_act_MAIL;
EEPROM_Data* EE_act_SNMP;
EEPROM_Data* EE_act_NMS;
// Lecture mails
EEPROM_Data* EE_From;
EEPROM_Data* EE_Email;

EEPROM_Data* EE_Bouquet;
EEPROM_Data* EE_ChoixChanelIn; // 13F
// Lecture des configurations réseau
EEPROM_Data* EE_uniqueName;
EEPROM_Data* EE_AddIp;
EEPROM_Data* EE_MaskIp;
EEPROM_Data* EE_GateIp;
EEPROM_Data* EE_DnsIp;
// Lecture adresses serveurs SNMP
EEPROM_Data* EE_ServSNMP1;
EEPROM_Data* EE_ServSNMP2;
EEPROM_Data* EE_ServSNMP3;
EEPROM_Data* EE_ServSNMP4;
EEPROM_Data* EE_ServNMS;
// Lecture des reset du PC
EEPROM_Data* EE_JourReset1;
EEPROM_Data* EE_HourReset1;
EEPROM_Data* EE_MinuteReset1;
EEPROM_Data* EE_JourReset2;
EEPROM_Data* EE_HourReset2;
EEPROM_Data* EE_MinuteReset2;
// Lecture des logs utilisateurs
EEPROM_Data* EE_User_x;
EEPROM_Data* EE_Pass_x;
// Lecture de l'adresse IP du NUC
EEPROM_Data* EE_AddIpPC;
// Options
EEPROM_Data* EE_TA_ON;
EEPROM_Data* EE_OP_IN_LOW;
// Lecture infos police
EEPROM_Data* EE_TxtInfoTraffic;
// Bootloader
EEPROM_Data* EE_StopBoot;
#endif /* _GEST_EEPROM_H */

/* *****************************************************************************
 End of File
 */
