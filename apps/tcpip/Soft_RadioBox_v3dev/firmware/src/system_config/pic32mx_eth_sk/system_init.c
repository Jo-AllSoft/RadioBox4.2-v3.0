/*******************************************************************************
  System Initialization File

  File Name:
    system_init.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits, 
    and allocates any necessary global system resources, such as the 
    sysObj structure that contains the object handles to all the MPLAB Harmony 
    module objects in the system.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the righEt to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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

#include "system_config.h"
#include "system_definitions.h"
#include "app.h"
#include "peripheral/usart/plib_usart.h"
//#include "peripheral/int/plib_int.h"
#include "EEPROM_24LC256.h"
#include "Mc32_I2cNew.h"
#include "Mc32Delays.h"
#include "custom_snmp_app.h"
#include "EEPROM_Driver.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
// <editor-fold defaultstate="collapsed" desc="Configuration Bits">

/*** DEVCFG0 ***/

#pragma config DEBUG =      OFF
#pragma config ICESEL =     ICS_PGx2
#pragma config PWP =        OFF
#pragma config BWP =        OFF
#pragma config CP =         OFF

/*** DEVCFG1 ***/

#pragma config FNOSC =      PRIPLL
#pragma config FSOSCEN =    OFF
#pragma config IESO =       OFF
#pragma config POSCMOD =    HS
#pragma config OSCIOFNC =   OFF
#pragma config FPBDIV =     DIV_1
#pragma config FCKSM =      CSDCMD
#pragma config WDTPS =      PS4096
#pragma config FWDTEN =     ON
/*** DEVCFG2 ***/

#pragma config FPLLIDIV =   DIV_2
#pragma config FPLLMUL =    MUL_20
#pragma config FPLLODIV =   DIV_1
#pragma config UPLLIDIV =   DIV_12
#pragma config UPLLEN =     OFF
/*** DEVCFG3 ***/

#pragma config USERID =     0xffff
#pragma config FSRSSEL =    PRIORITY_7
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     ON
#pragma config FCANIO =     OFF
#pragma config FUSBIDIO =   OFF
#pragma config FVBUSONIO =  OFF
// </editor-fold>

extern char Save_Adresse_IP[17];
extern char Save_Mask_IP[17];
extern char Save_Gateway_IP[17];
extern char Save_DNS_IP[17];
char ALL_EEPROM[500];
extern int Reset_Software;
extern char User_x[40];
extern char Pass_x[40];
extern char Adresse_IP_PC[17];


void DRV_TMR1_Initialize(void)
{
    /* Setup TMR1 Instance */
    PLIB_TMR_Stop(TMR_ID_1); /* Disable Timer */
    PLIB_TMR_ClockSourceSelect(TMR_ID_1, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK); /* Select clock source */
    PLIB_TMR_PrescaleSelect(TMR_ID_1, TMR_PRESCALE_VALUE_8); /* Select prescalar value */
    PLIB_TMR_Mode16BitEnable(TMR_ID_1); /* Enable 16 bit mode */
    PLIB_TMR_Counter16BitClear(TMR_ID_1); /* Clear counter */
    PLIB_TMR_Period16BitSet(TMR_ID_1, 1000); /*Set period */ //modification interuption de 1m à 100us

    /* Setup Interrupt */
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_TIMER_1);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_T1, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_T1, INT_SUBPRIORITY_LEVEL0);

    PLIB_TMR_Start(TMR_ID_1); /* Enable Timer */
}




const DRV_USART_INIT drvUsart0InitData = {
    .moduleInit.value = DRV_USART_POWER_STATE_IDX0,
    .usartID = DRV_USART_PERIPHERAL_ID_IDX0, 
    .mode = DRV_USART_OPER_MODE_IDX0,
    .flags = DRV_USART_INIT_FLAGS_IDX0,
    .brgClock = DRV_USART_BRG_CLOCK_IDX0,
    .lineControl = DRV_USART_LINE_CNTRL_IDX0,
    .baud = DRV_USART_BAUD_RATE_IDX0,
    .handshake = DRV_USART_HANDSHAKE_MODE_IDX0,
    .interruptTransmit = DRV_USART_XMIT_INT_SRC_IDX0,
    .interruptReceive = DRV_USART_RCV_INT_SRC_IDX0,
    .interruptError = DRV_USART_ERR_INT_SRC_IDX0,
    .queueSizeTransmit = DRV_USART_XMIT_QUEUE_SIZE_IDX0,
    .queueSizeReceive = DRV_USART_RCV_QUEUE_SIZE_IDX0,
    .dmaChannelTransmit = DMA_CHANNEL_NONE,
    .dmaInterruptTransmit = DRV_USART_XMIT_INT_SRC_IDX0,    
    .dmaChannelReceive = DMA_CHANNEL_NONE,
    .dmaInterruptReceive = DRV_USART_RCV_INT_SRC_IDX0,    
};

const DRV_USART_INIT drvUsart1InitData = {
    .moduleInit.value = DRV_USART_POWER_STATE_IDX1,
    .usartID = DRV_USART_PERIPHERAL_ID_IDX1, 
    .mode = DRV_USART_OPER_MODE_IDX1,
    .flags = DRV_USART_INIT_FLAGS_IDX1,
    .brgClock = DRV_USART_BRG_CLOCK_IDX1,
    .lineControl = DRV_USART_LINE_CNTRL_IDX1,
    .baud = DRV_USART_BAUD_RATE_IDX1,
    .handshake = DRV_USART_HANDSHAKE_MODE_IDX1,
    .interruptTransmit = DRV_USART_XMIT_INT_SRC_IDX1,
    .interruptReceive = DRV_USART_RCV_INT_SRC_IDX1,
    .interruptError = DRV_USART_ERR_INT_SRC_IDX1,
    .queueSizeTransmit = DRV_USART_XMIT_QUEUE_SIZE_IDX1,
    .queueSizeReceive = DRV_USART_RCV_QUEUE_SIZE_IDX1,
    .dmaChannelTransmit = DMA_CHANNEL_NONE,
    .dmaInterruptTransmit = DRV_USART_XMIT_INT_SRC_IDX1,    
    .dmaChannelReceive = DMA_CHANNEL_NONE,
    .dmaInterruptReceive = DRV_USART_RCV_INT_SRC_IDX1,    
};








// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="DRV_NVM Initialization Data">
/*** FLASH Driver Initialization Data ***/
extern const uint8_t NVM_MEDIA_DATA[];
SYS_FS_MEDIA_REGION_GEOMETRY NVMGeometryTable[3] = 
{
    {
        .blockSize = 1,
        .numBlocks = (DRV_NVM_MEDIA_SIZE * 1024),
    },
    {
       .blockSize = DRV_NVM_ROW_SIZE,
       .numBlocks = ((DRV_NVM_MEDIA_SIZE * 1024)/DRV_NVM_ROW_SIZE)
    },
    {
       .blockSize = DRV_NVM_PAGE_SIZE,
       .numBlocks = ((DRV_NVM_MEDIA_SIZE * 1024)/DRV_NVM_PAGE_SIZE)
    }
};

const SYS_FS_MEDIA_GEOMETRY NVMGeometry = 
{
    .mediaProperty = SYS_FS_MEDIA_WRITE_IS_BLOCKING,
    .numReadRegions = 1,
    .numWriteRegions = 1,
    .numEraseRegions = 1,
    .geometryTable = (SYS_FS_MEDIA_REGION_GEOMETRY *)&NVMGeometryTable
};

const DRV_NVM_INIT drvNvmInit =
{
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,
    .nvmID = NVM_ID_0,
    .interruptSource = INT_SOURCE_FLASH_CONTROL,

    .mediaStartAddress = 0x9D020000,
    .nvmMediaGeometry = (SYS_FS_MEDIA_GEOMETRY *)&NVMGeometry

};


// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_SPI Initialization Data"> 
 /*** SPI Driver Initialization Data ***/
  /*** Index 0  ***/

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_Timer Initialization Data">
/*** TMR Driver Initialization Data ***/

const DRV_TMR_INIT drvTmr0InitData =
{
    .moduleInit.sys.powerState = DRV_TMR_POWER_STATE_IDX0,
    .tmrId = DRV_TMR_PERIPHERAL_ID_IDX0,
    .clockSource = DRV_TMR_CLOCK_SOURCE_IDX0, 
    .prescale = DRV_TMR_PRESCALE_IDX0,
    .mode = DRV_TMR_OPERATION_MODE_IDX0,
    .interruptSource = DRV_TMR_INTERRUPT_SOURCE_IDX0,
    .asyncWriteEnable = false,
};
// </editor-fold>

// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************

/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Module Initialization Data
// *****************************************************************************
// *****************************************************************************
/* Net Presentation Layer Data Definitions */
#include "framework/net/pres/net_pres_enc_glue.h"
#include "TDRS/I2C_Drivers/drv_i2c_static_buffer_model.h"

static const NET_PRES_TransportObject netPresTransObject0SS = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_TCP_ServerOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_TCP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_TCP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_TCP_IsConnected,
    .fpWasReset          = (NET_PRES_TransBool)TCPIP_TCP_WasReset,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_TCP_Disconnect,
    .fpConnect           = (NET_PRES_TransBool)TCPIP_TCP_Connect,
    .fpClose             = (NET_PRES_TransClose)TCPIP_TCP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_TCP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_TCP_Flush,
    .fpPeek              = (NET_PRES_TransPeek)TCPIP_TCP_ArrayPeek,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_TCP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_TCP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_TCP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_TCP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_TCP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_TCP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_TCP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_TCPSecurePortGet,
};
static const NET_PRES_TransportObject netPresTransObject0SC = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_TCP_ClientOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_TCP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_TCP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_TCP_IsConnected,
    .fpWasReset          = (NET_PRES_TransBool)TCPIP_TCP_WasReset,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_TCP_Disconnect,
    .fpConnect           = (NET_PRES_TransBool)TCPIP_TCP_Connect,
    .fpClose             = (NET_PRES_TransClose)TCPIP_TCP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_TCP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_TCP_Flush,
    .fpPeek              = (NET_PRES_TransPeek)TCPIP_TCP_ArrayPeek,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_TCP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_TCP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_TCP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_TCP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_TCP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_TCP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_TCP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_TCPSecurePortGet,
};
static const NET_PRES_TransportObject netPresTransObject0DS = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_UDP_ServerOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_UDP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_UDP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_UDP_IsConnected,
    .fpWasReset          = NULL,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_UDP_Disconnect,
    .fpConnect          = NULL,
    .fpClose             = (NET_PRES_TransClose)TCPIP_UDP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_UDP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_UDP_Flush,
    .fpPeek              = NULL,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_UDP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_UDP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_UDP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_UDP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_UDP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_UDP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_UDP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_UDPSecurePortGet,
};
static const NET_PRES_TransportObject netPresTransObject0DC = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_UDP_ClientOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_UDP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_UDP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_UDP_IsConnected,
    .fpWasReset          = NULL,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_UDP_Disconnect,
    .fpConnect          = NULL,
    .fpClose             = (NET_PRES_TransClose)TCPIP_UDP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_UDP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_UDP_Flush,
    .fpPeek              = NULL,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_UDP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_UDP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_UDP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_UDP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_UDP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_UDP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_UDP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_UDPSecurePortGet,
};
static const NET_PRES_INST_DATA netPresCfgs[] = 
{
    {
        .pTransObject_ss = &netPresTransObject0SS,
        .pTransObject_sc = &netPresTransObject0SC,
        .pTransObject_ds = &netPresTransObject0DS,
        .pTransObject_dc = &netPresTransObject0DC,
        .pProvObject_ss = NULL,
        .pProvObject_sc = NULL,
        .pProvObject_ds = NULL,
        .pProvObject_dc = NULL,
    },
};

static const NET_PRES_INIT_DATA netPresInitData = 
{
    .numLayers = sizeof(netPresCfgs) / sizeof(NET_PRES_INST_DATA),
    .pInitData = netPresCfgs
};
  
 
// <editor-fold defaultstate="collapsed" desc="SYS_COMMAND Initialization Data">
/*** System Command Initialization Data ***/

SYS_CMD_INIT sysCmdInit =
{
    .moduleInit = {0},
    .consoleCmdIOParam = SYS_CMD_SINGLE_CHARACTER_READ_CONSOLE_IO_PARAM,
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_CONSOLE Initialization Data">
/*** System Console Initialization Data ***/

SYS_MODULE_OBJ sysConsoleObjects[] = { SYS_MODULE_OBJ_INVALID };


// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_DEBUG Initialization Data">
/*** System Debug Initialization Data ***/

SYS_DEBUG_INIT debugInit =
{
    .moduleInit = {0},
    .errorLevel = SYS_ERROR_FATAL
};
// </editor-fold>
//<editor-fold defaultstate="collapsed" desc="SYS_DEVCON Initialization Data">
/*******************************************************************************
  Device Control System Service Initialization Data
*/

const SYS_DEVCON_INIT sysDevconInit =
{
    .moduleInit = {0},
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_FS Initialization Data">
/*** File System Initialization Data ***/

const SYS_FS_MEDIA_MOUNT_DATA sysfsMountTable[SYS_FS_VOLUME_NUMBER] = 
{
	{NULL}
};



const SYS_FS_REGISTRATION_TABLE sysFSInit [ SYS_FS_MAX_FILE_SYSTEM_TYPE ] =
{
    {
        .nativeFileSystemType = MPFS2,
        .nativeFileSystemFunctions = &MPFSFunctions
    }
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_TMR Initialization Data">
/*** TMR Service Initialization Data ***/
const SYS_TMR_INIT sysTmrInitData =
{
    .moduleInit = {SYS_MODULE_POWER_RUN_FULL},
    .drvIndex = DRV_TMR_INDEX_0,
    .tmrFreq = 1000, 
};
// </editor-fold>

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="TCPIP Stack Initialization Data">
// *****************************************************************************
// *****************************************************************************
// Section: TCPIP Data
// *****************************************************************************
// *****************************************************************************

/*** ARP Service Initialization Data ***/
const TCPIP_ARP_MODULE_CONFIG tcpipARPInitData =
{ 
    .cacheEntries       = TCPIP_ARP_CACHE_ENTRIES,     
    .deleteOld          = TCPIP_ARP_CACHE_DELETE_OLD,    
    .entrySolvedTmo     = TCPIP_ARP_CACHE_SOLVED_ENTRY_TMO, 
    .entryPendingTmo    = TCPIP_ARP_CACHE_PENDING_ENTRY_TMO, 
    .entryRetryTmo      = TCPIP_ARP_CACHE_PENDING_RETRY_TMO, 
    .permQuota          = TCPIP_ARP_CACHE_PERMANENT_QUOTA, 
    .purgeThres         = TCPIP_ARP_CACHE_PURGE_THRESHOLD, 
    .purgeQuanta        = TCPIP_ARP_CACHE_PURGE_QUANTA, 
    .retries            = TCPIP_ARP_CACHE_ENTRY_RETRIES, 
    .gratProbeCount     = TCPIP_ARP_GRATUITOUS_PROBE_COUNT,
};

/*** telnet Server Initialization Data ***/
const TCPIP_TELNET_MODULE_CONFIG tcpipTelnetInitData =
{ 
};

/*** Announce Discovery Initialization Data ***/
const TCPIP_ANNOUNCE_MODULE_CONFIG tcpipAnnounceInitData =
{ 
};

/*** UDP Sockets Initialization Data ***/
const TCPIP_UDP_MODULE_CONFIG tcpipUDPInitData =
{
    .nSockets       = TCPIP_UDP_MAX_SOCKETS,
    .sktTxBuffSize  = TCPIP_UDP_SOCKET_DEFAULT_TX_SIZE, 
};

/*** TCP Sockets Initialization Data ***/
const TCPIP_TCP_MODULE_CONFIG tcpipTCPInitData =
{
    .nSockets       = TCPIP_TCP_MAX_SOCKETS,
    .sktTxBuffSize  = TCPIP_TCP_SOCKET_DEFAULT_TX_SIZE, 
    .sktRxBuffSize  = TCPIP_TCP_SOCKET_DEFAULT_RX_SIZE,
};

/*** HTTP Server Initialization Data ***/
const TCPIP_HTTP_MODULE_CONFIG tcpipHTTPInitData =
{
    .nConnections   = TCPIP_HTTP_MAX_CONNECTIONS,
    .nTlsConnections    = TCPIP_HTTP_MAX_TLS_CONNECTIONS,
    .dataLen		= TCPIP_HTTP_MAX_DATA_LEN,
    .sktTxBuffSize	= TCPIP_HTTP_SKT_TX_BUFF_SIZE,
    .sktRxBuffSize	= TCPIP_HTTP_SKT_RX_BUFF_SIZE,
    .tlsSktTxBuffSize	= TCPIP_HTTP_TLS_SKT_TX_BUFF_SIZE,
    .tlsSktRxBuffSize	= TCPIP_HTTP_TLS_SKT_RX_BUFF_SIZE,
    .configFlags	= TCPIP_HTTP_CONFIG_FLAGS,
};


/*** SNTP Client Initialization Data ***/
extern char Save_NTP1[30];
const TCPIP_SNTP_MODULE_CONFIG tcpipSNTPInitData =
{
    .ntp_server		        = Save_NTP1,
    .ntp_interface		    = TCPIP_NTP_DEFAULT_IF,
    .ntp_connection_type	= TCPIP_NTP_DEFAULT_CONNECTION_TYPE,
    .ntp_reply_timeout		= TCPIP_NTP_REPLY_TIMEOUT,
    .ntp_stamp_timeout		= TCPIP_NTP_TIME_STAMP_TMO,
    .ntp_success_interval	= TCPIP_NTP_QUERY_INTERVAL,
    .ntp_error_interval		= TCPIP_NTP_FAST_QUERY_INTERVAL,
};

/*** SMTP client Initialization Data ***/
const TCPIP_SMTP_CLIENT_MODULE_CONFIG tcpipSMTPInitData =
{ 
};

/*** DHCP client Initialization Data ***/
const TCPIP_DHCP_MODULE_CONFIG tcpipDHCPInitData =
{     
    .dhcpEnable     = TCPIP_DHCP_CLIENT_ENABLED,   
    .dhcpTmo        = TCPIP_DHCP_TIMEOUT,
    .dhcpCliPort    = TCPIP_DHCP_CLIENT_CONNECT_PORT,
    .dhcpSrvPort    = TCPIP_DHCP_SERVER_LISTEN_PORT,

};


/*** ICMP Server Initialization Data ***/
const TCPIP_ICMP_MODULE_CONFIG tcpipICMPInitData = 
{
};

/*** NBNS Server Initialization Data ***/
const TCPIP_NBNS_MODULE_CONFIG tcpipNBNSInitData =
{ 
};

/*** ETH MAC Initialization Data ***/
const TCPIP_MODULE_MAC_PIC32INT_CONFIG tcpipMACPIC32INTInitData =
{ 
    .nTxDescriptors         = TCPIP_EMAC_TX_DESCRIPTORS,
    .rxBuffSize             = TCPIP_EMAC_RX_BUFF_SIZE,
    .nRxDescriptors         = TCPIP_EMAC_RX_DESCRIPTORS,
    .nRxDedicatedBuffers    = TCPIP_EMAC_RX_DEDICATED_BUFFERS,
    .nRxInitBuffers         = TCPIP_EMAC_RX_INIT_BUFFERS,
    .rxLowThreshold         = TCPIP_EMAC_RX_LOW_THRESHOLD,
    .rxLowFill              = TCPIP_EMAC_RX_LOW_FILL,
    .ethFlags               = TCPIP_EMAC_ETH_OPEN_FLAGS,
    .phyFlags               = TCPIP_EMAC_PHY_CONFIG_FLAGS,
    .linkInitDelay          = TCPIP_EMAC_PHY_LINK_INIT_DELAY,
    .phyAddress             = TCPIP_EMAC_PHY_ADDRESS,
    .ethModuleId            = TCPIP_EMAC_MODULE_ID,
    .pPhyObject             = &DRV_ETHPHY_OBJECT_National_DP83848,
    .pPhyBase               = &DRV_ETHPHY_OBJECT_BASE_Default,
};



/*** Zeroconfig initialization data ***/
const ZCLL_MODULE_CONFIG tcpipZCLLInitData =
{
};



/*** FTP Server Initialization Data ***/
//const TCPIP_FTP_MODULE_CONFIG tcpipFTPInitData =
//{ 
//    .nConnections       = TCPIP_FTP_MAX_CONNECTIONS,
//    .dataSktTxBuffSize	= TCPIP_FTP_DATA_SKT_TX_BUFF_SIZE,
//    .dataSktRxBuffSize	= TCPIP_FTP_DATA_SKT_RX_BUFF_SIZE,
//    .userName			= TCPIP_FTP_USER_NAME,
//    .password		    = TCPIP_FTP_PASSWORD,
//};

/*** DNS Client Initialization Data ***/
const TCPIP_DNS_CLIENT_MODULE_CONFIG tcpipDNSClientInitData =
{
    .deleteOldLease         = TCPIP_DNS_CLIENT_DELETE_OLD_ENTRIES,
    .cacheEntries           = TCPIP_DNS_CLIENT_CACHE_ENTRIES,
    .entrySolvedTmo         = TCPIP_DNS_CLIENT_CACHE_ENTRY_TMO,    
    .nIPv4Entries  = TCPIP_DNS_CLIENT_CACHE_PER_IPV4_ADDRESS,
    .ipAddressType       = TCPIP_DNS_CLIENT_ADDRESS_TYPE,
    //.nIPv6Entries  = TCPIP_DNS_CLIENT_CACHE_PER_IPV6_ADDRESS,
};


/*** IPv6 Initialization Data ***/
//const TCPIP_IPV6_MODULE_CONFIG  tcpipIPv6InitData = 
//{
//    .rxfragmentBufSize      = TCPIP_IPV6_RX_FRAGMENTED_BUFFER_SIZE,
//    .fragmentPktRxTimeout   = TCPIP_IPV6_FRAGMENT_PKT_TIMEOUT,
//};

TCPIP_SNMP_COMMUNITY_CONFIG tcpipSNMPInitReadcommunity[] =
{
/*** SNMP Configuration Index 0 ***/
    {
        TCPIP_SNMP_STACK_READCOMMUNITY_NAME_IDX0,
    },
/*** SNMP Configuration Index 1 ***/
    {
        TCPIP_SNMP_STACK_READCOMMUNITY_NAME_IDX1,
    },
/*** SNMP Configuration Index 2 ***/	
    {
        TCPIP_SNMP_STACK_READCOMMUNITY_NAME_IDX2,
    },
};

TCPIP_SNMP_COMMUNITY_CONFIG tcpipSNMPInitWritecommunity[] =
{
/*** SNMP Configuration Index 0 ***/
    {
        TCPIP_SNMP_STACK_WRITECOMMUNITY_NAME_IDX0,
    },
/*** SNMP Configuration Index 1 ***/
    {
        TCPIP_SNMP_STACK_WRITECOMMUNITY_NAME_IDX1,
    },
/*** SNMP Configuration Index 2 ***/
    {
        TCPIP_SNMP_STACK_WRITECOMMUNITY_NAME_IDX2,
    },
};

const TCPIP_SNMP_MODULE_CONFIG tcpipSNMPInitData =
{
	.trapEnable             = TCPIP_SNMP_USE_TRAP_SUPPORT,
	.snmp_trapv2_use        = TCPIP_SNMP_STACK_USE_V2_TRAP,
	.snmpv3_trapv1v2_use    = false,
	.snmp_bib_file          = TCPIP_SNMP_BIB_FILE_NAME,
	.read_community_config  = (TCPIP_SNMP_COMMUNITY_CONFIG*)tcpipSNMPInitReadcommunity,
	.write_community_config = (TCPIP_SNMP_COMMUNITY_CONFIG*)tcpipSNMPInitWritecommunity,
	.usm_config             = NULL,
	.trap_target_config     = NULL,
};

TCPIP_STACK_HEAP_INTERNAL_CONFIG tcpipHeapConfig =
{
    .heapType = TCPIP_STACK_HEAP_TYPE_INTERNAL_HEAP,
    .heapFlags = TCPIP_STACK_HEAP_USE_FLAGS,
    .heapUsage = TCPIP_STACK_HEAP_USAGE_CONFIG,
    .malloc_fnc = TCPIP_STACK_MALLOC_FUNC,
    .calloc_fnc = TCPIP_STACK_CALLOC_FUNC,
    .free_fnc = TCPIP_STACK_FREE_FUNC,
    .heapSize = TCPIP_STACK_DRAM_SIZE,
};
 
const TCPIP_NETWORK_CONFIG __attribute__((unused))  TCPIP_HOSTS_CONFIGURATION[] =
{
/*** Network Configuration Index 0 ***/
    {
        TCPIP_NETWORK_DEFAULT_INTERFACE_NAME,       // interface
        TCPIP_NETWORK_DEFAULT_HOST_NAME,            // hostName
        TCPIP_NETWORK_DEFAULT_MAC_ADDR,             // macAddr
        //TCPIP_NETWORK_DEFAULT_IP_ADDRESS,           // ipAddr
        Save_Adresse_IP,           // ipAddr par moi
        //TCPIP_NETWORK_DEFAULT_IP_MASK,              // ipMask
        Save_Mask_IP,              // ipMask par moi
        //TCPIP_NETWORK_DEFAULT_GATEWAY,              // gateway
        Save_Gateway_IP,           // gateway par moi
        //TCPIP_NETWORK_DEFAULT_DNS,                  // priDNS
        Save_DNS_IP,               // priDNS par moi                 // priDNS
        TCPIP_NETWORK_DEFAULT_SECOND_DNS,           // secondDNS
        TCPIP_NETWORK_DEFAULT_POWER_MODE,           // powerMode
        TCPIP_NETWORK_DEFAULT_INTERFACE_FLAGS,      // startFlags
       &TCPIP_NETWORK_DEFAULT_MAC_DRIVER,           // pMacObject
    },
};

const TCPIP_STACK_MODULE_CONFIG TCPIP_STACK_MODULE_CONFIG_TBL [] =
{
    {TCPIP_MODULE_IPV4,          0},
    {TCPIP_MODULE_ICMP,          0},                           // TCPIP_MODULE_ICMP
    {TCPIP_MODULE_ARP,           &tcpipARPInitData},              // TCPIP_MODULE_ARP
    //{TCPIP_MODULE_IPV6,          &tcpipIPv6InitData},                           // TCPIP_MODULE_IPV6
    {TCPIP_MODULE_ICMPV6,        0},                           // TCPIP_MODULE_ICMPV6
    {TCPIP_MODULE_NDP,           0},                           // TCPIP_MODULE_NDP
    {TCPIP_MODULE_UDP,           &tcpipUDPInitData},              // TCPIP_MODULE_UDP,
    {TCPIP_MODULE_TCP,           &tcpipTCPInitData},              // TCPIP_MODULE_TCP,
    {TCPIP_MODULE_DHCP_CLIENT,   &tcpipDHCPInitData},             // TCPIP_MODULE_DHCP_CLIENT,
    {TCPIP_MODULE_ANNOUNCE,      &tcpipAnnounceInitData},                     // TCPIP_MODULE_ANNOUNCE,
    {TCPIP_MODULE_DNS_CLIENT,&tcpipDNSClientInitData}, // TCPIP_MODULE_DNS_CLIENT,
    {TCPIP_MODULE_NBNS,          &tcpipNBNSInitData},                           // TCPIP_MODULE_NBNS
    {TCPIP_MODULE_SNTP,    &tcpipSNTPInitData},                            // TCPIP_MODULE_SNTP,
    {TCPIP_MODULE_HTTP_SERVER,   &tcpipHTTPInitData},              // TCPIP_MODULE_HTTP_SERVER,
    {TCPIP_MODULE_SNMP_SERVER,   &tcpipSNMPInitData},                           // TCPIP_MODULE_SNMP_SERVER,
    {TCPIP_MODULE_ZCLL, 0},                                    // TCPIP_MODULE_ZCLL,
    {TCPIP_MODULE_MDNS, 0},                                    // TCPIP_MODULE_MDNS,
    { TCPIP_MODULE_MANAGER,    & tcpipHeapConfig },          // TCPIP_MODULE_MANAGER
    // MAC modules
    {TCPIP_MODULE_MAC_PIC32INT, &tcpipMACPIC32INTInitData},     // TCPIP_MODULE_MAC_PIC32INT

};

/*********************************************************************
 * Function:        SYS_MODULE_OBJ TCPIP_STACK_Init()
 *
 * PreCondition:    None
 *
 * Input:
 *
 * Output:          valid system module object if Stack and its componets are initialized
 *                  SYS_MODULE_OBJ_INVALID otherwise
 *
 * Overview:        The function starts the initialization of the stack.
 *                  If an error occurs, the SYS_ERROR() is called
 *                  and the function de-initialize itself and will return false.
 *
 * Side Effects:    None
 *
 * Note:            This function must be called before any of the
 *                  stack or its component routines are used.
 *
 ********************************************************************/


SYS_MODULE_OBJ TCPIP_STACK_Init()
{
    TCPIP_STACK_INIT    tcpipInit;

    tcpipInit.moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL;
    tcpipInit.pNetConf = TCPIP_HOSTS_CONFIGURATION;
    tcpipInit.nNets = sizeof (TCPIP_HOSTS_CONFIGURATION) / sizeof (*TCPIP_HOSTS_CONFIGURATION);
    tcpipInit.pModConfig = TCPIP_STACK_MODULE_CONFIG_TBL;
    tcpipInit.nModules = sizeof (TCPIP_STACK_MODULE_CONFIG_TBL) / sizeof (*TCPIP_STACK_MODULE_CONFIG_TBL);

    return TCPIP_STACK_Initialize(0, &tcpipInit.moduleInit);
}
// </editor-fold>

// *****************************************************************************
// *****************************************************************************
// Section: Static Initialization Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
    See prototype in system/common/sys_module.h.
 */

void SYS_Initialize ( void* data )
{
    delay_ms(100);
    /* Core Processor Initialization */
    SYS_CLK_Initialize( NULL );
    sysObj.sysDevcon = SYS_DEVCON_Initialize(SYS_DEVCON_INDEX_0, (SYS_MODULE_INIT*)&sysDevconInit);
    SYS_DEVCON_PerformanceConfig(SYS_CLK_SystemFrequencyGet());
    SYS_DEVCON_JTAGDisable();
//    SYS_DEVCON_JTAGEnable();
//    SYS_PORTS_Initialize();
    /* Board Support Package Initialization */
//    BSP_Initialize();
    sysObj.drvUsart0 = DRV_USART_Initialize(DRV_USART_INDEX_0, (SYS_MODULE_INIT *)&drvUsart0InitData);
    sysObj.drvUsart1 = DRV_USART_Initialize(DRV_USART_INDEX_1, (SYS_MODULE_INIT *)&drvUsart1InitData);
    SYS_INT_VectorPrioritySet(INT_VECTOR_UART2, INT_PRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_UART2, INT_SUBPRIORITY_LEVEL1);
    
    
    SYS_INT_VectorPrioritySet(INT_VECTOR_UART1, INT_PRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_UART1, INT_SUBPRIORITY_LEVEL1);
    i2c_init();


    #define Nb_Route 4
    typedef struct tROUTE_CONFIG
    {
        IPV4_ADDR IP_Route;    
        IPV4_ADDR IP_Mask;
        IPV4_ADDR IP_Net;

    } ROUTE_CONFIG;

    extern ROUTE_CONFIG routeconfig[Nb_Route];
    


    extern Niveau_In Audio_IN[6];
   

    extern int Stop_Boot;
    const char tabDefRoute[4] = {0,0,0,0};
    const char calibDef[24] = {142,125,0,0,
                               23,1,0,0,
                               106,220,243,255,
                               59,3,0,0,
                               191,183,255,255,    
                               97,21,17,1};
    
    char Audio_IN_ValueDef[1780];

    memset(Audio_IN_ValueDef,0,120);
    
    char Config_Usine [1024];
    char CRLF[2];
    CRLF[0] = 0x0D;
    CRLF[1] = 0x0A;
    
    

    
    EEPROM_Start_List();
    EEPROM_AddAndRead(&Reset_Software, 0, 0, CHAR_TYPE, 0);
        // Bootloader
    EEPROM_AddAndRead(&Stop_Boot, 1999, 1999, CHAR_TYPE, 0);
    if(Stop_Boot != 0)
    {
        Stop_Boot = 0;
        EEPROM_SaveData(&Stop_Boot); 
    }
    
    EEPROM_AddAndRead(Save_Adresse_IP, 300, 316, IP_STRING_TYPE, "10.96.0.71");
    EEPROM_AddAndRead(Save_Mask_IP, 317, 333, IP_STRING_TYPE, "255.255.255.0");
    EEPROM_AddAndRead(Save_Gateway_IP, 334, 350, IP_STRING_TYPE, "10.96.0.1");
    EEPROM_AddAndRead(Save_DNS_IP, 351, 367, IP_STRING_TYPE, Save_Gateway_IP);
    EEPROM_AddAndRead(Save_NTP1, 400, 429, STRING_TYPE, Save_Gateway_IP);
    
    EEPROM_AddAndRead(routeconfig[0].IP_Route.v, 500, 503, IP_NUM_TYPE, tabDefRoute);
    EEPROM_AddAndRead(routeconfig[0].IP_Mask.v, 504, 507, IP_NUM_MASK_TYPE, tabDefRoute);
    EEPROM_AddAndRead(routeconfig[0].IP_Net.v, 508, 511, IP_NUM_TYPE, tabDefRoute);
    
    EEPROM_AddAndRead(routeconfig[1].IP_Route.v, 512, 515, IP_NUM_TYPE, tabDefRoute);
    EEPROM_AddAndRead(routeconfig[1].IP_Mask.v, 516, 519, IP_NUM_MASK_TYPE, tabDefRoute);
    EEPROM_AddAndRead(routeconfig[1].IP_Net.v, 520, 523, IP_NUM_TYPE, tabDefRoute);
    
    EEPROM_AddAndRead(routeconfig[2].IP_Route.v, 524, 527, IP_NUM_TYPE, tabDefRoute);
    EEPROM_AddAndRead(routeconfig[2].IP_Mask.v, 528, 531, IP_NUM_MASK_TYPE, tabDefRoute);
    EEPROM_AddAndRead(routeconfig[2].IP_Net.v, 532, 535, IP_NUM_TYPE, tabDefRoute);
    
    EEPROM_AddAndRead(routeconfig[3].IP_Route.v, 536, 539, IP_NUM_TYPE, tabDefRoute);
    EEPROM_AddAndRead(routeconfig[3].IP_Mask.v, 540, 543, IP_NUM_MASK_TYPE, tabDefRoute);
    EEPROM_AddAndRead(routeconfig[3].IP_Net.v, 544, 547, IP_NUM_TYPE, tabDefRoute);
    

    EEPROM_AddAndRead(Valeur_Calibration, 1400, 1423, CALIBRATION_TYPE, calibDef);
    EEPROM_AddAndRead(Valeur_Calibration2, 1425, 1448, CALIBRATION_TYPE, calibDef);
    
    
    extern Save_Config Nconfig[5];
    extern Save_Config NconfigDefaut[5];
    
    extern int Config_Used;   
    float Perte;
    float Somm_Volume;
    int Somm_VolumeIN;
    int i;
    
    /*********Configuration Usine*******************/
//    Config_Used = 0;   
//    Upload_Audio_CSV(Config_Usine);  
//    ResetConfig(0);
    
  
    /****************************/
    
    int SizeNconfig = sizeof(Save_Config); 
    int StartNconfig1 = 2050;
    int StartNconfig2 = StartNconfig1 + SizeNconfig +1;
    int StartNconfig3 = StartNconfig2 + SizeNconfig +1;
    int StartNconfig4 = StartNconfig3 + SizeNconfig +1;
    int StartNconfig5 = StartNconfig4 + SizeNconfig +1;
    
    //EEPROM_AddAndRead(&Nconfig[0], StartNconfig1, StartNconfig1 + SizeNconfig, CHAR_TAB_TYPE,Audio_IN_ValueDef);//412
    EEPROM_AddAndRead(&Nconfig[1], StartNconfig2, StartNconfig2 + SizeNconfig, CHAR_TAB_TYPE,Audio_IN_ValueDef);//412
    EEPROM_AddAndRead(&Nconfig[2], StartNconfig3, StartNconfig3 + SizeNconfig, CHAR_TAB_TYPE,Audio_IN_ValueDef);//412
    EEPROM_AddAndRead(&Nconfig[3], StartNconfig4, StartNconfig4 + SizeNconfig, CHAR_TAB_TYPE,Audio_IN_ValueDef);//412
    EEPROM_AddAndRead(&Nconfig[4], StartNconfig5, StartNconfig5 + SizeNconfig, CHAR_TAB_TYPE,Audio_IN_ValueDef);//412
//    ResetConfig(0);
//    sprintf(Nconfig[0].Name_Config,"Config Usine");
    
    
//    NconfigDefaut = Nconfig;
//    memcpy(NconfigDefaut,Nconfig,sizeof(Nconfig));
//    NconfigDefaut[1] = Nconfig[1];
//    NconfigDefaut[2] = Nconfig[2];   
//    NconfigDefaut[3] = Nconfig[3];
//    NconfigDefaut[4] = Nconfig[4];
    
    for(i =0; i < 6;i++)
    {
        Somm_VolumeIN = (int)Nconfig[Config_Used].Device_IN[i].Volume;

        if(Somm_VolumeIN > 0)
        {
            if(Somm_VolumeIN%2 == 0)//si gain chiffre paire
            {
                Nconfig[Config_Used].Device_IN[i].Volume = 0;
                Nconfig[Config_Used].Device_IN[i].Gain = Somm_VolumeIN;
            }
            else//si gain chiffre impaire
            {
                Nconfig[Config_Used].Device_IN[i].Volume = -1;
                Nconfig[Config_Used].Device_IN[i].Gain = Somm_VolumeIN+1;
            }
        }
        else
        {
            Nconfig[Config_Used].Device_IN[i].Volume = Somm_VolumeIN;
            Nconfig[Config_Used].Device_IN[i].Gain = 0;                   
        }
        if(Nconfig[Config_Used].Device_IN[i].Volume < -30)
        {
            Nconfig[Config_Used].Device_IN[i].Volume = -56;//corespond a MUTE pour TDA7439
        }            
    }
    
    for(i=0;i<7;i++)
    {
        Somm_Volume = Nconfig[Config_Used].Device_OUT[i].Volume; 
        
        if((Somm_Volume > 0)&&(Somm_Volume <= 3.75))
        {
            Nconfig[Config_Used].Device_OUT[i].Gain = 3.75;            
        }
        else if((Somm_Volume > 3.75)&&(Somm_Volume <= 7.5))
        {
            Nconfig[Config_Used].Device_OUT[i].Gain = 7.5;               
        }
        else if((Somm_Volume > 7.5)&&(Somm_Volume <= 11.25))
        {
            Nconfig[Config_Used].Device_OUT[i].Gain = 11.25;               
        }
        else if(Somm_Volume <= 0)
        {
            Nconfig[Config_Used].Device_OUT[i].Gain = 0;
        }
        else
        {
            return;
        }
        Perte = Nconfig[Config_Used].Device_OUT[i].Gain - Somm_Volume;

        Nconfig[Config_Used].Device_OUT[i].Volume = -Perte; 
        if(Nconfig[Config_Used].Device_OUT[i].Volume < -30)
        {
            Nconfig[Config_Used].Device_OUT[i].Volume = -78.75;
        }       
    }
    
    ResetConfig(0);
    sprintf(Nconfig[0].Name_Config,"Config Usine");    
    memcpy(NconfigDefaut,Nconfig,sizeof(Nconfig));

    
    EEPROM_AddAndRead(&Config_Used, 2048, 2048, CHAR_TYPE,0);//1
    //EEPROM_AddAndRead(&Gain_Master, 2049, 2049, CHAR_TYPE,0);//1
    
    if(Config_Used > 4 ||Config_Used < 0)
    {
        Config_Used = 0;
    }
    
    int j;
    for(j=0;j<5;j++)
    {    
        Nop();
        if(Nconfig[j].Name_Config[0] == 0x00)
        {
            if(j == 0)
            {
                sprintf(Nconfig[j].Name_Config,"Config Usine");
            }
            else
            {
                sprintf(Nconfig[j].Name_Config,"Config Defaut%d",j);
            }
        }
        if((Nconfig[j].Master_Gain != false)||(Nconfig[j].Master_Gain != true))
        {
            Nconfig[j].Master_Gain == false;
        }
        
        for(i = 0; i < 6;i++)
        {
            if((Nconfig[j].Device_IN[i].Loudness != 0)&&(Nconfig[j].Device_IN[i].Loudness != 1))
            {
                Nconfig[j].Device_IN[i].Loudness = 0;
            }
            if((Nconfig[j].Device_IN[i].Aigue > 14)||(Nconfig[j].Device_IN[i].Aigue < -14))
            {
                Nconfig[j].Device_IN[i].Aigue = 0;
            }
            if((Nconfig[j].Device_IN[i].Middle > 14)||(Nconfig[j].Device_IN[i].Middle < -14))
            {
                Nconfig[j].Device_IN[i].Middle= 0;
            }
            if((Nconfig[j].Device_IN[i].Basse > 14)||(Nconfig[j].Device_IN[i].Basse < -14))
            {
                Nconfig[j].Device_IN[i].Basse= 0;
            }
            if((Nconfig[j].Device_IN[i].Volume > 0)||(Nconfig[j].Device_IN[i].Volume < -56))
            {
                Nconfig[j].Device_IN[i].Volume = 0;
            }
            if((Nconfig[j].Device_IN[i].Gain < 0)||(Nconfig[j].Device_IN[i].Gain > 12))
            {
                Nconfig[j].Device_IN[i].Gain = 0;
            }
            if((Nconfig[j].Device_IN[i].ReductionMax < 0.)||(Nconfig[j].Device_IN[i].ReductionMax > 20.))
            {
                Nconfig[j].Device_IN[i].ReductionMax = 10.;
            }
            if((Nconfig[j].Device_IN[i].Niveau_Overload > 5000)||(Nconfig[j].Device_IN[i].Niveau_Overload < 0))
            {
                Nconfig[j].Device_IN[i].Niveau_Overload = 200;
            }
            if((Nconfig[j].Device_IN[i].Niveau_Stop_Overload > 5000)||(Nconfig[j].Device_IN[i].Niveau_Stop_Overload < 0))
            {
                Nconfig[j].Device_IN[i].Niveau_Stop_Overload = 20;
            }
            if((Nconfig[j].Device_IN[i].Time_Mute < 10)||(Nconfig[j].Device_IN[i].Time_Mute > 60000))
            {
                Nconfig[j].Device_IN[i].Time_Mute = 5000;
            }
            Nconfig[j].Device_IN[i].L = 0;
            Nconfig[j].Device_IN[i].R= 0;
        }
        
        for(i = 0; i < 7;i++)
        {
            if((Nconfig[j].Device_OUT[i].Loudness != 0)&&(Nconfig[j].Device_OUT[i].Loudness != 1))
            {
                Nconfig[j].Device_OUT[i].Loudness = 0;
            }
            if((Nconfig[j].Device_OUT[i].Aigue > 14)||(Nconfig[j].Device_OUT[i].Aigue < -14))
            {
                Nconfig[j].Device_OUT[i].Aigue = 0;
            }
            if((Nconfig[j].Device_OUT[i].Basse > 14)||(Nconfig[j].Device_OUT[i].Basse < -14))
            {
                Nconfig[j].Device_OUT[i].Basse = 0;
            }      
            if((Nconfig[j].Device_OUT[i].Volume > 0)||(Nconfig[j].Device_OUT[i].Volume < -78.75))
            {
                Nconfig[j].Device_OUT[i].Volume = 0;
            }   
            if((Nconfig[j].Device_OUT[i].L > 0)||(Nconfig[j].Device_OUT[i].L < -30))
            {
                Nconfig[j].Device_OUT[i].L= 0;
            }   
            if((Nconfig[j].Device_OUT[i].R > 0)||(Nconfig[j].Device_OUT[i].R < -30))
            {
                Nconfig[j].Device_OUT[i].R= 0;
            }   
            if((Nconfig[j].Device_OUT[i].Gain != 0)&&(Nconfig[j].Device_OUT[i].Gain != 3.75)&&(Nconfig[j].Device_OUT[i].Gain != 7.5)&&(Nconfig[j].Device_OUT[i].Gain != 11.25))
            {
                Nconfig[j].Device_OUT[i].Gain = 11.25;
            }
        }
    }
    Nop();
    
    
    //Initialisation Acknolage Device i2c//
    
    for(i = 0; i<= 3;i++ )
    {
        StateAck.ACK_Expender[i] = -1;
    }
    for(i = 0; i<= 13;i++ )
    {
        StateAck.ACK_PT2314[i] = -1;
    }
    for(i = 0; i<= 4;i++ )
    {
        StateAck.ACK_AD5532[i] = -1;
    }



    
    /* Initialize Drivers */

    /*** SPI Driver Index 0 initialization***/

//    SYS_INT_VectorPrioritySet(DRV_SPI_INT_VECTOR_IDX0, DRV_SPI_INT_PRIORITY_IDX0);
//    SYS_INT_VectorSubprioritySet(DRV_SPI_INT_VECTOR_IDX0, DRV_SPI_INT_SUB_PRIORITY_IDX0);
//    sysObj.spiObjectIdx0 = DRV_SPI_Initialize(DRV_SPI_INDEX_0, (const SYS_MODULE_INIT  * const)&drvSpi0InitData);
    /* Configure the Flash Controller Interrupt Priority */
    SYS_INT_VectorPrioritySet(INT_VECTOR_FCE, INT_PRIORITY_LEVEL4);

    /* Configure the Flash Controller Interrupt Sub Priority */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_FCE, INT_SUBPRIORITY_LEVEL1);

    /* Initialize the NVM Driver */
    sysObj.drvNvm = DRV_NVM_Initialize(DRV_NVM_INDEX_0, (SYS_MODULE_INIT *)&drvNvmInit);

    sysObj.drvTmr0 = DRV_TMR_Initialize(DRV_TMR_INDEX_0, (SYS_MODULE_INIT *)&drvTmr0InitData);

    SYS_INT_VectorPrioritySet(INT_VECTOR_T2, INT_PRIORITY_LEVEL4);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_T2, INT_SUBPRIORITY_LEVEL0);
 
 

    /* Initialize System Services */

    /*** Command Service Initialization Code ***/
    //SYS_CMD_Initialize((SYS_MODULE_INIT*)&sysCmdInit);
    


    /*** Debug Service Initialization Code ***/
    sysObj.sysDebug = SYS_DEBUG_Initialize(SYS_DEBUG_INDEX_0, (SYS_MODULE_INIT*)&debugInit);

    /*** File System Service Initialization Code ***/
    SYS_FS_Initialize( (const void *) sysFSInit );

    /*** Interrupt Service Initialization Code ***/
    SYS_INT_Initialize();

    /*** Random Service Initialization Code ***/
    SYS_RANDOM_Initialize(0, 0);

    /*** TMR Service Initialization Code ***/
    sysObj.sysTmr  = SYS_TMR_Initialize(SYS_TMR_INDEX_0, (const SYS_MODULE_INIT  * const)&sysTmrInitData);
  
    /* Initialize Middleware */
    sysObj.netPres = NET_PRES_Initialize(0, (SYS_MODULE_INIT*)&netPresInitData);

    /* set priority for ETHERNET interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_ETH, INT_PRIORITY_LEVEL5);

    /* set sub-priority for ETHERNET interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_ETH, INT_SUBPRIORITY_LEVEL0);
    
    /* TCPIP Stack Initialization */
    sysObj.tcpip = TCPIP_STACK_Init();
    SYS_ASSERT(sysObj.tcpip != SYS_MODULE_OBJ_INVALID, "TCPIP_STACK_Init Failed" );

    DRV_I2C0_Initialize();
    
    DRV_TMR1_Initialize();
    //DRV_USART0_Initialize();

    /* Enable Global Interrupts */
    SYS_INT_Enable();

    /* Initialize the Application */
    APP_Initialize_Usart();

}
/*******************************************************************************
 End of File
*/

