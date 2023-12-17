#include "sdio_sdcard.h"

static void sdio_sdcard_rcc_config()
{
    SD_D0_GPIO_CLK_ENABLE();
    SD_D1_GPIO_CLK_ENABLE();
    SD_D2_GPIO_CLK_ENABLE();
    SD_D3_GPIO_CLK_ENABLE();
    SD_CLK_GPIO_CLK_ENABLE();
    SD_CMD_GPIO_CLK_ENABLE();
}

static void sdio_sdcard_gpio_config()
{
    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    
    //D0
    gpio_init_struct.GPIO_Pin = SD_D0_GPIO_PIN;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SD_D0_GPIO_PORT, &gpio_init_struct);

    //D1
    gpio_init_struct.GPIO_Pin = SD_D1_GPIO_PIN;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SD_D1_GPIO_PORT, &gpio_init_struct);


    //D2
    gpio_init_struct.GPIO_Pin = SD_D2_GPIO_PIN;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SD_D2_GPIO_PORT, &gpio_init_struct);

    //D3
    gpio_init_struct.GPIO_Pin = SD_D3_GPIO_PIN;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SD_D3_GPIO_PORT, &gpio_init_struct);
    
    //CLK
    gpio_init_struct.GPIO_Pin = SD_CLK_GPIO_PIN;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SD_CLK_GPIO_PORT, &gpio_init_struct);
    
    /*!< Configure PD.02 CMD line */
    gpio_init_struct.GPIO_Pin = SD_CMD_GPIO_PIN;
    GPIO_Init(SD_CMD_GPIO_PORT, &gpio_init_struct);
}



SD_Error sdio_sdcard_init(SD_CardInfo *cardinfo)
{
    SD_Error error_status = SD_ERROR;
    SDIO_InitTypeDef sdio_init_struct;

    sdio_sdcard_rcc_config();
    sdio_sdcard_gpio_config();
    
    SDIO_DeInit();
    
    SD_LowLevel_Init();

    error_status = SD_PowerON();  /*上电并进行卡识别流程，确认卡的操作电压  */
    if(error_status != SD_OK)
    {
        return error_status;
    }

    error_status = SD_InitializeCards();   /*卡识别成功，进行卡初始化    */
    if(error_status != SD_OK)
    {
        return error_status;
    }

    sdio_init_struct.SDIO_BusWide = SDIO_BusWide_1b;       //1bit
    //不使用 bypass 模式，直接用 HCLK 进行分频得到 SDIO_CK
    sdio_init_struct.SDIO_ClockBypass = SDIO_ClockBypass_Disable; 
    /* SDIOCLK = HCLK, SDIO_CK = HCLK/(2 + SDIO_TRANSFER_CLK_DIV) */
    sdio_init_struct.SDIO_ClockDiv = SDIO_TRANSFER_CLK_DIV;  
    sdio_init_struct.SDIO_ClockEdge = SDIO_ClockEdge_Rising; //上升沿
    /* 若开启此功能，在总线空闲时关闭sd_clk时钟 */
    sdio_init_struct.SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
	/* 硬件流，若开启，在FIFO不能进行发送和接收数据时，数据传输暂停 */
    sdio_init_struct.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
    SDIO_Init(&sdio_init_struct);

    if (error_status == SD_OK)
    {
        error_status = SD_GetCardInfo(cardinfo);
    }
    if (error_status == SD_OK)
    {
        error_status = SD_SelectDeselect((uint32_t)(cardinfo->RCA << 16));
    }
    if (error_status == SD_OK)
    {
        error_status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
    }
    return error_status;
}