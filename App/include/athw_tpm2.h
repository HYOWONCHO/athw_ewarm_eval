#ifndef __ATHW_ATHW_TPM2_H
#define __ATHW_ATHW_TPM2_H


#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"


enum ATHW_TPM_tis_access {
    ATHW_TPM_ACCESS_VALID            = 0x80,
    ATHW_TPM_ACCESS_ACTIVE_LOCALITY  = 0x20,
    ATHW_TPM_ACCESS_REQUEST_PENDING  = 0x04,
    ATHW_TPM_ACCESS_REQUEST_USE      = 0x02,
};

enum ATHW_TPM_tis_status {
    ATHW_TPM_STS_VALID               = 0x80,
    ATHW_TPM_STS_COMMAND_READY       = 0x40,
    ATHW_TPM_STS_GO                  = 0x20,
    ATHW_TPM_STS_DATA_AVAIL          = 0x10,
    ATHW_TPM_STS_DATA_EXPECT         = 0x08,
    ATHW_TPM_STS_SELF_TEST_DONE      = 0x04,
    ATHW_TPM_STS_RESP_RETRY          = 0x02,
};

/* enum ATHW_TPM_tis_int_flags */
#define ATHW_TPM_GLOBAL_INT_ENABLE       0x80000000UL
#define ATHW_TPM_INTF_BURST_COUNT_STATIC 0x100
#define ATHW_TPM_INTF_CMD_READY_INT      0x080
#define ATHW_TPM_INTF_INT_EDGE_FALLING   0x040
#define ATHW_TPM_INTF_INT_EDGE_RISING    0x020
#define ATHW_TPM_INTF_INT_LEVEL_LOW      0x010
#define ATHW_TPM_INTF_INT_LEVEL_HIGH     0x008
#define ATHW_TPM_INTF_LOC_CHANGE_INT     0x004
#define ATHW_TPM_INTF_STS_VALID_INT      0x002
#define ATHW_TPM_INTF_DATA_AVAIL_INT     0x001


#ifndef ATHW_TPM_BASE_ADDRESS
    #define ATHW_TPM_BASE_ADDRESS (0xD40000u)
#endif

#ifdef ATHW_TPM_I2C
/* For I2C only the lower 8-bits of the address are used */
    #define ATHW_TPM_ACCESS(l)           (ATHW_TPM_BASE_ADDRESS | 0x0004u | ((l) << 12u))
    #define ATHW_TPM_INTF_CAPS(l)        (ATHW_TPM_BASE_ADDRESS | 0x0030u | ((l) << 12u))
    #define ATHW_TPM_DID_VID(l)          (ATHW_TPM_BASE_ADDRESS | 0x0048u | ((l) << 12u))
    #define ATHW_TPM_RID(l)              (ATHW_TPM_BASE_ADDRESS | 0x004Cu | ((l) << 12u))
    #define ATHW_TPM_I2C_DEVICE_ADDR(l)  (ATHW_TPM_BASE_ADDRESS | 0x0038u | ((l) << 12u))
    #define ATHW_TPM_DATA_CSUM_ENABLE(l) (ATHW_TPM_BASE_ADDRESS | 0x0040u | ((l) << 12u))
    #define ATHW_TPM_DATA_CSUM(l)        (ATHW_TPM_BASE_ADDRESS | 0x0044u | ((l) << 12u))
#else
    #define ATHW_TPM_ACCESS(l)           (ATHW_TPM_BASE_ADDRESS | 0x0000u | ((l) << 12u))
    #define ATHW_TPM_INTF_CAPS(l)        (ATHW_TPM_BASE_ADDRESS | 0x0014u | ((l) << 12u))
    #define ATHW_TPM_DID_VID(l)          (ATHW_TPM_BASE_ADDRESS | 0x0F00u | ((l) << 12u))
    #define ATHW_TPM_RID(l)              (ATHW_TPM_BASE_ADDRESS | 0x0F04u | ((l) << 12u))
#endif

#define ATHW_TPM_INT_ENABLE(l)       (ATHW_TPM_BASE_ADDRESS | 0x0008u | ((l) << 12u))
#define ATHW_TPM_INT_VECTOR(l)       (ATHW_TPM_BASE_ADDRESS | 0x000Cu | ((l) << 12u))
#define ATHW_TPM_INT_STATUS(l)       (ATHW_TPM_BASE_ADDRESS | 0x0010u | ((l) << 12u))
#define ATHW_TPM_STS(l)              (ATHW_TPM_BASE_ADDRESS | 0x0018u | ((l) << 12u))
#define ATHW_TPM_BURST_COUNT(l)      (ATHW_TPM_BASE_ADDRESS | 0x0019u | ((l) << 12u))
#define ATHW_TPM_DATA_FIFO(l)        (ATHW_TPM_BASE_ADDRESS | 0x0024u | ((l) << 12u))
#define ATHW_TPM_XDATA_FIFO(l)       (ATHW_TPM_BASE_ADDRESS | 0x0083u | ((l) << 12u))



typedef enum {
    ATHW_TPM_RC_SUCCESS  = 0x000,
    ATHW_TPM_RC_BAD_TAG  = 0x01E,

    RC_VER1 = 0x100,
    ATHW_TPM_RC_INITIALIZE           = RC_VER1 + 0x000,
    ATHW_TPM_RC_FAILURE              = RC_VER1 + 0x001,
    ATHW_TPM_RC_SEQUENCE             = RC_VER1 + 0x003,
    ATHW_TPM_RC_PRIVATE              = RC_VER1 + 0x00B,
    ATHW_TPM_RC_HMAC                 = RC_VER1 + 0x019,
    ATHW_TPM_RC_DISABLED             = RC_VER1 + 0x020,
    ATHW_TPM_RC_EXCLUSIVE            = RC_VER1 + 0x021,
    ATHW_TPM_RC_AUTH_TYPE            = RC_VER1 + 0x024,
    ATHW_TPM_RC_AUTH_MISSING         = RC_VER1 + 0x025,
    ATHW_TPM_RC_POLICY               = RC_VER1 + 0x026,
    ATHW_TPM_RC_PCR                  = RC_VER1 + 0x027,
    ATHW_TPM_RC_PCR_CHANGED          = RC_VER1 + 0x028,
    ATHW_TPM_RC_UPGRADE              = RC_VER1 + 0x02D,
    ATHW_TPM_RC_TOO_MANY_CONTEXTS    = RC_VER1 + 0x02E,
    ATHW_TPM_RC_AUTH_UNAVAILABLE     = RC_VER1 + 0x02F,
    ATHW_TPM_RC_REBOOT               = RC_VER1 + 0x030,
    ATHW_TPM_RC_UNBALANCED           = RC_VER1 + 0x031,
    ATHW_TPM_RC_COMMAND_SIZE         = RC_VER1 + 0x042,
    ATHW_TPM_RC_COMMAND_CODE         = RC_VER1 + 0x043,
    ATHW_TPM_RC_AUTHSIZE             = RC_VER1 + 0x044,
    ATHW_TPM_RC_AUTH_CONTEXT         = RC_VER1 + 0x045,
    ATHW_TPM_RC_NV_RANGE             = RC_VER1 + 0x046,
    ATHW_TPM_RC_NV_SIZE              = RC_VER1 + 0x047,
    ATHW_TPM_RC_NV_LOCKED            = RC_VER1 + 0x048,
    ATHW_TPM_RC_NV_AUTHORIZATION     = RC_VER1 + 0x049,
    ATHW_TPM_RC_NV_UNINITIALIZED     = RC_VER1 + 0x04A,
    ATHW_TPM_RC_NV_SPACE             = RC_VER1 + 0x04B,
    ATHW_TPM_RC_NV_DEFINED           = RC_VER1 + 0x04C,
    ATHW_TPM_RC_BAD_CONTEXT          = RC_VER1 + 0x050,
    ATHW_TPM_RC_CPHASH               = RC_VER1 + 0x051,
    ATHW_TPM_RC_PARENT               = RC_VER1 + 0x052,
    ATHW_TPM_RC_NEEDS_TEST           = RC_VER1 + 0x053,
    ATHW_TPM_RC_NO_RESULT            = RC_VER1 + 0x054,
    ATHW_TPM_RC_SENSITIVE            = RC_VER1 + 0x055,
    RC_MAX_FM0                  = RC_VER1 + 0x07F,

    RC_FMT1 = 0x080,
    ATHW_TPM_RC_ASYMMETRIC       = RC_FMT1 + 0x001,
    ATHW_TPM_RC_ATTRIBUTES       = RC_FMT1 + 0x002,
    ATHW_TPM_RC_HASH             = RC_FMT1 + 0x003,
    ATHW_TPM_RC_VALUE            = RC_FMT1 + 0x004,
    ATHW_TPM_RC_HIERARCHY        = RC_FMT1 + 0x005,
    ATHW_TPM_RC_KEY_SIZE         = RC_FMT1 + 0x007,
    ATHW_TPM_RC_MGF              = RC_FMT1 + 0x008,
    ATHW_TPM_RC_MODE             = RC_FMT1 + 0x009,
    ATHW_TPM_RC_TYPE             = RC_FMT1 + 0x00A,
    ATHW_TPM_RC_HANDLE           = RC_FMT1 + 0x00B,
    ATHW_TPM_RC_KDF              = RC_FMT1 + 0x00C,
    ATHW_TPM_RC_RANGE            = RC_FMT1 + 0x00D,
    ATHW_TPM_RC_AUTH_FAIL        = RC_FMT1 + 0x00E,
    ATHW_TPM_RC_NONCE            = RC_FMT1 + 0x00F,
    ATHW_TPM_RC_PP               = RC_FMT1 + 0x010,
    ATHW_TPM_RC_SCHEME           = RC_FMT1 + 0x012,
    ATHW_TPM_RC_SIZE             = RC_FMT1 + 0x015,
    ATHW_TPM_RC_SYMMETRIC        = RC_FMT1 + 0x016,
    ATHW_TPM_RC_TAG              = RC_FMT1 + 0x017,
    ATHW_TPM_RC_SELECTOR         = RC_FMT1 + 0x018,
    ATHW_TPM_RC_INSUFFICIENT     = RC_FMT1 + 0x01A,
    ATHW_TPM_RC_SIGNATURE        = RC_FMT1 + 0x01B,
    ATHW_TPM_RC_KEY              = RC_FMT1 + 0x01C,
    ATHW_TPM_RC_POLICY_FAIL      = RC_FMT1 + 0x01D,
    ATHW_TPM_RC_INTEGRITY        = RC_FMT1 + 0x01F,
    ATHW_TPM_RC_TICKET           = RC_FMT1 + 0x020,
    ATHW_TPM_RC_RESERVED_BITS    = RC_FMT1 + 0x021,
    ATHW_TPM_RC_BAD_AUTH         = RC_FMT1 + 0x022,
    ATHW_TPM_RC_EXPIRED          = RC_FMT1 + 0x023,
    ATHW_TPM_RC_POLICY_CC        = RC_FMT1 + 0x024,
    ATHW_TPM_RC_BINDING          = RC_FMT1 + 0x025,
    ATHW_TPM_RC_CURVE            = RC_FMT1 + 0x026,
    ATHW_TPM_RC_ECC_POINT        = RC_FMT1 + 0x027,
    RC_MAX_FMT1             = RC_FMT1 + 0x03F,

    RC_WARN = 0x900,
    ATHW_TPM_RC_CONTEXT_GAP      = RC_WARN + 0x001,
    ATHW_TPM_RC_OBJECT_MEMORY    = RC_WARN + 0x002,
    ATHW_TPM_RC_SESSION_MEMORY   = RC_WARN + 0x003,
    ATHW_TPM_RC_MEMORY           = RC_WARN + 0x004,
    ATHW_TPM_RC_SESSION_HANDLES  = RC_WARN + 0x005,
    ATHW_TPM_RC_OBJECT_HANDLES   = RC_WARN + 0x006,
    ATHW_TPM_RC_LOCALITY         = RC_WARN + 0x007,
    ATHW_TPM_RC_YIELDED          = RC_WARN + 0x008,
    ATHW_TPM_RC_CANCELED         = RC_WARN + 0x009,
    ATHW_TPM_RC_TESTING          = RC_WARN + 0x00A,
    ATHW_TPM_RC_REFERENCE_H0     = RC_WARN + 0x010,
    ATHW_TPM_RC_REFERENCE_H1     = RC_WARN + 0x011,
    ATHW_TPM_RC_REFERENCE_H2     = RC_WARN + 0x012,
    ATHW_TPM_RC_REFERENCE_H3     = RC_WARN + 0x013,
    ATHW_TPM_RC_REFERENCE_H4     = RC_WARN + 0x014,
    ATHW_TPM_RC_REFERENCE_H5     = RC_WARN + 0x015,
    ATHW_TPM_RC_REFERENCE_H6     = RC_WARN + 0x016,
    ATHW_TPM_RC_REFERENCE_S0     = RC_WARN + 0x018,
    ATHW_TPM_RC_REFERENCE_S1     = RC_WARN + 0x019,
    ATHW_TPM_RC_REFERENCE_S2     = RC_WARN + 0x01A,
    ATHW_TPM_RC_REFERENCE_S3     = RC_WARN + 0x01B,
    ATHW_TPM_RC_REFERENCE_S4     = RC_WARN + 0x01C,
    ATHW_TPM_RC_REFERENCE_S5     = RC_WARN + 0x01D,
    ATHW_TPM_RC_REFERENCE_S6     = RC_WARN + 0x01E,
    ATHW_TPM_RC_NV_RATE          = RC_WARN + 0x020,
    ATHW_TPM_RC_LOCKOUT          = RC_WARN + 0x021,
    ATHW_TPM_RC_RETRY            = RC_WARN + 0x022,
    ATHW_TPM_RC_NV_UNAVAILABLE   = RC_WARN + 0x023,
    RC_MAX_WARN             = RC_WARN + 0x03F,

    ATHW_TPM_RC_NOT_USED         = RC_WARN + 0x07F,

    ATHW_TPM_RC_H        = 0x000,
    ATHW_TPM_RC_P        = 0x040,
    ATHW_TPM_RC_S        = 0x800,
    ATHW_TPM_RC_1        = 0x100,
    ATHW_TPM_RC_2        = 0x200,
    ATHW_TPM_RC_3        = 0x300,
    ATHW_TPM_RC_4        = 0x400,
    ATHW_TPM_RC_5        = 0x500,
    ATHW_TPM_RC_6        = 0x600,
    ATHW_TPM_RC_7        = 0x700,
    ATHW_TPM_RC_8        = 0x800,
    ATHW_TPM_RC_9        = 0x900,
    ATHW_TPM_RC_A        = 0xA00,
    ATHW_TPM_RC_B        = 0xB00,
    ATHW_TPM_RC_C        = 0xC00,
    ATHW_TPM_RC_D        = 0xD00,
    ATHW_TPM_RC_E        = 0xE00,
    ATHW_TPM_RC_F        = 0xF00,
    ATHW_TPM_RC_N_MASK   = 0xF00,

    /* use negative codes for internal errors */
    ATHW_TPM_RC_TIMEOUT = -100,
} tpm_ret_t;

/* Errors from wolfssl/wolfcrypt/error-crypt.h */
#define BAD_MUTEX_E           -106  /* Bad mutex operation */
#define WC_TIMEOUT_E          -107  /* timeout error */
#define MEMORY_E              -125  /* out of memory error */
#define BUFFER_E              -132  /* output buffer too small or input too large */
#define BAD_FUNC_ARG          -173  /* Bad function argument provided */
#define NOT_COMPILED_IN       -174  /* Feature not compiled in */
#define LENGTH_ONLY_E         -202  /* Returning output length only */
#define INPUT_SIZE_E          -412  /* input size too big error */



#ifdef __cplusplus
}
#endif

#endif
