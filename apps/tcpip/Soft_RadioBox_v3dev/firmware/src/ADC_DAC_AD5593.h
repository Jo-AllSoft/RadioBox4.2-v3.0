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

#ifndef _ADC_DAC_AD5593_H    /* Guard against multiple inclusion */
#define _ADC_DAC_AD5593_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <stdio.h>
#include <stdint.h>


#define Ref_x1 0
#define Ref_ADC_x2 32
#define Ref_DAC_x2 16
#define Ref_ADC_DAC_x2 48
#define A0_GND 0
#define A0_VCC 2

#define MAX_AD 10

typedef enum { ADC_FADERS, ADC_ROTATIFS}ADC_Ref_Tableau;
typedef struct
{
    uint16_t mic1;
    uint16_t mic2;
    uint16_t mic3;
    uint16_t mic4;
    uint16_t ln1;
    uint16_t ln2;
    uint16_t unused[2];
}AD_Faders;
typedef struct
{
    uint16_t r1;
    uint16_t r2;
    uint16_t r3;
    uint16_t r4;
    uint16_t r5;
    uint16_t r6;
    uint16_t r7;
    uint16_t unused;
}AD_Rotatif;
typedef union
{
    AD_Rotatif AD_rotatif;
    AD_Faders AD_faders;
    uint16_t Valeur[8];
}Parametre_AD;

Parametre_AD P_AD[10];

typedef enum IoFunction
{
	ADC,
	DAC,
	DAC_AND_ADC,
	GPIO,
	UNUSED_HIGH,
	UNUSED_LOW,
	UNUSED_TRISTATE,
	UNUSED_PULLDOWN,
}IoFunction;

typedef enum GpioDirection
{
	GPIO_INPUT,
	GPIO_OUTPUT,
}GpioDirection;

typedef enum AD5593Register
{
	AD5593R_REG_NOOP = 0x0,
	AD5593R_REG_DAC_READBACK = 0x1,
	AD5593R_REG_ADC_SEQ = 0x2,
	AD5593R_REG_CTRL = 0x3,
	AD5593R_REG_ADC_EN = 0x4,
	AD5593R_REG_DAC_EN = 0x5,
	AD5593R_REG_PULLDOWN = 0x6,
	AD5593R_REG_LDAC = 0x7,
	AD5593R_REG_GPIO_OUT_EN = 0x8,
	AD5593R_REG_GPIO_SET = 0x9,
	AD5593R_REG_GPIO_IN_EN = 0xA,
	AD5593R_REG_PD = 0xB,
	AD5593R_REG_OPEN_DRAIN = 0xC,
	AD5593R_REG_TRISTATE = 0xD,
	AD5593R_REG_RESET = 0xF,
}AD5593Register;

void Test_Write(void);
void Init_DAC_AD5593(long long Expender,int A0,int Port,int Ref);
void Write_ADC(long long Expender,int A0,int Port,int Valeur);
void Init_ADC_AD5593(long long Expender,int A0,int Port,int Ref);
void Lecture_ADC(long long Expender,int A0,int nbLecture, ADC_Ref_Tableau tab);
#endif /* _ADC_DAC_AD5593_H */

/* *****************************************************************************
 End of File
 */
