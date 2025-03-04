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
#define OPENBL_CLASSICCAN_VERSION             0x10U                /* Open Bootloader CLASSICCAN protocol V1.0 */
#define CLASSICCAN_RAM_BUFFER_SIZE             1156                /* Size of CLASSICCAN buffer used to store received data from the host */

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern uint8_t TxData[CLASSICCAN_RAM_BUFFER_SIZE];
extern uint8_t RxData[CLASSICCAN_RAM_BUFFER_SIZE];

extern OPENBL_CommandsTypeDef OPENBL_CLASSICCAN_Commands;

/* Exported functions ------------------------------------------------------- */
OPENBL_CommandsTypeDef *OPENBL_CLASSICCAN_GetCommandsList(void);

#endif /* OPENBL_CLASSICCAN_CMD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
