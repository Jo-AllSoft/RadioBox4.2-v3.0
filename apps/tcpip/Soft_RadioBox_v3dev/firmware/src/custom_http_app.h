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

#ifndef _CUSTOM_HTTP_APP_H    /* Guard against multiple inclusion */
#define _CUSTOM_HTTP_APP_H


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
#endif /* _CUSTOM_HTTP_APP_H */

/* *****************************************************************************
 End of File
 */
