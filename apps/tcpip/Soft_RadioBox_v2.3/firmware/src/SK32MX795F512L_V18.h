#ifndef __SK32MX795F512L_H
#define __SK32MX795F512L_H
//--------------------------------------------------------
// Fichier SK32MX795F512L_V17.h
//--------------------------------------------------------
//	Description : 	Définition des pattes	       
//	Auteur 		: 	F. Dominé
//      Création	: 	09.02.2012
//      Adaptation  :       12.02.2014 C. HUBER
//  LISTE DES MODIFICATIONS :
//      CHR  26.03.2014 : pont en H passage en LAT
//      CHR  27.03.2014 : Analog adaptation schéma B et suppression Analog2 et 3
//      CHR  03.04.2014 : SPI passage des CSx en LAT
//      CHR  10.04.2014 : Remplacement DDR par LAT
//      CHR  10.04.2014 : Modifications pour PEC12
//      CHR  26.05.2014 : Ajout définitions SYS_FREQ et PB_FREQ
//
//      Version KIT     PCB 11020_B
//	Version		:	V1.8
//	Compilateur	:	XC32 V1.31
//--------------------------------------------------------

//--------------------------------------------------------
// Analogique
//--------------------------------------------------------
// CHR 27.03.2014 adaptation schéma B et suppression Analog2 et 3
//#define Analog0		PORTBbits.RB0
//#define Analog1		PORTBbits.RB1

// I2C
//--------------------------------------------------------
#define I2C_SCL      PORTDbits.RD10
#define I2C_SDA      PORTDbits.RD9
#define I2C_SDA_T    LATDbits.LATD9



//--------------------------------------------------------
// Définition des fonctions prototypes
//--------------------------------------------------------
void SK32MX795F512L_IO_Default(void);


// Définition des fréquences


#define SYS_FREQ (80000000L)    //80 MHz
#define PB_DIV 1
#define PB_FREQ (SYS_FREQ / PB_DIV)

#endif
