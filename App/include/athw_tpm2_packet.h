#ifndef _athw_tpm2_packet_h
#define _athw_tpm2_packet_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "athw_tpm2_types.h"

#define ATHW_TPM2_HEADER_SZ 		10

typedef struct _tlv_t {
	uint16_t tag;
	uint32_t length;
	uint8_t  value[1];
}tlv_t;

/**
 * @brief TAG and Length structure
 * @val tag
 * @val length
 * 
 * @author hyowon.cho (2024-03-25)
 */
typedef struct _tl_t {
	uint16_t tag;		/*! TAG*/
	uint32_t length;	/*! Length */
}tl_t; 


typedef struct _athw_tpm2_header_t {
	tl_t 	tl;
	union {
		uint32_t code;
		uint32_t cc;
		int32_t  rc;
	};
}athw_tpm2_header_t;

typedef struct _athw_tpm2pkt_t {
	uint8_t *buf;
	int32_t  pos;
	int32_t  size;
}athw_tpm2pkt_t;


#ifdef __cplusplus
}
#endif
#endif
