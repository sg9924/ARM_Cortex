#ifndef INC_STM32F407XX_I2C_DRIVER_H
#define INC_STM32F407XX_I2C_DRIVER_H

#include "stm32f407xx.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/********************************************* I2C Structure Definitions Start **********************************************/

// I2C Configuration
typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t  I2C_DeviceAddress;
	uint8_t  I2C_AckControl;
	uint8_t  I2C_FMDutyCycle;

}I2C_Config;


// I2C Handler
typedef struct
{
	I2C_RegDef 	    *pI2Cx;             /*!<>*/
	I2C_Config 	    I2C_Config;         /*!<>*/
	uint8_t 		*pTxBuffer;         /*!<To store the app. Tx buffer address>*/
	uint8_t 		*pRxBuffer;	        /*!<To store the app. Rx buffer address>*/
	uint32_t 		TxLen;		        /*!<To store Tx len>*/
	uint32_t 		RxLen;		        /*!<To store Tx len>*/
	uint8_t 		TxRxState;	        /*!<To store Communication state>*/
	uint8_t 		DevAddr;	        /*!<To store slave/device address>*/
    uint32_t        RxSize;		        /*!<To store Rx size >*/
    uint8_t         Sr;			        /*!<To store repeated start value >*/
}I2C_Handle;

/********************************************** I2C Structure Definitions End ***********************************************/
/*--------------------------------------------------------------------------------------------------------------------------*/
/************************************************** I2C Definitions Start ***************************************************/

// I2C States
#define I2C_READY 					    0
#define I2C_BUSY_IN_RX 				    1
#define I2C_BUSY_IN_TX 				    2

// I2C SCL Speeds
#define I2C_SCL_SPEED_SM 	            100000
#define I2C_SCL_SPEED_FM4K 	            400000
#define I2C_SCL_SPEED_FM2K              200000


// I2C Ack Control
#define I2C_ACK_ENABLE                  1
#define I2C_ACK_DISABLE                 0


// I2C FM Duty Cycle
#define I2C_FM_DUTY_2                   0
#define I2C_FM_DUTY_16_9                1


// I2C Status Flags Configuration Values
#define I2C_FLAG_TXE   		            (1 << I2C_SR1_TXE)
#define I2C_FLAG_RXNE   	            (1 << I2C_SR1_RXNE)
#define I2C_FLAG_SB			            (1 << I2C_SR1_SB)
#define I2C_FLAG_OVR  		            (1 << I2C_SR1_OVR)
#define I2C_FLAG_AF   		            (1 << I2C_SR1_AF)
#define I2C_FLAG_ARLO 		            (1 << I2C_SR1_ARLO)
#define I2C_FLAG_BERR 		            (1 << I2C_SR1_BERR)
#define I2C_FLAG_STOPF 		            (1 << I2C_SR1_STOPF)
#define I2C_FLAG_ADD10 		            (1 << I2C_SR1_ADD10)
#define I2C_FLAG_BTF  		            (1 << I2C_SR1_BTF)
#define I2C_FLAG_ADDR 		            (1 << I2C_SR1_ADDR)
#define I2C_FLAG_TIMEOUT 	            (1 << I2C_SR1_TIMEOUT)

#define I2C_DISABLE_SR  	            RESET
#define I2C_ENABLE_SR   	            SET


// I2C Events Definitions
#define I2C_EV_TX_CMPLT  	 	        0
#define I2C_EV_RX_CMPLT  	 	        1
#define I2C_EV_STOP       		        2
#define I2C_ERROR_BERR 	 		        3
#define I2C_ERROR_ARLO  		        4
#define I2C_ERROR_AF    		        5
#define I2C_ERROR_OVR   		        6
#define I2C_ERROR_TIMEOUT 		        7
#define I2C_EV_DATA_REQ                 8
#define I2C_EV_DATA_RCV                 9

/*************************************************** I2C Definitions End ****************************************************/
/*--------------------------------------------------------------------------------------------------------------------------*/
/****************************************** I2C API's Function Declarations Start *******************************************/

// I2C Peripheral Clock Enable
void I2C_ClkEnable(I2C_RegDef *pI2Cx, uint8_t mode);

// Init and De-init
void I2C_Init(I2C_Handle *pI2CHandle);
void I2C_DeInit(I2C_RegDef *pI2Cx);


// I2C Data Send & Receive (Master)
void I2C_MasterSendData(I2C_Handle *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr);
void I2C_MasterReceiveData(I2C_Handle *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr);

// I2C Data Send & Receive for Interrupts (Master)
uint8_t I2C_MasterSendDataIT(I2C_Handle *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr);
uint8_t I2C_MasterReceiveDataIT(I2C_Handle *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr);

// I2C CLose Reception & Transmission
void I2C_CloseReceiveData(I2C_Handle *pI2CHandle);
void I2C_CloseSendData(I2C_Handle *pI2CHandle);

// I2C Data Send & Receive (Slave)
void I2C_SlaveSendData(I2C_RegDef *pI2C,uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_RegDef *pI2C);

// IRQ Configuration and Handling for I2C
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t mode);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void I2C_EV_IRQHandling(I2C_Handle *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle *pI2CHandle);


// Peripheral Control Functions
void I2C_PeripheralControl(I2C_RegDef *pI2Cx, uint8_t mode);
uint8_t I2C_GetFlagStatus(I2C_RegDef *pI2Cx , uint32_t FlagName);
void I2C_ManageAcking(I2C_RegDef *pI2Cx, uint8_t mode);
void I2C_GenerateStopCondition(I2C_RegDef *pI2Cx);

void I2C_SlaveEnableDisableCallbackEvents(I2C_RegDef *pI2Cx,uint8_t mode);

// Application event Callback
void I2C_ApplicationEventCallback(I2C_Handle *pI2CHandle,uint8_t AppEv);

/******************************************* I2C API's Function Declarations End ********************************************/
/*--------------------------------------------------------------------------------------------------------------------------*/

#endif /*INC_STM32F407XX_I2C_DRIVER_H*/