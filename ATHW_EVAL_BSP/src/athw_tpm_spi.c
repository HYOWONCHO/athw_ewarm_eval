/********************************************************************************
 * Copyright (C) 2020 by Trustkey                                               * 
 * This file is part of  Project                                                *   
 * This software contains confidential information of TrustKey Co.,Ltd.         *
 * and unauthorized distribution of this software, or any portion of it, are    *
 * prohibited.                                                                  *
 ********************************************************************************/

/**
 * @file athw_tpm_spi.c
 * TPM SPI interface
 *
 * @anchor ANCHOR_SPI
 * @author User, (c) Trustkey
 * @version Draft 
 * @date 011024
 * @bug No known bugs.
 * @note 
 * 
 * @copyright Copyright 2020 Trustkey. All rights reserved*
 */         

#include "athw_tpmio_types.h"

int athw_tpmiocb_spi(void *spictx) 
{
	int ret = ERRNGATE(EFAIL);
	SPI_HandleTypeDef *ctx = (SPI_HandleTypeDef *)spictx;
	HAL_StatusTypeDef status;

	if(ctx == NULL) {
		ret = ERRNGATE(ESNULLP);
		goto errdone;
	}

	__HAL_SPI_ENABLE(ctx);


	// To SPI start, CS goes active low
	HAL_GPIO_WritePin(TPM_SPI_CS_PORT, TPM_SPI_CS_PIN, GPIO_PIN_RESET);


	// To SPI stop, CS goes active high
	HAL_GPIO_WritePin(TPM_SPI_CS_PORT, TPM_SPI_CS_PIN, GPIO_PIN_SET);


errdone:

	return ret;

}





