/**
  ******************************************************************************
  * @file    		stm32f103xx_i2c.h
  * @author  		Vedant A. Rokad
  * @processor 	ARM Cortex-M3
	* @controller STM32F103C8T8
  * @date    		26-Feb-2022
  * @brief   		Device_Driver Header file
  ******************************************************************************
 **/
 
#include "stm32f103xx_spi.h"


void SPI_PeriClockControl(SPI_TypeDef *pSPIx , uint32_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
				RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
		else if(pSPIx == SPI2)
				RCC->APB2ENR |= RCC_APB1ENR_SPI2EN;
	}
	else
	{
		if(pSPIx == SPI1)
				RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
		else if(pSPIx == SPI2)
				RCC->APB2ENR &= ~RCC_APB1ENR_SPI2EN;
	}
}

void SPI_Init(SPI_Handle_t *pSPIHandler)
{
	SPI_PeriClockControl(pSPIHandler->pSPIx,ENABLE);
	pSPIHandler->pSPIx->CR1 |= (pSPIHandler->spiconf.BaudRate << 3);
	
	if(pSPIHandler->spiconf.SlvManage == SPI_SlvManage_Soft)
	{
		pSPIHandler->pSPIx->CR1 |= SPI_CR1_SSI;
		pSPIHandler->pSPIx->CR1 |= SPI_CR1_SSM;
	}
	else
	{
		pSPIHandler->pSPIx->CR1 &= ~SPI_CR1_SSM;
		pSPIHandler->pSPIx->CR2 |= SPI_CR2_SSOE;
	}
	
	if(pSPIHandler->spiconf.Mode == SPI_MODE_Master)
		pSPIHandler->pSPIx->CR1 |= SPI_CR1_MSTR;
	else
		pSPIHandler->pSPIx->CR1 &= ~SPI_CR1_MSTR;
}

void SPI_SendData(SPI_TypeDef *pSPIx,uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		
		while(!(pSPIx->SR & (1<<1)));
		
		
		if( (pSPIx->CR1 & (1 << 11) ) )
		{
			pSPIx->DR =   *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}else
		{
			pSPIx->DR =   *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}

}


void SPI_Enable(SPI_TypeDef *pSPIx)
{
	pSPIx->CR1 |= SPI_CR1_SPE;
}


uint8_t SPI_GetFlagStatus(SPI_TypeDef *pSPIx , uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

