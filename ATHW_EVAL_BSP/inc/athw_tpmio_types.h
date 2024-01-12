#ifndef __ATHW_TPMIO_TYPES_H
#define __ATHW_TPMIO_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "configs.h"

#define MAX_SPI_FRAMESIZE			64


#define TPM_SPI_WAIT_RETRY			50
#define TPM_SPI_CS_PORT				GPIOA
#define TPM_SPI_CS_PIN 				GPIO_PIN_4

#ifdef __cplusplus
}
#endif
#endif
