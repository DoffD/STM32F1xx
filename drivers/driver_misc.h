/**
  ******************************************************************************
  * @file    driver_misc.h
  * @author  Doff Deponio
  * @version V1.00
  * @date    5-December-2017
  * @brief   This file contains prototypes for miscellaneous functions.
  ******************************************************************************
  * @attention
  * Copyright 2017 Doff Deponio

  * Permission is hereby granted, free of charge, to any person obtaining a copy 
  * of this software and associated documentation files (the "Software"), to deal 
  * in the Software without restriction, including without limitation the rights 
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
  * copies of the Software, and to permit persons to whom the Software is 
  * furnished to do so, subject to the following conditions:

  * The above copyright notice and this permission notice shall be included in 
  * all copies or substantial portions of the Software.

  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
  * SOFTWARE.
  *
  ******************************************************************************
  */ 

#ifndef DRIVER_MISC_H
#define DRIVER_MISC_H

#include "stm32f10x.h"
#include "driver_config.h"

typedef enum {
	SYSTICK_CLK_SRC_HCLK_DIV8,
	SYSTICK_CLK_SRC_HCLK
} SysTick_Clk_Src_Type;
#define IS_SYSTICK_CLK_SRC_VALID(SOURCE) (((SOURCE) == SYSTICK_CLK_SRC_HCLK_DIV8) || \
                                       ((SOURCE) == SYSTICK_CLK_SRC_HCLK))

void SysTick_Init(SysTick_Clk_Src_Type clkSource, uint32_t reloadValue);
uint32_t millis(void);
#endif
