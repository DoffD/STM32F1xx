/**
  ******************************************************************************
  * @file    driver_config.h
  * @author  Doff Deponio
  * @version V1.00
  * @date    5-December-2017
  * @brief   This file contans common universal enumerations and define
  * statements for enabling and disabling parameter error handling.
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

#ifndef _DRIVER_CONF_H
#define _DRIVER_CONF_H

typedef enum{
	STATUS_DISABLE = 0,
	STATUS_ENABLE =!STATUS_DISABLE
} Status_Type;

#define ENABLE_PARAMETERS_ERROR_HANDLING


#ifdef ENABLE_PARAMETERS_ERROR_HANDLING
	typedef enum{
		TEST_GPIO_PORT = 0x00,
		TEST_GPIO_PIN = 0x01,
		TEST_GPIO_MODE = 0x02,
		TEST_GPIO_CONFIG = 0x03,
		TEST_GPIO_INPUT_CONFIG = 0x04,
		TEST_GPIO_OUTPUT_CONFIG = 0x05,
		TEST_GPIO_ALT_CONFIG = 0x06,
		TEST_GPIO_OUTPUT_SPEED = 0x07,
		TEST_GPIO_STATE_OUTPUT = 0x08,

		TEST_INTR_TRIG = 0x09,
		TEST_INTR_ISR = 0x0A,
		
		TEST_EXTI_LINE = 0x0B,

		TEST_SYSTICK_CLK_SRC = 0x0C,
		TEST_SYSTICK_RELOAD_VAL = 0x0D

	} Test_Type;
	
	void Param_Failed(uint8_t* file, uint32_t line, Test_Type TEST_TYPE);
	#define Check_Param(CONDITION, TEST_TYPE) ((CONDITION) ? (void)0 : Param_Failed((uint8_t*)__FILE__, __LINE__, TEST_TYPE))	
	
#else
	#define Check_Param(CONDITION, TEST_TYPE) ((CONDITION) ? (void)0 : return)
#endif	/* ENABLE_PARAMETERS_ERROR_HANDLING */
#endif	/* _DRIVER_CONF_H */
