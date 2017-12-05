/**
  ******************************************************************************
  * @file    driver_gpio.c
  * @author  Doff Deponio
  * @version V1.00
  * @date    5-December-2017
  * @brief   This file contains functions for configuring and using the GPIO
  * peripheral.
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

#include "driver_gpio.h"

// check IC for the number of available GPIO ports
#if defined (STM32F10X_LD) || defined (STM32F10X_LD_VL)
GPIO_TypeDef* PortPointers[GPIO_PORT_MAX + 1] = {GPIOA, GPIOB, GPIOC, GPIOD};
#elif defined (STM32F10X_HD) || defined (STM32F10X_XL) || defined (STM32F10X_HD_VL)
GPIO_TypeDef* PortPointers[GPIO_PORT_MAX + 1] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG};
#else
GPIO_TypeDef* PortPointers[GPIO_PORT_MAX + 1] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};
#endif /* defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) */


// register level funciton prototypes start
//=========================================================
void Hal_GPIO_Pin_Mode(GPIO_TypeDef* Portx, GPIO_Pin_Type pin, uint32_t modeBits);
void Hal_GPIO_Pin_Config(GPIO_TypeDef* Portx, GPIO_Pin_Type pin, uint32_t configBits);
void Hal_GPIO_Pin_Write(GPIO_TypeDef* Portx, GPIO_Pin_Type pin, uint32_t value);
uint32_t Hal_GPIO_Pin_Read(GPIO_TypeDef* Portx, GPIO_Pin_Type pin);
void Hal_GPIO_Bus_Write(GPIO_TypeDef* Portx, uint32_t value);
uint32_t Hal_GPIO_Bus_Read(GPIO_TypeDef* Portx);
void Hal_GPIO_Pin_ODR_Set(GPIO_TypeDef* Portx, GPIO_Pin_Type pin, uint32_t value);
uint32_t Hal_GPIO_Pin_Is_Output(GPIO_TypeDef* Portx, GPIO_Pin_Type pin);
//=========================================================
// register level funciton prototypes end


void GPIO_Pin_Mode(GPIO_Port_Type port, GPIO_Pin_Type pin, GPIO_Mode_Type mode, GPIO_Config_Type config){
	uint32_t modeBits;
	uint32_t configBits;
	
	Check_Param(IS_GPIO_PORT_VALID(port), TEST_GPIO_PORT);	
	Check_Param(IS_GPIO_PIN_VALID(pin), TEST_GPIO_PIN);	
	Check_Param(IS_GPIO_MODE_VALID(mode), TEST_GPIO_MODE);
	Check_Param(IS_GPIO_CONFIG_VALID(config), TEST_GPIO_CONFIG);

	if(mode == GPIO_MODE_INPUT)	
		Check_Param(IS_GPIO_INPUT_CONFIG_VALID(config), TEST_GPIO_INPUT_CONFIG);
	else if(mode == GPIO_MODE_OUTPUT)
		Check_Param(IS_GPIO_OUTPUT_CONFIG_VALID(config), TEST_GPIO_OUTPUT_CONFIG);
	else if(mode == GPIO_MODE_ALTERNATE)
		Check_Param(IS_GPIO_ALT_CONFIG_VALID(config), TEST_GPIO_ALT_CONFIG);
	

	if(mode == GPIO_MODE_INPUT){
		modeBits = 0;
		switch(config){
			case GPIO_CNFG_INPUT_FLOATING:
				configBits = 1;
				break;
			case GPIO_CNFG_INPUT_PULL_UP:
				configBits = 2;
				Hal_GPIO_Pin_ODR_Set(PortPointers[port], pin, 1);
				break;
			case GPIO_CNFG_INPUT_PULL_DOWN:
				configBits = 2;
				Hal_GPIO_Pin_ODR_Set(PortPointers[port], pin, 0);
				break;
			case GPIO_CNFG_INPUT_ANALOG:
				configBits = 0;
				break;
			default:
				break;
		}
	}
	else if(mode == GPIO_MODE_OUTPUT){
		modeBits = 2;
		switch(config){
			case GPIO_CNFG_OUTPUT_OPEN_DRAIN:
				configBits = 1;
				break;
			case GPIO_CNFG_OUTPUT_PUSH_PULL:
				configBits = 0;
				break;
			default:
				break;
		}
	}
	else if(mode == GPIO_MODE_ALTERNATE){
		modeBits = 2;
		switch(config){
			case GPIO_CNFG_ALTERNATE_OPEN_DRAIN:
				configBits = 1;
				break;
			case GPIO_CNFG_ALTERNATE_PUSH_PULL:
				configBits = 0;
				break;
			default:
				break;
		}
	}
	Hal_GPIO_Pin_Mode(PortPointers[port], pin, modeBits);
	Hal_GPIO_Pin_Config(PortPointers[port], pin, configBits);
}

void GPIO_Pin_Speed(GPIO_Port_Type port, GPIO_Pin_Type pin, GPIO_Output_Speed_Type speed){
	uint32_t modeBits;
	Check_Param(IS_GPIO_PORT_VALID(port), TEST_GPIO_PORT);
	Check_Param(IS_GPIO_PIN_VALID(pin), TEST_GPIO_PIN);
	Check_Param(IS_GPIO_OUTPUT_SPEED_VALID(speed), TEST_GPIO_OUTPUT_SPEED);

	if(Hal_GPIO_Pin_Is_Output(PortPointers[port], pin) == 0) Check_Param(0, TEST_GPIO_STATE_OUTPUT);

	switch(speed){
		case GPIO_OUTPUT_SPEED_2_MHZ:
			modeBits = 0x02;
			break;
		case GPIO_OUTPUT_SPEED_10_MHZ:			
			modeBits = 0x01;
			break;
		case GPIO_OUTPUT_SPEED_50_MHZ:			
			modeBits = 0x03;
			break;
		default:
			break;	
	}
	Hal_GPIO_Pin_Mode(PortPointers[port], pin, modeBits);
}

uint8_t GPIO_Pin_Read(GPIO_Port_Type port, GPIO_Pin_Type pin){
	Check_Param(IS_GPIO_PORT_VALID(port), TEST_GPIO_PORT);
	Check_Param(IS_GPIO_PIN_VALID(pin), TEST_GPIO_PIN);
	return (uint8_t)Hal_GPIO_Pin_Read(PortPointers[port], pin);
}

void GPIO_Pin_Write(GPIO_Port_Type port, GPIO_Pin_Type pin, uint8_t value){
	Check_Param(IS_GPIO_PORT_VALID(port), TEST_GPIO_PORT);
	Check_Param(IS_GPIO_PIN_VALID(pin), TEST_GPIO_PIN);
	Hal_GPIO_Pin_Write(PortPointers[port], pin, (uint32_t)value);
}

uint16_t GPIO_Bus_Read(GPIO_Port_Type port){
	Check_Param(IS_GPIO_PORT_VALID(port), TEST_GPIO_PORT);
	return (uint16_t)Hal_GPIO_Bus_Read(PortPointers[port]);
}

void GPIO_Bus_Write(GPIO_Port_Type port, uint16_t value){
	Check_Param(IS_GPIO_PORT_VALID(port), TEST_GPIO_PORT);
	Hal_GPIO_Bus_Write(PortPointers[port], (uint32_t)value);
}




/*=========================================================

=================== register level ===================

=========================================================*/





void Hal_GPIO_Pin_Mode(GPIO_TypeDef* Portx, GPIO_Pin_Type pin, uint32_t modeBits){
	if(pin < 8){
		Portx->CRL &= ~((uint32_t)0x03 << 4*pin); // reset bits
		Portx->CRL |=  (modeBits << 4*pin);
	}
	else if(pin >= 8){
		pin -= 8;
		Portx->CRH &= ~((uint32_t)0x03 << 4*pin); // reset bits
		Portx->CRH |=  (modeBits << 4*pin);
	}
}

void Hal_GPIO_Pin_Config(GPIO_TypeDef* Portx, GPIO_Pin_Type pin, uint32_t configBits){
	if(pin < 8){
		Portx->CRL &= ~((uint32_t)0x03 << (4*pin + 2)); // reset bits
		Portx->CRL |=  (configBits << (4*pin + 2));
	}
	else if(pin >= 8){
		pin -= 8;
		Portx->CRH &= ~((uint32_t)0x03 << (4*pin + 2)); // reset bits
		Portx->CRH |=  (configBits << (4*pin + 2));
	}
}

void Hal_GPIO_Pin_Write(GPIO_TypeDef* Portx, GPIO_Pin_Type pin, uint32_t value){
	if(value)
		Portx->BSRR = ((uint32_t)0x01 << pin);
	else
		Portx->BRR  = ((uint32_t)0x01 << pin);
}

uint32_t Hal_GPIO_Pin_Read(GPIO_TypeDef* Portx, GPIO_Pin_Type pin){
	return ((Portx->IDR >> pin) & 0x01);
}

void Hal_GPIO_Bus_Write(GPIO_TypeDef* Portx, uint32_t value){
	Portx->ODR = value;
}

uint32_t Hal_GPIO_Bus_Read(GPIO_TypeDef* Portx){
	return Portx->IDR;
}

void Hal_GPIO_Pin_ODR_Set(GPIO_TypeDef* Portx, GPIO_Pin_Type pin, uint32_t value){
	if(value)
		Portx->ODR |=  ((uint32_t)0x01 << pin);
	else
		Portx->ODR &= ~((uint32_t)0x01 << pin);		
}

uint32_t Hal_GPIO_Pin_Is_Output(GPIO_TypeDef* Portx, GPIO_Pin_Type pin){
	uint32_t configRegValue;
	if(pin < 8)
		configRegValue = Portx->CRL;
	else if(pin >= 8){
		pin -= 8;
		configRegValue = Portx->CRH;
	}
	configRegValue = (configRegValue >> 4*pin) & 0x03;
	return configRegValue ? 1 : 0;
}
