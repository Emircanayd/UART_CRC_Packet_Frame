#include "crc_com.h"

void GetCRC(char* message, uint8_t messageLength, char* crcBytes)
{
    uint16_t CRCFull = 0xFFFF;
    uint8_t  CRCHigh = 0xFF, CRCLow = 0xFF;
    uint16_t CRCLSB;
    uint8_t i, j;

    for (i = 0; i <= messageLength; i++)
    {
      CRCFull = (int16_t)(CRCFull ^ message[i]);
      for (j = 0; j < 8; j++)
      {
         CRCLSB = (int16_t)(CRCFull & 0x0001);
         CRCFull = (int16_t)((CRCFull >> 1) & 0x7FFF);
         if (CRCLSB == 1)
           CRCFull = (int16_t)(CRCFull ^ 0xA001);
      }
    }
    crcBytes[1] = CRCHigh = (uint8_t)((CRCFull >> 8) & 0xFF);
    crcBytes[0] = CRCLow = (uint8_t)(CRCFull & 0xFF);
}

uint8_t CheckSerialCRC(uint8_t* buffer)
{
    char crcBytesCalculated[2];
    GetCRC((char*)buffer, buffer[0], crcBytesCalculated);
    if(buffer[buffer[0] + 1] == crcBytesCalculated[0]
    && buffer[buffer[0] + 2] == crcBytesCalculated[1])
    return 1;
    else return 0;
}

/*void SendSerialBuffer(UART_HandleTypeDef *huart, uint8_t* tx_buffer)
{
    if(tx_buffer[0] < 14)
    {
      char crcBytes[2];
      GetCRC((char*)tx_buffer, tx_buffer[0], crcBytes);
      tx_buffer[tx_buffer[0] + 1] = crcBytes[0];
      tx_buffer[tx_buffer[0] + 2] = crcBytes[1];
      uint16_t total_buff = tx_buffer[0] + 3;
      HAL_UART_Transmit_DMA(huart, tx_buffer, total_buff);
    }
    else  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
}*/
