/*******************************************************************************
* File Name: A_GND_REF.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_A_GND_REF_ALIASES_H) /* Pins A_GND_REF_ALIASES_H */
#define CY_PINS_A_GND_REF_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define A_GND_REF_0			(A_GND_REF__0__PC)
#define A_GND_REF_0_PS		(A_GND_REF__0__PS)
#define A_GND_REF_0_PC		(A_GND_REF__0__PC)
#define A_GND_REF_0_DR		(A_GND_REF__0__DR)
#define A_GND_REF_0_SHIFT	(A_GND_REF__0__SHIFT)
#define A_GND_REF_0_INTR	((uint16)((uint16)0x0003u << (A_GND_REF__0__SHIFT*2u)))

#define A_GND_REF_INTR_ALL	 ((uint16)(A_GND_REF_0_INTR))


#endif /* End Pins A_GND_REF_ALIASES_H */


/* [] END OF FILE */
