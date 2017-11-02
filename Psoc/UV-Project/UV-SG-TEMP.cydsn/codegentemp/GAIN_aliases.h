/*******************************************************************************
* File Name: GAIN.h  
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

#if !defined(CY_PINS_GAIN_ALIASES_H) /* Pins GAIN_ALIASES_H */
#define CY_PINS_GAIN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GAIN_0			(GAIN__0__PC)
#define GAIN_0_PS		(GAIN__0__PS)
#define GAIN_0_PC		(GAIN__0__PC)
#define GAIN_0_DR		(GAIN__0__DR)
#define GAIN_0_SHIFT	(GAIN__0__SHIFT)
#define GAIN_0_INTR	((uint16)((uint16)0x0003u << (GAIN__0__SHIFT*2u)))

#define GAIN_INTR_ALL	 ((uint16)(GAIN_0_INTR))


#endif /* End Pins GAIN_ALIASES_H */


/* [] END OF FILE */
