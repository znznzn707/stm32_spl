/*
 * led.c
 *
 * PB5 LED0
 * PE5 LED1
 *  Created on: 2023年3月21日
 *      Author: znznzn707
 */
#include "led.h"
#include "stm32f10x_rcc.h"

void LED_GPIO_Init()
{
	GPIO_InitTypeDef gpio_init_struct;
	// 使能外设时钟 B E
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);

	// PB5
	gpio_init_struct.GPIO_Pin = LED0_GPIO_PIN;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);

	//PE5
	gpio_init_struct.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);

	// 初始PB5 PE5高电平，即灯灭
	LED0_OFF();
	LED1_OFF();
}
