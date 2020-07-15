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


#ifndef _AUDIO_PT2314_H    /* Guard against multiple inclusion */
#define _AUDIO_PT2314_H


#define ADRESSE 0x88

typedef struct
{
    char volUni:3;
    char volDiz:3;
    char mode:2;
}PT2314_Volume;

typedef struct
{
    char attUni:3;
    char attDiz:3;
    char LR:1;
    char mode:2;
}PT2314_Attenuation;

typedef struct
{
    char stereo:2;
    char loudness:1;
    char gain:2;
    char mode:3;
}PT2314_AudioSwitch;

typedef enum {
    Stereo1 = 0,
    Stereo2 = 1,
    Stereo3 = 2,
    Stereo4 = 3
}Stereo;

typedef enum {
    Loudeness_ON = 0,
    Loudeness_OFF = 1
}T_Loudeness;

typedef enum { Gain_11_25dB = 0, Gain_7_5dB = 1, Gain_3_75dB =2, Gain_0dB }T_Gain;

typedef enum {
    LEVEL_MOINS_14_DB = 0b0000,
    LEVEL_MOINS_12_DB = 0b0001,
    LEVEL_MOINS_10_DB = 0b0010,
    LEVEL_MOINS_8_DB = 0b0011,
    LEVEL_MOINS_6_DB = 0b0100,
    LEVEL_MOINS_4_DB = 0b0101,
    LEVEL_MOINS_2_DB = 0b0110,
    LEVEL_0_DB = 0b0111,
    LEVEL_PLUS_2_DB = 0b1110,
    LEVEL_PLUS_4_DB = 0b1101,
    LEVEL_PLUS_6_DB = 0b1100,
    LEVEL_PLUS_8_DB = 0b1011,
    LEVEL_PLUS_10_DB = 0b1010,
    LEVEL_PLUS_12_DB  = 0b1001,
    LEVEL_PLUS_14_DB  = 0b1000              
}LEVEL_DATA;

typedef enum {
    LEFT = 64,
    RIGHT = 96
}T_LR;

typedef enum
{
    PT_BASS = false,
    PT_TREBLE = true,
    TDA_MIDDLE = 2
}PT_BT;
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

void Volume(int Valeur_Vol,long long Channel_Select);//valeur 0 a 63

void SPEAKER_ATTENUATORS(T_LR LR,int Valeur_ATT_R,long long Channel_Select);// 0 a 31 (31 == Mute)
void Audio_Switch(Stereo Num,T_Loudeness Loudness,T_Gain Gain,long long Channel_Select);

void Reglage_BASS(LEVEL_DATA Valeur_Bass,long long Channel_Select);
void Reglage_TREBLE(LEVEL_DATA Valeur_Treble,long long Channel_Select);







//typedef struct
//{
//    int cmd:3;
//    int B:2;
//    int A:3;
//}Speaker_Attenuator;
//typedef struct
//{
//    int cmd:3;
//    int G:2;
//    int S:3;
//}Data_byte;
//
//typedef union
//{
//    unsigned char byte;
//    Data_byte db;
//    Speaker_Attenuator sa;
//}bytedecommande;
//bytedecommande cmd;
//cmd.db.G =
#endif /* _AUDIO_PT2314_H */

/* *****************************************************************************
 End of File
 */
