/**************************************************************************
 ** 创建日期：  2012-11-2                                                 *
 ** 文件名  ：  isr.h                                                     *
 ** 版本    ：	                                                          *
 ** 平台    ：  羽良工作室MK60DN512ZVLQ10最小系统板                       *
 ** 函数列表：	                                                          *
 ** 功能描述：  中断服务函数重新定义                                      *          
 ** 创建者  ：  羽良工作室 yullion.taobao.com                                                *
 ** 修改历史：                                                            *
 ** @版权所有： 羽良工作室 yullion.taobao.com                                               *
 ** 淘宝店：    yullion.taobao.com                                        *
 **************************************************************************/

/*******************************************************************************************
欢迎光临淘宝店  羽良工作室  yullion.taobao.com
K60淘宝链接     http://item.taobao.com/item.htm?spm=a1z10.1.w4.18.rMwvaU&id=21039172293
********************************************************************************************/

#ifndef __ISR_H
#define __ISR_H 1

#include  "include.h"

/***************************重新定义中断向量表**********************************
 *  先取消默认的中断向量元素宏定义       #undef  VECTOR_xxx
 *  在重新定义到自己编写的中断函数       #define VECTOR_xxx    xxx_IRQHandler
 *  例如：
 *       #undef  VECTOR_003
 *       #define VECTOR_003    HardFault_Handler    重新定义硬件上访中断服务函数
 *
 *       extren void  HardFault_Handler(void);      声明函数，然后在isr.c里定义
 *******************************************************************************/

//#undef  VECTOR_020
//#define VECTOR_020    DMA_CH4_Handler

#undef  VECTOR_084
#define VECTOR_084    PIT0_IRQHandler     //重新定义84号中断为PIT0_IRQHandler中断


/********************************************************************************/
//#undef  VECTOR_103
//#define VECTOR_103    PORTA_IRQHandler    //重新定义103号中断为PORTA_IRQHandler中断

//#undef  VECTOR_104
//#define VECTOR_104    PORTB_IRQHandler    //重新定义104号中断为PORTB_IRQHandler中断  
//#define TIAOSHI                           //供串口调试用，不用串口调试时注释掉本语句即可


//////////////////////////////////////////////////////////////////////////////////////////
//void  DMA_CH4_Handler(); 
void  PIT0_IRQHandler(); 
//void  PORTA_IRQHandler(); 
//void  PORTB_IRQHandler (); 
#endif

