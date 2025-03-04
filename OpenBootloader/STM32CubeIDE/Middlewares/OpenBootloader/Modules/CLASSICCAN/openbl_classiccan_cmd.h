/**
  ******************************************************************************
  * @file    openbl_classiccan_cmd.h
  * @author  Javi
  * @brief   Header for openbl_classiccan_cmd.c module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OPENBL_CLASSICCAN_CMD_H
#define OPENBL_CLASSICCAN_CMD_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define OPENBL_CLASSICCAN_VERSION             0x20U                /* Open Bootloader CLASSICCAN protocol V2.0 */
#define CLASSICCAN_RAM_BUFFER_SIZE             1156                /* Size of CLASSICCAN buffer used to store received data from the host */

/* Exported macro ------------------------------------------------------------*/
#define CLASSICCAN_MAX_PAYLOAD_BYTES 8U
/* Exported variables --------------------------------------------------------*/
extern uint8_t _TxData[CLASSICCAN_RAM_BUFFER_SIZE];
extern uint8_t _RxData[CLASSICCAN_RAM_BUFFER_SIZE];

extern OPENBL_CommandsTypeDef OPENBL_CLASSICCAN_Commands;

/* Exported functions ------------------------------------------------------- */
OPENBL_CommandsTypeDef *OPENBL_CLASSICCAN_GetCommandsList(void);

#endif /* OPENBL_CLASSICCAN_CMD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
