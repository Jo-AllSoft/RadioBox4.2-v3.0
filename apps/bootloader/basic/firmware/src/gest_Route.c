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
#include "gest_Route.h"
//#include "../framework/tcpip/ipv4.h"
#include "../framework/tcpip/tcpip_helpers.h"

#define TCPIP_ROUTE_TABLE_SIZE

//typedef struct tROUTE_INFO
//{
//   uint8_t Size;
//   struct
//   {
//       IPV4_ADDR IPAddress;     //IP address to which trap to be sent
//       
//   } table[TCPIP_ROUTE_TABLE_SIZE];
//} ROUTE_INFO;

IPV4_ADDR Gest_Route(IPV4_ADDR destAddress,IPV4_ADDR Mask, IPV4_ADDR Gateway)
{
        IPV4_ADDR Add_Route1;
        IPV4_ADDR Gateway2;
        
        TCPIP_Helper_StringToIPAddress("192.168.1.60", &Gateway2);//moi!!!
        TCPIP_Helper_StringToIPAddress("10.96.0.0", &Add_Route1);//moi!!!
        
        if((destAddress.Val & Mask.Val) == (Gateway.Val & Mask.Val))//Local
        {
            return destAddress;
        }
        else if((destAddress.Val & Mask.Val) == (Add_Route1.Val & Mask.Val))//Reseau Route
        {
            return Gateway2;//moi!!!
        }
        else
        {
            return Gateway ;//moi!!!
        }
        
}
/* *****************************************************************************
 End of File
 */
