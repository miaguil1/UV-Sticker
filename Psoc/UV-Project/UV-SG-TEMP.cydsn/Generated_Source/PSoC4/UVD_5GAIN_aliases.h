/*******************************************************************************
* File Name: UVD_5GAIN.h  
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

#if !defined(CY_PINS_UVD_5GAIN_ALIASES_H) /* Pins UVD_5GAIN_ALIASES_H */
#define CY_PINS_UVD_5GAIN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define UVD_5GAIN_0			(UVD_5GAIN__0__PC)
#define UVD_5GAIN_0_PS		(UVD_5GAIN__0__PS)
#define UVD_5GAIN_0_PC		(UVD_5GAIN__0__PC)
#define UVD_5GAIN_0_DR		(UVD_5GAIN__0__DR)
#define UVD_5GAIN_0_SHIFT	(UVD_5GAIN__0__SHIFT)
#define UVD_5GAIN_0_INTR	((uint16)((uint16)0x0003u << (UVD_5GAIN__0__SHIFT*2u)))

#define UVD_5GAIN_INTR_ALL	 ((uint16)(UVD_5GAIN_0_INTR))


#endif /* End Pins UVD_5GAIN_ALIASES_H */


/* [] END OF FILE */
