/**
  ******************************************************************************
  * @file    openbl_classiccan_cmd.c
  * @author  Javi
  * @brief   Contains CLASSICCAN protocol commands
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "openbl_mem.h"
#include "openbl_core.h"
#include "openbl_classiccan_cmd.h"

#include "openbootloader_conf.h"
#include "classiccan_interface.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define OPENBL_CLASSICCAN_COMMANDS_NB             11U    /* Number of supported commands */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void OPENBL_CLASSICCAN_GetCommand(void);
static void OPENBL_CLASSICCAN_GetVersion(void);
static void OPENBL_CLASSICCAN_GetID(void);
static void OPENBL_CLASSICCAN_ReadMemory(void);
static void OPENBL_CLASSICCAN_WriteMemory(void);
static void OPENBL_CLASSICCAN_Go(void);
static void OPENBL_CLASSICCAN_ReadoutProtect(void);
static void OPENBL_CLASSICCAN_ReadoutUnprotect(void);
static void OPENBL_CLASSICCAN_EraseMemory(void);
static void OPENBL_CLASSICCAN_WriteProtect(void);
static void OPENBL_CLASSICCAN_WriteUnprotect(void);


static uint8_t OPENBL_CLASSICCAN_GetAddress(uint32_t *Address);

/* Exported variables --------------------------------------------------------*/

OPENBL_CommandsTypeDef OPENBL_CLASSICCAN_Commands =
{
  OPENBL_CLASSICCAN_GetCommand,
  OPENBL_CLASSICCAN_GetVersion,
  OPENBL_CLASSICCAN_GetID,
  OPENBL_CLASSICCAN_ReadMemory,
  OPENBL_CLASSICCAN_WriteMemory,
  OPENBL_CLASSICCAN_Go,
  OPENBL_CLASSICCAN_ReadoutProtect,
  OPENBL_CLASSICCAN_ReadoutUnprotect,
  OPENBL_CLASSICCAN_EraseMemory,
  OPENBL_CLASSICCAN_WriteProtect,
  OPENBL_CLASSICCAN_WriteUnprotect,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

/* Exported functions---------------------------------------------------------*/
/**
  * @brief  This function is used to get a pointer to the structure that contains the available CLASSICCAN commands.
  * @return Returns a pointer to the OPENBL_CommandsTypeDef struct.
  */
OPENBL_CommandsTypeDef *OPENBL_CLASSICCAN_GetCommandsList(void)
{
  return (&OPENBL_CLASSICCAN_Commands);
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function is used to get the list of the available CLASSICCAN commands
  * @retval None.
  */
static void OPENBL_CLASSICCAN_GetCommand(void)
{
  uint32_t counter;
  const uint8_t a_OPENBL_CLASSICCAN_CommandsList[OPENBL_CLASSICCAN_COMMANDS_NB] =
  {
    CMD_GET_COMMAND,
    CMD_GET_VERSION,
    CMD_GET_ID,
    CMD_READ_MEMORY,
    CMD_GO,
    CMD_WRITE_MEMORY,
    CMD_EXT_ERASE_MEMORY,
    CMD_WRITE_PROTECT,
    CMD_WRITE_UNPROTECT,
    CMD_READ_PROTECT,
    CMD_READ_UNPROTECT
  };

  /* Send Acknowledge byte to notify the host that the command is recognized */
  OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

  /* Send the number of commands supported by CLASSICCAN protocol */
  OPENBL_CLASSICCAN_SendByte(OPENBL_CLASSICCAN_COMMANDS_NB);

  /* Send CLASSICCAN protocol version */
  OPENBL_CLASSICCAN_SendByte(OPENBL_CLASSICCAN_VERSION);

  /* Send the list of supported commands */
  for (counter = 0U; counter < OPENBL_CLASSICCAN_COMMANDS_NB; counter++)
  {
    OPENBL_CLASSICCAN_SendByte(a_OPENBL_CLASSICCAN_CommandsList[counter]);
  }

  /* Send last Acknowledge synchronization byte */
  OPENBL_CLASSICCAN_SendByte(ACK_BYTE);
}

/**
  * @brief  This function is used to get the CLASSICCAN protocol version.
  * @retval None.
  */
static void OPENBL_CLASSICCAN_GetVersion(void)
{
  /* Send Acknowledge byte to notify the host that the command is recognized */
  OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

  /* Send CLASSICCAN protocol version */
  OPENBL_CLASSICCAN_SendByte(OPENBL_CLASSICCAN_VERSION);

  /* Send dummy bytes */
  _TxData[0] = 0x0;
  _TxData[1] = 0x0;
  OPENBL_CLASSICCAN_SendBytes(_TxData, 2);

  /* Send last Acknowledge synchronization byte */
  OPENBL_CLASSICCAN_SendByte(ACK_BYTE);
}

/**
  * @brief  This function is used to get the device ID.
  * @retval None.
  */
static void OPENBL_CLASSICCAN_GetID(void)
{
  /* Send Acknowledge byte to notify the host that the command is recognized */
  OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

  /* Send the device ID starting by the MSB byte then the LSB byte */
  _TxData[0] = DEVICE_ID_MSB;
  _TxData[1] = DEVICE_ID_LSB;
  OPENBL_CLASSICCAN_SendBytes(_TxData, 2U);

  /* Send last Acknowledge synchronization byte */
  OPENBL_CLASSICCAN_SendByte(ACK_BYTE);
}

/**
  * @brief  This function is used to read memory from the device.
  * @retval None.
  */
static void OPENBL_CLASSICCAN_ReadMemory(void)
{
  uint32_t address;
  uint32_t counter;
  uint32_t number_of_bytes;
  uint32_t count;
  uint32_t single;
  uint32_t memory_index;
  uint8_t  data_length;

  /* Check memory protection then send adequate response */
  if (OPENBL_MEM_GetReadOutProtectionStatus() != RESET)
  {
    OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
  }
  else
  {
    if (OPENBL_CLASSICCAN_GetAddress(&address) == NACK_BYTE)
    {
      OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
    }
    else
    {
      OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

      /* Get the number of bytes to be read from memory (Max: data + 1 = 256) */
      number_of_bytes = (uint32_t)_RxData[4] + 1U;

      count  = number_of_bytes / CLASSICCAN_MAX_PAYLOAD_BYTES;
      single = (uint32_t)(number_of_bytes % CLASSICCAN_MAX_PAYLOAD_BYTES);

      /* Get the memory index to know from which memory we will read */
      memory_index = OPENBL_MEM_GetMemoryIndex(address);

      while (count != 0U)
      {
        data_length = 0;

        for (counter = CLASSICCAN_MAX_PAYLOAD_BYTES ; counter > 0U; counter--)
        {
          _TxData[data_length] = OPENBL_MEM_Read(address, memory_index);

          data_length++;
          address++;
        }

        OPENBL_CLASSICCAN_SendBytes(_TxData, CLASSICCAN_MAX_PAYLOAD_BYTES);

        count--;
      }

      if (single != 0U)
      {
        data_length = 0U;

        for (counter = single ; counter > 0U; counter--)
        {
          _TxData[data_length] = OPENBL_MEM_Read(address, memory_index);

          data_length++;
          address++;
        }

        OPENBL_CLASSICCAN_SendBytes(_TxData, data_length);
      }

      OPENBL_CLASSICCAN_SendByte(ACK_BYTE);
    }
  }
}

/**
  * @brief  This function is used to write in to device memory.
  * @retval None.
  */
static void OPENBL_CLASSICCAN_WriteMemory(void)
{
  uint32_t address;
  uint32_t CodeSize;
  uint32_t count;
  uint32_t single;
  uint32_t mem_area;
  uint8_t data_length;

  /* Check memory protection then send adequate response */
  if (OPENBL_MEM_GetReadOutProtectionStatus() != RESET)
  {
    OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
  }
  else
  {
    if (OPENBL_CLASSICCAN_GetAddress(&address) == NACK_BYTE)
    {
      OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
    }
    else
    {
      OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

      /* Get the number of bytes to be written to memory (Max: data + 1 = 256) */
      CodeSize = (uint32_t)_RxData[4] + 1U;

      count = CodeSize / CLASSICCAN_MAX_PAYLOAD_BYTES;
      single = (uint32_t)(CodeSize % CLASSICCAN_MAX_PAYLOAD_BYTES);

      data_length = 0;

      if (count != 0U)
      {
        while (data_length != count)
        {
        	uint32_t numberofbytes=0;
          OPENBL_CLASSICCAN_ReadBytes(&_RxData[data_length * CLASSICCAN_MAX_PAYLOAD_BYTES], &numberofbytes);

          data_length++;
          OPENBL_CLASSICCAN_SendByte(ACK_BYTE);//maybe we need to ack each message
        }
      }

      if (single != 0U)
      {
    	uint32_t numberofbytes=0;
        OPENBL_CLASSICCAN_ReadBytes(&_RxData[(CodeSize - single)], &numberofbytes);
      }

      /* Write data to memory */
      OPENBL_MEM_Write(address, (uint8_t *)_RxData, CodeSize);

      /* Send last Acknowledge synchronization byte */
      OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

      /* Check if the received address is an option byte address */
      mem_area = OPENBL_MEM_GetAddressArea(address);

      if (mem_area == OB_AREA)
      {
        /* Launch Option Bytes reload */
        OPENBL_MEM_OptionBytesLaunch();
      }
    }
  }
}

/**
  * @brief  This function is used to jump to the user application.
  * @retval None.
  */
static void OPENBL_CLASSICCAN_Go(void)
{
  uint32_t address;
  uint32_t mem_area;

  /* Check memory protection then send adequate response */
  if (OPENBL_MEM_GetReadOutProtectionStatus() != RESET)
  {
    OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
  }
  else
  {
    OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

    if (OPENBL_CLASSICCAN_GetAddress(&address) == NACK_BYTE)
    {
      OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
    }
    else
    {
      /* Check if received address is valid or not */
      mem_area = OPENBL_MEM_GetAddressArea(address);

      if ((mem_area != FLASH_AREA) && (mem_area != RAM_AREA))
      {
        OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
      }
      else
      {
        /* If the jump address is valid then send ACK */
        OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

        OPENBL_MEM_JumpToAddress(address);
      }
    }
  }
}

/**
 * @brief  This function is used to enable readout protection.
 * @retval None.
 */
static void OPENBL_CLASSICCAN_ReadoutProtect(void)
{
  /* Check memory protection then send adequate response */
  if (OPENBL_MEM_GetReadOutProtectionStatus() != RESET)
  {
    OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
  }
  else
  {
    OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

    /* Enable the read protection */
    OPENBL_MEM_SetReadOutProtection(ENABLE);

    OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

    /* Launch Option Bytes reload */
    OPENBL_MEM_OptionBytesLaunch();
  }
}

/**
 * @brief  This function is used to disable readout protection.
 * @retval None.
 */
static void OPENBL_CLASSICCAN_ReadoutUnprotect(void)
{
  OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

  /* Once the option bytes modification start bit is set in FLASH CR register,
     all the RAM is erased, this causes the erase of the Open Bootloader RAM.
     This is why the last ACK is sent before the call of OPENBL_MEM_SetReadOutProtection */
  OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

  /* Disable the read protection */
  OPENBL_MEM_SetReadOutProtection(DISABLE);

  /* Launch Option Bytes reload and reset system */
  OPENBL_MEM_OptionBytesLaunch();
}


/**
 * @brief  This function is used to erase a memory.
 * @retval None.
 */
static void OPENBL_CLASSICCAN_EraseMemory(void)
{
  uint8_t status = ACK_BYTE;
  ErrorStatus error_value;
  uint16_t *uint16_casted_p_RxData=(uint16_t*)_RxData;
  uint8_t canbusBuffer[CLASSICCAN_MAX_PAYLOAD_BYTES]={0};
  uint32_t numberofbytes=0;
  uint16_t numberofpagestobereceived=0;
  uint16_t numberoreceivedpages=0;

  /* Check if the memory is protected or not */
  if (OPENBL_MEM_GetReadOutProtectionStatus() != RESET)
  {
    OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
  }
  else
  {
    OPENBL_CLASSICCAN_SendByte(ACK_BYTE);
    numberofpagestobereceived=uint16_casted_p_RxData[0]+1;//from index to ammmount

    /* All commands in range 0xFFFZ are reserved for special erase features */
    if (( numberofpagestobereceived & 0xFFF0U) == 0xFFF0U){
        /* This sub-command is not supported */
    	//mass erase not supported
        status = NACK_BYTE;
    }
    else
    {
      OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

      /* Receive the list of pages to be erased (each page num is on two bytes)
       * The order of data received is LSB first
       */

      while(numberoreceivedpages<numberofpagestobereceived){
    	  OPENBL_CLASSICCAN_ReadBytes(canbusBuffer, &numberofbytes);
			  for (uint16_t i = 0; i < numberofbytes; i++) {
				  uint16_casted_p_RxData[numberoreceivedpages+1]=canbusBuffer[i];
				  numberoreceivedpages++;
			  }
    	  OPENBL_CLASSICCAN_SendByte(status);//ACK every received ERASE CANBUS PAGES canbus message 0x43
      }

      uint16_casted_p_RxData[0]=numberoreceivedpages;
      error_value = OPENBL_MEM_Erase(FLASH_START_ADDRESS, _RxData, numberoreceivedpages*2);

      /* Errors from memory erase are not managed, always return ACK */
      if (error_value == SUCCESS)
      {
        status = ACK_BYTE;
      }
    }


    OPENBL_CLASSICCAN_SendByte(status);
  }
}

/**
 * @brief  This function is used to enable write protect.
 * @retval None.
 */
static void OPENBL_CLASSICCAN_WriteProtect(void)
{
  uint32_t length;
  ErrorStatus error_value;

  /* Check if the memory is protected or not */
  if (OPENBL_MEM_GetReadOutProtectionStatus() != RESET)
  {
    OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
  }
  else
  {
    OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

    length = _RxData[0];

    /* Enable the write protection */
    error_value = OPENBL_MEM_SetWriteProtection(ENABLE, FLASH_START_ADDRESS, (uint8_t *) &_RxData[1], length);

    OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

    if (error_value == SUCCESS)
    {
      OPENBL_MEM_OptionBytesLaunch();
    }
  }
}

/**
 * @brief  This function is used to disable write protect.
 * @retval None.
 */
static void OPENBL_CLASSICCAN_WriteUnprotect(void)
{
  ErrorStatus error_value;

  /* Check if the memory is not protected */
  if (OPENBL_MEM_GetReadOutProtectionStatus() != RESET)
  {
    OPENBL_CLASSICCAN_SendByte(NACK_BYTE);
  }
  else
  {
    OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

    /* Disable write protection */
    error_value = OPENBL_MEM_SetWriteProtection(DISABLE, FLASH_START_ADDRESS, NULL, 0);

    OPENBL_CLASSICCAN_SendByte(ACK_BYTE);

    if (error_value == SUCCESS)
    {
      OPENBL_MEM_OptionBytesLaunch();
    }
  }
}

/**
  * @brief  This function is used to get a valid address.
  * @retval Returns NACK status in case of error else returns ACK status.
  */
static uint8_t OPENBL_CLASSICCAN_GetAddress(uint32_t *Address)
{
  uint8_t status;

  *Address = (((((uint32_t) _RxData[0]) << 24)  |
               (((uint32_t) _RxData[1]) << 16)  |
               (((uint32_t) _RxData[2]) << 8)   |
               (((uint32_t) _RxData[3]))));

  /* Check if received address is valid or not */
  if (OPENBL_MEM_GetAddressArea(*Address) == AREA_ERROR)
  {
    status = NACK_BYTE;
  }
  else
  {
    status = ACK_BYTE;
  }

  return status;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
