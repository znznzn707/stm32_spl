#include "delay.h"
#include "misc.h"

static uint16_t  s_fac_us = 0;      //1us计数多少次

void delay_init(uint16_t sysclk)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    s_fac_us = sysclk / 8;
}


void delay_us(uint32_t nus)
{
    uint32_t temp ;
    SysTick->LOAD = nus * s_fac_us;  //重装载值
    SysTick->VAL = 0x00;            //清空计数器
    SysTick->CTRL |= ( 1 << 0);             //启动滴答计数器

    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));
    
    SysTick->CTRL &= ~(1 << 0);             //关闭滴答计数器
    SysTick->VAL = 0x00;            //清空计数器
}


void delay_ms(uint16_t nms)
{
    uint32_t repeat = nms / 1000; 
    uint32_t remain = nms % 1000;

    while (repeat)
    {
        delay_us(1000000);    //1s
        repeat--;
    }

    if (remain)
    {
        delay_us(remain * 1000);    
    }
}