/**
  ******************************************************************************
  * @file    classiccan_interface.h
  * @author  javi
  * @brief   Header for classiccan_interface.c module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CLASSICCAN_INTERFACE_H
#define CLASSICCAN_INTERFACE_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void OPENBL_CLASSICCAN_Configuration(void);
uint8_t OPENBL_CLASSICCAN_ProtocolDetection(void);

uint8_t OPENBL_CLASSICCAN_GetCommandOpcode(void);
uint8_t OPENBL_CLASSICCAN_ReadByte(void);
void OPENBL_CLASSICCAN_ReadBytes(uint8_t *Buffer, uint32_t *BufferSize);
void OPENBL_CLASSICCAN_SendByte(uint8_t Byte);
void OPENBL_CLASSICCAN_SendBytes(uint8_t *Buffer, uint32_t BufferSize);

#endif /* CLASSICCAN_INTERFACE_H */


