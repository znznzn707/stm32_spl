#ifndef SDIO_SDCARD_H_
#define SDIO_SDCARD_H_

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32_eval_sdio_sd.h>

#define SD_D0_GPIO_PORT                GPIOC
#define SD_D0_GPIO_PIN                 GPIO_Pin_8
#define SD_D0_GPIO_CLK_ENABLE()        RCC->APB2ENR |= 1 << 4

#define SD_D1_GPIO_PORT                GPIOC
#define SD_D1_GPIO_PIN                 GPIO_Pin_9
#define SD_D1_GPIO_CLK_ENABLE()        RCC->APB2ENR |= 1 << 4

#define SD_D2_GPIO_PORT                GPIOC
#define SD_D2_GPIO_PIN                 GPIO_Pin_10
#define SD_D2_GPIO_CLK_ENABLE()        RCC->APB2ENR |= 1 << 4

#define SD_D3_GPIO_PORT                GPIOC
#define SD_D3_GPIO_PIN                 GPIO_Pin_11
#define SD_D3_GPIO_CLK_ENABLE()        RCC->APB2ENR |= 1 << 4

#define SD_CLK_GPIO_PORT                GPIOC
#define SD_CLK_GPIO_PIN                 GPIO_Pin_12
#define SD_CLK_GPIO_CLK_ENABLE()        RCC->APB2ENR |= 1 << 4

#define SD_CMD_GPIO_PORT                GPIOD
#define SD_CMD_GPIO_PIN                 GPIO_Pin_2
#define SD_CMD_GPIO_CLK_ENABLE()        RCC->APB2ENR |= 1 << 5

/*
 * SDIOCLK = HCLK, SDIO_CK = HCLK/(2 + SDIO_TRANSFER_CLK_DIV) 
 * 72MHZ /( 2 + 1 ) = 25MHz
 */
#define SDIO_TRANSFER_CLK_DIV           0x1

SD_Error sdio_sdcard_init(SD_CardInfo *cardinfo);

#endif // !SDIO_SDCARD_H_
