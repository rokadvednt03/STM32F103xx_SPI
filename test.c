#include "stm32f103xx_spi.h"
#include "stm32f103xx_gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
