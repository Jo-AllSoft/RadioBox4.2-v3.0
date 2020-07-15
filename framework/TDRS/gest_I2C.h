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

#ifndef _GEST_I2C_H_    /* Guard against multiple inclusion */
#define _GEST_I2C_H_

#include "app.h"
#include "../peripheral/i2c/plib_i2c.h"

typedef enum {I2C_OK, I2C_ADD_CONFLIT, I2C_ID_CONFLIT, I2C_NO_RESPONSE}I2C_STATUS;

typedef struct I2C_Element I2C_Element;
struct I2C_Element
{
    unsigned int id;
    unsigned int freq;
    unsigned int add;
    I2C_MODULE_ID mod_Id;
    bool isOnBus;
    I2C_Element* nextElm;
};

void I2C_Start(void);
I2C_STATUS I2C_New(I2C_MODULE_ID mod, unsigned int freq, unsigned int add, unsigned int id);

#endif /* _GEST_I2C_H_ */

/* *****************************************************************************
 End of File
 */
