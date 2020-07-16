/*
 * File:   EEPROM_24LC256.h
 * Author: swoxtelecom
 *
 * Created on 8. décembre 2015, 17:26
 */

#ifndef EEPROM_24LC256_H
#define	EEPROM_24LC256_H
///*--------------------------------------------------------*/
///*EEPROM_24LC256.h
///*--------------------------------------------------------*/
///*	Description :	Gestion par I2C de l'EEPROM du 24LC256
///*
///*	Auteur 		: 	J. Jeanneret
///*	Version		:	V1.0    12.08.2015
///*	Compilateur	:	XC32 V1.34 & Harmony 1_03
////
///*--------------------------------------------------------*/



#include <stdint.h>
#include "Type_Def32.h"

//void EEPROM_INIT(void);

void Write_EEPROM(int Buffer,int Adresse);
int Read_EEPROM(int Adresse);

void Lecture_Word_EEPROM(char *Word[100],int Start_Adresse, int Stop_Adresse);

//char Read_Word_EEPROM(int H_Byte,int L_Byte);
//void Write_Word_EEPROM(char Buffer,int H_Byte,int L_Byte);

//void Use_DAC(void);


#endif	/* EEPROM_24LC256_H */

