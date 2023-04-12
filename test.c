#include "stm32f103xx_gpio.h"
#include "stm32f103xx_spi.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	GPIO_Handle_t gpio;
		char a[] = "hello this SPI communication" ;
	uint8_t len ;
	uint8_t *data;
	len = sizeof(a);
	data = (uint8_t*)a;

	gpio.pGPIOx = GPIOA ;
	gpio.GPIO_PinConfig.GPIO_ModeInOut = GPIO_OUT_50MHZ;
	gpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN_OUT_PP ;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIO_PeriClockControl(GPIOA,ENABLE);
	
	gpio.GPIO_PinConfig.GPIO_PinNumber = 5 ;
	GPIO_Init(&gpio);

	gpio.GPIO_PinConfig.GPIO_PinNumber = 7 ;
	GPIO_Init(&gpio);
	
	gpio.GPIO_PinConfig.GPIO_PinNumber = 4 ;
	GPIO_Init(&gpio);
	
	GPIOC->CRH |= (1<<20);
	GPIOC->CRH |= (1<<21);
	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	
	SPI1->CR1 |= SPI_CR1_SSM;
	SPI1->CR1 |= (7<<3);
	SPI1->CR1 |= SPI_CR1_SSI;
	SPI1->CR1 |= SPI_CR1_MSTR;
	SPI1->CR1 |= SPI_CR1_SPE;
	
	while(len>0)
	{
		while(!(SPI1->SR & SPI_SR_TXE));
		SPI1->DR = *data;
		data++;
		len--;
	}

}


