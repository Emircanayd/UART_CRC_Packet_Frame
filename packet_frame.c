#include "packet_frame.h"
#include "crc_com.h"

const uint8_t FRAME_HEAD = 0xAA;
const uint8_t FRAME_TAIL = 0xEF;
static uint8_t tx_frame_buff[32];

uint8_t FrameControl(uint8_t* rx_buffer)
{
    if (rx_buffer[0] != FRAME_HEAD) return 0;
    uint8_t len = rx_buffer[1];
    if(len > 27) return 0;										// data uzunluğu 27'dan büyük olmamalı
    if (rx_buffer[len + 4] != FRAME_TAIL) return 0;
    return 1;
}

void SendData(UART_HandleTypeDef *huart, uint8_t* raw_data)
{
    uint8_t len = raw_data[0];
    tx_frame_buff[0] = FRAME_HEAD;
    for(int i=0; i <= len; i++)
    {
        tx_frame_buff[1+i] = raw_data[i];
    }
    char crcBytes[2];
    GetCRC((char*)&tx_frame_buff[1], len, crcBytes);
    tx_frame_buff[1 + len + 1] = crcBytes[0];					// head + len + 1
    tx_frame_buff[1 + len + 2] = crcBytes[1];					// head + len + 2
    tx_frame_buff[1 + len + 3] = FRAME_TAIL;					// head + len + 3
    HAL_UART_Transmit_DMA(huart, tx_frame_buff, len + 5);		// {Head, Length, Data, CRC1, CRC2, Tail}
}
