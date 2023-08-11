/*
 * led.h
 *
 *  Created on: 2023年3月21日
 *      Author: znznzn707
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define LED0_GPIO_PORT          GPIOB
#define LED1_GPIO_PORT          GPIOE

#define LED0_GPIO_PIN           GPIO_Pin_5
#define LED1_GPIO_PIN           GPIO_Pin_5

#define LED0_ON()              (GPIO_ResetBits(LED0_GPIO_PORT, LED0_GPIO_PIN))
#define LED0_OFF()             (GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIO_PIN))

#define LED1_ON()              (GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN))
#define LED1_OFF()             (GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN))


void LED_GPIO_Init();

#endif /* LED_H_ */
