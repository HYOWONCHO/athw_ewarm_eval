#ifndef __ATHW_ATHW_TPM_TIS_H
#define __ATHW_ATHW_TPM_TIS_H

#define __cplusplus
extern "C"
{
#endif

#define ATHW_TPM_TIS_READ       			0x80
#define ATHW_TPM_TIS_WRITE      			0x00

#define ATHW_TPM_TIS_HEADER_SZ  			4

#define ATHW_TPM_TIS_READY_MASK 			0x01

/* Typically only 0-2 wait states are required */
#ifndef ATHW_TPM_TIS_MAX_WAIT
#define ATHW_TPM_TIS_MAX_WAIT   			3
#endif

#define __cplusplus
}
#endif

#endif
