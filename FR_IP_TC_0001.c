/**
*   Copyright 2019 NXP
*
*   @file    FR_IP_TC_0001.c
*   @brief   Verify Flexray_Ip_Init function initialize normally with default configuration
*   @details Verify Flexray_Ip_Init function initialize normally with default configuration
*   @addtogroup [FLEXRAY_TESTS]
*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "FR_IP_TC_0001.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/**
* @test_id        FR_IP_TC_0001
* @brief          Verify Flexray_Ip_Init function initialize normally with default configuration
* @details        Verify Flexray_Ip_Init function initialize normally with default configuration
* @pre            N/A
* @post           N/A
* @test_level     Component Validation
* @test_type      Functional
* @test_technique BlackBox
* @test_procedure Steps:
*                    -# Declare local test variables
*                    -# Get Default configuration
*                    -# Initialize module
*                    -# Verification Point: return FLEXRAY_STATUS_SUCCESS
*                    -# De-Initialize module
* @pass_criteria  Verification Points are successful
* @requirements   FLEXRAY_IP_034_001, FLEXRAY_IP_034_002, FLEXRAY_IP_034_013, FLEXRAY_IP_049_001, FLEXRAY_IP_049_002
* @traceability   N/A
* @execution_type Automated
* @hw_depend      MAF
* @sw_depend      N/A
* @boundary_test  N/A
* @defects        N/A
* @test_priority  High
* @note           N/A
* @keywords       Flexray_Ip_GetDefaultConfig
*/
void FR_IP_TC_0001(void)
{
    /* Declare local test variables */
    volatile Flexray_Ip_StatusType retStatus;

    /* Get Default configuration */ 
    Flexray_Ip_GetDefaultConfig(&fr_userCfg0);

    /* Initialize module */
    retStatus = Flexray_Ip_Init(FLEXRAY_INST_0,
                                 &fr_userCfg0,
                                 &stateAlloc0);

    /* Verification Point: return FLEXRAY_STATUS_SUCCESS */
    EU_ASSERT(FLEXRAY_STATUS_SUCCESS == retStatus);

    /* De-Initialize module */
    retStatus = Flexray_Ip_Deinit(FLEXRAY_INST_0);

    EU_ASSERT(FLEXRAY_STATUS_SUCCESS == retStatus);
}


#ifdef __cplusplus
}
#endif

/** @} */
