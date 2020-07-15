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

#ifndef _EEPROM_DRIVER_H    /* Guard against multiple inclusion */
#define _EEPROM_DRIVER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "driver/i2c/drv_i2c.h"
#include "ADC_DAC_AD5593.h"
#include "Audio_PT2314.h"


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
void I2CMasterOpStatusCb ( DRV_I2C_BUFFER_EVENT event,
                           DRV_I2C_BUFFER_HANDLE bufferHandle,
                           uintptr_t context);

void I2CSlaveOpStatusCb  ( DRV_I2C_BUFFER_EVENT event,
                           DRV_I2C_BUFFER_HANDLE bufferHandle,
                           uintptr_t context);

DRV_I2C_BUFFER_EVENT APP_Check_Transfer_Status(DRV_HANDLE drvOpenHandle, DRV_I2C_BUFFER_HANDLE drvBufferHandle);

void DelayMs(unsigned long int msDelay );

void DelayUs(unsigned long int usDelay );


#define NB_DEVICE I2C_NB_AD5593     // Défini le nombre de chip I2C sur le bus

//#define EXPENDER_PCA9547
#define EXPENDER_TCA9548



#define I2C_EXPANDER0_ADD   0xE0
#define I2C_EXPANDER1_ADD   0xE2
#define I2C_EXPANDER2_ADD   0xE4
#ifdef EXPENDER_TCA9548

#define DEACTIVATE_EXPANDER 0
// Expander 0
#define EXP_ADC_FADER       1<<0     // 6 faders (0-5) (MIC1:0, MIC4:3, ln1:4, ln2:5)
#define EXP_ADC_POT_ROT     1<<1     // 7 pots rotatifs (0-6)

//Expander 1
#define EXP_PT_MIC1         1<<5
#define EXP_PT_MIC2         1<<4
#define EXP_PT_MIC3         1<<3
#define EXP_PT_MIC4         1<<2
#define EXP_PT_LIGNE1       1<<0
#define EXP_PT_LIGNE2       1<<1
#define EXP_DAC_ADC_FADER   1<<6
    
//Expander 2
#define EXP_STUDIO          1<<3
#define EXP_MASTER          1<<2
#define EXP_PHONE1          1<<7
#define EXP_PHONE2          1<<6
#define EXP_PHONE3          1<<5
#define EXP_PHONE4          1<<4
#define EXP_PHONE_DJ        1<<1

#define EXP_ON_AIR          1<<0

#endif

#ifdef EXPENDER_PCA9547

#define DEACTIVATE_EXPANDER ((0<<3) + 0)

// Expander 0
#define EXP_ADC_FADER       ((1<<3) + 0)     // 6 faders (0-5) (MIC1:0, MIC4:3, ln1:4, ln2:5)
#define EXP_ADC_POT_ROT     ((1<<3) + 1)     // 7 pots rotatifs (0-6)

//Expander 1
#define EXP_PT_MIC1         ((1<<3) + 5)
#define EXP_PT_MIC2         ((1<<3) + 4)
#define EXP_PT_MIC3         ((1<<3) + 3)
#define EXP_PT_MIC4         ((1<<3) + 2)
#define EXP_PT_LIGNE1       ((1<<3) + 0)
#define EXP_PT_LIGNE2       ((1<<3) + 1)
#define EXP_DAC_ADC_FADER   ((1<<3) + 6)
    
//Expander 2
#define EXP_STUDIO          ((1<<3) + 3)
#define EXP_MASTER          ((1<<3) + 2)
#define EXP_PHONE1          ((1<<3) + 7)
#define EXP_PHONE2          ((1<<3) + 6)
#define EXP_PHONE3          ((1<<3) + 5)
#define EXP_PHONE4          ((1<<3) + 4)
#define EXP_PHONE_DJ        ((1<<3) + 1)

#define EXP_ON_AIR          ((1<<3) + 0)

#endif
/*******************************************************************************
 *                      AD5593 INIT REGISTERS
 *******************************************************************************
 * Géré pour l'instant, ADC, DAC, GPIO en output
 * 
 *                  General-purpose control register (0x03)
 * - 15-10  : Unused (set to 0)
 * - 9      : ADC buffer precharge, active l'AD uniquement lors de conversions
 * - 8      : ADC buffer enable, active le buffer de l'ADC (voir Datasheet p.19)
 * - 7      : Lock configuration, Bloque le contenu des registres de configuration
 * - 6      : Write all DACs, écris la valeur envoyée sur tout les DACs
 * - 5      : ADC range select, double la tension de référence de l'ADC
 * - 4      : DAC range select, double la tension de référence du DAC
 * - 3-0    : Unused (set to 0)
 * 
 *                  ADC pin configuration (0x04)
 * - 15-8   : Unused (set to 0)
 * - 7-0    : Selectionne la pin (de 7 à 0) comme ADC
 * 
 *                  ADC sequence register (0x02)
 * - 15-10  : Unused (set to 0)
 * - 9      : ADC sequence repeat, lis en boucle la séquence donnée (IMPORTANT: sans lui la conversion AD ne se fait qu'une fois !!)
 * - 8      : TEMP, Inclut la lecture de la température
 * - 7-0    : Inclus la pin (de 7 à 0) dans la séquence de conversion
 * 
 *                  DAC pin configuration (0x05)
 * - 15-8   : Unused (set to 0)
 * - 7-0    : Selectionne la pin (de 7 à 0) comme DAC
 * 
 *                  GPIO write configuration (0x08)
 * - 15-8   : Unused (set to 0)
 * - 7-0    : Selectionne la pin (de 7 à 0) comme output
 * 
 *                  GPIO read configuration (0x0A)
 * - 15-8   : Unused (set to 0)
 * - 7-0    : Selectionne la pin (de 7 à 0) comme input
 * 
 * 
 *                  Power-down/reference control (0x0B)
 * -15-11   : Unused (set to 0)
 * -10      : PD ALL, désactive tout
 * -9       : EN REF, active la référence
 * -8       : Unused (set to 0)
 * -7-0     : Désactive un port précis (de 7 à 0)
 * 
 *                  open drain configuration (0x0C)
 * - 15-8   : Unused (set to 0)
 * - 7-0    : Selectionne la pin (de 7 à 0) comme open drain
 * 
 ******************************************************************************/

#define I2C_AD5593_ADD  0x20
#define I2C_NB_AD5593   4
#define I2C_NB_PT2314 13
#define I2C_AD5593_INIT_SIZE 27
typedef struct
{
    struct
    {
        char msgInit[I2C_AD5593_INIT_SIZE];
        size_t initPtr;
        bool isInit;
    }Init;
    struct
    {
        char port;
        char msgRead[17];
        size_t nbADC;
        uint16_t valeur[8];
    }ADC;
    struct
    {
        char port;
        char msgWrite[3*8];
        char nbDAC;
        char wrPtr;
    }DAC;
    struct
    {
        char portIN;
        char portOUT;
        char msgWrite[3];
        char msgRead[3];
        bool writeAsked;
    }GPIO;
    uint8_t add;
}I2C_Msg_AD5593;


// Ce define permet d'avoir la séquence d'initialisation ainsi que de lecture pour un AD5593 utilisé en ADC uniquement
//#define I2C_AD5593_INIT_START_READ(doubleRefADC, portADC, refIntEnable) {3, 3, doubleRefADC<<5, 4, 0, portADC, 2, 2, portADC, 11, refIntEnable<<1, 0, 0b01000000}// Le dernier byte permet de lancer la lecture ADC
#define I2C_AD5593_START_READ {0b01000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}// Le premier byte permet de lancer la lecture ADC
//#define I2C_AD5593_START_INPUT {0b01000000, 0}// Registre des valeurs pour les outputs
#define I2C_AD5593_START_OUTPUT {0b00001001, 0, 0}// Registre des valeurs pour les outputs
#define I2C_AD5593_INIT_START_WRITE(doubleRefDAC, portDAC, refIntEnable) {3, 3, doubleRefDAC<<4, 5, 0, portDAC, 6, 0, ~portDAC, 11, refIntEnable<<1, 0, 0b00010100, 0b11000001, 0b00000000}// Le dernier byte permet de lancer la lecture ADC
#define I2C_AD5593_INIT(RefADCx2, portADC, RefDACx2, portDAC, refIntEn, portIN, portOUT, portOpenDrain)\
{3, 3, (RefADCx2<<5)+(RefDACx2<<4),         /* Configure les références */ \
 4, 0, portADC,                             /* Défini les port ADC */\
 2, 2, portADC,                             /* Configure la séquence ADC */\
 6, 0, (portDAC|portADC|portOUT|portIN)==0xFF ? 0:~(portDAC|portADC|portOUT|portIN),   /* Désactive les pull down pour les ports utilisés */\
 5, 0, portDAC,                             /* Défini les ports DAC */\
 8, 0, portOUT,                             /* Défini les ports OUT */\
 10, 0, portIN,                             /* Défini les ports IN */\
 12, 0, portOpenDrain,                     /* Défini les ports opendrain */\
 11, refIntEn<<1, 0},                       /* Défini la référence interne */\
 .ADC.port = portADC, .DAC.port = portDAC, .ADC.nbADC=0, .DAC.nbDAC=0, .Init.initPtr = 0, .Init.isInit = false, .GPIO.msgWrite=I2C_AD5593_START_OUTPUT   /* Défini les paramètres pour l'I2C */

typedef enum{   AD_FADERS_IN, AD_POTROT_IN, AD_PT_OUT, AD_ON_AIR}AD_DEVICES;

typedef enum{SONG_MASTER,SONG_STUDIO,SONG_PHONE1,SONG_PHONE2,SONG_PHONE3,SONG_PHONE4,SONG_PHONEDJ}SONG_OUTPUT;

typedef enum{SONG_LIGNE1_DAC=0,SONG_LIGNE2_DAC=2,SONG_MICRO1_DAC=4,SONG_MICRO2_DAC,SONG_MICRO3_DAC,SONG_MICRO4_DAC}SONG_INPUT_DAC;
typedef enum{SONG_MICRO1_ADC,SONG_MICRO2_ADC,SONG_MICRO3_ADC,SONG_MICRO4_ADC,SONG_LIGNE1_ADC,SONG_LIGNE2_ADC}SONG_INPUT_ADC;



void I2C_AD5593_Init_Buffer(void);


typedef struct
{
    char msg[2];
    size_t size;
    uint8_t add[2];
}I2C_Msg_Expander;

typedef enum {I2C_DEVICE_WRITE, I2C_DEVICE_WAIT}I2C_Devices_States;

typedef struct
{
    struct
    {
        PT2314_Volume vol;
        PT2314_Attenuation leftAttenuation;
        PT2314_Attenuation rightAttenuation;
        PT2314_AudioSwitch audioSwitch;
        int bass;
        int treble;
    }param;
    char msgWrite[10];
    size_t size;
    uint8_t add;
    bool isConfigurate;
}I2C_PT2314;
#define I2C_PT2314_WRITE {\
0b00111111, /* Volume au minimum */\
0b11011111, /* Speaker gauche Mute */\
0b11111111, /* Speaker droite Mute */\
0b01011100, /* Stereo 1 Loudness OFF 0dB */\
0b01100000, /* Bass -14dB */\
0b01110000  /* Treble -14dB */\
}, .isConfigurate=true
#define I2C_PT2314_ADD 0x88

typedef enum{   PT_MIC1, PT_MIC2, PT_MIC3, PT_MIC4, PT_LIGNE1, PT_LIGNE2, 
                PT_MASTER,PT_STUDIO, PT_PHONE1, PT_PHONE2, PT_PHONE3, PT_PHONE4, PT_PHONE_DJ}PT_DEVICES;

#define I2C_EEPROM_ADD 0xA0
typedef struct
{
    struct
    {
        bool toWrite;
        char msgWrite[66];
        size_t size;
    }write;
    struct
    {
        bool toRead;
        char* msgRead;
        size_t size;
        uint8_t startAddress[2];
    }read;
    uint8_t add;
}I2C_EEPROM;

typedef enum {I2C_EXPANDER_HANDLE, I2C_AD5593_HANDLE, I2C_PT2314_HANDLE, I2C_EEPROM_HANDLE, I2C_HANDLE, I2C_ERROR}I2C_States;
I2C_States I2C_state;


typedef struct
{

    int ACK_Expender[3];
    int ACK_PT2314[13];
    int ACK_AD5532[4];
    
}I2C_ETAT_ACKNOLEGE;

I2C_ETAT_ACKNOLEGE StateAck;


// Fonctions utilisateurs
void I2C_PT_Volume(PT_DEVICES d, float volume);
void I2C_PT_Speak_Att(PT_DEVICES d, float attenuation, T_LR lr);
void I2C_PT_AudioSwitch(PT_DEVICES d, float gain, bool loodness, Stereo stereo);
void I2C_PT_BASS_TREBLE(PT_DEVICES d, int attenuation, PT_BT choice);
void I2C_Write_Buffer(AD_DEVICES device, int port, int value);
void I2C_Write_GPIO(AD_DEVICES device, int port, bool value);
#define ON_AIR(out) I2C_Write_GPIO(AD_ON_AIR, 2, out)
uint16_t I2C_Read_Buffer(AD_DEVICES device, int port);
// Fonctions EEPROM
bool I2C_EEPROM_write(char* w, size_t size, uint16_t add);
bool I2C_EEPROM_read(char* r, size_t size, uint16_t add);
bool I2C_EEPROM_isReady(void);

bool APP_Write_Tasks(void);

PT_DEVICES Select_Input(int i);//Jo (13.02.2018)
PT_DEVICES Select_Ouput(int i);//Jo (13.02.2018)
void ResetConfig(int Nconfig);//Jo (13.03.2018)
char *InputTxt (int N);//Jo (14.03.2018)
void Upload_Audio_CSV(char* csv);
#endif /* _EEPROM_DRIVER_H */

/* *****************************************************************************
 End of File
 */
