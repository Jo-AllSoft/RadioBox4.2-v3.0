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

#ifndef _GEST_PC_MUX_PIC_H    /* Guard against multiple inclusion */
#define _GEST_PC_MUX_PIC_H

#ifdef PIC_AMPLI
    #define PIC_RESET_TIME 30
#else
    #define PIC_RESET_TIME 20
#endif
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#ifdef PIC_RF

#define PC_PULSE_ON_TIME 40     // 2 secondes pour être sûr de l'extinction complète
#define PC_PULSE_OFF_TIME 400   // 20 secondes pour être sûr de l'extinction complète
#define MUX_WAITING_CHANGE 2400

void statementTask(void);

void PC_Restart(void);
void PC_Shutdown(void);
void PC_Boot(void);
bool PC_IsOk(void);

void MUX_ChangeBouquet(void);
bool MUX_IsOn(void);
#endif
void PIC_reset(void);
void PIC_ForceReset(void);
char* createTime(char* msg, bool forCSV);
#endif /* _GEST_PC_MUX_PIC_H */

/* *****************************************************************************
 End of File
 */
