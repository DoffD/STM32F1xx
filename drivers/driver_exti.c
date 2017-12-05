/**
  ******************************************************************************
  * @file    driver_exti.c
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
#include "driver_exti.h"

// check IC
void (*EXTI_ISRs[EXTI_LINE_MAX + 1]) (void) = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// register level funciton prototypes start
//=========================================================
void Hal_EXTI_Line_Set(EXTI_Line_Type line, GPIO_Port_Type port);
void Hal_EXTI_Mask(EXTI_Line_Type line, Status_Type status);
void Hal_EXTI_Rising(EXTI_Line_Type line, Status_Type status);
void Hal_EXTI_Falling(EXTI_Line_Type line, Status_Type status);
void Hal_EXTI_Pending_Clear(EXTI_Line_Type line);
uint32_t Hal_EXTI_9to5_Pending_Get(void);
uint32_t Hal_EXTI_15to10_Pending_Get(void);
//=========================================================
// register level funciton prototypes end


void EXTI_Line_Set(EXTI_Line_Type line, GPIO_Port_Type port){
	Check_Param(IS_EXTI_LINE_VALID(line), TEST_EXTI_LINE);
	Check_Param(IS_GPIO_PORT_VALID(port), TEST_GPIO_PORT);
	Hal_EXTI_Line_Set(line, port);
}

void EXTI_Line_Config(EXTI_Line_Type line, Intr_Trig_Type trigger, void(*isr)(void)){
	Check_Param(IS_EXTI_LINE_VALID(line), TEST_EXTI_LINE);
	Check_Param(IS_INTR_TRIG_VALID(trigger), TEST_INTR_TRIG);
	if(isr == 0) Check_Param(0, TEST_INTR_ISR);

	if(trigger == INTR_EDGE_RISING){
		Hal_EXTI_Rising(line, STATUS_ENABLE);
		Hal_EXTI_Falling(line, STATUS_DISABLE);		
	}
	else if(trigger == INTR_EDGE_FALLING){
		Hal_EXTI_Falling(line, STATUS_ENABLE);
		Hal_EXTI_Rising	(line, STATUS_DISABLE);
	}
	else if(trigger == INTR_EDGE_RISING_FALLING){
		Hal_EXTI_Falling(line, STATUS_ENABLE);
		Hal_EXTI_Rising(line, STATUS_ENABLE);
	}
	EXTI_ISRs[line] = isr;
}

// check IC
IRQn_Type EXTI_IRQNs[EXTI_LINE_MAX + 1] = {
	EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn,	EXTI4_IRQn, 
	EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, 
	EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn
};

void EXTI_Line_Enable(EXTI_Line_Type line){
	Check_Param(IS_EXTI_LINE_VALID(line), TEST_EXTI_LINE);
	Hal_EXTI_Pending_Clear(line);
	Hal_EXTI_Mask(line, STATUS_ENABLE);
	NVIC_ClearPendingIRQ(EXTI_IRQNs[line]);
	NVIC_EnableIRQ(EXTI_IRQNs[line]);
}

void EXTI_Line_Clear(EXTI_Line_Type line){
	Check_Param(IS_EXTI_LINE_VALID(line), TEST_EXTI_LINE);
	NVIC_ClearPendingIRQ(EXTI_IRQNs[line]);
	Hal_EXTI_Pending_Clear(line);
}

void EXTI_Line_Disable(EXTI_Line_Type line){
	Check_Param(IS_EXTI_LINE_VALID(line), TEST_EXTI_LINE);
	NVIC_DisableIRQ(EXTI_IRQNs[line]);
	NVIC_ClearPendingIRQ(EXTI_IRQNs[line]);	
	Hal_EXTI_Mask(line, STATUS_DISABLE);
	Hal_EXTI_Pending_Clear(line);		
}

uint8_t EXTI_9to5_Pending_Get(void){	
	return (uint8_t)Hal_EXTI_9to5_Pending_Get();
}

uint8_t EXTI_15to10_Pending_Get(void){
	return (uint8_t)Hal_EXTI_15to10_Pending_Get();
}




/*=========================================================

=================== register level ===================

=========================================================*/





void Hal_EXTI_Line_Set(EXTI_Line_Type line, GPIO_Port_Type port){
	uint32_t offset = 4*(line % 4);
	uint32_t index = line / 4;
	AFIO->EXTICR[index] &= ~((uint32_t)0x0F << offset); // reset bits
	AFIO->EXTICR[index] |=  ((uint32_t)port << offset);
}

void Hal_EXTI_Mask(EXTI_Line_Type line, Status_Type status){
	if(status == STATUS_ENABLE)
		EXTI->IMR |=  ((uint32_t)0x01 << line);
	else
		EXTI->IMR &= ~((uint32_t)0x01 << line);
}

void Hal_EXTI_Rising(EXTI_Line_Type line, Status_Type status){
	if(status == STATUS_ENABLE)
		EXTI->RTSR |=  ((uint32_t)0x01 << line);
	else
		EXTI->RTSR &= ~((uint32_t)0x01 << line);
}

void Hal_EXTI_Falling(EXTI_Line_Type line, Status_Type status){
	if(status == STATUS_ENABLE)
		EXTI->FTSR |=  ((uint32_t)0x01 << line);
	else
		EXTI->FTSR &= ~((uint32_t)0x01 << line);
}

void Hal_EXTI_Pending_Clear(EXTI_Line_Type line){
	EXTI->PR |= ((uint32_t)0x01 << line);
}

// returns bits of pended lines
uint32_t Hal_EXTI_9to5_Pending_Get(void){
	uint32_t pendingLines = 0x00;
	if((EXTI->PR & 0x0020))	pendingLines |= 0x01; // line 5
	if((EXTI->PR & 0x0040))	pendingLines |= 0x02; // line 6
	if((EXTI->PR & 0x0080))	pendingLines |= 0x04; // line 7
	if((EXTI->PR & 0x0100))	pendingLines |= 0x08; // line 8
	if((EXTI->PR & 0x0200))	pendingLines |= 0x10; // line 9
	return pendingLines;
}

// returns bits of pended lines
uint32_t Hal_EXTI_15to10_Pending_Get(void){
	uint32_t pendingLines = 0x00;
	if((EXTI->PR & 0x0400))	pendingLines |= 0x01; // line 10
	if((EXTI->PR & 0x0800))	pendingLines |= 0x02; // line 11
	if((EXTI->PR & 0x1000))	pendingLines |= 0x04; // line 12
	if((EXTI->PR & 0x2000))	pendingLines |= 0x08; // line 13
	if((EXTI->PR & 0x4000))	pendingLines |= 0x10; // line 14
	if((EXTI->PR & 0x8000))	pendingLines |= 0x20; // line 15
	return pendingLines;
}
