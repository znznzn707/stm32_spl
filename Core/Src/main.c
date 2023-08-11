#include "led.h"

int main(void)
{
  LED_GPIO_Init();

  LED0_ON();
  LED1_ON();

  while (1)
  {
  }
  
}