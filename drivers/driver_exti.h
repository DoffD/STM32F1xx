/**
  ******************************************************************************
  * @file    driver_exti.h
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

#ifndef DRIVER_EXTI_H
#define DRIVER_EXTI_H

//#include <stdint.h>
#include "stm32f10x.h"
#include "driver_config.h"
#include "driver_gpio.h"

typedef enum{
	INTR_EDGE_RISING,
	INTR_EDGE_FALLING,
	INTR_EDGE_RISING_FALLING
} Intr_Trig_Type;
#define IS_INTR_TRIG_VALID(TRIG) (((TRIG) >= INTR_EDGE_RISING) && ((TRIG) <= INTR_EDGE_RISING_FALLING))

typedef enum{
	EXTI_LINE_0 = 0x00,
	EXTI_LINE_1,
	EXTI_LINE_2,
	EXTI_LINE_3,
	EXTI_LINE_4,
	EXTI_LINE_5,
	EXTI_LINE_6,
	EXTI_LINE_7,
	EXTI_LINE_8,
	EXTI_LINE_9,
	EXTI_LINE_10,
	EXTI_LINE_11,
	EXTI_LINE_12,
	EXTI_LINE_13,
	EXTI_LINE_14,
	EXTI_LINE_15,
	EXTI_LINE_MAX = EXTI_LINE_15
} EXTI_Line_Type;
#define IS_EXTI_LINE_VALID(LINE) (((LINE) >= EXTI_LINE_0) && ((LINE) <= EXTI_LINE_MAX))


void EXTI_Line_Set(EXTI_Line_Type line, GPIO_Port_Type port);
void EXTI_Line_Config(EXTI_Line_Type line, Intr_Trig_Type trigger, void(*isr)(void));
void EXTI_Line_Enable(EXTI_Line_Type line);
void EXTI_Line_Clear(EXTI_Line_Type line);
void EXTI_Line_Disable(EXTI_Line_Type line);
uint8_t EXTI_9to5_Pending_Get(void);
uint8_t EXTI_15to10_Pending_Get(void);

#endif
