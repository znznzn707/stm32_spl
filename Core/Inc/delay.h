#ifndef DELAY_H_
#define DELAY_H_

#include "stm32f10x.h"

void delay_init(uint16_t sysclk);

void delay_ms(uint16_t nms);       

void delay_us(uint32_t nus);       


#endif // !DELAY_H_
