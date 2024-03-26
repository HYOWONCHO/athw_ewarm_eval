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



