#ifndef _ATHW_EVAL_IT_H
#define _ATHW_EVAL_IT_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * ATHW Interface handle structure
 * 
 * @author User (1/9/2024)
 */
typedef struct _athw_it_handle_t {
	UART_HandleTypeDef	*h_debguart;		/**< Serial & Debugf UART interface*/
	SPI_HandleTypeDef 	*h_hostspi;		 	/**< TPM SPI Master interface */
	SPI_HandleTypeDef 	*h_tpmspi;			/**< Host SPI Slave interface*/
}athw_if_handle_t;

#ifdef __cplusplus
}
#endif
#endif
