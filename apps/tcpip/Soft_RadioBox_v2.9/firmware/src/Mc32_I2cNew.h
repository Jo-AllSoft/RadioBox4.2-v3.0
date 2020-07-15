#ifndef MC32_I2CUTILCCS_H
#define MC32_I2CUTILCCS_H
//--------------------------------------------------------
//	Mc32_I2cUtilCCS.h
//--------------------------------------------------------
//	Description :	Adaptation des fonctions I2C afin
//			de pouvoir utiliser la même syntaxe 
//			que sous CCS.
//
//	Auteur 		: 	C. HUBER
//      Date            :       22.05.2014
//	Version		:	V1.0
//	Compilateur	:	XC32 V1.31
// Modifications :
//     
/*--------------------------------------------------------*/

#include <stdbool.h>
#include "Type_Def32.h"
#include "peripheral\I2C\plib_i2c.h"


//------------------------------------------------------------------------------
// i2c_init
//
// Initialisationde l'I2c
//   si bool Fast = false   LOW speed
//   si bool Fast = true    HIGH speed
//------------------------------------------------------------------------------

void i2c_init(void);
void i2c_start(void);
void i2c_reStart(void);
void i2c_write( uint8 data );
uint8 i2c_read(void);
void i2c_stop( void );

//------------------------------------------------------------------------------
// i2c_read()
//
// Syntaxe : 	data = i2c_read (ack);
// La fonction retourne l'octet lu.
// Le paramètre ack :
// 1 signifie qu'il faut effectuer l'acquittement.
// 0 signifie qu'il ne faut pas effectuer l'acquittement.
//
// Remarque : réalisée à partir du code de l'exemple
//




#endif
