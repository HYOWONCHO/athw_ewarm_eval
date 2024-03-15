#include "x_common.h"
#include "configs.h"
//#include "athw_errno.h"


static int _athw_tpm2io_ctx_param_check(tpmio_ctx_t *h) 
{
	int ret = EOK;
	X_ASSERT_PARAM((h != NULL), ERRNGATE(ESNULLP)); 
	X_ASSERT_PARAM((h->handle != NULL), ERRNGATE(ESNULLP));
	X_ASSERT_PARAM((h->txlv != NULL), ERRNGATE(ESNULLP));
	//X_ASSERT_PARAM((h->rxlv != NULL), ERRNGATE(ESNULLP));

	X_ASSERT_PARAM((h->txlv->value != NULL), ERRNGATE(ESNULLP));
	X_ASSERT_PARAM((h->txlv->len > 0), ERRNGATE(ESZEROL));

	if(h->rxlv != NULL) {
		X_ASSERT_PARAM((h->rxlv->value != NULL), ERRNGATE(ESNULLP));
		X_ASSERT_PARAM((h->rxlv->len > 0), ERRNGATE(ESZEROL));
	}

	return ret;

}

/**
 * @fn athw_tpm2io_spi - TPM command send and receive
 * 
 * @author hyowon.cho (2024-03-14)
 * 
 * @param [in,out]priv   TPM Input/Output context handle 
 * 
 * @return On success, return EOK, otherwise return ne 
 */
static int _athw_tpm2io_spi(void *priv) 
{
	int ret = EOK;
	tpmio_ctx_t *ctx = NULL;
#ifdef _ATHW_STM32_TPM_
	SPI_HandleTypeDef *handle; // = (SPI_HandleTypeDef *)ctx->handle;
	HAL_StatusTypeDef status = HAL_OK;
#else
#error "Unsupport Device, Please check the Device Define"
	//void *handle; // = ctx->handle;
	//uint32_t status = 0UL;
#endif

	int timeout = 
	
	ctx = (tpmio_ctx_t *)priv;

	ret = _athw_tpm2io_ctx_param_check(priv)
	if(ret != EOK) {
		tr_log("SPI I/O param check fail");
		goto errdone;
	}

#ifdef _ATHW_STM32_TPM_
	__HAL_SPI_ENABLE(handle);
	HAL_GPIO_WritePin(TPM_SPI_CS_PORT, TPM_SPI_CS_PIN, GPIO_PIN_RESET);

	status = HAL_SPI_TransmitReceive(handle, (uint8_t *)ctx->txlv->value,
									 (uint8_t *)ctx->rxlv->value,
									 ATHW_TPM_TIS_HEADER_SZ,
									 ATHW_TPM_SPI_TMO);
	if(status != HAL_OK) {
		tr_log("TPM SPI TIS HEADER exchange fail");
		ret = ERRNGATE(EIOFAIL);
		goto errdone;
	}

	// Check for TPM wait states
	if((ctx->rxlv->value[ATHW_TPM_TIS_HEADER_SZ - 1] & ATHW_TPM_TIS_READY_MASK) == 0) {
		do {
			// check for TPM ready
			status = HAL_SPI_TransmitReceive(handle, (uint8_t *)ctx->txlv->value,
											 (uint8_t *)ctx->rxlv->value, 1,
											 ATHW_TPM_SPI_TMO);
			if(ctx->rxlv->value[0] & ATHW_TPM_TIS_READY_MASK) 
				break;


		} while(status == HAL_OK && --timeout > 0);
#define ATHW_TPM_DEBUG
		tr_log("TPM SPI Ready wait %d \r\n", ATHW_TPM_SPI_WAIT_RETRY - timeout);
#endif			

		if(timeout <= 0) {
			tr_log("TPM ready check fail");
			ret = ERRNGATE(EIOFAIL);
			goto errdone;
		}


	}

	// Send remainder data
	status = HAL_SPI_TransmitReceive(handle,
									 (uint8_t *)&ctx->txlv->value[ATHW_TPM_TIS_HEADER_SZ],
									 &ctx->txlv->value[ATHW_TPM_TIS_HEADER_SZ],
									 ctx->txlv->len - ATHW_TPM_TIS_HEADER_SZ,
									 ATHW_TPM_SPI_TMO);
	




	//HAL_GPIO_WritePin(TPM_SPI_CS_PORT, TPM_SPI_CS_PIN, GPIO_PIN_SET); 
#else
#error "Unsupport Device, Please check the Device Define"
#endif

	 
		 
errdone:

#ifdef _STM32_TPM_
	HAL_GPIO_WritePin(TPM_SPI_CS_PORT, TPM_SPI_CS_PIN, GPIO_PIN_SET);
	__HAL_SPI_DISABLE(handle);
#endif

	return ret;

}

/**
 * 
 * 
 * @author hyowon.cho (2024-03-14)
 * 
 * @param priv   
 * 
 * @return int 
 */
int athw_tpm2io_i2c(void *priv) 
{
	(void)priv;
	return 0;

}


int athw_tpm_io(uint32_t addr, int isread, void *ptr, int len)
{
	int ret = EOK;
	//tpmio_ctx_t *ctx;
	tpmio_ctx_t ctx;
	tpmio_lv_t txlv;
	tpmio_lv_t rxlv;

	uint8_t txbuf[ATHW_TPM_SPI_FRAME_SZ + ATHW_TPM_TIS_HEADER_SZ] = { 0, };
	uint8_t rxbuf[ATHW_TPM_SPI_FRAME_SZ + ATHW_TPM_TIS_HEADER_SZ] = { 0, }; 


#if 0
	ctx = (tpmio_ctx_t *)priv;
	ret = _athw_tpm2io_ctx_param_check(ctx);
	if(ret != EOK) {
		tr_log("Context struct parch check fail");
		goto errdone;
	}
#endif

	txlv.value = (void *)txbuf;  //x_memcreate(ATHW_TPM_TIS_HEADER_SZ + len);
	rxlv.value = (void *)rxbuf;  //x_memcreate(ATHW_TPM_TIS_HEADER_SZ + len);

	txlv.len = rxlv.len = len + ATHW_TPM_TIS_HEADER_SZ;

	ctx.handle = ATHW_TPM_SPI_PORT;
	ctx.txlv = &txlv;
	ctx.rxlv = &rxlv;

	// Generate TPM Header
	ctx.txlv.value[1] = (addr >> 16) 	& 0xFF;
	ctx.txlv.value[2] = (addr >> 8) 	& 0xFF; 
	ctx.txlv.value[3] = (addr) 			& 0xFF;

	if(isread) {
		ctx.txlv.value[0] = ATHW_TPM_TIS_READ | ((len & 0xFF) - 1);
	}
	else {
		ctx.txlv.value[0] = ATHW_TPM_TIS_WRITE | ((len & 0xFF) - 1);
		x_memcpy(&ctx.txlv.value[ATHW_TPM_TIS_HEADER_SZ], len,
				 (const void *)ptr, len);
		
	}

	ret = _athw_tpm2io_spi((void *)&ctx);
	if(ret != EOK) {
		goto errdone;
	}

	if(isread) {
		x_memcpy(ptr, len, &ctx.txlv.value[ATHW_TPM_TIS_HEADER_SZ], len);
	}

#ifdef ATHW_TPM_DEBUG
	printf("TPM IO exchange : (ret : %d, sz : %d) \r\n", ret, size);
	_x_print_bin("TX", (const uint8_t *)ctx.txlv.value, len + ATHW_TPM_TIS_HEADER_SZ);
	_x_print_bin("RX", (const uint8_t *)ptr, len);
#endif

	//ctx.txlv = ()x_memcreate(sizeof ctx.txlv);
	//x_memcreate(ctx.txlv->value, len + ATHW_TPM_TIS_HEADER_SZ);

	//x_memcreate(ctx.rxlv, )

errdone:

//	x_memdestory(txlv.value);
//	x_memdestory(rxlv.value);
	return ret;
}


