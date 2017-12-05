/**
  ******************************************************************************
  * @file    driver_rcc.c
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
#include "driver_rcc.h"



// register level funciton prototypes start
//=========================================================
void Hal_RCC_Clock_Set(GPIO_Port_Type port, Status_Type status);

//=========================================================
// register level funciton prototypes end


void RCC_Clock_Enable(GPIO_Port_Type port){
	Check_Param(IS_GPIO_PORT_VALID(port), TEST_GPIO_PORT);
	Hal_RCC_Clock_Set(port, STATUS_ENABLE);
}
/*
#define gpio_Clock_Enable(PORT);	(Check_Param(IS_GPIO_PORT_VALID(PORT));\
									 Hal_Gpio_ClockSet(PORT, STATUS_ENABLE);)
*/
void RCC_Clock_Disable(GPIO_Port_Type port){
	Check_Param(IS_GPIO_PORT_VALID(port), TEST_GPIO_PORT);
	Hal_RCC_Clock_Set(port, STATUS_DISABLE);
}





/*=========================================================

=================== register level ===================

=========================================================*/





#if defined (STM32F10X_LD) || defined (STM32F10X_LD_VL)
uint32_t RCC_APB2ENR_GPIO_BitDefs[GPIO_PORT_MAX + 1] = {
	RCC_APB2ENR_IOPAEN,
	RCC_APB2ENR_IOPBEN,
	RCC_APB2ENR_IOPCEN,
	RCC_APB2ENR_IOPDEN
};

#elif defined (STM32F10X_HD) || defined (STM32F10X_XL) || defined (STM32F10X_HD_VL)
uint32_t RCC_APB2ENR_GPIO_BitDefs[GPIO_PORT_MAX + 1] = {
	RCC_APB2ENR_IOPAEN,
	RCC_APB2ENR_IOPBEN,
	RCC_APB2ENR_IOPCEN,
	RCC_APB2ENR_IOPDEN,
	RCC_APB2ENR_IOPEEN,
	RCC_APB2ENR_IOPFEN,
	RCC_APB2ENR_IOPGEN
};

#else
uint32_t RCC_APB2ENR_GPIO_BitDefs[GPIO_PORT_MAX + 1] = {
	RCC_APB2ENR_IOPAEN,
	RCC_APB2ENR_IOPBEN,
	RCC_APB2ENR_IOPCEN,
	RCC_APB2ENR_IOPDEN,
	RCC_APB2ENR_IOPEEN
};
#endif /* defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) */

void Hal_RCC_Clock_Set(GPIO_Port_Type port, Status_Type status){
	if(status == STATUS_DISABLE)
		RCC->APB2ENR &= ~RCC_APB2ENR_GPIO_BitDefs[port];
	else if(status == STATUS_ENABLE)
		RCC->APB2ENR |= RCC_APB2ENR_GPIO_BitDefs[port];
}
