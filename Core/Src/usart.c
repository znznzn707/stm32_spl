#include <stdio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_dma.h>
#include "usart.h"

/*
int _read(int fd, char *ptr, int len)
{

}*/

//gcc 重定向
int _write(int fd, char *pBuffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        while((USART_UX->SR & 0X40) == 0);        /* 等待上一个字符发送完成，即等待TC标志置1 */
        USART_UX->DR = (uint8_t) pBuffer[i];       //写DR,串口1将发送数据
    }
    return size;
}

static void usart_rcc_config()
{
    USART_TX_GPIO_CLK_ENABLE();
    USART_RX_GPIO_CLK_ENABLE();
    USART_UX_CLK_ENABLE();
}

static void usart_gpio_config()
{
    GPIO_InitTypeDef gpio_init_struct;
    
    gpio_init_struct.GPIO_Pin = USART_TX_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_TX_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.GPIO_Pin = USART_RX_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART_RX_GPIO_PORT, &gpio_init_struct);
}

static void usart_config(uint32_t baudrate)
{
    USART_InitTypeDef usart_init_struct;

    usart_init_struct.USART_BaudRate = baudrate;
    usart_init_struct.USART_WordLength = USART_WordLength_8b;
    usart_init_struct.USART_StopBits = USART_StopBits_1;
    usart_init_struct.USART_Parity = USART_Parity_No;
    usart_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART_UX, &usart_init_struct);

    USART_ITConfig(USART_UX, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART_UX, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART_UX, USART_IT_IDLE, DISABLE);
}

void usart_init(uint32_t baudrate)
{
    usart_rcc_config();
    usart_gpio_config();
    usart_config(baudrate);
    
    USART_Cmd(USART_UX, ENABLE);
}

