  
/********************************************************************************
 * Copyright (C) 2020 by Trustkey                                               * 
 * This file is part of  Project                                                *   
 * This software contains confidential information of TrustKey Co.,Ltd.         *
 * and unauthorized distribution of this software, or any portion of it, are    *
 * prohibited.                                                                  *
 ********************************************************************************/

/**
 * @file athw_eval_it.c
 * ATHW Evaluation module interface 
 *
 * @anchor ATHW_EVAL_BSP
 * @author User, (c) Trustkey
 * @version Draft 
 * @date 010924
 * @bug No known bugs.
 * @note 
 * 
 * @copyright Copyright 2020 Trustkey. All rights reserved*
 */         


#include "configs.h"

extern void error_handler(void *priv);


/**
 * @fn athw_system_hal_init - Init the low level hardware
 * 
 * @author User (1/9/2024)
 * 
 * @return int 
 */
static int athw_system_hal_init(void)
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
static void athw_system_clock_config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    // Configure the main internal regulator output voltage
    if(HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
        error_handler();
    }

    // Initializes the RCC Oscillators according to the specified paramters
    osc.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    osc.MSIState = RCC_MSI_ON;
    osc.MSICalibrationValue = 0;
    osc.MSIClockRange = RCC_MSIRANGE_6;
    osc.PLL.PLLState = RCC_PLL_NONE:
    if(HAL_RCC_OscConfig(&osc) != HAL_OK) {
        error_handler();
    }

    // Initialize the CPU, AHB and APB buses clocks
    clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK 
                    | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV2;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&clk, FLASH_LATENCY, 0) != HAL_OK) {
        error_handler();
    }

    return;
}

static void athw_eval_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};


    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_8, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

    /*Configure GPIO pins : PC13 PC11 PC12 */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pin : PA3 */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PA4 PA8 */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_8, GPIO_PIN_SET);

    /*Configure GPIO pin : PB11 */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : PB12 */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

static void athw_eval_uart_init(UART_HandleTypeDef *com)
{  
    com.Instance = COM_UART_PORT;
    com.Init.BaudRate = COM_UART_SPEED;
    com.Init.WordLength = UART_WORDLENGTH_8B;
    com.Init.StopBits = UART_STOPBITS_1;
    com.Init.Parity = UART_PARITY_NONE;
    com.Init.Mode = UART_MODE_TX_RX;
    com.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    com.Init.OverSampling = UART_OVERSAMPLING_16;
    com.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    com.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&com) != HAL_OK)
    {
        error_handler();
    }
    

    // Turn off buffers, so I/O occurs immediately
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

}


/**
 * @fn HAL_SPI_MspInit - SPI MSP Initialization 
 * 
 * @author User (1/9/2024)
 * 
 * @param hi2c   
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef gpio = {0};
    
    if(hspi->Instance == SPI1) {
        // Peripher Clock Enable
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /**
         * SPI1 GPIO Configuration 
         * PA5  ----->  SPI1_SCK 
         * PA6  ----->  SPI1_MISO 
         * PA7  ----->  SPI1_MOSI 
         */

        gpio.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        gpio.Mode = GPIO_MODE_AF_PP;
        gpio.Pull = GPIO_NOPULL; //GPIO_PULLDOWN;
        gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio.Alternate = GPIO_AF5_SPI1;

        HAL_GPIO_Init(GPIOA, &gpio);
    }
    else if(hspi->Instance == SPI2) {
        __HAL_RCC_SPI2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /**
         * SPI2 GPIO Configuration 
         * PB13  -----> SPI2_SCK 
         * PB14  -----> SPI2_MISO 
         * PB15  -----> SPI2_MOSI
         */

        gpio.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
        gpio.Mode = GPIO_MODE_AF_PP;
        gpio.Pull = GPIO_NOPULL; //GPIO_PULLDOWN;
        gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio.Alternate = GPIO_AF5_SPI2;

        HAL_GPIO_Init(GPIOB, &gpio);

    }

}

/**
 * @fn HAL_SPI_MspDeint - De-initalization
 * 
 * @author User (1/9/2024)
 * 
 * @param hspi   - [in] SPI handle address 
 */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef gpio = {0};
    
    if(hspi->Instance == SPI1) {
        // Peripher Clock Enable
        __HAL_RCC_SPI1_CLK_DISABLE();

        /**
         * SPI1 GPIO Configuration 
         * PA5  ----->  SPI1_SCK 
         * PA6  ----->  SPI1_MISO 
         * PA7  ----->  SPI1_MOSI 
         */

        gpio.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        HAL_GPIO_DeInit(GPIOA, gpio.pin);
    }
    else if(hspi->Instance == SPI2) {
        __HAL_RCC_SPI2_CLK_DISABLE();

        /**
         * SPI2 GPIO Configuration 
         * PB13  -----> SPI2_SCK 
         * PB14  -----> SPI2_MISO 
         * PB15  -----> SPI2_MOSI
         */

        gpio.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;

        HAL_GPIO_DeInit(GPIOB, gpio.pin);

    }

}


/**
 * @fn HAL_UART_MspInit - UART MSP Initialization
 * 
 * @author User (1/9/2024)
 * 
 * @param [in]huart  - Uart handle address
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio = {0};
    RCC_PeriphCLKInitTypeDef clk = {0};

    if(huart->Instance = USART1) {
        clk.PeriphClockSelection = RCC_PERIPHCLK_USUART1;
        clk.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
        if(HAL_RCCEx_PeriphCLKConfig(&clk) != HAL_OK) {
            error_handler();
        }

        __HAL_RCC_USUART1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /*
            USUART1 GPIO Configuration
            PB6 -----> UAUART1_TX
            PB7 -----> USUART1_RX
        */

        gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7;
        gpio.Mode = GPIO_MODE_AF_PP;
        gpio.Pull = GPIO_NOPULL;
        gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio.Alternate = GPIO_AF7_USUART1;
        HAL_GPIO_Init(GPIOB, &gpio);
    }

}

/**
 * @fn HAL_UART_MspDeInit - UART MSP De-Initialization
 * 
 * @author User (1/9/2024)
 * 
 * @param [in]huart  - Uart handle address
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio = {0};

    if(huart->Instance = USART1) {
       
        __HAL_RCC_USUART1_CLK_DISABLE();

        /*
            USUART1 GPIO Configuration
            PB6 -----> UAUART1_TX
            PB7 -----> USUART1_RX
        */

        gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7;
        HAL_GPIO_DeInit(GPIOB, gpio.pin);
    }

}


/**
 * @fn int athw_eval_it_init(void *priv)
 * @brief Evaluation Board interface init
 * 
 * @author User (1/9/2024)
 * 
 * @param priv		- [in,out]Interface data structure   
 * 
 * @return On success, rturn EOK, negative on failure 
 */
int athw_eval_it_init(void *priv)
{
    int ret = ERRNGATE(EFAIL);

    // Reset of all perpheral
    athw_system_hal_init();

    // Configure the system clock 
    athw_system_clock_config();





    return ret;
}

