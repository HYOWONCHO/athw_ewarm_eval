#include "config.h"
#include "athw_tpm2.h"
#include "athw_tpm_tis.h"

#define ATHW_TPM2_RET_STRINGIFY(ret)	#ret
#ifdef TPM2_DEBUG
	#define ATHW_TPM2_RET_STR(ret, desc) case ret: return ATHW_TPM2_RET_STRINGIFY(ret) ": " desc
#else
	#define ATHW_TPM2_RET_STR(rc, desc) case ret: return ATHW_TPM2_RET_STRINGIFY(rc)
#endif

const char* athw_tpm2_get_ret_string(int ret) 
{
	if(ret < 0) {
		switch(ret) {
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_TIMEOUT, "Hardware Timeout");
		default:
			break;
		}

		switch(ret) {
			ATHW_TPM2_RET_STR(BAD_FUNC_ARG, "Bad function argument");
			ATHW_TPM2_RET_STR(BUFFER_E, "Buffer error, output too small or input too big");
			ATHW_TPM2_RET_STR(NOT_COMPILED_IN, "Feature not compiled in");
			ATHW_TPM2_RET_STR(BAD_MUTEX_E, "Bad mutex, operation failed");
			ATHW_TPM2_RET_STR(WC_TIMEOUT_E, "Timeout error");
		default:
			break;
		}
	}
	else if(ret == EOK) {
		return "Success";
	}

	if(ret & RC_VER1) {
		int ret_fm0 = ret & RC_MAX_FM0;

		switch(ret_fm0) {
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_SUCCESS, "Success");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_BAD_TAG, "Bad Tag");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_INITIALIZE, "TPM not initialized by TPM2_Startup or already initialized");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_FAILURE, "Commands not being accepted because of a TPM failure");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_SEQUENCE, "Improper use of a sequence handle");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_DISABLED, "The command is disabled");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_EXCLUSIVE, "Command failed because audit sequence required exclusivity");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_AUTH_TYPE, "Authorization handle is not correct for command");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_AUTH_MISSING, "Command requires an authorization session for handle and it is not present");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_POLICY, "Policy failure in math operation or an invalid authPolicy value");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_PCR, "PCR check fail");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_PCR_CHANGED, "PCR have changed since checked");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_UPGRADE, "Indicates that the TPM is in field upgrade mode");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_TOO_MANY_CONTEXTS, "Context ID counter is at maximum");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_AUTH_UNAVAILABLE, "The authValue or authPolicy is not available for selected entity");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_REBOOT, "A _TPM_Init and Startup(CLEAR) is required before the TPM can resume operation");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_UNBALANCED, "The protection algorithms (hash and symmetric) are not reasonably balanced");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_COMMAND_SIZE, "Command commandSize value is inconsistent with contents of the command buffer");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_COMMAND_CODE, "Command code not supported");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_AUTHSIZE, "The value of authorizationSize is out of range or the number of octets in the Authorization Area is greater than required");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_AUTH_CONTEXT, "Use of an authorization session with a context command or another command that cannot have an authorization session");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_NV_RANGE, "NV offset+size is out of range");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_NV_SIZE, "Requested allocation size is larger than allowed");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_NV_LOCKED, "NV access locked");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_NV_AUTHORIZATION, "NV access authorization fails in command actions");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_NV_UNINITIALIZED, "An NV Index is used before being initialized or the state saved by TPM2_Shutdown(STATE) could not be restored");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_NV_SPACE, "Insufficient space for NV allocation");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_NV_DEFINED, "NV Index or persistent object already defined");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_BAD_CONTEXT, "Context in TPM2_ContextLoad() is not valid");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_CPHASH, "The cpHash value already set or not correct for use");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_PARENT, "Handle for parent is not a valid parent");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_NEEDS_TEST, "Some function needs testing");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_NO_RESULT, "Cannot process a request due to an unspecified problem");
			ATHW_TPM2_RET_STR(ATHW_TPM_RC_SENSITIVE, "The sensitive area did not unmarshal correctly after decryption");
		default:
			break;
		}
	}

}

int athw_tpm2_chip_startup(void *handle, int tmo) 
{
	int ret = EOK;
	athw_tpm2ctx_t *ctx = NULL;

	X_ASSERT_PARAM((handle != NULL), ERRNGATE(ESNULLP));
	X_ASSERT_PARAM((tmo > 0), ERRNGATE(ESZEROL));

	ctx = (athw_tpm2ctx_t *)handle;

	ret = athw_tpm2_tis_startup_wait(tmo);
	if(ret != EOK) {
#ifdef TPM2_DEBUG
		tr_log("TIS startup wait fail (%d)", ret);
#endif
		goto errdone;
	}

	ret = athw_tpm2_tis_request_locality((void *)ctx, tmo);
	if(ret != EOK) {
#ifdef TPM2_DEBUG
		tr_log("TIS request locality fail (%d)", ret);
#endif
		goto errdone;
	}

	ret = athw_tpm2_tis_getinfo(ctx);
	if(ret != EOK) {
#ifdef TPM2_DEBUG
		tr_log("TISGet Information fail (%d)", ret);
#endif
		goto errdone;
	}


errdone:

	return ret;
}

int athw_tpm2_startup(void *handle, uint16_t *inctx) 
{
	int ret = EOK;
	athw_tpm2ctx_t *ctx;

	X_ASSERT_PARAM((handle != NULL), ERRNGATE(ESNULLP));
	X_ASSERT_PARAM((inctx != NULL), ERRNGATE(ESNULLP));




errdone:

	return ret;

}

int athw_tpm2_init(void *handle, int tmotries) 
{
	int ret = EOK;
	athw_tpm2ctx_t *ctx;

	//if(handle == NULL) {
	//	return ERRNGATE(ESNULLP);
	//}

	X_ASSERT_PARAM((handle != NULL), ERRNGATE(ESNULLP));
	X_ASSERT_PARAM((tmotries > 0), ERRNGATE(ESZEROL));

	ctx = (athw_tpm2ctx_t *)handle;

	ret = athw_tpm2_chip_startup(ctx, tmotries);
	if(ret != EOK) {
#ifdef TPM2_DEBUG
		tr_log("TPM Device initialization fila %d - (%s)", 
			   ret, athw_tpm2_get_ret_string(ret));
#endif
		goto errdone;
	}

#ifdef TPM2_DEBUG
	tr_log("TPM2 Caps 0x%08x, Did : 0x%04x, Vid : 0x%04x, Rid : 0x%02x \r\r\r\n",
		   ctx->caps, (ctx->didvid >> 16) & 0xFFFF, ctx->didvid & 0xFFFF, ctx->rid)
#endif



errdone:

	return ret;

}



