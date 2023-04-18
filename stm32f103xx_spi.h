/**
  ******************************************************************************
  * @file    		stm32f103xx_spi.h
  * @author  		Vedant A. Rokad
  * @processor 	ARM Cortex-M3
	* @controller STM32F103C8T6
  * @date    		26-Feb-2022
  * @brief   		Device_Driver Header file
  ******************************************************************************
 **/
 
#include <stm32f10x.h>

/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//      																SPI_MACROS                                     //
//																															  										 //
/////////////////////////////////////////////////////////////////////////////////////////

#define SPI_CPHA_En 1
#define SPI_CPHA_Dn 0

#define SPI_CPOL_En 1
#define SPI_CPOL_Dn 0

#define SPI_BRR_Fpclk_2		0
#define SPI_BRR_Fpclk_4		1
#define SPI_BRR_Fpclk_8		2
#define SPI_BRR_Fpclk_16	3
#define SPI_BRR_Fpclk_32	4
#define SPI_BRR_Fpclk_64	5
#define SPI_BRR_Fpclk_128	6
#define SPI_BRR_Fpclk_256	7

#define SPI_DFF_8		0
#define SPI_DFF_16	1

#define SPI_MODE_Master 1
#define SPI_MODE_Slave 	0

#define SPI_SlvManage_Soft 1
#define SPI_SlvManage_Hard 0

#define FLAG_SET 1
#define FLAG_RESET 0
/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//																SPI_Configuration_Structure                          //
//																															  										 //
/////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	uint32_t CPHA ;
	uint32_t CPOL ;
	uint32_t BaudRate;
	uint32_t DFF ;
	uint32_t Mode ;
	uint32_t SlvManage;
}SPI_Config_t;




/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//																SPI_Handling_Structure                               //
//																															  										 //
/////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	SPI_Config_t spiconf;
	SPI_TypeDef *pSPIx;
}SPI_Handle_t;





/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//												  	SPI_APIs_&_HELPING_FUNCTION                              //
//																															  										 //
/////////////////////////////////////////////////////////////////////////////////////////
void SPI_PeriClockControl(SPI_TypeDef *pSPIx , uint32_t EnorDi);

void SPI_Init(SPI_Handle_t *pSPIHandler);
void SPI_Enable(SPI_TypeDef *pSPIx);
void SPI_SendData(SPI_TypeDef *pSPIx,uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_GetFlagStatus(SPI_TypeDef *pSPIx , uint32_t FlagName);
void SPI_MasterReceiveData(SPI_Handle_t *pSPIHandler , uint8_t *pRxBuffer , uint32_t len ,uint8_t Slaveaddr);

void SPI_Mem_Write(SPI_Handle_t *pSPIHandler , uint8_t Slaveaddr , uint8_t MemAddr ,uint8_t MemAddrSize ,uint8_t *pTxBuffer);
void SPI_Mem_Read(SPI_Handle_t *pSPIHandler , uint8_t Slaveaddr , uint8_t MemAddr ,uint8_t MemAddrSize ,uint8_t *pRxBuffer);
