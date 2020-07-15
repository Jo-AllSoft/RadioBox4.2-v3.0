/*******************************************************************
 * FileName: mib.h
 * This file was automatically generated on jeu. nov. 02 2017 09:20:44
 * by mib2bib utility.
 * This file contains 'C' defines for dynamic OIDs and AgentID only.
 * Do not modify this file manually.
 * Include this file in your application source file that handles SNMP callbacks and TRAP.
 * 
 * Software License Agreement
 *
 * Copyright (C) 2012 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and 
 * distribute: 
 * (i)  the Software when embedded on a Microchip microcontroller or 
 *      digital signal controller product ("Device") which is 
 *      integrated into Licensee's product; or 
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *      ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *      used in conjunction with a Microchip ethernet controller for
 *      the sole purpose of interfacing with the ethernet controller.
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
 *******************************************************************/
#define MICROCHIP      255		// This is an Agent ID for use in SNMPNotify() only.
#define SYS_UP_TIME      250			//43.6.1.2.1.1.3 :  READONLY TIME_TICKS.
#define TRAP_MUX_ON      500			//43.6.1.4.1.17095.1.0.1 :  READONLY BYTE.
#define TRAP_MUX_OFF      501			//43.6.1.4.1.17095.1.0.2 :  READONLY BYTE.
#define TRAP_AUDIO_ON      502			//43.6.1.4.1.17095.1.0.3 :  READONLY BYTE.
#define TRAP_AUDIO_OFF      503			//43.6.1.4.1.17095.1.0.4 :  READONLY BYTE.
#define TRAP_INPUT_ON      504			//43.6.1.4.1.17095.1.0.5 :  READONLY BYTE.
#define TRAP_INPUT_OFF      505			//43.6.1.4.1.17095.1.0.6 :  READONLY BYTE.
#define TRAP_TEST      506			//43.6.1.4.1.17095.1.0.7 :  READONLY BYTE.
#define TRAP_INPUT_LOW      538			//43.6.1.4.1.17095.1.0.39 :  READONLY BYTE.
#define TRAP_RECEIVER_ID      1			//43.6.1.4.1.17095.1.2.1.1.1 :  READWRITE BYTE.
#define TRAP_RECEIVER_ENABLED      2			//43.6.1.4.1.17095.1.2.1.1.2 :  READWRITE BYTE.
#define TRAP_RECEIVER_IP      3			//43.6.1.4.1.17095.1.2.1.1.3 :  READWRITE IP_ADDRESS.
#define TRAP_COMMUNITY      4			//43.6.1.4.1.17095.1.2.1.1.4 :  READWRITE ASCII_STRING.
#define IPV6_TRAP_RECEIVER_ID      101			//43.6.1.4.1.17095.1.2.2.1.1 :  READWRITE BYTE.
#define IPV6_TRAP_ENABLED      102			//43.6.1.4.1.17095.1.2.2.1.2 :  READWRITE BYTE.
#define IPV6_TRAP_RECEIVER_IP      103			//43.6.1.4.1.17095.1.2.2.1.3 :  READWRITE OCTET_STRING.
#define IPV6_TRAP_COMMUNITY      104			//43.6.1.4.1.17095.1.2.2.1.4 :  READWRITE ASCII_STRING.
#define Control_MUX_ON      5			//43.6.1.4.1.17095.1.3.3 :  READONLY ASCII_STRING.
#define Control_MUX_OFF      6			//43.6.1.4.1.17095.1.3.4 :  READONLY ASCII_STRING.
#define Control_AUDIO_ON      7			//43.6.1.4.1.17095.1.3.5 :  READONLY ASCII_STRING.
#define Control_AUDIO_OFF      8			//43.6.1.4.1.17095.1.3.6 :  READONLY ASCII_STRING.
#define Control_INPUT_ON      9			//43.6.1.4.1.17095.1.3.7 :  READONLY ASCII_STRING.
#define Control_INPUT_OFF      10			//43.6.1.4.1.17095.1.3.8 :  READONLY ASCII_STRING.
#define Control_TEST      11			//43.6.1.4.1.17095.1.3.9 :  READONLY ASCII_STRING.
#define Control_INPUT_LOW      42			//43.6.1.4.1.17095.1.3.40 :  READONLY ASCII_STRING.
#define USM_INDEX_ID      50			//43.6.1.4.1.17095.1.4.1.1.1 :  READONLY BYTE.
#define USER_SECURITY_NAME      51			//43.6.1.4.1.17095.1.4.1.1.2 :  READWRITE ASCII_STRING.
#define USM_AUTH_PROT      52			//43.6.1.4.1.17095.1.4.1.1.3 :  READWRITE BYTE.
#define USM_AUTH_KEY      53			//43.6.1.4.1.17095.1.4.1.1.4 :  READWRITE ASCII_STRING.
#define USM_PRIV_PROT      54			//43.6.1.4.1.17095.1.4.1.1.5 :  READWRITE BYTE.
#define USM_PRIV_KEY      55			//43.6.1.4.1.17095.1.4.1.1.6 :  READWRITE ASCII_STRING.
#define SNMP_TARGET_INDEX_ID      56			//43.6.1.4.1.17095.1.5.1.1.1 :  READONLY BYTE.
#define SNMP_TARGET_MP_MODEL      57			//43.6.1.4.1.17095.1.5.1.1.2 :  READWRITE BYTE.
#define SNMP_TARGET_SECURITY_MODEL      58			//43.6.1.4.1.17095.1.5.1.1.3 :  READWRITE BYTE.
#define SNMP_TARGET_SECURITY_NAME      59			//43.6.1.4.1.17095.1.5.1.1.4 :  READWRITE ASCII_STRING.
#define SNMP_TARGET_SECURITY_LEVEL      60			//43.6.1.4.1.17095.1.5.1.1.5 :  READWRITE BYTE.
#define ENGINE_ID      249			//43.6.1.6.3.10.2.1.1 :  READONLY ASCII_STRING.
#define ENGINE_BOOT      248			//43.6.1.6.3.10.2.1.2 :  READONLY DWORD.
#define ENGINE_TIME      247			//43.6.1.6.3.10.2.1.3 :  READONLY DWORD.
#define ENGINE_MAX_MSG      246			//43.6.1.6.3.10.2.1.4 :  READONLY WORD.
