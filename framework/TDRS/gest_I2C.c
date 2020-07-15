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
#include "gest_I2C.h"

static I2C_Element I2C_elem;

bool I2C_IsOnBus(I2C_Element* elem);

__inline void I2C_Start(void)
{
    I2C_elem.nextElm = (I2C_Element*) 1;
}

I2C_STATUS I2C_New(I2C_MODULE_ID mod, unsigned int freq, unsigned int add, unsigned int id)
{
    if(I2C_elem.nextElm == (I2C_Element*) 1)
    {
        I2C_elem.id = id;
        I2C_elem.add = add;
        I2C_elem.freq = freq;
        I2C_elem.mod_Id = mod;
        if(I2C_IsOnBus(&I2C_elem))
        {
            I2C_elem.nextElm = 0;
            I2C_elem.isOnBus = true;
        }
        else
        {
            I2C_elem.isOnBus = false;
            return I2C_NO_RESPONSE;
        }
    }
    else
    {
        I2C_Element* I2C_elemTmp = &I2C_elem;
        while(I2C_elemTmp->nextElm != 0)
        {
            if(I2C_elemTmp->mod_Id == mod && I2C_elemTmp->add == add)
            {
                return I2C_ADD_CONFLIT;
            }
            if(I2C_elemTmp->id == id)
            {
                return I2C_ID_CONFLIT;
            }
            I2C_elemTmp = I2C_elemTmp->nextElm;
        }
        I2C_Element* nElem = malloc(sizeof(I2C_Element));
        nElem->add = add;
        nElem->freq = freq;
        nElem->mod_Id = mod;
        I2C_elemTmp->nextElm = nElem;
        if(!I2C_IsOnBus(nElem))
        {
            nElem->isOnBus = false;
            return I2C_NO_RESPONSE;
        }
        else
        {
            nElem->isOnBus = true;
        }
    }
    return I2C_OK;
}

void I2C_Init(I2C_Element* elem)
{
    PLIB_I2C_Disable(elem->mod_Id);
    PLIB_I2C_BaudRateSet(elem->mod_Id,SYS_CLK_SystemFrequencyGet(),elem->freq);
    PLIB_I2C_Enable(elem->mod_Id);
}

bool I2C_IsOnBus(I2C_Element* elem)
{
    I2C_Init(elem);
    PLIB_I2C_MasterStart(elem->mod_Id);
    PLIB_I2C_TransmitterByteSend(elem->mod_Id, elem->add);
    
    while(!PLIB_I2C_TransmitterByteHasCompleted(elem->mod_Id));
    delay_ms(1);
    if(PLIB_I2C_TransmitterByteWasAcknowledged(elem->mod_Id))
    {
        PLIB_I2C_MasterStop(elem->mod_Id);
        return true;
    }
    else
    {
        PLIB_I2C_MasterStop(elem->mod_Id);
        return false;
    }
}
bool I2C_Write(I2C_Element* elem, char msg)
{
    PLIB_I2C_TransmitterByteSend(elem->mod_Id, msg);
    while(!PLIB_I2C_TransmitterByteHasCompleted(elem->mod_Id));
    if(PLIB_I2C_TransmitterByteWasAcknowledged(elem->mod_Id) == true)
    {
        return true;
    }
    else
    {
        elem->isOnBus = false;
        PLIB_I2C_MasterStop(elem->mod_Id);
        return false;
    }
}

bool I2C_Write_n(unsigned int id, char* msg, unsigned int n)
{
    I2C_Element* I2C_elemTmp = &I2C_elem;
    while(I2C_elemTmp != 0)
    {
        if(I2C_elemTmp->id == id)
        {
            if(I2C_elemTmp->isOnBus == false)
            {
                if(I2C_IsOnBus(I2C_elemTmp))
                {
                    I2C_elemTmp->isOnBus = true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                I2C_Init(I2C_elemTmp);
                PLIB_I2C_MasterStart(I2C_elemTmp->mod_Id);
                if(!I2C_Write(I2C_elemTmp, I2C_elemTmp->add)){return false;}
                int i;
                for(i = 0; i < n; i++)
                {
                    if(!I2C_Write(I2C_elemTmp, msg[i])){return false;}
                }
                PLIB_I2C_MasterStop(I2C_elemTmp->mod_Id);
                return true;
            }
        }
        I2C_elemTmp = I2C_elemTmp->nextElm;
    }
    return false;
}

bool I2C_Write_EEPROM(unsigned int id, unsigned int add, char* msg, unsigned int n)
{
    I2C_Element* I2C_elemTmp = &I2C_elem;
    while(I2C_elemTmp != 0)
    {
        if(I2C_elemTmp->id == id)
        {
            if(I2C_elemTmp->isOnBus == false)
            {
                if(I2C_IsOnBus(I2C_elemTmp))
                {
                    I2C_elemTmp->isOnBus = true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                I2C_Init(I2C_elemTmp);
                PLIB_I2C_MasterStart(I2C_elemTmp->mod_Id);
                if(!I2C_Write(I2C_elemTmp, I2C_elemTmp->add)){return false;}
                if(!I2C_Write(I2C_elemTmp, ((add >> 8) & 0xFF))){return false;}
                if(!I2C_Write(I2C_elemTmp, (add & 0xFF))){return false;}
                int i;
                for(i = 0; i < n; i++)
                {
                    if(!I2C_Write(I2C_elemTmp, msg[i])){return false;}
                }
                PLIB_I2C_MasterStop(I2C_elemTmp->mod_Id);
                return true;
            }
        }
        I2C_elemTmp = I2C_elemTmp->nextElm;
    }
    return false;
}
/* *****************************************************************************
 End of File
 */
