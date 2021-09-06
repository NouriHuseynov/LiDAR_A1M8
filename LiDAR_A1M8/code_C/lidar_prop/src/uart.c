#include"uart.h"
#include"stdint.h"
#include"main.h"
#include "lidar_protoc.h"
#include "lidar_cmd.h"
#include "stdbool.h"

#define RESULT_OPERATION_TIMEOUT        (0x8002 | RESULT_FAIL_BIT)
#define RESULT_FAIL_BIT                 0x80000000

UART_HandleTypeDef huart3;

void uart_init (void)
{
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_NVIC_SetPriority(USART3_4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_4_IRQn);
}

//Mode sans interrupt 
void uart_send(UART_HandleTypeDef *huart,uint8_t *data, uint16_t size)
{
    HAL_UART_Transmit(huart, data, size, HAL_MAX_DELAY);  
}

void  uart_receive(UART_HandleTypeDef *huart,uint8_t *Data, uint16_t size)
{
    HAL_UART_Receive(huart, Data, size, HAL_MAX_DELAY);
}
//Mode interrupt
void uart_send_IT(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size)
{
    HAL_UART_Transmit_IT(huart, data, size);   
}
void  uart_receive_IT(UART_HandleTypeDef *huart, uint8_t *Data, uint16_t size)
{
    HAL_UART_Receive_IT(huart, Data, size);
}



