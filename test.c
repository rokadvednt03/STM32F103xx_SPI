#include "stm32f103xx_spi.h"
#include "stm32f103xx_gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>


void GPIO_LED_ON(void);

int main(void)
{
	char rcvdata[50] ;
	uint8_t code = 0xF5;
	uint8_t dummy_data;
	uint8_t ack;
	
	GPIO_Handle_t gpio;
	SPI_Handle_t spi;
	gpio.pGPIOx = GPIOA;
	gpio.GPIO_PinConfig.GPIO_ModeInOut = GPIO_OUT_50MHZ;
	gpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN_OUT_PP;
	
	spi.pSPIx = SPI1;
	spi.spiconf.BaudRate = SPI_BRR_Fpclk_128;
	spi.spiconf.SlvManage = SPI_SlvManage_Hard;
	spi.spiconf.Mode = SPI_MODE_Master;
	
	GPIO_PeriClockControl(GPIOA,ENABLE);
	
	gpio.GPIO_PinConfig.GPIO_PinNumber = 4;
	GPIO_Init(&gpio);
	gpio.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&gpio);
	gpio.GPIO_PinConfig.GPIO_PinNumber = 7;
	GPIO_Init(&gpio);
	gpio.GPIO_PinConfig.GPIO_PinNumber = 6;
	/*gpio.GPIO_PinConfig.GPIO_ModeInOut = GPIO_IN ;
	gpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN_PUPD;*/
	GPIO_Init(&gpio);
	
	SPI_Init(&spi);
	SPI_Enable(SPI1);
	
	SPI_SendData(SPI1,&code,1);
	SPI_ReceiveData(SPI1,&dummy_data,1);
	dummy_data = 0xFF;
	SPI_SendData(SPI1,&dummy_data,1);
	SPI_ReceiveData(SPI1,&ack,1);
	
	if(ack == 0xF5)
	{
		GPIO_LED_ON();
	}
	
}

void GPIO_LED_ON(void)
{
	GPIO_Handle_t led;
	led.pGPIOx = GPIOC;
	led.GPIO_PinConfig.GPIO_ModeInOut = GPIO_OUT_10MHZ;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_PP;
	led.GPIO_PinConfig.GPIO_PinNumber = 13 ;
	GPIO_PeriClockControl(GPIOC,ENABLE);
	GPIO_Init(&led);
}

/*
int main(void)
{
	char data[] = "hello ivedant rokad here";
	uint8_t *pdata;
	unsigned int len;
	len = strlen(data);
	pdata = (uint8_t*)data;
	
	
	GPIO_Handle_t gpio;
	SPI_Handle_t spi;
	gpio.pGPIOx = GPIOA;
	gpio.GPIO_PinConfig.GPIO_ModeInOut = GPIO_OUT_50MHZ;
	gpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN_OUT_PP;
	
	spi.pSPIx = SPI1;
	spi.spiconf.BaudRate = SPI_BRR_Fpclk_128;
	spi.spiconf.SlvManage = SPI_SlvManage_Hard;
	spi.spiconf.Mode = SPI_MODE_Master;
	
	GPIO_PeriClockControl(GPIOA,ENABLE);
	
	gpio.GPIO_PinConfig.GPIO_PinNumber = 4;
	GPIO_Init(&gpio);
	gpio.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&gpio);
	gpio.GPIO_PinConfig.GPIO_PinNumber = 7;
	GPIO_Init(&gpio);
	
	SPI_Init(&spi);
	SPI_Enable(SPI1);
	
	SPI_SendData(SPI1,(uint8_t*)len,1);
	SPI_SendData(SPI1,pdata,*(uint8_t*)len);
	
}
*/
