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

#ifndef _EXPENDER_I2C_TCA9548A_H    /* Guard against multiple inclusion */
#define _EXPENDER_I2C_TCA9548A_H

typedef union
{
    long long All_Expender;
    char One_Expender[8];
}Channel_Expender;


//typedef enum 
//{
//    Channel_ExpenderNul = 65,
//    Channel_Expender0 = 0,
//    Channel_Expender1 = 1,
//    Channel_Expender2 = 2,
//    Channel_Expender3 = 3,
//    Channel_Expender4 = 4,
//    Channel_Expender5 = 5,
//    Channel_Expender6 = 6,
//    Channel_Expender7 = 7,
//    Channel_Expender8 = 8,
//    Channel_Expender9 = 9,
//    Channel_Expender10 = 10,
//    Channel_Expender11 = 11,
//    Channel_Expender12 = 12,
//    Channel_Expender13 = 13,
//    Channel_Expender14 = 14,
//    Channel_Expender15 = 15               
//            
//}Channel_Expender;
#define All_Expender_Close 0

#define CHANNEL_SELECT(chan) ((long long)1<<chan)
#define ADC_Fader CHANNEL_SELECT(0) 
#define ADC_Pot_Rotatif CHANNEL_SELECT(1) 
#define MP3_Num3 CHANNEL_SELECT(2) 
#define MP3_Num4 CHANNEL_SELECT(3) 
#define MP3_Num5 CHANNEL_SELECT(4) 
#define MP3_Num6 CHANNEL_SELECT(5) 
#define MP3_Num7 CHANNEL_SELECT(6) 
#define MP3_Num8 CHANNEL_SELECT(7) 

void Target_IC(long long Channel_Select);





#endif /* _EXPENDER_I2C_TCA9548A_H */

/* *****************************************************************************
 End of File
 */
