#ifndef _athw_tpm2_types_h
#define _athw_tpm2_types_h

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __GNUC__
#include <fetures.h>
#endif

#include <stdint.h>

/**
 * Performs a left circular arthmetic shift of x by y value
 * 
 * @author hyowon.cho (2024-03-25)
 * 
 * @param x      
 * @param y      
 * 
 * @return uint32_t 
 */
static inline uint32_t rotleft_fixed(uint32_t x, uint32_t y) {
	return (x << y) | (x >> (sizeof(y) * 8 - y));
}

static inline uint32_t rotright_fixed(uint32_t x, uint32_t y) {
	return (x >> y) | (x << (sizeof(y) * 8 - y));
}

static inline uint16_t _byte_swap_16(uint16_t value) {
#if defined(__ICCARM__)
	return (uint16_t)__REV16(value);
#elif defined(__GNUC_PREREQ) && __GNUC_PREREQ(4, 3) 
	return (uint16_t)__builtin_bswap16(value);
#else
	return (value >> 8) | (value << 8);
#endif
}

static inline uint32_t _byte_swap_32(uint32_t value) {
#if defined(__ICCARM__)
	return (uint16_t)__REV32(value);
#elif defined(__GNUC_PREREQ) && __GNUC_PREREQ(4, 3)
	return (uint32_t)__builtin_bswap32(value);
#elif define(FAST_ROTATE)
	return (rotright_fixed(value, 8U) & 0xff00ff00) |
		   (rotleft_fixed(value, 8U) & 0x00ff00ff);
#else
	value = ((value & 0xFF00FF00) >> 8) | ((value & 0x00FF00FF) << 8);
	return rotleft_fixed(value, 16U);
#endif
}


#ifdef __cplusplus
}
#endif

#endif
