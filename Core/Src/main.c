#include "delay.h"
#include "led.h"


int main(void)
{
  LED_GPIO_Init();
  delay_init(72);

  while (1)
  {
    delay_ms(50);
    LED0_OFF();
    LED1_ON();
    delay_ms(50);
    LED0_ON();
    LED1_OFF();
  }
}