#ifndef __MC32DRIVERADC_H
#define __MC32DRIVERADC_H
/*--------------------------------------------------------*/
//	Mc32DriverAdc.h
/*--------------------------------------------------------*/
//	Description :	Gestion ADC10 en mode scan
//
//
//	Auteur 		: 	C. Huber
//
//	Version		:	V1.0
//	Compilateur	:	XC32 V1.33 & Harmony V1.00
//
/*--------------------------------------------------------*/

#include "bsp_config.h"

// Structure � adapter selon le nombre de canaux
// Limite � 8 avec les buffers altern�

typedef struct {
   uint16_t Chan9;
//  uint16_t Chan2;
//   uint16_t Chan3;
   uint16_t Chan5;
//   uint16_t Chan15;
//   uint16_t Chan5;
//   uint16_t Chan15;
//   uint16_t Chan11;
} S_ADCResults ;

/*--------------------------------------------------------*/
// Fonction BSP_InitADC10
/*--------------------------------------------------------*/
void BSP_InitADC10(void);

/*--------------------------------------------------------*/
// Fonction BSP_ReadAllADC()
/*--------------------------------------------------------*/
S_ADCResults BSP_ReadAllADC();

#endif
