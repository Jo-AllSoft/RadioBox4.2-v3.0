/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "ADC_DAC_AD5593.h"
#include "Expender_i2c_TCA9548A.h"
#include "Mc32_I2cNew.h"

void Test_Write(void)
{
    i2c_start();
    i2c_write(0x20);
    i2c_write(0b00000011);//configuration Mode //general_purpose ctrl
    i2c_write(0b00000000);
    i2c_write(0b00000000);
    i2c_stop(); 
    
    i2c_start();
    i2c_write(0x20);
    i2c_write(AD5593R_REG_DAC_EN);//configuration Mode //DAC Configuration
    i2c_write(0b00000000);
    i2c_write(0b11111111);
    i2c_stop();
    
    
    i2c_start();
    i2c_write(0x20);
    i2c_write(AD5593R_REG_PD);
    i2c_write(0b00000000);
    i2c_write(0b00000000);
    i2c_stop(); 
    
    i2c_start();
    i2c_write(0x20);
    i2c_write(AD5593R_REG_PULLDOWN);
    i2c_write(0b00000000);
    i2c_write(0b00000000);
    i2c_stop(); 
    
    i2c_start();
    i2c_write(0x20);
    i2c_write(AD5593R_REG_TRISTATE);
    i2c_write(0b00000000);
    i2c_write(0b00000000);
    i2c_stop(); 
    
    i2c_start();
    i2c_write(0x20);
    i2c_write(0b00010000);//DAC ecriture
    i2c_write(0b10000111);//DAC I/O0 
    i2c_write(0b11111111);
    i2c_stop(); 
    
    i2c_start();
    i2c_write(0x20);
    i2c_write(0b00010000);
    i2c_write(0b10001111);
    i2c_write(0b11111111);
    i2c_stop(); 

    static uint8_t Read1 = 0;
    static uint8_t Read2 = 0;  
    
    i2c_start();
    i2c_write(0x20);
    i2c_write(0b01010010);
    i2c_reStart();
    i2c_write(0x21);
    Read1 = i2c_read();
    Read2 = i2c_read();    
    i2c_stop();     
}
void Init_ADC_AD5593(long long Expender,int A0,int Port,int Ref)
{
    Target_IC(Expender);
    
    i2c_start();
    i2c_write(0x20+A0);    
    i2c_write(0b00000011);//configuration Mode //general_purpose ctrl
    i2c_write(0b00000001);//config par defaut
    i2c_write(0b00000000+Ref);//config par defaut

    i2c_start();
    i2c_write(0x20+A0);
    i2c_write(0b00000100);
    i2c_write(0b00000000);
    i2c_write(Port);
    i2c_stop(); 

    Target_IC(0);
}
//void Lecture_ADC(long long Expender,int A0,int Port)
//{
//    Target_IC(Expender);
//    
//    static uint16 Valeur_AD_MSB[8];
//    static uint16 Valeur_AD_LSB[8];
//    static uint16 Valeur_AD[8];
//  
//    i2c_start();
//    i2c_write(0x20+A0);
//    i2c_write(0b00000010);
//    i2c_write(0b00000010);
//    i2c_write(Port);
//    i2c_stop(); 
//
//    i2c_start();
//    i2c_write(0x20+A0);
//    i2c_write(0b01000000);
//
//    static int i = 0;
//    static int num;
//    static uint16 Valeur;
//    for(i = 0; i <= 7; i++)
//    {
//        i2c_reStart();
//        i2c_write(0x21+A0);
//        Valeur_AD_MSB[i] = i2c_read();
//        Valeur_AD_MSB[i] = Valeur_AD_MSB[i] << 8;
//        Valeur_AD_LSB[i] = i2c_read();
//        Valeur_AD[i] = Valeur_AD_MSB[i] + Valeur_AD_LSB[i];
//        
//        num = Valeur_AD[i]>>12;
//        
//        
//        Valeur = Valeur_AD_MSB[i] + Valeur_AD_LSB[i];
//        Valeur = Valeur & 0b0000111111111111;
////        Valeur = Valeur<<4;
////        Valeur = Valeur>>4;
//        
//        P_AD[Expender].Valeur[num] = Valeur;
//    }
//
//    i2c_stop();  
//
//    Target_IC(0);
//}

/* *****************************************************************************
 End of File
 */
