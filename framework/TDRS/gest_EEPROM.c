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
#include "gest_EEPROM.h"
#include "system_config.h"
#include "EEPROM_24LC256.h"
#include "app.h"

static EEPROM_Element list;
int erase = 0;

#define START_MAINTENANCE_CSV 2001
char EEPROM_MaintenanceCSV[30001];
void EEPROM_AddAndRead_1(unsigned char* d, int start, int end, EEPROM_Type type, const unsigned char* def);

__inline void EEPROM_Start_List(void)
{
    list.nextElm = (EEPROM_Element*) 1;
    EEPROM_AddAndRead(EEPROM_MaintenanceCSV, START_MAINTENANCE_CSV, 30000, MAINTENANCE_TYPE, "Device;State;Time\r\n");
}


void EEPROM_AddAndRead_1(unsigned char* d, int start, int end, EEPROM_Type type, const unsigned char* def)
{
    EEPROM_Element* listTmp = &list;
    EEPROM_Element* nlist = malloc(sizeof(EEPROM_Element));
    int i = 0, size = (end - start + 1);  // Lecture
    if(type == STRING_TYPE || type == MAINTENANCE_TYPE)
    {
        do
        {
            d[i] = Read_EEPROM(start + i);
            i++;
        }while(i < size && d[i - 1] != 0 && d[i - 1] != 0xFF);
    }
    else
    {
        for(i = 0; i < size; i++)
        {
            d[i] = Read_EEPROM(start + i);
        }
    }
    switch(type)
    {
        case CHAR_TYPE:
            if(d[0] == 0xFF)
                d[0] = (int) def;
        break;
        case CHAR_TAB_TYPE:
            if(d[0] == 0xFF)
                memcpy(d, def, size);
        break;
        case STRING_TYPE:
            if(d[0] == 0xFF)
                strcpy(d, def);
        break;
        case IP_STRING_TYPE:
            if((d[0] == '0') || (d[0] == 0xFF) || (d[0] == 0x0a))
                strcpy(d, def);
        break;
        case IP_NUM_TYPE:
            if((d[0] == 0) || (d[0] == 0xFF))
                memcpy(d, def, 4);
        break;
        case IP_NUM_MASK_TYPE:
        break;
        case MAINTENANCE_TYPE:
            if(d[0] == 0 || d[0] == 0xFF)
            {
                strcpy(d, def);
                size = strlen(d);
                list.mem.change = true;
                list.byteToChange = 0;
            }
            else
            {
                size = i-1;
                list.mem.change = false;
                list.byteToChange = size;
            }
        break;
        case CALIBRATION_TYPE:
            if(d[0] == 0)
            {
                memcpy(d, def, size);
            }
        break;
        default:break;
    }
    // ajout dans la liste pour la fonction d'écriture
    if(listTmp->nextElm != (EEPROM_Element*)1)
    {
        nlist->mem.data = d;
        nlist->size = size;
        nlist->start = start;
        nlist->nextElm = NULL;
        nlist->mem.change = false;
        nlist->byteToChange = 0;
        nlist->type = type;
        
        while(listTmp->nextElm != NULL)
        {
            listTmp = listTmp->nextElm;
        }
        listTmp->nextElm = nlist;
    }
    else
    {   // Dans le cas du premier élement dans la liste
        list.mem.data = d;
        list.size = size;
        list.start = start;
        list.nextElm = NULL;
        list.type = type;
    }
}

// Cette fonction doit être synchronisée à 5ms pour fonctionner correctement 
// avec l'EEPROM 24LC256.
void EEPROM_Task(void)
{
    EEPROM_Element* listTmp = &list;
    bool writting = false;
    do
    {
        if(listTmp->mem.change == true)
        {
            if(listTmp->byteToChange < listTmp->size)
            {
#ifdef TABLE_DE_MIX
                unsigned int endPage, size;
                if(listTmp->byteToChange == 0)
                {
                    endPage = 64 - (listTmp->start & 0b111111);
                }
                else
                {
                    endPage = 64;
                }
                size = listTmp->size - listTmp->byteToChange;
                if(size >= endPage)
                {
                    size = endPage;
                }
#endif
                
                if(erase == 0)
                {
#ifdef TABLE_DE_MIX
                    I2C_EEPROM_write(&listTmp->mem.data[listTmp->byteToChange], size, listTmp->start + listTmp->byteToChange);
#else
                    Write_EEPROM(listTmp->mem.data[listTmp->byteToChange], listTmp->start + listTmp->byteToChange);
#endif
                }
                else
                {
#ifdef TABLE_DE_MIX
                    char erase[64]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
                    I2C_EEPROM_write(erase, size, listTmp->start + listTmp->byteToChange);
#else
                     Write_EEPROM(0xFF, listTmp->start + listTmp->byteToChange);
#endif
                }
                writting = true;
#ifdef TABLE_DE_MIX
                listTmp->byteToChange +=size;
#else
                listTmp->byteToChange ++;
#endif
                if(listTmp->byteToChange == listTmp->size)
                {
                    listTmp->mem.change = false;
                    listTmp->byteToChange = 0;
                }
                return;
            }
        }
        listTmp = listTmp->nextElm;
    }while(listTmp != 0 && writting == false);
}

void EEPROM_SaveData_1(char* d)
{
    EEPROM_Element* listTmp = &list;
    do
    {
        if(listTmp->mem.data == d)
        {
            listTmp->mem.change = true;
            return;
        }
        listTmp = listTmp->nextElm;
    }while(listTmp != NULL);
}

bool EEPROM_IsSaved_1(char* d)
{
    EEPROM_Element* listTmp = &list;
    do
    {
        if(listTmp->mem.data == d)
        {
            return !listTmp->mem.change;
        }
        listTmp = listTmp->nextElm;
    }while(listTmp != NULL);
    return false;
}

void EEPROM_SaveAll(void)
{
    EEPROM_Element* listTmp = &list;
    do
    {
        listTmp->mem.change = true;
        listTmp = listTmp->nextElm;
    }while(listTmp != NULL);
}

bool EEPROM_IsAllSaved(void)
{
    EEPROM_Element* listTmp = &list;
    do
    {
        if(listTmp->mem.change == true)
        {
            return false;
        }
        listTmp = listTmp->nextElm;
    }while(listTmp != NULL);
    return true;
}

void EEPROM_EraseAll(void)
{
    EEPROM_Element* listTmp = &list;
    erase = 1;
    do
    {
        listTmp->mem.change = true;
        listTmp = listTmp->nextElm;
    }while(listTmp != NULL);
}

void EEPROM_SaveNow(void)
{
//    char temp[100] = "temp";
//    char temp2[100] = "temp2";
    EEPROM_Element* listTmp = &list;
    do
    {
        if(listTmp->mem.change == true)
        {
            while((listTmp->byteToChange < listTmp->size) && (listTmp->mem.change == true))
            {
                static int mem = 0;
//                memcpy(temp, listTmp->mem.data, listTmp->size);
                Write_EEPROM(listTmp->mem.data[mem], listTmp->start + mem);
                mem++;
                delay_ms(10);
                if(mem == listTmp->size)
                {
                    /*int i;
                    bool writeIsOk = true;
                    for(i = 0; i < listTmp->size; i++)
                    {
                        temp2[i] = Read_EEPROM(listTmp->start + i);
                    }
                    if(listTmp->size > 1)
                    {
                        if(!strcmp(temp2, temp))
                        {
                            listTmp->mem.change = false;
                        }
                        else
                        {
                            WDTCONbits.WDTCLR = 1; //remet a zero le WTDPS a 0
                            listTmp->mem.change = true;
                        }
                    }*/
                    listTmp->byteToChange = 0;
                    mem = 0;
                    listTmp->mem.change = false;
                }
            }
        }
        listTmp = listTmp->nextElm;
    }while(listTmp != 0);
}

bool EEPROM_ReadData_1(unsigned char* d, const unsigned char* def)
{
    EEPROM_Element* listTmp = &list;
    do
    {
        if(listTmp->mem.data == (char*)d)
        {
            int i;
            for(i = 0; i < listTmp->size; i++)
            {
                d[i] = Read_EEPROM(listTmp->start + i);
            }
            switch(listTmp->type)
            {
                case CHAR_TYPE:
                    if(d[0] == 0xFF)
                        d[0] = (int) def;
                break;
                case STRING_TYPE:
                    if(d[0] == 0xFF)
                        strcpy(d, def);
                break;
                case IP_STRING_TYPE:
                    if((d[0] == '0') || (d[0] == 0xFF) || (d[0] == 0x0a))
                        strcpy(d, def);
                break;
                case IP_NUM_TYPE:
                    if((d[0] == 0) || (d[0] == 0xFF))
                        memcpy(d, def, 4);
                break;
                case IP_NUM_MASK_TYPE:
                break;
            }
            return true;
        }
        listTmp = listTmp->nextElm;
    }while(listTmp != NULL);
    return false;
}

void EEPROM_Maintenance_csv_Write(char* msgToAdd)
{
    static unsigned int start = 0, cpt = 0;
    unsigned int j = 0;
    
    if(start == 0)
    {
        start = 1;
        if(list.byteToChange == 0)
        {
            cpt = list.size;
        }
        else
        {
            cpt = list.byteToChange;
        }
    }
    if(EEPROM_IsSaved(EEPROM_MaintenanceCSV) == true)
    {
        list.byteToChange = cpt;
    }
    
    while(msgToAdd[j] != 0)
    {
        int add = ((list.size - list.byteToChange) + (list.start - START_MAINTENANCE_CSV)) + j;
        EEPROM_MaintenanceCSV[cpt++] = msgToAdd[j];
        j++;
    }

    list.size += j;
    
    EEPROM_SaveData(EEPROM_MaintenanceCSV);
}

char* EEPROM_Maintenance_csv_Read(void)
{
    return EEPROM_MaintenanceCSV;
}

void EEPROM_Maintenance_csv_Reset(void)
{
    int i;
    list.start = START_MAINTENANCE_CSV;
    list.size = 30000 - START_MAINTENANCE_CSV;
    for(i = 0; i < list.size; i++)
    {
        EEPROM_MaintenanceCSV[i] = 0;
    }
    EEPROM_SaveData(EEPROM_MaintenanceCSV);
}
/* *****************************************************************************
 End of File
 */
