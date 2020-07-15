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
#include "Expender_i2c_TCA9548A.h"
#include "math.h"


void Target_IC(long long Channel_Select)
{
    Channel_Expender Num_Expender;

    Num_Expender.All_Expender = Channel_Select;
    int i;
    for(i = 0; i <= 1; i++) //gere 2 expender
    {
        uint8_t Adresse = 0x70+i;
        uint8_t Adresse_Test = 0b11100000;
        uint8_t Chips = Num_Expender.One_Expender[i];
//        Adresse += 224;
        Adresse = Adresse << 1;
        //Adresse += 224;
        i2c_start();
        i2c_write(Adresse); 
        i2c_write(Chips);
        i2c_stop(); 
    }
}
/* *****************************************************************************
 End of File
 */
