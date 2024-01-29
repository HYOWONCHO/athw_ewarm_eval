/********************************************************************************
 * Copyright (C) 2020 by Trustkey                                               * 
 * This file is part of  Project                                                *   
 * This software contains confidential information of TrustKey Co.,Ltd.         *
 * and unauthorized distribution of this software, or any portion of it, are    *
 * prohibited.                                                                  *
 ********************************************************************************/

/**
 * @file athw_host_spi.c
 * HOST command processing
 *
 * @anchor ANCHOR_SPI
 * @author User, (c) Trustkey
 * @version Draft 
 * @date 011224
 * @bug No known bugs.
 * @note 
 * 
 * @copyright Copyright 2020 Trustkey. All rights reserved*
 */         

#include "configs.h"


/**
 * SPI TX/RX complete IRQ callback 
 * 
 * @author rocke (2024-01-26)
 * 
 * @param hspi   SPI Handle
 */
void HAL_SPI_RxCpltCallBack(SPI_HandleTypeDef *hspi) 
{

}

/**
 * @brief SPI error callback
 * 
 * @author rocke (2024-01-26)
 * 
 * @param hspi    SPI Handle
 */
void HAL_SPI_ErrorCallBack(SPI_HandleTypeDef *hspi)
{

}


