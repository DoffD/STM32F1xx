/**
  ******************************************************************************
  * @file    IRQHandlers.c
  * @author  Doff Deponio
  * @version V1.00
  * @date    5-December-2017
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
#include "IRQHandlers.h"

void EXTI0_IRQHandler(void)
{	
	EXTI_Line_Clear(EXTI_LINE_0);
	if((*EXTI_ISRs[0]))	(*EXTI_ISRs[0])();
}

void EXTI1_IRQHandler(void)
{
	EXTI_Line_Clear(EXTI_LINE_1);
	if((*EXTI_ISRs[1]))	(*EXTI_ISRs[1])();
}

void EXTI2_IRQHandler(void)
{
	EXTI_Line_Clear(EXTI_LINE_2);
	if((*EXTI_ISRs[2]))	(*EXTI_ISRs[2])();
}

void EXTI3_IRQHandler(void)
{
	EXTI_Line_Clear(EXTI_LINE_3);
	if((*EXTI_ISRs[3]))	(*EXTI_ISRs[3])();
}

void EXTI4_IRQHandler(void)
{
	EXTI_Line_Clear(EXTI_LINE_4);
	if((*EXTI_ISRs[4]))	(*EXTI_ISRs[4])();
}

void EXTI9_5_IRQHandler(void)
{		
	uint8_t lines = EXTI_9to5_Pending_Get(); 
	uint8_t line = 0x00;
	uint8_t mask = 0x01;
	uint8_t i;
	for(i = 0; i < 5; i++){
		line = lines & (mask << i);
		if(line){
			EXTI_Line_Clear((EXTI_Line_Type)(i + 5));
			if((*EXTI_ISRs[i + 5]))	(*EXTI_ISRs[i + 5])();
		}
	}
}

void EXTI15_10_IRQHandler(void)
{
	uint8_t lines = EXTI_15to10_Pending_Get(); 
	uint8_t line = 0x00;
	uint8_t mask = 0x01;
	uint8_t i;
	for(i = 0; i < 6; i++){
		line = lines & (mask << i);
		if(line){
			EXTI_Line_Clear((EXTI_Line_Type)(i + 10));
			if((*EXTI_ISRs[i + 10])) (*EXTI_ISRs[i + 10])();
		}
	}
}

void SysTick_Handler(void){
	millisTimer++;
}
