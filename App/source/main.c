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

extern void _pkt_proc_suspend_tick(void);
extern void _pkt_proc_resume_tick(void);
extern uint8_t spi_rx_end;
extern int rxcnt; 
extern uint8_t rxbuf[64];
extern uint8_t is_timbegin;
static uint32_t gn_starttick; 


int main(void)
{
    extern int athw_pkt_proc_init(void *priv);
    extern uint32_t SystemCoreClock;
    int ret = 0;
    //UART_HandleTypeDef	debguart;		/**< Serial & Debugf UART interface*/
    SPI_HandleTypeDef 	hostspi;		 	/**< TPM SPI Master interface */
    SPI_HandleTypeDef 	tpmspi;	
    athw_if_handle_t ifhnd = {
        .h_debuguart = &dbguart,
        .h_hostspi = &hostspi,
        .h_tpmspi = &tpmspi
    };

    
    
    uint8_t rxdata = 0;


    x_memzero(ifhnd.h_debuguart, sizeof dbguart);
    x_memzero(ifhnd.h_hostspi, sizeof hostspi);
   // x_memzero(ifhnd.h_tpmspi, sizeof tpmspi);


    // ATHW Device peripheral and low device setting
    ret = athw_eval_it_init((void *)&ifhnd);
    if( ret != EOK ) {
        error_handler(NULL);
    }

    printf("System Core Clock : %d Hz \r\n", SystemCoreClock);

    ret = athw_pkt_proc_init((void *)&ifhnd);
    if( ret != EOK ) {
        printf("Packet proc initialization fail !!! \r\n");
        error_handler(NULL);
    }

    do {
#if 1
        ret = HAL_SPI_Receive(ifhnd.h_hostspi, &rxdata, 1, 0xFFFFFFFF);
        switch( ret ) {
        case HAL_OK:
            //printf("0x%x ", rxbuf[0]);
            rxbuf[rxcnt++] = rxdata;
            //if( !is_timbegin  ) {
            _pkt_proc_resume_tick();
                //gn_starttick = HAL_GetTick();
                //is_timbegin = 1;
            //}

            //rxcnt++;
//
//          if( spi_rx_end == 1 ) {
//             //_pkt_proc_suspend_tick();
//              spi_rx_end = 0;
//              is_timbegin = 0;
//              _pkt_proc_suspend_tick();
//              //printf("Tim Tick Period : %d sec \r\n", (HAL_GetTick() - gn_starttick) / 1000);
//              x_mem_print_bin("incoming", rxbuf, rxcnt);
//
//              rxcnt = 0;
//          }

            //printf("rx : 0x%x \r\n", rxbuf[0]);
            //x_mem_print_bin("incoming", rxbuf, 12);
            break; 
        case HAL_ERROR:
            printf("SPI RX HAL ERROR \r\n");
            //x_mem_print_bin("error", rxbuf, 12);;
            break; 
        case HAL_BUSY:
            printf("SPI BUSY \r\n");
            break; 
        case HAL_TIMEOUT:\
            printf("SPI Timeout \r\n");
            break;
        default:
            printf("Unknown Error : %d \r\n", ret);
            break;
        }

#endif
    } while (1);

    //return 0;      
}