#ifndef USART_H_
#define USART_H_

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

#define USART_TX_GPIO_PORT                  GPIOA
#define USART_TX_GPIO_PIN                   GPIO_Pin_9
#define USART_TX_GPIO_CLK_ENABLE()          RCC->APB2ENR |= 1 << 2  //IO端口A时钟使能

#define USART_RX_GPIO_PORT                  GPIOA
#define USART_RX_GPIO_PIN                   GPIO_Pin_10
#define USART_RX_GPIO_CLK_ENABLE()          RCC->APB2ENR |= 1 << 2  //IO端口A时钟使能

#define USART_UX                            USART1
#define USART_UX_IRQn                       USART1_IRQn
#define USART_UX_IRQHandler                 USART1_IRQHandler
#define USART_UX_CLK_ENABLE()               RCC->APB2ENR |= 1 << 14  //IO端口USART1时钟使能


void usart_init(uint32_t baudrate);

#endif // !USART_H_