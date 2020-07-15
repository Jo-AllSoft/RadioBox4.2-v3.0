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

#ifndef _CUSTOM_SNMP_APP_H    /* Guard against multiple inclusion */
#define _CUSTOM_SNMP_APP_H

#include "app.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
typedef struct tSNMP_TRAP_INFO
{
   uint8_t Size;
   struct
   {
       uint8_t communityLen;	//Community name length
       char community[TCPIP_SNMP_COMMUNITY_MAX_LEN];         //TCPIP_SNMP_TRAP_COMMUNITY_MAX_LEN   Community name array
       IPV4_ADDR IPAddress;     //IP address to which trap to be sent
       struct
       {
           unsigned int bEnabled : 1;   //Trap enabled flag
       } Flags;
   } table[TCPIP_SNMP_TRAP_TABLE_SIZE];
} SNMP_TRAP_INFO;








// Sert à l'envoi des traps (switch dans la fonction SNMP_Send_Trap)
typedef enum {SNMP_MUX_OFF, SNMP_MUX_ON, SNMP_DAB_OFF, SNMP_DAB_ON} SNMP_Trap;
// Gère l'envoi des traps, utiliser SNMP_Send_Trap pour envoyer une trap
extern void SNMPTrap(void); 
extern void SNMPTrap_Swox(void);
#define SNMP_TX_SIZE 10     // Nombre de trap simultanées maximum
extern int SNMP_active;
extern int SNMP_active_Swox;
extern SNMP_ID SNMP_trap[SNMP_TX_SIZE], SNMP_id[SNMP_TX_SIZE];
extern SNMP_ID SNMP_trap_Swox[SNMP_TX_SIZE], SNMP_id_Swox[SNMP_TX_SIZE];
typedef enum {MUX_ON, MUX_OFF, AUDIO_ON, AUDIO_OFF, INPUT_ON, INPUT_OFF, TEST,
        INPUT_LOW} SNMP_Type;
extern void SNMP_Send_Trap(SNMP_Type SNMP_type, int act);
extern void SNMP_Send_Trap_Swox(SNMP_Type SNMP_type, int act);
extern SNMP_TRAP_INFO trapInfo;
#endif /* _CUSTOM_SNMP_APP_H */

/* *****************************************************************************
 End of File
 */
