#include "main.h"

#include <stdio.h>
#include <string.h>

extern void error_handler(void *priv);
static UART_HandleTypeDef dbguart;

#ifdef __GNUC__
/* With GCC/RAISONANCE, small msg_info (option LD Linker->Libraries->Small msg_info
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
    //(void)f;
    // place your implementation of futpc here
    while( HAL_UART_Transmit(&dbguart, (uint8_t *)&ch, 1, 30000) != HAL_OK) {
        ;
    }

    return ch;
}

GETCHAR_PROTOTYPE
{
    //(void)f;
    uint8_t ch = 0;
    while( HAL_UART_Receive(&dbguart, (uint8_t *)&ch, 1, 30000) != HAL_OK) {
        ;
    }

    return ch;
}

#if 0
int __io_putchar(int ch) 
{
    uint8_t c[1];
    c[0] = ch & 0x00FF;


    HAL_UART_Transmit(&dbguart, &*c, 1, 10);
    return ch;
}

int _write(int32_t file, uint8_t *ptr, int32_t len) 
{
    (void)file;

    int idx;

    for( idx = 0; idx < len; idx++ ) {
        __io_putchar(*ptr++);
    }

    return len;

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
#endif

int main(void)
{
    extern uint32_t SystemCoreClock;
    int ret = 0;
    //UART_HandleTypeDef	debguart;		/**< Serial & Debugf UART interface*/
    SPI_HandleTypeDef 	hostspi;		 	/**< TPM SPI Master interface */
    SPI_HandleTypeDef 	tpmspi;	
    athw_if_handle_t ifhnd = {
        .h_debuguart = &dbguart,
        .h_hostspi = &hostspi,
        //.h_tpmspi = &tpmspi
    };



    x_memzero(ifhnd.h_debuguart, sizeof dbguart);
    x_memzero(ifhnd.h_hostspi, sizeof hostspi);
   // x_memzero(ifhnd.h_tpmspi, sizeof tpmspi);


    // ATHW Device peripheral and low device setting
    ret = athw_eval_it_init((void *)&ifhnd);
    if( ret != EOK ) {
        error_handler(NULL);
    }

    printf("System Core Clock : %d Hz \r\n", SystemCoreClock);

    athw_pkt_proc_init();

    do {
    } while (1);

    //return 0;      
}