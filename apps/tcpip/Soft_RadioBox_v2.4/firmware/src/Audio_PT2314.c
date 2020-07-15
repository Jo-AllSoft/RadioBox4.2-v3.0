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

#include "Mc32_I2cNew.h"
#include "Audio_PT2314.h"
#include "Expender_i2c_TCA9548A.h"




void Volume(int Valeur_Vol,long long Channel_Select)//valeur 0 a 63
{
    Target_IC(Channel_Select);

    int MSB = 0;
    int LSB = 0;
    int Trame;
    
    if(Valeur_Vol > 63)
    {
        Valeur_Vol = 63;
    }
    if(Valeur_Vol < 0)
    {
        Valeur_Vol = 0;        
    }
    MSB = Valeur_Vol>>4;
    LSB = Valeur_Vol & 0x0F;
  
    i2c_start();
    i2c_write(ADRESSE);
    
    Trame = (MSB << 4) + LSB;
    i2c_write(Trame);
    //i2c_write(LSB);
  
    i2c_stop();
         
}

void SPEAKER_ATTENUATORS(T_LR LR,int Valeur_ATT_R,long long Channel_Select)// 0 a 31 (31 == Mute)
{
    Target_IC(Channel_Select);
    
    int MSB = 0;
    int LSB = 0;  
    int Trame;
    
    if(Valeur_ATT_R > 31)
    {
        Valeur_ATT_R = 31;
    }
    if(Valeur_ATT_R < 0)
    {
        Valeur_ATT_R = 0;        
    }
    MSB = (Valeur_ATT_R + 128 + LR) >> 4;
    LSB = (Valeur_ATT_R + 128 + LR) & 0x0F;
    
    i2c_start();
    i2c_write(ADRESSE);
    
    Trame = (MSB << 4) + LSB;
    i2c_write(Trame);
  
    i2c_stop();
    


}


void Audio_Switch(Stereo Num,T_Loudeness Loudness,T_Gain Gain,long long Channel_Select)// 
{
    Target_IC(Channel_Select);

    int MSB = 0;
    int LSB = 0;  
    int Trame;
    
    int Config_Audio = 64 + Gain + Loudness + Num;
    
    MSB = Config_Audio >> 4;
    LSB = Config_Audio & 0x0F;
    
    i2c_start();
    i2c_write(ADRESSE);

    Trame = (MSB << 4) + LSB;
    i2c_write(Trame);
  
    i2c_stop();
    
}


void Reglage_BASS(LEVEL_DATA Valeur_Bass,long long Channel_Select)
{
    Target_IC(Channel_Select);

    int MSB = 0;
    int LSB = 0; 
    int Trame;
       
    int Config_Bass = 64 + 32 + Valeur_Bass;
    
    MSB = Config_Bass >> 4;
    LSB = Config_Bass & 0x0F;
    
    i2c_start();
    i2c_write(ADRESSE);
    
    Trame = (MSB << 4) + LSB;
    i2c_write(Trame);;
  
    i2c_stop();
    

}

void Reglage_TREBLE(LEVEL_DATA Valeur_Treble,long long Channel_Select)
{
    Target_IC(Channel_Select);

    int MSB = 0;
    int LSB = 0; 
    int Trame;
       
    int Config_Treble = 64 + 32 + 16 + Valeur_Treble;
    
    MSB = Config_Treble >> 4;
    LSB = Config_Treble & 0x0F;
    
    i2c_start();
    i2c_write(ADRESSE);
    
    Trame = (MSB << 4) + LSB;
    i2c_write(Trame);
  
    i2c_stop();   

}

/* *****************************************************************************
 End of File
 */
