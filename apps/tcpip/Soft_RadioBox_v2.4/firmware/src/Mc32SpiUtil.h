#ifndef Mc32SpiUtil_H
#define Mc32SpiUtil_H



#include <stdint.h>


// prototypes des fonctions
void spi_write1( uint8_t Val);
void spi_write2( uint8_t Val);
uint8_t spi_read1( uint8_t Val);
uint8_t spi_read2( uint8_t Val);

#endif
