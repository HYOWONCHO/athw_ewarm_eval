#ifndef __CONFIGS_H
#define __CONFIGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"

#define ATHW_SYSTEM_MAJOR	0
#define ATHW_SYSTEM_MINOR	0
#define ATHW_SYSTEM_BUILD	101

#define TPM_SPI_PORT		SPI1
#define TPM_SPI_MODE		SPI_MODE_MASTER

#define HOST_SPI_PORT		SPI2
#define HOST_SPI_MODE		SPI_MODE_SLAVE

#define COM_UART_PORT		USART1
#define COM_UART_SPEED		(115200)


#ifdef __cplusplus
}
#endif



#endif
