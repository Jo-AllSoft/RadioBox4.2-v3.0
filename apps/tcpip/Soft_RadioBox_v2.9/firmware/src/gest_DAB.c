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
#include "gest_DAB.h"
#include <string.h>
   
const char Name_Channels[CHANNELS_NUMBERS][CHANNELS_LEN]={
    "5A", "5B", "5C", "5D", "6A", "6B", "6C", "6D", 
    "7A", "7B", "7C", "7D", "8A", "8B", "8C", "8D", 
    "9A", "9B", "9C", "9D", "10A", "10B", "10C", "10D", "10N", 
    "11A", "11B", "11C", "11D", "11N", "12A", "12B", "12C", "12D", "12N",
    "13A", "13B", "13C", "13D", "13E", "13F"};

typedef struct
{
    Channels val;
    int freq;
    char name[4];
}Channel;
void Freq_2_Channal (long Freq, char* channel)
{
    Freq_Channels f = Freq;
    switch (f)
    {
        case FREQ_5A:
            strcpy(channel,"5A");
        break;
        case FREQ_5B:
            strcpy(channel,"5B");
        break;
        case FREQ_5C:
            strcpy(channel,"5C");
        break;
        case FREQ_5D:
            strcpy(channel,"5D");
        break;
        case FREQ_6A:
            strcpy(channel,"6A");
        break;
        case FREQ_6B:
            strcpy(channel,"6B");
        break;
        case FREQ_6C:
            strcpy(channel,"6C");
        break;
        case FREQ_6D:
            strcpy(channel,"6D");
        break;
        case FREQ_7A:
            strcpy(channel,"7A");
        break;
        case FREQ_7B:
            strcpy(channel,"7B");
        break;
        case FREQ_7C:
            strcpy(channel,"7C");
        break;
        case FREQ_7D:
            strcpy(channel,"7D");
        break;
        case FREQ_8A:
            strcpy(channel,"8A");
        break;
        case FREQ_8B:
            strcpy(channel,"8B");
        break;
        case FREQ_8C:
            strcpy(channel,"8C");
        break;
        case FREQ_8D:
            strcpy(channel,"8D");
        break;
         case FREQ_9A:
            strcpy(channel,"9A");
        break;
        case FREQ_9B:
            strcpy(channel,"9B");
        break;
        case FREQ_9C:
            strcpy(channel,"9C");
        break;
        case FREQ_9D:
            strcpy(channel,"9D");
        break;
        case FREQ_10A:
            strcpy(channel,"10A");
        break;
        case FREQ_10B:
            strcpy(channel,"10B");
        break;
        case FREQ_10C:
            strcpy(channel,"10C");
        break;
        case FREQ_10D:
            strcpy(channel,"10D");
        break;
        case FREQ_10N:
            strcpy(channel,"10N");
        break;
        case FREQ_11A:
            strcpy(channel,"11A");
        break;
        case FREQ_11B:
            strcpy(channel,"11B");
        break;
        case FREQ_11C:
            strcpy(channel,"11C");
        break;
        case FREQ_11D:
            strcpy(channel,"11D");
        break;
        case FREQ_11N:
            strcpy(channel,"11N");
        break;
        case FREQ_12A:
            strcpy(channel,"12A");
        break;
        case FREQ_12B:
            strcpy(channel,"12B");
        break;
        case FREQ_12C:
            strcpy(channel,"12C");
        break;
        case FREQ_12D:
            strcpy(channel,"12D");
        break;
        case FREQ_12N:
            strcpy(channel,"12N");
        break;
        case FREQ_13A:
            strcpy(channel,"13A");
        break;
        case FREQ_13B:
            strcpy(channel,"13B");
        break;
        case FREQ_13C:
            strcpy(channel,"13C");
        break;
        case FREQ_13D:
            strcpy(channel,"13D");
        break;
        case FREQ_13E:
            strcpy(channel,"13E");
        break;
        case FREQ_13F:
            strcpy(channel,"13F");
        break;
    }
}

int Change_Channel(int Num_Channel)
{
    switch (Num_Channel)
    {
        case 1:
            return FREQ_5A;
        break;

        case 2:
            return FREQ_5B;
        break;

        case 3:
            return FREQ_5C;
        break;

        case 4:
            return FREQ_5D;
        break;

        case 5:
            return FREQ_6A;
        break;

        case 6:
            return FREQ_6B;
        break;

        case 7:
            return FREQ_6C;
        break;

        case 8:
            return FREQ_6D;
        break;

        case 9:
            return FREQ_7A;
        break;

        case 10:
            return FREQ_7B;
        break;

        case 11:
            return FREQ_7C;
        break;

        case 12:
            return FREQ_7D;
        break;

        case 13:
            return FREQ_8A;
        break;

        case 14:
            return FREQ_8B;
        break;

        case 15:
            return FREQ_8C;
        break;

        case 16:
            return FREQ_8D;
        break;

        case 17:
            return FREQ_9A;
        break;

        case 18:
            return FREQ_9B;
        break;

        case 19:
            return FREQ_9C;
        break;

        case 20:
            return FREQ_9D;
        break;

        case 21:
            return FREQ_10A;
        break;

        case 22:
            return FREQ_10B;
        break;

        case 23:
            return FREQ_10C;
        break;

        case 24:
            return FREQ_10D;
        break;

        case 25:
            return FREQ_10N;
        break;

        case 26:
            return FREQ_11A;
        break;

        case 27:
            return FREQ_11B;
        break;

        case 28:
            return FREQ_11C;
        break;

        case 29:
            return FREQ_11D;
        break;

        case 30:
            return FREQ_11N;
        break;

        case 31:
            return FREQ_12A;
        break;

        case 32:
            return FREQ_12B;
        break;

        case 33:
            return FREQ_12C;
        break;

        case 34:
            return FREQ_12D;
        break;

        case 35:
            return FREQ_12N;
        break;

        case 36:
            return FREQ_13A;
        break;

        case 37:
            return FREQ_13B;
        break;

        case 38:
            return FREQ_13C;
        break;

        case 39:
            return FREQ_13D;
        break;

        case 40:
            return FREQ_13E;
        break;

        case 41:
            return FREQ_13F;
        break;
    }
}



int DAB_channel_stringToNum(char* chan)
{
    int num;
    for(num = 0; num < CHANNELS_NUMBERS; num++)
    {
        if(!strcmp(chan, Name_Channels[num]))
        {
            return num+1;
        }
    }
    return 0;
}

/* *****************************************************************************
 End of File
 */
