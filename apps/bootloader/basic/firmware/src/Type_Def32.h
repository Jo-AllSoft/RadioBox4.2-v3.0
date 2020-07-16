//----------------------------------------------------------
//  Type_Def32.h
//----------------------------------------------------------

// ETML Ecole Sup�rieure
// D�finitions des types de donn�es    						  
// Cr�ation 18.04.2002 CHR   V 1.0    						  
// Adaptation XC32 16.05.2013 CHR
// Modifications :
//      26.05.2014 C. Huber ajout du type byte
//
// Le fichier Type_Def32.h est � copier dans chaque projet et
// est � inclure dans chaque module 

#ifndef TYPE_DEF32_H
#define TYPE_DEF32_H

// definitions pour XC32

//typedef int1 bool;				// 1 bit flag

typedef signed char sint8;		// 8 bits sign�
typedef unsigned char uint8;				// 8 bits non sign�
typedef unsigned char byte;             // pour compatibilit� avec certains projets PIC18

typedef signed short sint16;	// 16 bits sign�
typedef unsigned short uint16;			// 16 bits non sign�

typedef signed int sint32;	// 32 bits sign�
typedef unsigned int uint32;			// 32 bits non sign�

#endif
