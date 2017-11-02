/*******************************************************************************
* File Name: h1.h  
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

#if !defined(CY_PINS_h1_ALIASES_H) /* Pins h1_ALIASES_H */
#define CY_PINS_h1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define h1_0			(h1__0__PC)
#define h1_0_PS		(h1__0__PS)
#define h1_0_PC		(h1__0__PC)
#define h1_0_DR		(h1__0__DR)
#define h1_0_SHIFT	(h1__0__SHIFT)
#define h1_0_INTR	((uint16)((uint16)0x0003u << (h1__0__SHIFT*2u)))

#define h1_INTR_ALL	 ((uint16)(h1_0_INTR))


#endif /* End Pins h1_ALIASES_H */


/* [] END OF FILE */
