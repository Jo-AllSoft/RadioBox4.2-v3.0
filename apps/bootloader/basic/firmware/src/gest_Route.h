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

#ifndef _GEST_ROUTE_H    /* Guard against multiple inclusion */
#define _GEST_ROUTE_H




/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

//#include "../framework/tcpip/ipv4.h"
//#include "tcpip.h"
#include "../framework/tcpip/tcpip.h"

//typedef struct
//{
//
//    IPV4_ADDR           arpTarget;      // ARP resolution target
//    IPV4_ADDR           Add_Route;
//    
//} IPV4_ROUTE;


IPV4_ADDR  Gest_Route(IPV4_ADDR destAddress,IPV4_ADDR Mask, IPV4_ADDR Gateway);


#endif /* _GEST_ROUTE_H */

/* *****************************************************************************
 End of File
 */
