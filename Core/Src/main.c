#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "sdio_sdcard.h"

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

static void sdcard_task()
{
  SD_CardInfo sdcard_info;
  sdio_sdcard_init(&sdcard_info);
  while (1)
  {
    printf("ManufacturerID=%u\r\n", sdcard_info.SD_cid.ManufacturerID);
    printf("ManufactDate=%u\r\n", sdcard_info.SD_cid.ManufactDate);
    printf("ProdSN=%u\r\n", sdcard_info.SD_cid.ProdSN);
    printf("OEM_AppliID=%u\r\n", sdcard_info.SD_cid.OEM_AppliID);
    printf("CardCapacity=%u\r\n", sdcard_info.CardCapacity);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  
}
int main(void)
{
  LED_GPIO_Init();
//  delay_init(72);
  usart_init(115200);

  // xTaskCreate(led0_task, "led0_task", 128, NULL, 1, NULL);
  // xTaskCreate(led1_task, "led1_task", 128, NULL, 1, NULL);
  xTaskCreate(sdcard_task, "sdcard_task", 128, NULL, 1, NULL);
  vTaskStartScheduler();
}