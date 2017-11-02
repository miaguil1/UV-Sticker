/*******************************************************************************
* File Name: GAIN_REF.h  
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

#if !defined(CY_PINS_GAIN_REF_ALIASES_H) /* Pins GAIN_REF_ALIASES_H */
#define CY_PINS_GAIN_REF_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GAIN_REF_0			(GAIN_REF__0__PC)
#define GAIN_REF_0_PS		(GAIN_REF__0__PS)
#define GAIN_REF_0_PC		(GAIN_REF__0__PC)
#define GAIN_REF_0_DR		(GAIN_REF__0__DR)
#define GAIN_REF_0_SHIFT	(GAIN_REF__0__SHIFT)
#define GAIN_REF_0_INTR	((uint16)((uint16)0x0003u << (GAIN_REF__0__SHIFT*2u)))

#define GAIN_REF_INTR_ALL	 ((uint16)(GAIN_REF_0_INTR))


#endif /* End Pins GAIN_REF_ALIASES_H */


/* [] END OF FILE */
