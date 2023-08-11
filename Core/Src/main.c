#include <stdio.h>
#include "usart.h"
#include "delay.h"
#include "led.h"

int main(void)
{
  LED_GPIO_Init();
  delay_init(72);
  usart_init(115200);
  uint8_t temp_int = 27, temp_dec = 6;

  while (1)
  {
    delay_ms(100);
    printf("温度：%d.%d\r\n", temp_int, temp_dec);
  }
}