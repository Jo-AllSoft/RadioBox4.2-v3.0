// Mc32SpiUtil.c
// Utilitaire  SPI
//
//	Description : 	fonctions SPI CCS like
//	Auteur 		: 	C. HUBER
//      Création	: 	08.04.2014
//      Modifications   :       09.02.2015 CHR

//  LISTE DES MODIFICATIONS :
//      Utilisation des stdint      09.02.2015 CHR
//      Adaptation à la plib_spi    09.02.2015 CHR

//      Version KIT     PCB 11020_B
//	Version		:	V1.1
//	Compilateur	:	XC32 V1.33 + Harmony 1.00
/*--------------------------------------------------------*/


#include "Mc32SpiUtil.h"
#include "peripheral\SPI\plib_spi.h"


void spi_write1( uint8_t Val){
   bool SpiBusy, SpiFull;

   // Attente si Tx Buffer Full
   do {
     SpiFull =  PLIB_SPI_TransmitBufferIsFull(SPI_ID_1) ;
   } while (SpiFull == true);
   PLIB_SPI_BufferWrite(SPI_ID_1, Val);

   // Attente de la fin de la transmission
   do {
     SpiBusy =  PLIB_SPI_IsBusy(SPI_ID_1) ;
   } while (SpiBusy == true);
} // spi_write1


//void spi_write2( uint8_t Val){
//   bool SpiBusy, SpiFull;
//
//   // Attente si Tx Buffer Full
//   do {
//     SpiFull =  PLIB_SPI_TransmitBufferIsFull(SPI_ID_2) ;
//   } while (SpiFull == true);
//   PLIB_SPI_BufferWrite(SPI_ID_2, Val);
//
//   // Attente de la fin de la transmission
//   do {
//     SpiBusy =  PLIB_SPI_IsBusy(SPI_ID_2) ;
//   } while (SpiBusy == true);
//} // spi_write2

uint8_t spi_read1( uint8_t Val){
   int SpiTxBuffFull, SpiRxBuffEmpty;
   uint32_t lu;

   // Attente si Tx Buffer Full
   do {
     SpiTxBuffFull =  PLIB_SPI_TransmitBufferIsFull(SPI_ID_1) ;
   } while (SpiTxBuffFull == true);

   PLIB_SPI_BufferWrite(SPI_ID_1, Val);

   // Attente tans que Rx Buffer is Empty
   do {
     SpiRxBuffEmpty =  PLIB_SPI_ReceiverFIFOIsEmpty(SPI_ID_1) ;
   } while (SpiRxBuffEmpty == true);
  
   lu = PLIB_SPI_BufferRead(SPI_ID_1);
   return lu;
}

// uint8_t spi_read2( uint8_t Val){
//   int SpiTxBuffFull, SpiRxBuffEmpty;
//   uint8_t lu;
//
//   // Attente si Tx Buffer Full
//   do {
//     SpiTxBuffFull =  PLIB_SPI_TransmitBufferIsFull(SPI_ID_2) ;
//   } while (SpiTxBuffFull == true);
//
//   PLIB_SPI_BufferWrite(SPI_ID_2, Val);
//
//    // Attente tans que Rx Buffer is Empty
//   do {
//     SpiRxBuffEmpty =  PLIB_SPI_ReceiverFIFOIsEmpty(SPI_ID_2) ;
//   } while (SpiRxBuffEmpty == true);
//   lu = PLIB_SPI_BufferRead(SPI_ID_2);
//
//   return lu;
//}



