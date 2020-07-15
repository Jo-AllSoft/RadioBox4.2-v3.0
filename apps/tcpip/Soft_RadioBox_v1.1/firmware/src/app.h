/*******************************************************************************
  File Name:
    app.h

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

#ifndef _APP_HEADER_H
#define _APP_HEADER_H



#define WIFI_TCPIP_WEB_SERVER_DEMO
#define WIFI_TCPIP_WEB_SERVER_DEMO_VERSION "1.0"

#define VERSION "24.01.2019 - RDBX 1.1"
#define TABLE_DE_MIX
#define ECRAN 2


//#define PIC_MONITORING_ENABLE
#ifdef __DEBUG
    char debugInfo[3000];
#endif
    
typedef struct
{
    unsigned int time;
    unsigned int error;
}I2C_Error;
    
#define MAX_NUMBER_OF_BUFFERS                   10
    
#define GetSystemClock() (80000000UL)/* Fcy = 80MHz */
#define us_SCALE   (GetSystemClock()/2000000)
#define ms_SCALE   (GetSystemClock()/2000)
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE

#include "system_config.h"
#include "system_definitions.h"
#include "Mc32Delays.h"
#include "bsp_config.h"
#include "Type_Def32.h"
#include "string.h"


#include "tcpip/tcpip.h"
#include "custom_snmp_app.h"
#include "TDRS/gest_EEPROM.h"
#include "TDRS/gest_PC_MUX_PIC.h"
#include "TDRS/gest_Upload.h"

#if(ECRAN == 1)
    #include "Mc32gestSpiFT800.h"
#elif(ECRAN > 1)
    #include "Mux_gestSpiFT800.h"   
#endif
    
#include "Audio_PT2314.h"
#include "Expender_i2c_TCA9548A.h"
#include "ADC_DAC_AD5593.h"
#include "Fct_Ecran.h"


#include "driver/usart/drv_usart.h"
#include "App_Task_Usart.h"



//#include "TDRS/gest_I2C.h"
#ifdef PIC_RF
#include "gest_DAB.h"
#include "gest_TELNET.h"
#endif

#define LIGNE1 1
#define LIGNE2 2
#define PHONE1 3
#define PHONE2 4
#define PHONE3 5
#define PHONE4 6
#define PHONEDJ 7

#define GAIN_POT_ACTIF 1
#define GAIN_WEB_ACTIF 0

#define  MODE_ON_AIR 1
#define  MODE_MUTE 2

typedef union
{
    int Calibration_32;
    uint8 Calibration_8[4];   
}Calibration_Memoire;

Calibration_Memoire Valeur_Calibration[6];
Calibration_Memoire Valeur_Calibration2[6];

typedef struct
{
    bool R1Manuel:1;
    bool R1AutoOn:1;
    bool R2Manuel:1;
    bool R2AutoOn:1;
    bool R3Manuel:1;
    bool R3AutoOn:1;
    bool R4Manuel:1;
    bool R4AutoOn:1;
}GestionRelais;
typedef union 
{
    uint8_t global;
    GestionRelais relais;  
}Relais;

typedef struct
{
    IPV4_ADDR add_IP;
    unsigned int nbPingsOK;
    unsigned int nbPingsNOK;
    bool ping_ok;
    bool conn_ok;
    uint16_t waitingOn;
    uint16_t delayReset;
    uint16_t ping_id;
    TCPIP_NET_HANDLE net_handle;
    ICMP_HANDLE handle;
}PingParam;


typedef struct 
{
    uint8 Loudness;
    float Gain;
    float Volume;
    float R;
    float L;
    int Basse;
    int Aigue;
    float ReductionMax;
    float Niveau_Overload; //niveau en Mv pour detecter l'overloed sur l'entree ligne
    float Niveau_Stop_Overload; // niveau en mV pour detecter le muting
    int Time_Mute;//temps d'attente sans son pour retirer la reduction
    
    
}Niveau_In;

typedef struct 
{
    bool Loudness;
    float Gain;
    float Volume;
    float R;
    float L;
    int Basse;
    int Aigue;  
}Niveau_Out;

typedef struct 
{    
    bool Master_Gain;
    char Name_Config[20];
    Niveau_In Device_IN[6];
    Niveau_Out Device_OUT[7];
    
}Save_Config;

int Config_Used;
Save_Config Nconfig[5];
Save_Config NconfigDefaut[5];






//typedef enum{All_MUTING,SONG_PHONE1,SONG_PHONE2,SONG_PHONE3,SONG_PHONE4,SONG_PHONEDJ}MODE_BTN;
#if defined(TCPIP_IF_MRF24W) /* Wi-Fi Interface */
#include "driver/wifi/mrf24w/src/drv_wifi_config_data.h"
#include "driver/wifi/mrf24w/src/drv_wifi_iwpriv.h"
#elif defined(TCPIP_IF_MRF24WN)
#include "wdrv_mrf24wn_iwpriv.h"
#endif /* Wi-Fi Interface */

#if defined(TCPIP_IF_MRF24W) /* Wi-Fi Interface */

#define WF_DISABLED DRV_WIFI_DISABLED
#define WF_ENABLED DRV_WIFI_ENABLED

#define WF_NETWORK_TYPE_INFRASTRUCTURE DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE
#define WF_NETWORK_TYPE_ADHOC DRV_WIFI_NETWORK_TYPE_ADHOC
#define WF_NETWORK_TYPE_P2P 0xff /* Unsupported */
#define WF_NETWORK_TYPE_SOFT_AP DRV_WIFI_NETWORK_TYPE_SOFT_AP

#define WF_SECURITY_OPEN DRV_WIFI_SECURITY_OPEN
#define WF_SECURITY_WEP_40 DRV_WIFI_SECURITY_WEP_40
#define WF_SECURITY_WEP_104 DRV_WIFI_SECURITY_WEP_104
#define WF_SECURITY_WPA_WITH_KEY DRV_WIFI_SECURITY_WPA_WITH_KEY
#define WF_SECURITY_WPA_WITH_PASS_PHRASE DRV_WIFI_SECURITY_WPA_WITH_PASS_PHRASE
#define WF_SECURITY_WPA2_WITH_KEY DRV_WIFI_SECURITY_WPA2_WITH_KEY
#define WF_SECURITY_WPA2_WITH_PASS_PHRASE DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE
#define WF_SECURITY_WPA_AUTO_WITH_KEY DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY
#define WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE
#define WF_SECURITY_WPS_PUSH_BUTTON DRV_WIFI_SECURITY_WPS_PUSH_BUTTON
#define WF_SECURITY_WPS_PIN DRV_WIFI_SECURITY_WPS_PIN

#define WF_DEFAULT_ADHOC_HIDDEN_SSID DRV_WIFI_DEFAULT_ADHOC_HIDDEN_SSID
#define WF_DEFAULT_ADHOC_BEACON_PERIOD DRV_WIFI_DEFAULT_ADHOC_BEACON_PERIOD
#define WF_DEFAULT_ADHOC_MODE DRV_WIFI_DEFAULT_ADHOC_MODE

#define WF_DEFAULT_POWER_SAVE DRV_WIFI_DEFAULT_POWER_SAVE

#define WF_WEP_KEY_INVALID 0xff

#define WF_ASSERT(condition, msg) DRV_WIFI_ASSERT(condition, msg)

typedef DRV_WIFI_SCAN_RESULT WF_SCAN_RESULT;
typedef DRV_WIFI_CONFIG_DATA WF_CONFIG_DATA;
typedef DRV_WIFI_DEVICE_INFO WF_DEVICE_INFO;
typedef DRV_WIFI_ADHOC_NETWORK_CONTEXT WF_ADHOC_NETWORK_CONTEXT;

#elif defined(TCPIP_IF_MRF24WN) /* Wi-Fi Interface */

#define WF_DISABLED WDRV_FUNC_DISABLED
#define WF_ENABLED WDRV_FUNC_ENABLED

#define WF_NETWORK_TYPE_INFRASTRUCTURE WDRV_NETWORK_TYPE_INFRASTRUCTURE
#define WF_NETWORK_TYPE_ADHOC WDRV_NETWORK_TYPE_ADHOC
#define WF_NETWORK_TYPE_P2P WDRV_NETWORK_TYPE_P2P
#define WF_NETWORK_TYPE_SOFT_AP WDRV_NETWORK_TYPE_SOFT_AP

#define WF_SECURITY_OPEN WDRV_SECURITY_OPEN
#define WF_SECURITY_WEP_40 WDRV_SECURITY_WEP_40
#define WF_SECURITY_WEP_104 WDRV_SECURITY_WEP_104
#define WF_SECURITY_WPA_WITH_KEY 0xff /* Unsupported */
#define WF_SECURITY_WPA_WITH_PASS_PHRASE WDRV_SECURITY_WPA_WITH_PASS_PHRASE
#define WF_SECURITY_WPA2_WITH_KEY 0xff /* Unsupported */
#define WF_SECURITY_WPA2_WITH_PASS_PHRASE WDRV_SECURITY_WPA2_WITH_PASS_PHRASE
#define WF_SECURITY_WPA_AUTO_WITH_KEY 0xff /* Unsupported */
#define WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE 0xff /* Unsupported */
#define WF_SECURITY_WPS_PUSH_BUTTON WDRV_SECURITY_WPS_PUSH_BUTTON
#define WF_SECURITY_WPS_PIN WDRV_SECURITY_WPS_PIN

#define WF_DEFAULT_ADHOC_HIDDEN_SSID WDRV_DEFAULT_ADHOC_HIDDEN_SSID
#define WF_DEFAULT_ADHOC_BEACON_PERIOD WDRV_DEFAULT_ADHOC_BEACON_PERIOD
#define WF_DEFAULT_ADHOC_MODE WDRV_DEFAULT_ADHOC_MODE

#define WF_DEFAULT_POWER_SAVE WDRV_DEFAULT_POWER_SAVE

#define WF_WEP_KEY_INVALID 0xff

#define WF_ASSERT(condition, msg) WDRV_ASSERT(condition, msg)

typedef WDRV_SCAN_RESULT WF_SCAN_RESULT;
typedef WDRV_CONFIG_DATA WF_CONFIG_DATA;
typedef WDRV_DEVICE_INFO WF_DEVICE_INFO;
typedef WDRV_ADHOC_NETWORK_CONTEXT WF_ADHOC_NETWORK_CONTEXT;

#endif /* Wi-Fi Interface */

/* It is intentionally declared this way to sync with DRV_WIFI_DEVICE_TYPE. */
typedef enum {
    MRF24WG_MODULE = 2,
    MRF24WN_MODULE = 3
} MRF24W_MODULE_TYPE;

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
typedef uintptr_t APP_I2C_DRIVER_HANDLE;

typedef uintptr_t APP_I2C_BUFFER_HANDLE;
// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behaviour of the application at various times.
 */


typedef enum
{
    /* The application mounts the disk. */
    APP_MOUNT_DISK = 0,

    /* In this state, the application waits for the initialization of the TCP/IP stack
       to complete. */
    APP_TCPIP_WAIT_INIT,

    /* The application configures the Wi-Fi settings. */
    APP_WIFI_CONFIG,

    /* In this state, the application runs the Wi-Fi prescan. */
    APP_WIFI_PRESCAN,

    /* In this state, the application enables TCP/IP modules such as DHCP, NBNS and mDNS
       in all available interfaces. */
    APP_TCPIP_MODULES_ENABLE,

    /* In this state, the application can do TCP/IP transactions. */
    APP_TCPIP_TRANSACT,

    /* The application waits in this state for the driver to be ready
       before sending the "hello world" message. */
    //APP_STATE_WAIT_FOR_READY,

    /* The application waits in this state for the driver to finish
       sending the message. */
    //APP_STATE_WAIT_FOR_DONE,

    /* The application does nothing in the idle state. */
    //APP_STATE_IDLE

    APP_USERIO_LED_DEASSERTED,

    APP_USERIO_LED_ASSERTED,

    APP_TCPIP_ERROR,

} APP_STATE;

typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE2_INIT=0,
        APP_STATE2_EXEC = 1,
        APP_STATE2_WAIT = 2,
        APP_STATE2_Calibration = 3,
        APP_STATE2_MESURE_AD = 4,


	/* TODO: Define states used by the application state machine. */

} APP_STATES2;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */
typedef struct
{
    /* SYS_FS file handle */
    SYS_FS_HANDLE fileHandle;

    /* application's current state */
    APP_STATE state;
    APP_STATES2 state2;
    
        /* I2C Driver Handle  */
    APP_I2C_DRIVER_HANDLE               drvI2CHandle_Master;

    APP_I2C_DRIVER_HANDLE               drvI2CHandle_Slave;      
    
    APP_I2C_BUFFER_HANDLE               drvI2CTxRxBufferHandle[MAX_NUMBER_OF_BUFFERS];
    
    APP_I2C_BUFFER_HANDLE               drvI2CSlaveReadHandle;
    
    APP_I2C_BUFFER_HANDLE               drvI2CSlaveWriteHandle;
} APP_DATA;

typedef struct {
    uint8_t ssid[32 + 1]; // 32-byte SSID plus null terminator
    uint8_t networkType;
    uint8_t prevSSID[32 + 1]; // previous SSID
    uint8_t prevNetworkType; // previous network type
    uint8_t wepKeyIndex;
    uint8_t securityMode;
    uint8_t securityKey[64 + 1]; // 64-byte key plus null terminator
    uint8_t securityKeyLen; // number of bytes in security key (can be 0)
} WF_REDIRECTION_CONFIG;

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize(void)

  Summary:
     This routine initializes the application object.

  Description:
    This routine initializes the application object. The application state is
    set to wait for media attach.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
 */
void APP_Initialize(void);

/*******************************************************************************
  Function:
    void APP_Tasks(void)

  Summary:
    Application Tasks Function

  Description:
    This routine implements the application in a non blocking manner.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this function.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */
void APP_Tasks(void);
void APP_UpdateState ( APP_STATE NewState  ) ;
void APP_UpdateState2 ( APP_STATES2 NewState  ) ;






#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
 */
