#ifndef __ATHW_TPM_IO_H
#define __ATHW_TPM_IO_H

#ifdef _cplusplus
extern "C"
{
#endif

typedef struct _t_tpmio_lv {
	int len;			/*! Transfer or Received length of data*/
	void *value;		/*! Byte stream for Transfer or Receiving */
}tpmio_lv_t;

typedef struct _t_tpmio_ctx {
	void *handle;			/*! TPM IO Handle */
	tpmio_lv_t *txlv;
	tpmio_lv_t *rxlv;

}tpmio_ctx_t;

#ifdef _cplusplus
}
#endif



#endif
