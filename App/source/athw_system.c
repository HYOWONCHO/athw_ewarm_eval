/********************************************************************************
 * Copyright (C) 2020 by Trustkey                                               * 
 * This file is part of  Project                                                *   
 * This software contains confidential information of TrustKey Co.,Ltd.         *
 * and unauthorized distribution of this software, or any portion of it, are    *
 * prohibited.                                                                  *
 ********************************************************************************/

/**
 * @file system_config.c
 * ATHW System configuration and initialize
 *
 * @anchor ANCHOR_SYSTEM
 * @author User, (c) Trustkey
 * @version Draft 
 * @date 011024
 * @bug No known bugs.
 * @note 
 * 
 * @copyright Copyright 2020 Trustkey. All rights reserved*
 */         



#include "main.h"
#include "stm32l4xx.h"
extern void error_handler(void *priv);


/**
 * @fn athw_system_hal_init - Init the low level hardware
 * 
 * @author User (1/9/2024)
 * 
 * @return int 
 */
int athw_system_hal_init(void)
{
    int ret = EOK;
    HAL_Init();

    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    return ret;
}

/**
 * @fn athw_system_clock_config 
 * @brief System clock configuration 
 * 
 * @author User (1/9/2024)
 * 
 * @retval None
 */
void athw_system_clock_config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    // Configure the main internal regulator output voltage
    if(HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
        error_handler(NULL);
    }

    // Initializes the RCC Oscillators according to the specified paramters
    osc.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    osc.MSIState = RCC_MSI_ON;
    osc.MSICalibrationValue = 0;
    osc.MSIClockRange = RCC_MSIRANGE_6;
    osc.PLL.PLLState = RCC_PLL_NONE;
    if(HAL_RCC_OscConfig(&osc) != HAL_OK) {
        error_handler(NULL);
    }

    // Initialize the CPU, AHB and APB buses clocks
    clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK 
                    | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV2;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0) != HAL_OK) {
        error_handler(NULL);
    }

    return;
}


