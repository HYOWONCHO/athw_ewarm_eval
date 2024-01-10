#include "main.h"

#include <stdio.h>
#include <string.h>

extern void error_handler(void *priv);
static UART_HandleTypeDef dbguart;

int _write(int32_t file, uint8_t *ptr, int32_t len) 
{
    (void)file;

    if( HAL_UART_Transmit(&dbguart, ptr, len, 0xFFFF) == HAL_OK )
        return len;
    else
        return 0;

    //return HAL_UART_Transmit(&huart1, ptr, len, 0xFFFF);
}


int _read (int fd, char *ptr, int len)
{
    /* Read "len" of char to "ptr" from file id "fd"
    * Return number of char read.
    * Need implementing with UART here. */
    (void)fd;

    return HAL_UART_Receive(&dbguart, (uint8_t*)ptr, len, 0xFFFF);
}

void _ttywrch(int ch) {
    /* Write one char "ch" to the default console
    * Need implementing with UART here. */
    _write(0, (uint8_t *)&ch, 1);
}

int main(void)
{ 
    int ret = 0;
    //UART_HandleTypeDef	debguart;		/**< Serial & Debugf UART interface*/
    SPI_HandleTypeDef 	hostspi;		 	/**< TPM SPI Master interface */
    SPI_HandleTypeDef 	tpmspi;	
    athw_if_handle_t ifhnd = {
        .h_debuguart = &dbguart,
        .h_hostspi = &hostspi,
        .h_tpmspi = &tpmspi
    };



    x_memzero(ifhnd.h_debuguart, sizeof dbguart);
    x_memzero(ifhnd.h_hostspi, sizeof hostspi);
    x_memzero(ifhnd.h_tpmspi, sizeof tpmspi);




    ret = athw_eval_it_init((void *)&ifhnd);
    if( ret != EOK ) {
        error_handler(NULL);
    }

    do {
    } while (1);

    return 0;      
}