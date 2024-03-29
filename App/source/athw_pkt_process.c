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
#include "athw_it_types.h"

spi_ioctx_t host_spictx;
uint8_t spi_rx_end;
int rxcnt; 
uint8_t rxbuf[64];
uint8_t is_timbegin;


static TIM_HandleTypeDef TimHandle;


#define ATHW_PKT_ROCESS_TIM_COUNT_CLK				1000000U  /*! 1MHz */


//static uint32_t gn_stoptick;

void _pkt_proc_suspend_tick(void) 
{
	__HAL_TIM_DISABLE_IT(&TimHandle, TIM_IT_UPDATE); 
	__HAL_TIM_DISABLE(&TimHandle);

	//HAL_TIM_Base_Stop_IT(&TimHandle);
	
	

}

void _pkt_proc_resume_tick(void) 
{
	__HAL_TIM_ENABLE_IT(&TimHandle, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(&TimHandle);

	//HAL_TIM_Base_Start_IT(&TimHandle);
	
}

static int _pkt_proc_tim_init(void) 
{

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
	uwPrescalerValue = (uint32_t)((uwTimclock  / 1000) - 1U);   // 1000HZ

	/* Initialize TIM6 */
	TimHandle.Instance = TIM3;

	/* Initialize TIMx peripheral as follow:
	+ Period = [(TIM6CLK/1000) - 1]. to have a (1/1000) s time base.
	+ Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
	+ ClockDivision = 0
	+ Counter direction =
	+	To get TIM3 counter clock at 10 KHz, the Prescaler is computed as following:
		Prescaler = (TIM3CLK / TIM3 counter clock) - 1
		Prescaler = (SystemCoreClock /10 KHz) - 1
	+ Update rate = TIM3 counter clock / (Period + 1) = 1 Hz,
	*/
	TimHandle.Init.Period = 3000 - 1; // 3sec
	TimHandle.Init.Prescaler = uwPrescalerValue;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;
	//TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK) {
		/* Start the TIM time Base generation in interrupt mode */
		return -1;
	}

	rxcnt = 0;
	spi_rx_end = 0;
	is_timbegin = 0;
	HAL_TIM_Base_Start_IT(&TimHandle);

	delay_ms(100);
	// Timer update interrupt disable
	_pkt_proc_suspend_tick();

	/* Return function status */
	return -1; 

}

static int timer_began = 0;
extern int athw_tpm2io_spi(void *priv);

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

	//printf("TIM7 IRQ !!! \r\n"); 
	//spi_rx_end = 1;

	//if(timer_began != 0) {
	HAL_TIM_Base_Stop_IT(htim);

	if(rxcnt > 0) {

		tpmio_ctx_t ctx;



		// Wake up the packet processing module
		//	if(rxcnt > 4) {
		_x_print_bin("Incoming", rxbuf, rxcnt);
		rxcnt = 0;
		is_timbegin = 0;

		athw_tpm2io_spi();
	}


//	}
//	else {
//		timer_began = 1;
//	}
//	}
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
int athw_pkt_proc_init(void *priv) 
{
	int ret = EOK;

	x_memzero((void *)&host_spictx, sizeof host_spictx);

	host_spictx.h_ctx = NULL;
	host_spictx.h_io = (void *)(((athw_if_handle_t *)priv)->h_hostspi);
	host_spictx.iobuf.tx = calloc(64, 1);
	host_spictx.iobuf.rx = calloc(64, 1);
	host_spictx.iobuf.rxlen = 0;
	host_spictx.iobuf.txlen = 0;
	host_spictx.state = 0;

	if(host_spictx.iobuf.tx == NULL || host_spictx.iobuf.rx == NULL) {
		printf("iobuf gen fail tx: %p, rx : %p \r\n",
			   host_spictx.iobuf.tx, host_spictx.iobuf.rx);
		ret  = ERRNGATE(ESNULLP);
		goto errdone;
	}


	// Compute the prescaler value
	 // = (uint32_t)((SystemCoreClock / ATHW_PKT_ROCESS_TIM_COUNT_CLK) - 1);
	//x_memzero(&h_host_tm, sizeof h_host_tm);


	if((uint32_t)uwTickFreq) {
		_pkt_proc_tim_init();
	}

//	if((ret = HAL_SPI_Receive_IT((SPI_HandleTypeDef *)host_spictx.h_io,
//						  host_spictx.iobuf.rx,
//						  1)) != HAL_OK) {
//		ret = ERRNGATE(EFAIL);
//		goto errdone;
//	}


errdone:

	return ret;

}

void* athw_pkt_proc_tim_handle(void *priv) 
{
	return (void *)&TimHandle;
}

/**
 * @fn athw_pkt_incoming
 * 
 * @author rocke (2024-02-06)
 * 
 * @param priv   
 * 
 * @return int 
 */
int athw_pkt_incoming(void *priv) 
{
	UNUSED(priv); // Not yet used 

	int ret = EOK;
	//__HAL_LOCK()
	switch(host_spictx.state) {
	case ATHW_IFCB_PROCEDURE_TYPE_RX:
		host_spictx.iobuf.rxlen += 1;
		break;
	case ATHW_IFCB_PROCEDURE_TYPE_TX:
		host_spictx.iobuf.txlen += 1; 
		break;
	case ATHW_IFCB_PROCEDURE_TYPE_RXTX:
		host_spictx.iobuf.txlen += 1; 
		host_spictx.iobuf.rxlen += 1; 
		break;
	default:
		goto errdone;
	}
	
errdone:
	_pkt_proc_resume_tick(); 
	
	return ret;
}

