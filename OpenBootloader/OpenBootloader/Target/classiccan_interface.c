/**
  ******************************************************************************
  * @file    classiccan_interface.c
  * @author  Javi
  * @brief   Contains CLASSICCAN HW configuration
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

#include "openbl_core.h"
#include "openbl_classiccan_cmd.h"

#include "classiccan_interface.h"

#include "iwdg_interface.h"
#include "interfaces_conf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FDCAN_HandleTypeDef _hfdcan;
FDCAN_FilterTypeDef _sFilterConfig;
FDCAN_TxHeaderTypeDef _TxHeader;
FDCAN_RxHeaderTypeDef _RxHeader;

/* Exported variables --------------------------------------------------------*/
uint8_t _TxData[CLASSICCAN_RAM_BUFFER_SIZE];
uint8_t _RxData[CLASSICCAN_RAM_BUFFER_SIZE];

/* Private function prototypes -----------------------------------------------*/
static void OPENBL_CLASSICCAN_Init(void);

/* Private functions ---------------------------------------------------------*/

static void OPENBL_CLASSICCAN_Init(void)
{
/*
#define FDCANx_TX_PIN                     GPIO_PIN_9
#define FDCANx_TX_GPIO_PORT               GPIOB
#define FDCANx_TX_AF                      GPIO_AF9_FDCAN1
#define FDCANx_RX_PIN                     GPIO_PIN_8
#define FDCANx_RX_GPIO_PORT               GPIOB
#define FDCANx_RX_AF                      GPIO_AF9_FDCAN1
	*/
  /*                Bit time configuration: 125Kbaud
	Bit time parameter         | Nominal      |  Data
	---------------------------|--------------|----------------
	fdcan_ker_ck               | 20 MHz       | 20 MHz
  */
	//http://www.bittiming.can-wiki.info/

  _hfdcan.Instance                  = FDCANx;
  _hfdcan.Init.ClockDivider 		= FDCAN_CLOCK_DIV1;
  _hfdcan.Init.FrameFormat          = FDCAN_FRAME_CLASSIC;//FDCAN_FRAME_FD_BRS;
  _hfdcan.Init.Mode                 = FDCAN_MODE_NORMAL;
  _hfdcan.Init.AutoRetransmission   = ENABLE;
  _hfdcan.Init.TransmitPause        = DISABLE;
  _hfdcan.Init.ProtocolException    = DISABLE;
  _hfdcan.Init.NominalPrescaler     = 10;
  _hfdcan.Init.NominalSyncJumpWidth = 1;
  _hfdcan.Init.NominalTimeSeg1      = 13;
  _hfdcan.Init.NominalTimeSeg2      = 2;
  _hfdcan.Init.DataPrescaler        = 0x1;
  _hfdcan.Init.DataSyncJumpWidth    = 0x1;
  _hfdcan.Init.DataTimeSeg1         = 0x1;
  _hfdcan.Init.DataTimeSeg2         = 0x1;
  _hfdcan.Init.StdFiltersNbr        = 1;
  _hfdcan.Init.ExtFiltersNbr        = 0;
  _hfdcan.Init.TxFifoQueueMode      = FDCAN_TX_FIFO_OPERATION;

  if (HAL_FDCAN_Init(&_hfdcan) != HAL_OK)
  {
    while (1);
  }

  /* Configure Rx filter */
  _sFilterConfig.IdType       = FDCAN_STANDARD_ID;
  _sFilterConfig.FilterIndex  = 0;
  _sFilterConfig.FilterType   = FDCAN_FILTER_MASK;
  _sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  _sFilterConfig.FilterID1    = 0x111;
  _sFilterConfig.FilterID2    = 0x7FF;
  HAL_FDCAN_ConfigFilter(&_hfdcan, &_sFilterConfig);

  /* Prepare Tx Header */
  _TxHeader.Identifier          = 0x111;
  _TxHeader.IdType              = FDCAN_STANDARD_ID;
  _TxHeader.TxFrameType         = FDCAN_DATA_FRAME;
  _TxHeader.DataLength          = CLASSICCAN_MAX_PAYLOAD_BYTES;
  _TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
  _TxHeader.BitRateSwitch       = FDCAN_BRS_OFF;
  _TxHeader.FDFormat            = FDCAN_CLASSIC_CAN;
  _TxHeader.TxEventFifoControl  = FDCAN_NO_TX_EVENTS;
  _TxHeader.MessageMarker       = 0;

  /* Start the FDCAN module */
  HAL_FDCAN_Start(&_hfdcan);
}

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  This function is used to configure FDCAN pins and then initialize the used FDCAN instance.
 * @retval None.
 */
void OPENBL_CLASSICCAN_Configuration(void)
{

	OPENBL_CLASSICCAN_Init();
}

/**
 * @brief  This function is used to detect if there is any activity on FDCAN protocol.
 * @retval None.
 */
uint8_t OPENBL_CLASSICCAN_ProtocolDetection(void)
{
  uint8_t detected;

  /* check if FIFO 0 receive at least one message */
  if (HAL_FDCAN_GetRxFifoFillLevel(&_hfdcan, FDCAN_RX_FIFO0) > 0)
  {
    detected = 1;
  }
  else
  {
    detected = 0;
  }

  return detected;
}

/**
 * @brief  This function is used to get the command opcode from the host.
 * @retval Returns the command.
 */
uint8_t OPENBL_CLASSICCAN_GetCommandOpcode(void)
{
  uint8_t command_opc      = 0x0;
  HAL_StatusTypeDef status = HAL_OK;

  /* check if FIFO 0 receive at least one message */
  while (HAL_FDCAN_GetRxFifoFillLevel(&_hfdcan, FDCAN_RX_FIFO0) < 1)
  {}

  /* Retrieve Rx messages from RX FIFO0 */
  status = HAL_FDCAN_GetRxMessage(&_hfdcan, FDCAN_RX_FIFO0, &_RxHeader, _RxData);

  /* Check for errors */
  if (status == HAL_ERROR)
  {
    command_opc = ERROR_COMMAND;
  }
  else
  {
    command_opc         = _RxHeader.Identifier;
    _TxHeader.Identifier = _RxHeader.Identifier;
  }

  return command_opc;
}

/**
  * @brief  This function is used to read one byte from FDCAN pipe.
  * @retval Returns the read byte.
  */
uint8_t OPENBL_CLASSICCAN_ReadByte(void)
{
  uint8_t byte = 0x0;

  /* check if FIFO 0 receive at least one message */
  while (HAL_FDCAN_GetRxFifoFillLevel(&_hfdcan, FDCAN_RX_FIFO0) < 1)
  {
    OPENBL_IWDG_Refresh();
  }

  /* Retrieve Rx messages from RX FIFO0 */
  HAL_FDCAN_GetRxMessage(&_hfdcan, FDCAN_RX_FIFO0, &_RxHeader, &byte);

  return byte;
}

/**
  * @brief  This function is used to read bytes from FDCAN pipe.
  * @retval Returns the read byte.
  */
void OPENBL_CLASSICCAN_ReadBytes(uint8_t *Buffer, uint32_t *BufferSize)
{
  /* check if FIFO 0 receive at least one message */
  while (HAL_FDCAN_GetRxFifoFillLevel(&_hfdcan, FDCAN_RX_FIFO0) < 1)
  {
    OPENBL_IWDG_Refresh();
  }

  /* Retrieve Rx messages from RX FIFO0 */
  HAL_FDCAN_GetRxMessage(&_hfdcan, FDCAN_RX_FIFO0, &_RxHeader, Buffer);
  *BufferSize=_RxHeader.DataLength;
}

/**
  * @brief  This function is used to send one byte through FDCAN pipe.
  * @param  Byte The byte to be sent.
  * @retval None.
  */
void OPENBL_CLASSICCAN_SendByte(uint8_t Byte)
{
  _TxHeader.DataLength = FDCAN_DLC_BYTES_1;

  while (HAL_FDCAN_GetTxFifoFreeLevel(&_hfdcan) == 0)
  {}

  HAL_FDCAN_AddMessageToTxFifoQ(&_hfdcan, &_TxHeader, &Byte);

  /* Wait that the data is completely sent (sent FIFO empty) */
  while (((&_hfdcan)->Instance->IR & FDCAN_IR_TFE) != FDCAN_IR_TFE)
  {}

  /* Clear the complete flag */
  (&_hfdcan)->Instance->IR &= FDCAN_IR_TFE;
}

/**
  * @brief  This function is used to send a buffer using FDCAN.
  * @param  Buffer The data buffer to be sent.
  * @param  BufferSize The size of the data buffer to be sent.
  * @retval None.
  */
void OPENBL_CLASSICCAN_SendBytes(uint8_t *Buffer, uint32_t BufferSize)
{
  _TxHeader.DataLength = BufferSize;

  while (HAL_FDCAN_GetTxFifoFreeLevel(&_hfdcan) == 0)
  {}

  HAL_FDCAN_AddMessageToTxFifoQ(&_hfdcan, &_TxHeader, Buffer);

  /* Wait that the data is completely sent (sent FIFO empty) */
  while (((&_hfdcan)->Instance->IR & FDCAN_IR_TFE) != FDCAN_IR_TFE)
  {}

  /* Clear the complete flag */
  (&_hfdcan)->Instance->IR &= FDCAN_IR_TFE;
}


