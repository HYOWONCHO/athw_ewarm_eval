/********************************************************************************
 * Copyright (C) 2020 by Trustkey                                               * 
 * This file is part of  Project                                                *   
 * This software contains confidential information of TrustKey Co.,Ltd.         *
 * and unauthorized distribution of this software, or any portion of it, are    *
 * prohibited.                                                                  *
 ********************************************************************************/

/**
 * @file athw_pkt_process.c
 * Packet processing and accumulation
 *
 * @anchor ATHW SYSTEM
 * @author rocke, (c) Trustkey
 * @version Draft 
 * @date 012924
 * @bug No known bugs.
 * @note 
 * 
 * @copyright Copyright 2020 Trustkey. All rights reserved*
 */         

#include "main.h"
#include "configs.h"

static TIM_HandleTypeDef TimHandle;


#define ATHW_PKT_ROCESS_TIM_COUNT_CLK				1000000U  /*! 1MHz */




//void TIM7_IRQHandler(void)
//{
//	//HAL_TIM_IRQHandler(&h_host_tm);
//	//__HAL_TIM_DISABLE_IT(&h_host_tm, TIM_IT_UPDATE);
//
//	if(__HAL_TIM_GET_FLAG(&h_host_tm, TIM_FLAG_UPDATE) != RESET) {
//		if(__HAL_TIM_GET_IT_SOURCE(&h_host_tm, TIM_IT_UPDATE) != RESET) {
//			__HAL_TIM_CLEAR_IT(&h_host_tm, TIM_IT_UPDATE);
//			printf("TIM7 IRQ !!! \r\n");
//		}
//	}
//
//
//	//__HAL_TIM_ENABLE_IT(&h_host_tm, TIM_IT_UPDATE);
//}

static void _pkt_proc_suspend_tick(void) 
{
	__HAL_TIM_DISABLE_IT(&TimHandle, TIM_IT_UPDATE); 
}

static void _pkt_proc_resume_tick(void) {
	__HAL_TIM_ENABLE_IT(&TimHandle, TIM_IT_UPDATE);
}

static int _pkt_proc_tim_init(void) 
{
#if 1
	RCC_ClkInitTypeDef    clkconfig;
	uint32_t              uwTimclock, uwAPB1Prescaler = 0U;
	uint32_t              uwPrescalerValue = 0U;
	uint32_t              pFLatency;

	/* Configure the TIM6 IRQ priority */
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 3, 0U);

	/* Enable the TIM6 global Interrupt */
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	/* Enable TIM6 clock */
	__HAL_RCC_TIM3_CLK_ENABLE();

	/* Get clock configuration */
	HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

	/* Get APB1 prescaler */
	uwAPB1Prescaler = clkconfig.APB1CLKDivider;

	/* Compute TIM6 clock */
	if(uwAPB1Prescaler == RCC_HCLK_DIV1) {
		uwTimclock = HAL_RCC_GetPCLK1Freq();
	} else {
		uwTimclock = 2 * HAL_RCC_GetPCLK1Freq();
	}

	/* Compute the prescaler value to have TIM6 counter clock equal to 1MHz */
	//uwPrescalerValue = (uint32_t)((uwTimclock / 1000000U)- 1U);
	uwPrescalerValue = (uint32_t)((SystemCoreClock  / 1000) - 1U);   // 1000HZ

	/* Initialize TIM6 */
	TimHandle.Instance = TIM3;

	/* Initialize TIMx peripheral as follow:
	+ Period = [(TIM6CLK/1000) - 1]. to have a (1/1000) s time base.
	+ Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
	+ ClockDivision = 0
	+ Counter direction = Up
	*/
	TimHandle.Init.Period = 3000 - 1;
	TimHandle.Init.Prescaler = uwPrescalerValue;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	 TimHandle.Init.RepetitionCounter = 0;
	//TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if(HAL_TIM_Base_Init(&TimHandle) == HAL_OK) {
		/* Start the TIM time Base generation in interrupt mode */
		return HAL_TIM_Base_Start_IT(&TimHandle);
	}

	/* Return function status */
	return HAL_ERROR; 
#else
	int ret = EOK;

	RCC_ClkInitTypeDef	clkconfig;

	uint32_t pf_latency;
	uint32_t apbclkpres;
	uint32_t timeclock;
	uint32_t prscval; 

	HAL_NVIC_EnableIRQ(PKT_TIM_IRQn); 

	// Enable TIM clock
	PKT_TIM_CLK_ENABLE;
    
    
	HAL_RCC_GetClockConfig(&clkconfig, &pf_latency);
	apbclkpres = clkconfig.APB1CLKDivider;
	printf("APB1 Clock Divider value : %d \r\n", apbclkpres);

	if(apbclkpres == RCC_HCLK_DIV1) {
		timeclock = HAL_RCC_GetPCLK1Freq();
	} else {
		timeclock = 2U * HAL_RCC_GetPCLK1Freq();
	}


	prscval = (uint32_t)((timeclock / ATHW_PKT_ROCESS_TIM_COUNT_CLK) - 1U);

	printf("TIM7 clock : %d  and Prescaler value : %d \r\n", timeclock, prscval);
	/*
	   Initialize TIMx peripheral as follows:
		+ Period = [(TIMx LK/1000) - 1]. to have a (1/1000)s (1ms) time base.
		+ Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
		+ ClockDivision = 0
		+ Counter direction = Up
	*/
	h_host_tm.Instance 						= PKT_TIMx;

	h_host_tm.Init.Period					= 1000000U - 1;//(ATHW_PKT_ROCESS_TIM_COUNT_CLK / 1000)-1U; // ATHW_PKT_ROCESS_TIM_COUNT_CLK - 1;
	h_host_tm.Init.Prescaler				= prscval;
	h_host_tm.Init.ClockDivision 			= 0;
	h_host_tm.Init.CounterMode 				= TIM_COUNTERMODE_UP;
	//h_host_tm.Init.RepetitionCounter 		= 0;
	h_host_tm.Init.AutoReloadPreload 		= TIM_AUTORELOAD_PRELOAD_DISABLE;

	if(HAL_TIM_Base_Init(&h_host_tm) != HAL_OK) {
		ret = ERRNGATE(EIOFAIL);
		goto errdone;
	}

	if(HAL_TIM_Base_Start_IT(&h_host_tm) != HAL_OK) {
		ret = ERRNGATE(EIOFAIL);
		goto errdone;
	}

	
	
errdone:

	return ret;
#endif
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) 
{
	printf("TIM7 IRQ !!! \r\n"); 
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void) {
	HAL_TIM_IRQHandler(&TimHandle);
}



/**
 * @fn int athw_pkt_proc_init(void) - Host pacet process module
 *     initialization
 * 
 * @author rocke (2024-01-29)
 * 
 * @return int On success, return the EOK, on error, return the
 *  	   nv.
 */
int athw_pkt_proc_init(void) 
{
	int ret = EOK;

	// Compute the prescaler value
	 // = (uint32_t)((SystemCoreClock / ATHW_PKT_ROCESS_TIM_COUNT_CLK) - 1);
	//x_memzero(&h_host_tm, sizeof h_host_tm);


	if((uint32_t)uwTickFreq) {
		_pkt_proc_tim_init();
	}

	






errdone:

	return ret;

}

void* athw_pkt_proc_tim_handle(void *priv) 
{
	return (void *)&TimHandle;
}

