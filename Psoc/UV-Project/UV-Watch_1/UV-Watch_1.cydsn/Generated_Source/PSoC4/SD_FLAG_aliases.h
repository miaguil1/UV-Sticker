/*******************************************************************************
* File Name: SD_FLAG.h  
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

#if !defined(CY_PINS_SD_FLAG_ALIASES_H) /* Pins SD_FLAG_ALIASES_H */
#define CY_PINS_SD_FLAG_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SD_FLAG_0			(SD_FLAG__0__PC)
#define SD_FLAG_0_PS		(SD_FLAG__0__PS)
#define SD_FLAG_0_PC		(SD_FLAG__0__PC)
#define SD_FLAG_0_DR		(SD_FLAG__0__DR)
#define SD_FLAG_0_SHIFT	(SD_FLAG__0__SHIFT)
#define SD_FLAG_0_INTR	((uint16)((uint16)0x0003u << (SD_FLAG__0__SHIFT*2u)))

#define SD_FLAG_INTR_ALL	 ((uint16)(SD_FLAG_0_INTR))


#endif /* End Pins SD_FLAG_ALIASES_H */


/* [] END OF FILE */
