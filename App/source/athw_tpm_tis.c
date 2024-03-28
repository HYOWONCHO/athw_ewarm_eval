#include "athw_tpm2.h"
#include "athw_tpm_tis.h"

static uint32_t gn_locality = 0UL;

static int athw_tpm2_tis_check_locality_access_valid(athw_tpm2ctx_t *ctx, int locality, uint8_t access)
{
	if((access & (ATHW_TPM_ACCESS_ACTIVE_LOCALITY | ATHW_TPM_ACCESS_VALID)) ==
		   (ATHW_TPM_ACCESS_ACTIVE_LOCALITY | ATHW_TPM_ACCESS_VALID)) {
		ctx->locality = locality;
		return locality;
	}

	return ERRNGATE(EFAIL); 
}


int athw_tpm2_check_locality(int locality, uint8_t *access) 
{
	int ret = EOK;
	ret = athw_tpm_io(ATHW_TPM_ACCESS(locality), access, sizeof(*access));
	return ret;
}



int athw_tpm2_tis_request_locality(void *handle, int tmo) 
{
	int ret = EOK;
	int locality = ATHW_LOCALITY_DEFAULT;
	uint8_t access = 0;

	athw_tpm2ctx_t *ctx = (athw_tpm2ctx_t *)handle;

	ret = athw_tpm2_check_locality(locality, &access);
	if(ret == ATHW_TPM_RC_SUCCESS) {
		ret = athw_tpm2_tis_check_locality_access_valid(ctx, locality, access);
		if(ret >= 0) {
			goto errdone;
		}
	}

	access = ATHW_TPM_ACCESS_REQUEST_USE;
	ret = athw_tpm_io(ATHW_TPM_ACCESS(locality), &access, sizeof(access));
	if(ret != EOK) {
		goto errdone;
	}

	do {
		access = 0;
		ret = athw_tpm2_check_locality(locality, &access);
		if(ret == EOK) {
			ret = athw_tpm2_tis_check_locality_access_valid(locality, access);
			if(ret >= 0) {
				goto errdone;
			}
		}

		__NOP();
	} while(ret < 0 && --tmo > 0);


	tr_log("ATHW TIS Request Locality : timeout %d \r\n\n", TPM_TIMEOUT_TRIES - tmo);

	if(tmo <= 0) {
		ret = ATHW_TPM_RC_TIMEOUT;
	}


errdone:

	return ret;
}

/**
 * @fn athw_tpm2_startup - Wait for chip startup to complete and
 *     get the device information
 *
 * 
 * @author hyowon.cho (2024-03-15)
 * 
 * @param tmo    
 * 
 * @return int 
 */
int athw_tpm2_tis_startup_wait(int tmo) 
{
	int ret = EOK;
	uint8_t tpmaccess = 0;

	//int athw_tpm_io(uint32_t addr, int isread, void *ptr, int len)

	do {
		ret = athw_tpm_io(ATHW_TPM_ACCESS(0), ATHW_TPM_TIS_READ, (void *)&tpmaccess, sizeof tpmaccess);

		if(ret == EOK && (tpmaccess & ATHW_TPM_ACCESS_VALID) && (tpmaccess != 0xFF)) {
			goto errdone;
		}

		//delay_ms(1);
		__NOP;

	} while(ret == EOK && --tmo > 0);

	tr_log("%s: Timeout %d\r\r\n", __FUNCTION__, TPM_TIMEOUT_TRIES - tmo);

	if(tmo <= 0) {
		ret = ERRNGATE(EIOTIMEOUT);
	}


errdone:

	return ret;
}

int athw_tpm2_tis_getinfo(void *handle) 
{
	int ret = EOK;

	uint32_t reg = 0UL;
	athw_tpm2ctx_t *ctx = (athw_tpm2ctx_t *)handle;

	if(ctx == NULL) {
		return ERRNGATE(ESNULLP);
	}

	ret = athw_tpm_io(ATHW_TPM_INTF_CAPS(gn_locality), ATHW_TPM_TIS_READ, (uint8_t *)&reg, sizeof reg);
	if(ret == EOK) {
		ctx->caps = reg;
#ifdef ATHW_TPM_TIS_DEBUG
		tr_log("CAPS : 0x%x", ctx->caps);
#endif
	}

	x_memzero((void *)&reg, sizeof reg);
	ret = athw_tpm_io(ATHW_TPM_DID_VID(gn_locality), ATHW_TPM_TIS_READ, (uint8_t *)&reg, sizeof reg);
	if(ret == EOK) {
		ctx->didvid = reg;
#ifdef ATHW_TPM_TIS_DEBUG
		tr_log("DID VID  : 0x%x", ctx->caps);
#endif
	}

	x_memzero((void *)&reg, sizeof reg);
	ret = athw_tpm_io(ATHW_TPM_RID(gn_locality), ATHW_TPM_TIS_READ, (uint8_t *)&reg, 1);
	if(ret == EOK) {
		ctx->rid = reg;
#ifdef ATHW_TPM_TIS_DEBUG
		tr_log("RID  : 0x%x", ctx->caps);
#endif
	}

	return ret;


}

int athw_tpm2_tis_checklocality(int locality, uint8_t *access) 
{
	int ret = EOK;

	ret = athw_tpm_io(ATHW_TPM_ACCESS(locality), access, sizeof(*access));

	return ret;
}

int athw_tpm2_tis_status(athw_tpm2ctx_t *ctx, uint8_t *status) 
{
	return athw_tpm_io(ATHW_TPM_STS(ctx->locality), TPM_TIS_READ, status, sizeof(*status));
}

int athw_tpm2_tis_wait_status(athw_tpm2ctx_t *ctx, uint8_t status, uint8_t st_mask) 
{
	int ret = ATHW_TPM_RC_SUCCESS;
	int timeout = 1000000;
	uint8_t regval = 0;

	do {
		ret = athw_tpm2_tis_status(ctx, &regval);
		if(ret == ATHW_TPM_RC_SUCCESS && ((regval & status) == st_mask)) {
			break;
		}

		__NOP;
	} while((ret == ATHW_TPM_RC_SUCCESS) && (--timeout > 0));

#ifdef ATHW_TPM_TIS_DEBUG
	tr_log("%s : timeout %d \r\r\n", __FUNCTION__, 1000000 - timeout);
#endif

	if(timeout <= 0) {
		return ATHW_TPM_RC_TIMEOUT;
	}

	return ret;


}

int athw_tpm2_tis_ready(athw_tpm2ctx_t *ctx) 
{
	uint8_t status = 0x40;

	return athw_tpm_io(ATHW_TPM_STS(ctx->locality), TPM_TIS_WRITE, &status, sizeof(status))
}

/**
 * 
 * 
 * @author hyowon.cho (2024-03-27)
 * 
 * @param ctx    
 * @param cnt    Burst count 
 * 
 * @return int 
 */
int athw_tpm2_tis_getburstcnt(athw_tpm2ctx_t *ctx, uint16_t *cnt) 
{
	int ret = ATHW_TPM_RC_SUCCESS;
	uint16_t vid = 0;
	int timeout = 1000000;

	X_ASSERT_PARAM((ctx != NULL), BAD_FUNC_ARG); 
	X_ASSERT_PARAM((cnt != NULL), BAD_FUNC_ARG);
	
	*cnt = 0;
	vid = (uint16_t)(ctx->didvid & 0xFFFF);

	// TPM ST33
	if(vid == 0x104A) {
		*cnt = 32; // Fixed value
		goto errdone;
	}

	do {
		ret = athw_tpm_io(ATHW_TPM_BURST_COUNT(ctx->locality),
						  TPM_TIS_READ,
						  (void *)cnt, sizeof(*cnt));
		if(ret == ATHW_TPM_RC_SUCCESS && *cnt > 0) {
			break;
		}

		__NOP;

	} while(ret = ATHW_TPM_RC_SUCCESS && --timeout > 0);

	(*cnt > MAX_SPI_FRAMESIZE) ? *cnt = MAX_SPI_FRAMESIZE;

	if(timeout <= 0) {
		ret = ATHW_TPM_RC_TIMEOUT;
		goto errdone;
	}


errdone:

	return ret;

}

int athw_tpm2_tis_sendcmd(athw_tpm2ctx_t *ctx, athw_tpm2pkt_t *pkt) 
{
	int ret = EOK;
	uint8_t status = 0, access;
	uint16_t burstcnt;

	int pos = 0L;
	int sz_xfer = 0L;
	int sz_rsp = 0L;

	X_ASSERT_PARAM((ctx != NULL), ERRNGATE(ESNULLP));
	X_ASSERT_PARAM((pkt != NULL), ERRNGATE(ESNULLP)); 

#ifdef ATHW_TPM_TIS_DEBUG
	_buf_dump(pkt->buf, "Command", pkt->pos);
#endif

	
	ret = athw_tpm2_tis_status(ctx, &status);
	if(ret != EOK) {
		goto errdone;
	}


	// make sure tpm is ready for command 
	switch((status & 0x40)) {
	case 0:
		// Command is not ready
		{
			ret = athw_tpm2_tis_ready(ctx);
			if(ret != ATHW_TPM_RC_SUCCESS) {
				goto errdone;
			}

			ret = athw_tpm2_tis_wait_status(ctx, 0x40, 0x40);
			if(ret != ATHW_TPM_RC_SUCCESS) {
				goto errdone;
			}

		}
	default:
		break;
	}

	// write command
	while(pos < pkt->pos) {
		ret = athw_tpm2_tis_getburstcnt(ctx, &burstcnt);
		if(ret < 0) {
			goto errdone;
		}

		sz_xfer = pkt->pos - pos;
		if(sz_xfer > burstcnt) {
			sz_xfer = burstcnt;
		}

		ret = athw_tpm_io(ATHW_TPM_DATA_FIFO(ctx->locality, TPM_TIS_WRITE , &pkt->buf[pos], sz_xfer));
		if(ret != ATHW_TPM_RC_SUCCESS) {
			goto errdone;
		}

		pos += sz_xfer;
		if(pos < pkt->pos) {
			// data expect
			ret = athw_tpm2_tis_wait_status(ctx, 0x08, 0x08);
			if(ret != ATHW_TPM_RC_SUCCESS) {
#ifdef ATHW_TPM_TIS_DEBUG
				tr_log("%s write expected more data \r\n", __FUNCTION__);
#endif
				goto errdone;
			}
		}
	}


	// wait for data expect and valid
	ret = athw_tpm2_tis_wait_status(ctx, 0x80 | 0x08, 0x80);
	if(ret != ATHW_TPM_RC_SUCCESS) {
#ifdef ATHW_TPM_TIS_DEBUG
		tr_log("command status valid timeout \r\n");
#endif
		goto errdone;
	}

	// excute command
	access = 0x20;
	ret = athw_tpm_io(ATHW_TPM_STS(ctx->locality), TPM_TIS_WRITE, &access, sizeof access);
	if(ret != ATHW_TPM_RC_SUCCESS) {
		goto errdone;
	}


	// read response
	pos = 0;
	sz_rsp = ATHW_TPM2_HEADER_SZ;//10; // tpm header size

	while(pos < sz_rsp) {
		ret = athw_tpm2_tis_wait_status(ctx, 0x10, 0x10);
		if(ret != ATHW_TPM_RC_SUCCESS) {
#ifdef ATHW_TPM_TIS_DEBUG
			tr_log("command status valid timeout \r\n");
#endif
			goto errdone;
		}

		ret = athw_tpm2_tis_getburstcnt(ctx, &burstcnt);
		if(ret < 0) {
			goto errdone;
		}

		sz_xfer = sz_rsp - pos;
		if(sz_xfer > burstcnt) {
			sz_xfer = burstcnt;
		}

		ret = athw_tpm_io(ATHW_TPM_DATA_FIFO(ctx->locality), TPM_TIS_WRITE, &pkt->buf[pos], sz_xfer);
		if(ret != ATHW_TPM_RC_SUCCESS)  {
			goto errdone;
		}

		pos += sz_xfer;

		// get response size
		if(pos == ATHW_TPM2_HEADER_SZ) {
			uint32_t tmpsz;
			x_memcpy(&tmpsz, 4, &pkt->buf[2], 4);

			sz_rsp = ahtw_tpm2_packet_swapu32(tmpsz);

			if(sz_rsp < 0 || sz_rsp >= 4096 || sz_rsp > pkt->size) {
				ret = ATHW_TPM_RC_FAILURE;
				goto errdone;
			}
		}

	}

#ifdef ATHW_TPM_TIS_DEBUG
	if(sz_rsp > 0) {
		_buf_dump(pkt->buf, "Response", sz_rsp);
	}
#endif

	ret = ATHW_TPM_RC_SUCCESS;

errdone:

	if(ret == ATHW_TPM_RC_SUCCESS) {
		ret = athw_tpm2_tis_ready(ctx);
	}

	return ret;

}



