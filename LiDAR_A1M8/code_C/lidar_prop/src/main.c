/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "lidar_cmd.h"
#include "lidar_protoc.h"
#include  "stdio.h"
#include "stdlib.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void uart_init(void);
/* USER CODE BEGIN PFP */
uint8_t angle[360];
uint8_t distance[360];//On stocke les 72 valeurs qui nous intéressent car byte_offset en a 360 et que 1 point est codée sur 5 octets donc 360/5
uint8_t interlude[1872];//There is 72 byte between the end of the scan command and the first byte that interests us so we store 360 
uint8_t byte_offset[1800];//Stockage de 360 valeurs d'octets en rapport avec les points mesurés par le LiDAR 
uint8_t flag_LiDAR=0;//Flag pour synchroniser la fin de l'interruption avec le main
/* USER CODE END PFP */
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/*
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  uart_init();
  /* USER CODE BEGIN 2 */
  
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  rplidar_cmd_packet_t env1; //STOP send packet
  rplidar_cmd_packet_t env2; //RESET send packet
  rplidar_cmd_packet_t env3; //GET_DEVICE_INFO send packet
  rplidar_cmd_packet_t env4; //GET_DEVICE_HEALTH send packet
  rplidar_cmd_packet_t env5; //SAMPLERATE send packet
  rplidar_cmd_packet_t env6; //FORCE_SCAN send packet
  rplidar_cmd_packet_t env7; //SCAN send packet (2000 pt/s => 360 pt/tour)
  rplidar_cmd_packet_t env8; //EXPRESS_SCAN send packet (4000 pt/s => 720 pt/tour)


  /*All commands available on LiDAR*/

  /*Commands without response*/

  //STOP command in order to stop LiDAR scan
  /*env1.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env1.cmd_flag=RPLIDAR_CMD_STOP;
  env1.size=0x00;*/
  /*uart_send(&huart3,(uint8_t *) &env1, sizeof(env1));*/

  //RESET Command in order to restart LiDAR and empty buffer. The LiDAR will return something when you send this command
  //It'about "RP LiDAR SYSTEM.
  //FIRMWARE VER  1.20 - rtm, HW VER 0
  //MODE 18.
  //it's not really like response, it's the same thing than when you restart your computer and it display "Windows 98..."
  /*env2.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env2.cmd_flag=RPLIDAR_CMD_RESET;
  env2.size=0x00;*/

  /*commands with single response*/
  
  //GET_DEVICE_INFO command in order to receive all information about LiDAR (model, firmware, serial number, Hardware version)
  /*env3.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env3.cmd_flag= RPLIDAR_CMD_GET_DEVICE_INFO;
  env3.size=0x00;
  uart_send(&huart3,(uint8_t *) &env3, sizeof(env3));*/

  //GET_DEVICE_HEALTH command in order to obtain complete diagnostic of LiDAR
  /*env4.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env4.cmd_flag=RPLIDAR_CMD_GET_DEVICE_HEALTH;
  env4.size=0x00;
  uart_send(&huart3,(uint8_t *) &env4, sizeof(env4));*/
  
  //GET_SAMPLERATE command in order to obtain the duration of single acquisition. 
  /*env5.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env5.cmd_flag=RPLIDAR_CMD_GET_SAMPLERATE;
  env5.size=0x00;
  uart_send(&huart3,(uint8_t *) &env5, sizeof(env5));*/
  
  /*SCAN command with several response*/

  //FORCE_SCAN command in order to force LiDAR to do a scan
  /*uint8_t buf_void[1];
  env6.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env6.cmd_flag=RPLIDAR_CMD_FORCE_SCAN;
  env6.size=0x00;
  uart_send(&huart3,(uint8_t *) &env2, sizeof(env2));//Need to reset LiDAR in order to exit of the Idle state
  uart_receive(&huart3,(uint8_t *) &buf_void, sizeof(buf_void));//Receive one byte of the RESET return in order to confirm that LiDAR has correctly restart
  uart_send(&huart3,(uint8_t *) &env6, sizeof(env6));*///Then we can send FORCE_SCAN 
  
  //Envoie d'une commande scan pour avoir la map en balayage "standard", attention si le lidar est en "protection stop state" faire un "RESET" sinon le lidar n'enverra rien.
  uint8_t buf_void;
  env7.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env7.cmd_flag=RPLIDAR_CMD_SCAN;
  env7.size=0x00;

  uart_send(&huart3,(uint8_t *) &env2, sizeof(env2));//Need to reset LiDAR in order to exit of the Idle state
  
  uart_receive(&huart3,(uint8_t *) &buf_void, sizeof(buf_void));///Receive one byte of the RESET return in order to confirm that LiDAR has correctly restart
  
  uart_send(&huart3,(uint8_t *) &env7, sizeof(env7));//Then we can send SCAN, pay attention if LiDAR is already in SCAN mode 
                                                      //The new scan command my not work, send command a second time.

  /*Do interrupts until interlude table will fill before calling RxCpltCallback function*/
  /*for(uint64_t i=0; i<sizeof(interlude); i++)
  {   
    uart_receive_IT(&huart3,(uint8_t *) &interlude, sizeof(interlude));
  }*/
  /*while(1)
  {*/
    /* USER CODE END WHILE */
    /*if (flag_LiDAR==1)//When flag is equal to 1, it's significate that I filled my interlude table with all value return by my LiDAR 
    {
      uart_send(&huart3,(uint8_t *) &env1, sizeof(env1));//We send a STOP command in order to stop scan 
      flag_LiDAR=0;
      break;
    }*/
    /* USER CODE BEGIN 3 */
  //}
  
  /*Add your code here in order to recover value of distance and angle*/
  

  /*Command with multiple response and recquire a payload*/

  //Send EXPRESS_SCAN command in order to obtain more acquisition (4000 pt/s)
  
  //Definition of first packet for command
  uint8_t buf_void_exp;
  env8.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env8.cmd_flag=RPLIDAR_CMD_EXPRESS_SCAN;
  env8.size=0x05;

  //Definition of second packet with payload
  rplidar_payload_express_scan_t payload;//Définition of payload
  payload.working_mode=RPLIDAR_EXPRESS_SCAN_MODE_NORMAL;
  payload.working_flags=0x0000;
  payload.param=0x0000;

  //Checksum definition
  uint8_t checksum; //Checksum definition
  checksum=0x22;
  
  uart_send(&huart3,(uint8_t *) &env2, sizeof(env2));//Need to reset LiDAR in order to exit of the Idle state

  uart_receive(&huart3,(uint8_t *) &buf_void_exp, sizeof(buf_void_exp));//Receive one byte of the RESET return in order to confirm that LiDAR has correctly restart
  
  //Send first packet 
  uart_send(&huart3,(uint8_t *) &env8, sizeof(env8));//Envoi de la commande
  
  //Send the payload
  uart_send(&huart3,(uint8_t *) &payload, sizeof(payload));
  
  //Send the checksum
  uart_send(&huart3,(uint8_t *) &checksum, sizeof(checksum));
  
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  flag_LiDAR=1;//use a flag to synchhronize the end of interrupt with main function
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
