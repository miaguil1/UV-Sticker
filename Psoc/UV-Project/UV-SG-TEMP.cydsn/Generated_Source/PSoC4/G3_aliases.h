/*******************************************************************************
* File Name: G3.h  
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

#if !defined(CY_PINS_G3_ALIASES_H) /* Pins G3_ALIASES_H */
#define CY_PINS_G3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define G3_0			(G3__0__PC)
#define G3_0_PS		(G3__0__PS)
#define G3_0_PC		(G3__0__PC)
#define G3_0_DR		(G3__0__DR)
#define G3_0_SHIFT	(G3__0__SHIFT)
#define G3_0_INTR	((uint16)((uint16)0x0003u << (G3__0__SHIFT*2u)))

#define G3_INTR_ALL	 ((uint16)(G3_0_INTR))


#endif /* End Pins G3_ALIASES_H */


/* [] END OF FILE */
