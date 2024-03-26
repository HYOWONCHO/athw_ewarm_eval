#ifndef _athw_tpm2_tis_h
#define _athw_tpm2_tis_h

#ifdef __cplusplus
extern "C"
{
#endif

// TPM Context structure
typedef struct _athw_tpm2ctx_t {
	// TPM2 TIS information
	int locality;
	uint32_t caps;
	uint32_t didvid;

	uint8_t cmdrsp_buf[TPM_XFER_MAX_SZ];
	uint8_t rid;

}athw_tpm2ctx_t; 


int athw_tpm2_tis_request_locality(void *handle, int tmo);

int athw_tpm2_tis_checklocality(int locality, uint8_t *access);
int athw_tpm2_tis_getinfo(void *handle);
int athw_tpm2_tis_startup_wait(int tmo);
int athw_tpm2_check_locality(int locality, uint8_t *access);

#ifdef __cplusplus
}
#endif

#endif
