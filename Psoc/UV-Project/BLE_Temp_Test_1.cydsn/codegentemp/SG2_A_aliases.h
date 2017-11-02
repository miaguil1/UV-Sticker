/*******************************************************************************
* File Name: SG2_A.h  
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

#if !defined(CY_PINS_SG2_A_ALIASES_H) /* Pins SG2_A_ALIASES_H */
#define CY_PINS_SG2_A_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SG2_A_0			(SG2_A__0__PC)
#define SG2_A_0_PS		(SG2_A__0__PS)
#define SG2_A_0_PC		(SG2_A__0__PC)
#define SG2_A_0_DR		(SG2_A__0__DR)
#define SG2_A_0_SHIFT	(SG2_A__0__SHIFT)
#define SG2_A_0_INTR	((uint16)((uint16)0x0003u << (SG2_A__0__SHIFT*2u)))

#define SG2_A_INTR_ALL	 ((uint16)(SG2_A_0_INTR))


#endif /* End Pins SG2_A_ALIASES_H */


/* [] END OF FILE */
