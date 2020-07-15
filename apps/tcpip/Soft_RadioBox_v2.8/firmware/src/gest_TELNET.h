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

#ifndef _GEST_TELNET_H    /* Guard against multiple inclusion */
#define _GEST_TELNET_H

#include <stdbool.h>                    // Defines true
#include "tcpip/tcpip.h"

typedef enum {CMDTEL_STARTUP_BOUQUET, CMDTEL_RESTART, CMDTEL_REMOVE_LOGS, CMDTEL_CHANGE_DLS, CMDTEL_CHANGE_IP_NUC, CMDTEL_TUNNEL_TA, CMDTEL_STANDBY}TELNET_COMMANDS;
void TELNET_Task(void);
void CMDTEL_Start(TELNET_COMMANDS cmd);
void CMDTEL_ChangeIpNuc(char* ip);
bool CMDTEL_Ready(void);
void CMDTEL_NewIpNuc(char* ip, char* mask, char* gateway);
void CMDTEL_ChangeDLS(char* dls);
char* CMDTEL_PrintState(char* msg);
char* CMDTEL_PrintStatement(char* msg);
#endif /* _GEST_TELNET_H */

/* *****************************************************************************
 End of File
 */
