#ifndef __CONFIGS_H
#define __CONFIGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"

#define ATHW_SYSTEM_VERSION_MAJOR	0x01 	/*! [31:24] major */
#define ATHW_SYSTEM_VERSION_MINOR	0x00	/*! [23:16] minor*/
#define ATHW_SYSTEM_VERSION_BUILD	0x00	/*! [15:8] builid */
#define ATHW_SYSTEM_VERSION_RC		0x00	/*!	[7:0] release condidate */
#define ATHW_SYSTEM_VERSION 		((ATHW_SYSTEM_VERSION_MAJOR << 24)\
									|(ATHW_SYSTEM_VERSION_MINOR << 16)\
									|(ATHW_SYSTEM_VERSION_BUILD << 8)\
									|(ATHW_SYSTEM_VERSION_RC))


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
