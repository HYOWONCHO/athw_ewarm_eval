///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V9.50.1.380/W64 for ARM        12/Jan/2024  16:55:48
// Copyright 1999-2023 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\ATHW_EVAL_BSP\src\athw_tpm_spi.c
//    Command line =
//        -f
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\Debug\Obj\ATHW_EVAL_6662199345816623431.dir\athw_tpm_spi.o.rsp
//        (C:\workspace\ATHW_ETRI\athw_ewarm_eval\ATHW_EVAL_BSP\src\athw_tpm_spi.c
//        -D STM32L476xx -D USE_HAL_DRIVER -D USE_STM32L476G_EVAL_REVB -D
//        USE_IOEXPANDER -lC
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\Debug\List\ATHW_EVAL_6662199345816623431.dir
//        -lA
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\Debug\List\ATHW_EVAL_6662199345816623431.dir
//        -o
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\Debug\Obj\ATHW_EVAL_6662199345816623431.dir
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=VFPv4_sp --dlib_config "C:\Program Files\IAR
//        Systems\Embedded Workbench 9.2\arm\inc\c\DLib_Config_Full.h" -I
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\App\include\ -I
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\STM32-base-STM32Cube\CMSIS\ARM\inc\
//        -I
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\STM32-base-STM32Cube\CMSIS\STM32L4xx\inc\
//        -I
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\STM32-base-STM32Cube\HAL\STM32L4xx\inc\
//        -I C:\workspace\ATHW_ETRI\athw_ewarm_eval\util\inc\ -I
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\ATHW_EVAL_BSP\inc\ -On)
//        --dependencies=n
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\Debug\Obj\ATHW_EVAL_6662199345816623431.dir\athw_tpm_spi.o.iar_deps
//    Locale       =  C
//    List file    =
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\Debug\List\ATHW_EVAL_6662199345816623431.dir\athw_tpm_spi.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__CPP_Runtime", "1"
        RTMODEL "__SystemLibrary", "DLib"
        RTMODEL "__dlib_file_descriptor", "1"
        RTMODEL "__dlib_full_locale_support", "1"
        RTMODEL "__dlib_version", "6"
        RTMODEL "__iar_require _Printf", ""
        AAPCS BASE,INTERWORK,VFP
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        EXTERN HAL_GPIO_WritePin
        EXTERN HAL_SPI_TransmitReceive
        EXTERN printf

        PUBLIC athw_tpmiocb_spi
        
          CFI Names cfiNames0
          CFI StackFrame CFA R13 DATA
          CFI Resource R0:32, R1:32, R2:32, R3:32, R4:32, R5:32, R6:32, R7:32
          CFI Resource R8:32, R9:32, R10:32, R11:32, R12:32, R13:32, R14:32
          CFI Resource D0:64, D1:64, D2:64, D3:64, D4:64, D5:64, D6:64, D7:64
          CFI Resource D8:64, D9:64, D10:64, D11:64, D12:64, D13:64, D14:64
          CFI Resource D15:64
          CFI EndNames cfiNames0
        
          CFI Common cfiCommon0 Using cfiNames0
          CFI CodeAlign 2
          CFI DataAlign 4
          CFI ReturnAddress R14 CODE
          CFI CFA R13+0
          CFI R0 Undefined
          CFI R1 Undefined
          CFI R2 Undefined
          CFI R3 Undefined
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI R8 SameValue
          CFI R9 SameValue
          CFI R10 SameValue
          CFI R11 SameValue
          CFI R12 Undefined
          CFI R14 SameValue
          CFI D0 Undefined
          CFI D1 Undefined
          CFI D2 Undefined
          CFI D3 Undefined
          CFI D4 Undefined
          CFI D5 Undefined
          CFI D6 Undefined
          CFI D7 Undefined
          CFI D8 SameValue
          CFI D9 SameValue
          CFI D10 SameValue
          CFI D11 SameValue
          CFI D12 SameValue
          CFI D13 SameValue
          CFI D14 SameValue
          CFI D15 SameValue
          CFI EndCommon cfiCommon0
        
// C:\workspace\ATHW_ETRI\athw_ewarm_eval\ATHW_EVAL_BSP\src\athw_tpm_spi.c
//    1 /********************************************************************************
//    2  * Copyright (C) 2020 by Trustkey                                               * 
//    3  * This file is part of  Project                                                *   
//    4  * This software contains confidential information of TrustKey Co.,Ltd.         *
//    5  * and unauthorized distribution of this software, or any portion of it, are    *
//    6  * prohibited.                                                                  *
//    7  ********************************************************************************/
//    8 
//    9 /**
//   10  * @file athw_tpm_spi.c
//   11  * TPM SPI interface
//   12  *
//   13  * @anchor ANCHOR_SPI
//   14  * @author User, (c) Trustkey
//   15  * @version Draft 
//   16  * @date 011024
//   17  * @bug No known bugs.
//   18  * @note 
//   19  * 
//   20  * @copyright Copyright 2020 Trustkey. All rights reserved*
//   21  */         
//   22 
//   23 #include "athw_tpmio_types.h"
//   24 #include "athw_it_types.h"
//   25 #include "x_common.h"
//   26 

        SECTION `.text`:CODE:NOROOT(2)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function athw_tpmiocb_spi
        THUMB
//   27 int athw_tpmiocb_spi(void *handle) 
//   28 {
athw_tpmiocb_spi:
        PUSH     {R3-R11,LR}    
          CFI R14 Frame(CFA, -4)
          CFI R11 Frame(CFA, -8)
          CFI R10 Frame(CFA, -12)
          CFI R9 Frame(CFA, -16)
          CFI R8 Frame(CFA, -20)
          CFI R7 Frame(CFA, -24)
          CFI R6 Frame(CFA, -28)
          CFI R5 Frame(CFA, -32)
          CFI R4 Frame(CFA, -36)
          CFI CFA R13+40
        MOVS     R7,R0          
//   29 	int ret = EOK;
        MOVS     R8,#+0         
//   30 	SPI_HandleTypeDef *ctx = (SPI_HandleTypeDef *)(((spi_ioctx_t *)handle)->h_io);
        LDR      R4,[R7, #+4]   
//   31 	HAL_StatusTypeDef status;
//   32 	int timeout = TPM_SPI_WAIT_RETRY;
        MOVS     R9,#+50        
//   33 	
//   34 	uint8_t *txbuf = (uint8_t *)(((spi_ioctx_t *)handle)->ioctx.tx);
        LDR      R5,[R7, #+8]   
//   35 	uint8_t *rxbuf = (uint8_t *)(((spi_ioctx_t *)handle)->ioctx.tx); 
        LDR      R6,[R7, #+8]   
//   36 	uint16_t xfersz = (uint16_t)(((spi_ioctx_t *)handle)->ioctx.txlen);
        LDR      R10,[R7, #+12] 
//   37 
//   38 	X_RET_VAL_IF_FAIL((txbuf != NULL), ERRNGATE(ESNULLP));
        CMP      R5,#+0         
        BNE.N    ??athw_tpmiocb_spi_1
        LDR.N    R1,??athw_tpmiocb_spi_0
        LDR.N    R0,??athw_tpmiocb_spi_0+4
          CFI FunCall printf
        BL       printf         
        LDR.N    R0,??athw_tpmiocb_spi_0+8
        B.N      ??athw_tpmiocb_spi_2
//   39 	X_RET_VAL_IF_FAIL((rxbuf != NULL), ERRNGATE(ESNULLP)); 
??athw_tpmiocb_spi_1:
        CMP      R6,#+0         
        BNE.N    ??athw_tpmiocb_spi_3
        LDR.N    R1,??athw_tpmiocb_spi_0+12
        LDR.N    R0,??athw_tpmiocb_spi_0+4
          CFI FunCall printf
        BL       printf         
        LDR.N    R0,??athw_tpmiocb_spi_0+8
        B.N      ??athw_tpmiocb_spi_2
//   40 	X_RET_VAL_IF_FAIL((xfersz != 0), ERRNGATE(ESZEROL));
??athw_tpmiocb_spi_3:
        MOV      R0,R10         
        UXTH     R0,R0          
        CMP      R0,#+0         
        BNE.N    ??athw_tpmiocb_spi_4
        LDR.N    R1,??athw_tpmiocb_spi_0+16
        LDR.N    R0,??athw_tpmiocb_spi_0+4
          CFI FunCall printf
        BL       printf         
        MVNS     R0,#+400       
        B.N      ??athw_tpmiocb_spi_2
//   41 
//   42 	if(ctx == NULL) {
??athw_tpmiocb_spi_4:
        CMP      R4,#+0         
        BNE.N    ??athw_tpmiocb_spi_5
//   43 		ret = ERRNGATE(ESNULLP);
        LDR.N    R0,??athw_tpmiocb_spi_0+8
        MOV      R8,R0          
//   44 		goto errdone;
        B.N      ??athw_tpmiocb_spi_6
//   45 	}
//   46 
//   47 	__HAL_SPI_ENABLE(ctx);
??athw_tpmiocb_spi_5:
        LDR      R0,[R4, #+0]   
        LDR      R1,[R0, #+0]   
        ORRS     R1,R1,#0x40    
        LDR      R0,[R4, #+0]   
        STR      R1,[R0, #+0]   
//   48 
//   49 
//   50 	// To SPI start, CS goes active low
//   51 	HAL_GPIO_WritePin(TPM_SPI_CS_PORT, TPM_SPI_CS_PIN, GPIO_PIN_RESET);
        MOVS     R2,#+0         
        MOVS     R1,#+16        
        MOVS     R0,#+1207959552
          CFI FunCall HAL_GPIO_WritePin
        BL       HAL_GPIO_WritePin
//   52 
//   53 	status = HAL_SPI_TransmitReceive(ctx, txbuf, rxbuf, TPM_TIS_HEADER_SZ, TPM_SPI_TIMEOUT);
        MOVS     R0,#+250       
        STR      R0,[SP, #+0]   
        MOVS     R3,#+4         
        MOVS     R2,R6          
        MOVS     R1,R5          
        MOVS     R0,R4          
          CFI FunCall HAL_SPI_TransmitReceive
        BL       HAL_SPI_TransmitReceive
        MOV      R11,R0         
//   54 	if(status != HAL_OK) {
        MOV      R0,R11         
        UXTB     R0,R0          
        CMP      R0,#+0         
        BEQ.N    ??athw_tpmiocb_spi_7
//   55 		ret = ERRNGATE(EIOFAIL);
        LDR.N    R0,??athw_tpmiocb_spi_0+20
        MOV      R8,R0          
//   56 		goto errdone;
        B.N      ??athw_tpmiocb_spi_6
//   57 	}
//   58 
//   59 
//   60 	//  check for wait status
//   61 	if((rxbuf[TPM_TIS_HEADER_SZ - 1] && TPM_TIS_READY_MASK) == 0) {
??athw_tpmiocb_spi_7:
        LDRB     R0,[R6, #+3]   
        CMP      R0,#+0         
        BEQ.N    ??athw_tpmiocb_spi_8
        MOVS     R0,#+1         
        B.N      ??athw_tpmiocb_spi_9
??athw_tpmiocb_spi_8:
        MOVS     R0,#+0         
??athw_tpmiocb_spi_9:
        UXTB     R0,R0          
        CMP      R0,#+0         
        BNE.N    ??athw_tpmiocb_spi_10
//   62 		do {
//   63 			// Check ready
//   64 			status = HAL_SPI_TransmitReceive(ctx, txbuf, rxbuf, 1, TPM_SPI_TIMEOUT);
??athw_tpmiocb_spi_11:
        MOVS     R0,#+250       
        STR      R0,[SP, #+0]   
        MOVS     R3,#+1         
        MOVS     R2,R6          
        MOVS     R1,R5          
        MOVS     R0,R4          
          CFI FunCall HAL_SPI_TransmitReceive
        BL       HAL_SPI_TransmitReceive
        MOV      R11,R0         
//   65 			if(rxbuf[0] & TPM_TIS_READY_MASK) {
        LDRB     R0,[R6, #+0]   
        LSLS     R0,R0,#+31     
        BMI.N    ??athw_tpmiocb_spi_10
//   66 				break;
//   67 			}
//   68 		} while(status == HAL_OK && --timeout > 0);
??athw_tpmiocb_spi_12:
        MOV      R0,R11         
        UXTB     R0,R0          
        CMP      R0,#+0         
        BNE.N    ??athw_tpmiocb_spi_10
        SUBS     R9,R9,#+1      
        CMP      R9,#+1         
        BGE.N    ??athw_tpmiocb_spi_11
//   69 	}
//   70 #if defined(ATHW_TPM_SPI_DEBUG) || defined(ATHW_DEBUG_ALL)
//   71 	printf(" spi ready wait is %d \r\n", TPM_SPI_WAIT_RETRY - timeout);
//   72 #endif
//   73 
//   74 	if(timeout <= 0) {
??athw_tpmiocb_spi_10:
        CMP      R9,#+1         
        BGE.N    ??athw_tpmiocb_spi_13
//   75 		ret = ERRNGATE(EIOTIMEOUT);
        MVNS     R0,#+800       
        MOV      R8,R0          
//   76 		goto errdone;
        B.N      ??athw_tpmiocb_spi_6
//   77 	}
//   78 
//   79 	// send reminder payload 
//   80 	status = HAL_SPI_TransmitReceive(ctx, 
//   81 									 &txbuf[TPM_TIS_HEADER_SZ], 
//   82 									 &rxbuf[TPM_TIS_HEADER_SZ], 
//   83 									 xfersz - TPM_TIS_HEADER_SZ,
//   84 									 TPM_SPI_TIMEOUT);
??athw_tpmiocb_spi_13:
        MOVS     R0,#+250       
        STR      R0,[SP, #+0]   
        SUBS     R3,R10,#+4     
        UXTH     R3,R3          
        ADDS     R2,R6,#+4      
        ADDS     R1,R5,#+4      
        MOVS     R0,R4          
          CFI FunCall HAL_SPI_TransmitReceive
        BL       HAL_SPI_TransmitReceive
        MOV      R11,R0         
//   85 
//   86 
//   87 
//   88 	if(status != HAL_OK) {
        MOV      R0,R11         
        UXTB     R0,R0          
        CMP      R0,#+0         
        BEQ.N    ??athw_tpmiocb_spi_6
//   89 		ret = ERRNGATE(EIOFAIL);
        LDR.N    R0,??athw_tpmiocb_spi_0+20
        MOV      R8,R0          
//   90 	}
//   91 
//   92 errdone:
//   93 
//   94 #if defined(ATHW_TPM_SPI_DEBUG) || defined(ATHW_DEBUG_ALL)
//   95 	printf("ret code : %d , xfer : %d, status : 0x%x \n", ret, xfersz, status);
//   96 #endif
//   97 
//   98 	// To SPI stop, CS goes active high
//   99 	HAL_GPIO_WritePin(TPM_SPI_CS_PORT, TPM_SPI_CS_PIN, GPIO_PIN_SET);
??athw_tpmiocb_spi_6:
        MOVS     R2,#+1         
        MOVS     R1,#+16        
        MOVS     R0,#+1207959552
          CFI FunCall HAL_GPIO_WritePin
        BL       HAL_GPIO_WritePin
//  100 	__HAL_SPI_DISABLE(ctx);
        LDR      R0,[R4, #+0]   
        LDR      R1,[R0, #+0]   
        BICS     R1,R1,#0x40    
        LDR      R0,[R4, #+0]   
        STR      R1,[R0, #+0]   
//  101 	return ret;
        MOV      R0,R8          
??athw_tpmiocb_spi_2:
        POP      {R1,R4-R11,PC} 
        Nop                     
        DATA
??athw_tpmiocb_spi_0:
        DATA32
        DC32     ?_1            
        DC32     ?_0            
        DC32     0xfffffe70     
        DC32     ?_2            
        DC32     ?_3            
        DC32     0xfffffce0     
//  102 
//  103 }
          CFI EndBlock cfiBlock0

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
?_0:
        DATA8
        DC8 "'%s' FAILED."
        DATA
        DS8 3

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
?_1:
        DATA8
        DC8 "(txbuf != NULL)"

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
?_2:
        DATA8
        DC8 "(rxbuf != NULL)"

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
?_3:
        DATA8
        DC8 "(xfersz != 0)"
        DATA16
        DS8 2

        END
//  104 
//  105 
//  106 
//  107 
//  108 
// 
//  64 bytes in section .rodata
// 308 bytes in section .text
// 
// 308 bytes of CODE  memory
//  64 bytes of CONST memory
//
//Errors: none
//Warnings: none
