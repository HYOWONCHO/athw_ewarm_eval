#ifndef _TPM_TYPES_H
#define _TPM_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

#include "athw_errno.h"
#include "x_log.h"
#include "x_typedef.h"

//#define _IFPACKED				(__attribute__((packed)))

#ifndef bool
typedef uint8_t    bool;
#endif

#ifndef true
#define true   (1==1)
#endif

#ifndef false
#define false   (!true)
#endif

#define min_t(type, x, y) ({            \
    type __min1 = (x);          \
    type __min2 = (y);          \
    __min1 < __min2 ? __min1: __min2; })

#define max_t(type, x, y) ({            \
    type __max1 = (x);          \
    type __max2 = (y);          \
    __max1 > __max2 ? __max1: __max2; })


#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#define BIT(nr)         (1 << (nr))

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#define SPI_XFER_BEGIN      BIT(0)  /* Assert CS before transfer */
#define SPI_XFER_END        BIT(1)  /* Deassert CS after transfer */
#define SPI_XFER_ONCE       (SPI_XFER_BEGIN | SPI_XFER_END)

#define MAX_SPI_BYTES              32

#pragma pack(1)
typedef struct  _io_tlv_t {
	void *tx;			/*! Transfer buffer pointer*/
	int txlen;			/*! Length of Transfer */
	void *rx;			/*! Receive buffer pointer */
	int *rxlen;			/*! Length of Receive */
}io_tlv_t;

typedef  struct  _spi_ioctx_t {
	void *h_ctx;		/*! Device handle*/
	void *h_io;			/*! IO device handle (like UART, I2C and SPI) */
	io_tlv_t ioctx;		/*! Data exchange structure*/
}spi_ioctx_t;
#pragma pack()


#ifdef __cplusplus
}
#endif

#endif
