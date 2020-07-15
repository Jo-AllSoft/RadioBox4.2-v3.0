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
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "Type_Def32.h"
#include "FT_GPU.h"
#include "stdint.h"



#ifndef _FCT_ECRAN_H    /* Guard against multiple inclusion */
#define _FCT_ECRAN_H

#define MAX_BAR 2
#define MAX_BTN 25
#define SIZE_TXT_BTN 20

uint8_t Mem_BTN[MAX_BTN];
uint8_t Rebond[MAX_BTN];




/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
typedef enum {
    BTN_OFF = 0,
    BTN_ON = 1,
    BTN_TOGGLE = 2
     
}T_Action_BTN;
typedef enum {
    ONE_CLICK = 0,
    TOGGLE = 1,
    MODE_ON = 2,
    MODE_OFF = 3        
}T_BTN;

typedef struct
{
    long x;
    long y;
    long Long_Bar;
    long Larg_Bar;
    
}Parametre_Barre;

Parametre_Barre P_Bar[MAX_BAR];
long max[MAX_BAR];
int Time_max[MAX_BAR];



typedef struct
{
    long x;
    long y;
    long H_BTN;
    long W_BTN;
    long FG_Color1;
    long FG_Color2;
    long Txt_Color;
    int Taille_Txt;
    char Txt[50];
    
}Parametre_BTN;


Parametre_BTN P_BTN[MAX_BTN];

typedef struct
{
    uint8 Blue;
    uint8 Grun;
    uint8 Red;
    
}Color3;


typedef union
{
    long Global_Color;
    Color3 color;
}Separate_color;


typedef struct Bitmap_header
{
    uint8 Format;
    uint16 Width;
    uint16 Height;
    uint16 Stride;
    uint32 Arrayoffset;
    
}Bitmap_header_t;




void Fct_Bar(int N_Bar,long Pourcent_Bar);
void Fct_Bar_Init(int N_Bar,long x,long y,long Long_Bar,long Larg_Bar);
int Affichage_BTN(int N_BTN,T_BTN Mode);
void Fct_BTN_Init(int N_BTN,int FG_Color1,int FG_Color2,int Color_txt,int x,int y ,int w,int h,int T_Txt,char *txt_BTN);
int CMD_BTN(int N_BTN,T_BTN Mode,int BTN,int Rebond_BTN);

void Check_BTN(int N_BTN,T_Action_BTN Mode);
void Change_Text_BTN(int N_BTN,char Text_BTN[]);
void Change_Color_ON_BTN(int N_BTN,long Color);
void Change_Color_OFF_BTN(int N_BTN,long Color);
void Load_Image(void);

void Load_RadioBox1(void);
void Load_Logo_Network(void);

#endif /* _FCT_ECRAN_H */

/* *****************************************************************************
 End of File
 */
