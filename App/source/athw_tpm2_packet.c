#include "ahtw_tpm2_packet.h"

#ifdef _LITTLE_ENDIAN_ORDER_
	#define cpu_to_be16(d) _uint8_t_swap_16(d)
	#define cpu_to_be32(d) _uint8_t_swap_32(d)
	#define be16_to_cpu(d) _uint8_t_swap_16(d)
	#define be32_to_cpu(d) _uint8_t_swap_32(d)
#else
	#define cpu_to_be16(d) (d)
	#define cpu_to_be32(d) (d)
	#define cpu_to_be64(d) (d)
	#define be16_to_cpu(d) (d)
	#define be32_to_cpu(d) (d)
	#define be64_to_cpu(d) (d)
#endif

/* convert 16 bit integer to opaque */
static inline void _c16toa(uint16_t wc_u16, uint8_t *c) {
    c[0] = (wc_u16 >> 8) & 0xff;
    c[1] =  wc_u16 & 0xff;
}
/* convert 32 bit integer to opaque */
static inline void _c32toa(uint32_t wc_u32, uint8_t *c) {
    c[0] = (wc_u32 >> 24) & 0xff;
    c[1] = (wc_u32 >> 16) & 0xff;
    c[2] = (wc_u32 >>  8) & 0xff;
    c[3] =  wc_u32 & 0xff;
}

void TPM2_Packet_U16Touint8_tArray(uint16_t val, uint8_t *b)
{
    if (b) _c16toa(val, b);
}

void TPM2_Packet_U32Touint8_tArray(uint32_t val, uint8_t *b) 
{
    if (b) _c32toa(val, b);
}

uint16_t TPM2_Packet_SwapU16(uint16_t data) 
{
    return cpu_to_be16(data);
}

uint32_t TPM2_Packet_SwapU32(uint32_t data) 
{
    return cpu_to_be32(data);
}

UINT64 TPM2_Packet_SwapU64(UINT64 data)
{
    return cpu_to_be64(data);
}

void 
