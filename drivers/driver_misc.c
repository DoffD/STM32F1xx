/**
  ******************************************************************************
  * @file    driver_misc.c
  * @author  Doff Deponio
  * @version V1.00
  * @date    5-December-2017
  * @brief   This file contains functions to configure the SysTick timer.
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

#include "driver_misc.h"

volatile uint32_t millisTimer = 0;

// register level funciton prototypes start
//=========================================================
void Hal_SysTick_Clk_Src(SysTick_Clk_Src_Type clkSource);
void Hal_SysTick_Reload_Val(uint32_t reloadValue);
void Hal_SysTick_Clear(void);
void Hal_SysTick_Intr_Config(Status_Type status);
void Hal_SysTick_Status_Config(Status_Type status);
//=========================================================
// register level funciton prototypes end


void SysTick_Init(SysTick_Clk_Src_Type clkSource, uint32_t reloadValue){
  Check_Param(IS_SYSTICK_CLK_SRC_VALID(clkSource), TEST_SYSTICK_CLK_SRC); 
  if((reloadValue - (uint32_t)0x01) > 0x00FFFFFF) Check_Param(0, TEST_SYSTICK_RELOAD_VAL); 

  Hal_SysTick_Clk_Src(clkSource);
  Hal_SysTick_Reload_Val(reloadValue);
  Hal_SysTick_Clear();
  NVIC_ClearPendingIRQ(SysTick_IRQn);
  NVIC_EnableIRQ(SysTick_IRQn);
  //set interrupt priority here
  Hal_SysTick_Intr_Config(STATUS_ENABLE);  
  Hal_SysTick_Status_Config(STATUS_ENABLE);
}

uint32_t millis(void){
	return millisTimer;
}

//=================== register level ===================

void Hal_SysTick_Clk_Src(SysTick_Clk_Src_Type clkSource){
  if (clkSource == SYSTICK_CLK_SRC_HCLK)  
    SysTick->CTRL |= (uint32_t)0x04; 
  else  
    SysTick->CTRL &= ~((uint32_t)0x04); 
}

// specifies the reload value
void Hal_SysTick_Reload_Val(uint32_t reloadValue){
	SysTick->LOAD = reloadValue - (uint32_t)0x01;
}

void Hal_SysTick_Clear(){
	SysTick->VAL = (uint32_t)0x00;
}

void Hal_SysTick_Intr_Config(Status_Type status){
	if(status == STATUS_ENABLE)
		SysTick->CTRL |=  (uint32_t)0x02;
	else
		SysTick->CTRL &= ~((uint32_t)0x02);
}

void Hal_SysTick_Status_Config(Status_Type status){
	if(status == STATUS_ENABLE)
		SysTick->CTRL |=  (uint32_t)0x01;
	else
		SysTick->CTRL &= ~(uint32_t)0x01;
}


