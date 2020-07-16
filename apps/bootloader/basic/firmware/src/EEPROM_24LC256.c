
//--------------------------------------------------------
// EEPROM 24LC256
//--------------------------------------------------------
// Gestion par I2C de l'EEPROM du 24LC256
//	Description :	Fonctions pour init et lecture EEPROM 24LC256
//
//	Auteur 		: 	J. Jeanneret
//      Date            :       08.12.2015
//	Version		:	V1.0
//	Compilateur	:	XC32 V1.34 & Harmony 1_03
// Modifications :
//
/*--------------------------------------------------------*/
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "system/common/sys_module.h"   // SYS function prototypes
#include "EEPROM_24LC256.h"
#include "Mc32_I2cNew.h"

#include "Type_Def32.h"
#include <string.h>

#define EEPROM1_WR  0xA0      // 24LC256 Address to write
#define EEPROM1_RD  0xA1      // 24LC256 Address to read


#define DAC_Add_WR  0xC0      // 24LC256 Address to write
#define DAC_Add_RD  0xC1      // 24LC256 Address to write

void EEPROM_INIT(void)
{
    i2c_start();
    i2c_write(EEPROM1_WR);

    i2c_write(0x01);
    i2c_write(0x00);

}

void Write_EEPROM(int Buffer,int Adresse)
{
    int H_Byte;
    int L_Byte;

    H_Byte = Adresse>>8;
    L_Byte = Adresse & 0xFF;

    i2c_start();

    i2c_write(EEPROM1_WR);

    i2c_write(H_Byte);
    i2c_write(L_Byte);

    i2c_write(Buffer);

    i2c_stop();
}



int Read_EEPROM(int Adresse)
{
    int Valeur_Lecture;
    int H_Byte;
    int L_Byte;

    H_Byte = Adresse >>8; // Permet de garde que le bit de poids fort

    L_Byte = Adresse & 0xFF; //permet de garder que le bit de poids faible

    i2c_start();

    i2c_write(EEPROM1_WR);

    i2c_write(H_Byte);
    i2c_write(L_Byte);

    i2c_reStart();
    i2c_write(EEPROM1_RD);

    Valeur_Lecture = i2c_read();

    i2c_stop();

    return Valeur_Lecture;
}












