#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include "usart.h"
#include "delay.h"
#include "led.h"

static void led0_task()
{
  while (1)
  {
    vTaskDelay(pdMS_TO_TICKS(250));
    LED0_ON();
    vTaskDelay(pdMS_TO_TICKS(250));
    LED0_OFF();
  }
  
}

static void led1_task()
{
  while (1)
  {
    LED1_ON();
    vTaskDelay(pdMS_TO_TICKS(250));
    LED1_OFF();
    vTaskDelay(pdMS_TO_TICKS(250));
  }
  
}
int main(void)
{
  LED_GPIO_Init();
//  delay_init(72);
  usart_init(115200);

  xTaskCreate(led0_task, "led0_task", 128, NULL, 1, NULL);
  xTaskCreate(led1_task, "led1_task", 128, NULL, 1, NULL);
  vTaskStartScheduler();
}