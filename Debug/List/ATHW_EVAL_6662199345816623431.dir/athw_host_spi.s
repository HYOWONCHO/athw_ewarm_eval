///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V9.50.1.380/W64 for ARM        12/Jan/2024  16:56:25
// Copyright 1999-2023 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\ATHW_EVAL_BSP\src\athw_host_spi.c
//    Command line =
//        -f
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\Debug\Obj\ATHW_EVAL_6662199345816623431.dir\athw_host_spi.o.rsp
//        (C:\workspace\ATHW_ETRI\athw_ewarm_eval\ATHW_EVAL_BSP\src\athw_host_spi.c
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
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\Debug\Obj\ATHW_EVAL_6662199345816623431.dir\athw_host_spi.o.iar_deps
//    Locale       =  C
//    List file    =
//        C:\workspace\ATHW_ETRI\athw_ewarm_eval\Debug\List\ATHW_EVAL_6662199345816623431.dir\athw_host_spi.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__CPP_Runtime", "1"
        RTMODEL "__SystemLibrary", "DLib"
        AAPCS BASE,INTERWORK,VFP
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        EXTERN HAL_DMA_IRQHandler

        PUBLIC DMA1_Channel2_IRQHandler
        
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
        
// C:\workspace\ATHW_ETRI\athw_ewarm_eval\ATHW_EVAL_BSP\src\athw_host_spi.c
//    1 /********************************************************************************
//    2  * Copyright (C) 2020 by Trustkey                                               * 
//    3  * This file is part of  Project                                                *   
//    4  * This software contains confidential information of TrustKey Co.,Ltd.         *
//    5  * and unauthorized distribution of this software, or any portion of it, are    *
//    6  * prohibited.                                                                  *
//    7  ********************************************************************************/
//    8 
//    9 /**
//   10  * @file athw_host_spi.c
//   11  * HOST command processing
//   12  *
//   13  * @anchor ANCHOR_SPI
//   14  * @author User, (c) Trustkey
//   15  * @version Draft 
//   16  * @date 011224
//   17  * @bug No known bugs.
//   18  * @note 
//   19  * 
//   20  * @copyright Copyright 2020 Trustkey. All rights reserved*
//   21  */         
//   22 
//   23 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function DMA1_Channel2_IRQHandler
        THUMB
//   24 void DMA1_Channel2_IRQHandler(void) 
//   25 {
DMA1_Channel2_IRQHandler:
        PUSH     {R7,LR}        
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//   26 	HAL_DMA_IRQHandler();
          CFI FunCall HAL_DMA_IRQHandler
        BL       HAL_DMA_IRQHandler
//   27 }
        POP      {R0,PC}        
          CFI EndBlock cfiBlock0

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//   28 
//   29 
//   30 
//   31 
// 
// 8 bytes in section .text
// 
// 8 bytes of CODE memory
//
//Errors: none
//Warnings: 1
