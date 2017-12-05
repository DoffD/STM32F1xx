/**
  ******************************************************************************
  * @file    driver_gpio.h
  * @author  Doff Deponio
  * @version V1.00
  * @date    5-December-2017
  * @brief   This file contains prototypes of functions for configuring 
  *	and using the GPIO peripheral.
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

#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

//#include <stdint.h>
#include "stm32f10x.h"
#include "driver_config.h"

#if defined (STM32F10X_LD) || defined (STM32F10X_LD_VL)
typedef enum{
	GPIO_PORT_A,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_MAX = GPIO_PORT_D // change accordingly (not all ICs have the same number of ports)
} GPIO_Port_Type;

#elif defined (STM32F10X_HD) || defined (STM32F10X_XL) || defined (STM32F10X_HD_VL)
typedef enum{
	GPIO_PORT_A,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_E,
	GPIO_PORT_F,
	GPIO_PORT_G,	
	GPIO_PORT_MAX = GPIO_PORT_G // change accordingly (not all ICs have the same number of ports)
} GPIO_Port_Type;

#else
typedef enum{
	GPIO_PORT_A,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_E,
	GPIO_PORT_MAX = GPIO_PORT_E // change accordingly (not all ICs have the same number of ports)
} GPIO_Port_Type;
#endif /* defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) */
#define IS_GPIO_PORT_VALID(PORT) (((PORT) >= GPIO_PORT_A) && ((PORT) <= GPIO_PORT_MAX))

typedef enum{
	GPIO_PIN_0,	
	GPIO_PIN_1,
	GPIO_PIN_2,	
	GPIO_PIN_3,
	GPIO_PIN_4,	
	GPIO_PIN_5,
	GPIO_PIN_6,	
	GPIO_PIN_7,	
	GPIO_PIN_8,	
	GPIO_PIN_9,
	GPIO_PIN_10,	
	GPIO_PIN_11,
	GPIO_PIN_12,	
	GPIO_PIN_13,
	GPIO_PIN_14,	
	GPIO_PIN_15,
	GPIO_PIN_MAX = GPIO_PIN_15
} GPIO_Pin_Type;
#define IS_GPIO_PIN_VALID(PIN) (((PIN) >= GPIO_PIN_0) && ((PIN) <= GPIO_PIN_MAX))


typedef enum{
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_ALTERNATE
} GPIO_Mode_Type;
#define IS_GPIO_MODE_VALID(MODE) (((MODE) >= GPIO_MODE_INPUT) && ((MODE) <= GPIO_MODE_ALTERNATE))

typedef enum{
	GPIO_CNFG_INPUT_FLOATING,
	GPIO_CNFG_INPUT_PULL_UP,
	GPIO_CNFG_INPUT_PULL_DOWN,
	GPIO_CNFG_INPUT_ANALOG,

	GPIO_CNFG_OUTPUT_OPEN_DRAIN,
	GPIO_CNFG_OUTPUT_PUSH_PULL,

	GPIO_CNFG_ALTERNATE_OPEN_DRAIN,
	GPIO_CNFG_ALTERNATE_PUSH_PULL
} GPIO_Config_Type;
#define IS_GPIO_CONFIG_VALID(CONFIG) (((CONFIG) >= GPIO_CNFG_INPUT_FLOATING) && ((CONFIG) <= GPIO_CNFG_ALTERNATE_PUSH_PULL))

#define IS_GPIO_INPUT_CONFIG_VALID(CONFIG) (((CONFIG) >= GPIO_CNFG_INPUT_FLOATING) && ((CONFIG) <= GPIO_CNFG_INPUT_ANALOG))
#define IS_GPIO_OUTPUT_CONFIG_VALID(CONFIG) (((CONFIG) == GPIO_CNFG_OUTPUT_OPEN_DRAIN) || ((CONFIG) == GPIO_CNFG_OUTPUT_PUSH_PULL))
#define IS_GPIO_ALT_CONFIG_VALID(CONFIG) (((CONFIG) == GPIO_CNFG_ALTERNATE_OPEN_DRAIN) || ((CONFIG) == GPIO_CNFG_ALTERNATE_PUSH_PULL))

typedef enum{
	GPIO_OUTPUT_SPEED_2_MHZ,
	GPIO_OUTPUT_SPEED_10_MHZ,
	GPIO_OUTPUT_SPEED_50_MHZ
} GPIO_Output_Speed_Type;
#define IS_GPIO_OUTPUT_SPEED_VALID(SPEED) (((SPEED) >= GPIO_OUTPUT_SPEED_2_MHZ) && ((SPEED) <= GPIO_OUTPUT_SPEED_50_MHZ))

// typedef enum{
// 	STATUS_DISABLE,
// 	STATUS_ENABLE
// } Status_Type;


void GPIO_Pin_Mode(GPIO_Port_Type port, GPIO_Pin_Type pin, GPIO_Mode_Type mode, GPIO_Config_Type config);
void GPIO_Pin_Speed(GPIO_Port_Type port, GPIO_Pin_Type pin, GPIO_Output_Speed_Type speed);
uint8_t GPIO_Pin_Read(GPIO_Port_Type port, GPIO_Pin_Type pin);
void GPIO_Pin_Write(GPIO_Port_Type port, GPIO_Pin_Type pin, uint8_t value);
uint16_t GPIO_Bus_Read(GPIO_Port_Type port);
void GPIO_Bus_Write(GPIO_Port_Type port, uint16_t value);

#endif
