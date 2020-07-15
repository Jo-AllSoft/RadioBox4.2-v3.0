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

#ifndef _GEST_UPLOAD_H    /* Guard against multiple inclusion */
#define _GEST_UPLOAD_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

void uploadAndSave(char* csv);
void createBackup(void);
void BCKUP_Popup(char* msg);
bool BCKUP_Ready(void);
#endif /* _GEST_UPLOAD_H */

/* *****************************************************************************
 End of File
 */
