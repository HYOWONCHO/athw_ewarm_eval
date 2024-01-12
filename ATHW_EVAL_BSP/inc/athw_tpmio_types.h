#ifndef __ATHW_TPMIO_TYPES_H
#define __ATHW_TPMIO_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "configs.h"

#define MAX_SPI_FRAMESIZE			64

#define HOST_SPI_BANK	 			SPI2
#define HOST_SPI_IO_PORT			GPIOB
#define HOST_SPI_CS_PIN 	 		GPIO_PIN_12
#define HOST_SPI_CLK_PIN			GPIO_PIN_13
#define HOST_SPI_MISO_PIN			GPIO_PIN_14
#define HOST_SPI_MOSI_PIN 			GPIO_PIN_15

#define TPM_SPI_WAIT_RETRY			50
#define TPM_SPI_CS_PORT				GPIOA
#define TPM_SPI_CS_PIN 				GPIO_PIN_4
#define TPM_SPI_TIMEOUT				250

#define TPM_TIS_HEADER_SZ			4
#define TPM_TIS_READ       0x80
#define TPM_TIS_WRITE      0x00
#define TPM_TIS_READY_MASK 0x01

/* Typically only 0-2 wait states are required */
#ifndef TPM_TIS_MAX_WAIT
#define TPM_TIS_MAX_WAIT   3
#endif


#ifdef __cplusplus
}
#endif
#endif
