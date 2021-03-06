/*********************************************************************
 * File Name: http_print.c
 *
 * Provides callback headers and resolution for user's custom
 * HTTP Application.
 * 
 * This file is automatically generated by the MPFS Utility
 * ALL MODIFICATIONS WILL BE OVERWRITTEN BY THE MPFS GENERATOR
 *
 * Software License Agreement
 *
 * Copyright (C) 2012 Microchip Technology Inc.  All rights
 * reserved.
 * Microchip licenses to you the right to use, modify, copy, and distribute
 * software only embedded on a Microchip microcontroller or digital signal 
 * controller that is integrated into your product or third party product
 * (pursuant to the sublicense terms in the accompanying license agreement)

 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *********************************************************************/

#include "tcpip/tcpip.h"

void TCPIP_HTTP_Print(HTTP_CONN_HANDLE connHandle,uint32_t callbackID);
void TCPIP_HTTP_Print_AudioInSelect(HTTP_CONN_HANDLE connHandle,uint16_t);
void TCPIP_HTTP_Print_LoudnessChecked(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_ValV(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_ValR(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_ValL(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_ValB(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_ValA(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_AudioOutSelect(HTTP_CONN_HANDLE connHandle,uint16_t);
void TCPIP_HTTP_Print_Val_Basse_Out(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Val_Aigue_Out(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_EEPROM(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_config_ver(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_config_name(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_config_ip(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_config_gw(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_config_subnet(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_config_dns1(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_config_NTP(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_dst1(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_mask1(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_interface1(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_dst2(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_mask2(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_interface2(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_dst3(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_mask3(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_interface3(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_dst4(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_mask4(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_Config_rte_interface4(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_uploadedmd5(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_stateBackup(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_stateBackupPopup(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_BCKUP_Ready(HTTP_CONN_HANDLE connHandle);

void TCPIP_HTTP_Print(HTTP_CONN_HANDLE connHandle,uint32_t callbackID)
{
    TCP_SOCKET sktHTTP; 
    switch(callbackID)
    {
        case 0x00000000:
			TCPIP_HTTP_FileInclude(connHandle,(const uint8_t *)"header.inc");
			break;
        case 0x00000001:
			TCPIP_HTTP_Print_AudioInSelect(connHandle,0);
			break;
        case 0x00000002:
			TCPIP_HTTP_Print_AudioInSelect(connHandle,1);
			break;
        case 0x00000003:
			TCPIP_HTTP_Print_AudioInSelect(connHandle,2);
			break;
        case 0x00000004:
			TCPIP_HTTP_Print_AudioInSelect(connHandle,3);
			break;
        case 0x00000005:
			TCPIP_HTTP_Print_AudioInSelect(connHandle,4);
			break;
        case 0x00000006:
			TCPIP_HTTP_Print_AudioInSelect(connHandle,5);
			break;
        case 0x00000007:
			TCPIP_HTTP_Print_LoudnessChecked(connHandle);
			break;
        case 0x00000008:
			TCPIP_HTTP_Print_ValV(connHandle);
			break;
        case 0x00000009:
			TCPIP_HTTP_Print_ValR(connHandle);
			break;
        case 0x0000000a:
			TCPIP_HTTP_Print_ValL(connHandle);
			break;
        case 0x0000000b:
			TCPIP_HTTP_Print_ValB(connHandle);
			break;
        case 0x0000000c:
			TCPIP_HTTP_Print_ValA(connHandle);
			break;
        case 0x0000000d:
			TCPIP_HTTP_FileInclude(connHandle,(const uint8_t *)"footer.inc");
			break;
        case 0x0000000e:
			TCPIP_HTTP_Print_AudioOutSelect(connHandle,0);
			break;
        case 0x0000000f:
			TCPIP_HTTP_Print_AudioOutSelect(connHandle,1);
			break;
        case 0x00000010:
			TCPIP_HTTP_Print_AudioOutSelect(connHandle,2);
			break;
        case 0x00000011:
			TCPIP_HTTP_Print_AudioOutSelect(connHandle,3);
			break;
        case 0x00000012:
			TCPIP_HTTP_Print_AudioOutSelect(connHandle,4);
			break;
        case 0x00000013:
			TCPIP_HTTP_Print_AudioOutSelect(connHandle,5);
			break;
        case 0x00000014:
			TCPIP_HTTP_Print_AudioOutSelect(connHandle,6);
			break;
        case 0x00000015:
			TCPIP_HTTP_Print_Val_Basse_Out(connHandle);
			break;
        case 0x00000016:
			TCPIP_HTTP_Print_Val_Aigue_Out(connHandle);
			break;
        case 0x00000017:
			TCPIP_HTTP_Print_EEPROM(connHandle);
			break;
        case 0x00000018:
			TCPIP_HTTP_Print_config_ver(connHandle);
			break;
        case 0x00000019:
			TCPIP_HTTP_Print_config_name(connHandle);
			break;
        case 0x0000001a:
			TCPIP_HTTP_Print_config_ip(connHandle);
			break;
        case 0x0000001b:
			TCPIP_HTTP_Print_config_gw(connHandle);
			break;
        case 0x0000001c:
			TCPIP_HTTP_Print_config_subnet(connHandle);
			break;
        case 0x0000001d:
			TCPIP_HTTP_Print_config_dns1(connHandle);
			break;
        case 0x0000001e:
			TCPIP_HTTP_Print_config_NTP(connHandle);
			break;
        case 0x0000001f:
			TCPIP_HTTP_Print_Config_rte_dst1(connHandle);
			break;
        case 0x00000020:
			TCPIP_HTTP_Print_Config_rte_mask1(connHandle);
			break;
        case 0x00000021:
			TCPIP_HTTP_Print_Config_rte_interface1(connHandle);
			break;
        case 0x00000022:
			TCPIP_HTTP_Print_Config_rte_dst2(connHandle);
			break;
        case 0x00000023:
			TCPIP_HTTP_Print_Config_rte_mask2(connHandle);
			break;
        case 0x00000024:
			TCPIP_HTTP_Print_Config_rte_interface2(connHandle);
			break;
        case 0x00000025:
			TCPIP_HTTP_Print_Config_rte_dst3(connHandle);
			break;
        case 0x00000026:
			TCPIP_HTTP_Print_Config_rte_mask3(connHandle);
			break;
        case 0x00000027:
			TCPIP_HTTP_Print_Config_rte_interface3(connHandle);
			break;
        case 0x00000028:
			TCPIP_HTTP_Print_Config_rte_dst4(connHandle);
			break;
        case 0x00000029:
			TCPIP_HTTP_Print_Config_rte_mask4(connHandle);
			break;
        case 0x0000002a:
			TCPIP_HTTP_Print_Config_rte_interface4(connHandle);
			break;
        case 0x0000002b:
			TCPIP_HTTP_Print_uploadedmd5(connHandle);
			break;
        case 0x0000002c:
			TCPIP_HTTP_Print_stateBackup(connHandle);
			break;
        case 0x0000002d:
			TCPIP_HTTP_Print_stateBackupPopup(connHandle);
			break;
        case 0x0000002e:
			TCPIP_HTTP_Print_BCKUP_Ready(connHandle);
			break;
        default:
            // Output notification for undefined values
            sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
            TCPIP_TCP_ArrayPut(sktHTTP, (const uint8_t *)"!DEF", 4);
    }
    return;
}

void TCPIP_HTTP_Print_myVariable(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_TCP_Put(sktHTTP, '~');
    return;
}
