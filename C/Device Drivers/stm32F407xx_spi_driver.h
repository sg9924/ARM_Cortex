#ifndef INC_STM32F407XX_SPI_DRIVER_H
#define INC_STM32F407XX_SPI_DRIVER_H

#include "stm32f407xx.h"

/*--------------------------------------------------------------------------------------------------------------------------*/
/********************************************* SPI Structure Definitions Start **********************************************/

// SPI Configuration Structure
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config;


// SPI Handle Structure
typedef struct
{
	SPI_RegDef	    *pSPIx;         /*!<This holds the base address of SPIx(x:0,1,2) peripheral>*/
	SPI_Config 	    SPIConfig;      /*!<>*/
	uint8_t 		*pTxBuffer;     /*!<To store the app. Tx buffer address>*/
	uint8_t 		*pRxBuffer;	    /*!<To store the app. Rx buffer address>*/
	uint32_t 		TxLen;		    /*!<To store Tx len>*/
	uint32_t 		RxLen;		    /*!<To store Tx len>*/
	uint8_t 		TxState;	    /*!<To store Tx state>*/
	uint8_t 		RxState;	    /*!<To store Rx state>*/
}SPI_Handle;
/*********************************************** SPI Structure Definitions End **********************************************/
/*--------------------------------------------------------------------------------------------------------------------------*/
/*********************************************** SPI API's Declarartions Start **********************************************/

// SPI Peripheral Clock Enable
void SPI_Clk_Enable(SPI_RegDef *pSPIx, uint8_t EnorDi);

// Init and De-init
void SPI_Init(SPI_Handle *pSPIHandle);
void SPI_DeInit(SPI_RegDef *pSPIx);

// Data Send & Receive
void SPI_SendData(SPI_RegDef *pSPIx,uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

// Data Send & Receive for Interrupts
uint8_t SPI_SendDataIT(SPI_Handle *pSPIHandle,uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

// IRQ Configuration and ISR handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle *pHandle);

// Peripheral Control Functions
void SPI_Enable(SPI_RegDef *pSPIx, uint8_t mode);
void SPI_SSIConfig(SPI_RegDef *pSPIx, uint8_t mode);
void SPI_SSOEConfig(SPI_RegDef *pSPIx, uint8_t mode);
uint8_t SPI_GetFlagStatus(SPI_RegDef *pSPIx , uint32_t FlagName);
void SPI_ClearOVRFlag(SPI_RegDef *pSPIx);
void SPI_CloseTransmisson(SPI_Handle *pSPIHandle);
void SPI_CloseReception(SPI_Handle *pSPIHandle);
// uint8_t I2C_DeviceMode(I2C_RegDef *I2Cx); //--> ?????

// Application callback
void SPI_ApplicationEventCallback(SPI_Handle *pSPIHandle, uint8_t AppEv);

/************************************************ SPI API's Declarations End ************************************************/
/*--------------------------------------------------------------------------------------------------------------------------*/

#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */