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

#ifndef _ROUTE_ADD_APP_H    /* Guard against multiple inclusion */
#define _ROUTE_ADD_APP_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */



#define Nb_Route 4


typedef struct tROUTE_CONFIG
{
    IPV4_ADDR IP_Route;    
    IPV4_ADDR IP_Mask;
    IPV4_ADDR IP_Net;

} ROUTE_CONFIG;

ROUTE_CONFIG routeconfig[Nb_Route];
#endif /* _ROUTE_ADD_APP_H */



/* *****************************************************************************
 End of File
 */
