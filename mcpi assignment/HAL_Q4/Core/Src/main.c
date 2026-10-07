/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "main.h"


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

TIM_HandleTypeDef htim2;


/* USER CODE BEGIN PV */

uint8_t led = 0;

/* USER CODE END PV */


/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);

static void MX_GPIO_Init(void);

static void MX_TIM2_Init(void);


/* USER CODE BEGIN PFP */

/* USER CODE END PFP */


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */


  /* MCU Configuration--------------------------------------------------------*/

  HAL_Init();


  /* USER CODE BEGIN Init */

  /* USER CODE END Init */


  /* Configure the system clock */

  SystemClock_Config();


  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */


  /* Initialize all configured peripherals */

  MX_GPIO_Init();

  MX_TIM2_Init();


  /* USER CODE BEGIN 2 */

  /*
   * Start TIM2 Channel 1
   * in Output Compare Interrupt mode
   */
  HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1);

  /* USER CODE END 2 */


  /* Infinite loop */

  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */


    /* USER CODE BEGIN 3 */

    /*
     * Nothing is required here.
     *
     * LED changing is handled by
     * Output Compare interrupt.
     */

  }

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


  /** Configure the main internal regulator output voltage
  */

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);


  /** Initializes the RCC Oscillators
  */

  RCC_OscInitStruct.OscillatorType =
      RCC_OSCILLATORTYPE_HSI;

  RCC_OscInitStruct.HSIState =
      RCC_HSI_ON;

  RCC_OscInitStruct.HSICalibrationValue =
      RCC_HSICALIBRATION_DEFAULT;

  RCC_OscInitStruct.PLL.PLLState =
      RCC_PLL_ON;

  RCC_OscInitStruct.PLL.PLLSource =
      RCC_PLLSOURCE_HSI;

  RCC_OscInitStruct.PLL.PLLM = 8;

  RCC_OscInitStruct.PLL.PLLN = 50;

  RCC_OscInitStruct.PLL.PLLP =
      RCC_PLLP_DIV4;

  RCC_OscInitStruct.PLL.PLLQ = 7;


  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }


  /** Initializes the CPU, AHB and APB buses clocks
  */

  RCC_ClkInitStruct.ClockType =
      RCC_CLOCKTYPE_HCLK |
      RCC_CLOCKTYPE_SYSCLK |
      RCC_CLOCKTYPE_PCLK1 |
      RCC_CLOCKTYPE_PCLK2;

  RCC_ClkInitStruct.SYSCLKSource =
      RCC_SYSCLKSOURCE_PLLCLK;

  RCC_ClkInitStruct.AHBCLKDivider =
      RCC_SYSCLK_DIV1;

  RCC_ClkInitStruct.APB1CLKDivider =
      RCC_HCLK_DIV4;

  RCC_ClkInitStruct.APB2CLKDivider =
      RCC_HCLK_DIV2;


  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct,
                          FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */

static void MX_TIM2_Init(void)
{
  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */


  TIM_ClockConfigTypeDef sClockSourceConfig = {0};

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  TIM_OC_InitTypeDef sConfigOC = {0};


  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */


  htim2.Instance = TIM2;

  /*
   * TIM2 clock = 12.5 MHz
   *
   * Prescaler = 9999
   *
   * Timer frequency =
   * 12,500,000 / 10,000
   * = 1250 Hz
   */
  htim2.Init.Prescaler = 9999;

  htim2.Init.CounterMode =
      TIM_COUNTERMODE_UP;

  /*
   * 1250 counts = 1 second
   */
  htim2.Init.Period = 1249;

  htim2.Init.ClockDivision =
      TIM_CLOCKDIVISION_DIV1;

  htim2.Init.AutoReloadPreload =
      TIM_AUTORELOAD_PRELOAD_DISABLE;


  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }


  sClockSourceConfig.ClockSource =
      TIM_CLOCKSOURCE_INTERNAL;


  if (HAL_TIM_ConfigClockSource(&htim2,
                                &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }


  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }


  sMasterConfig.MasterOutputTrigger =
      TIM_TRGO_RESET;

  sMasterConfig.MasterSlaveMode =
      TIM_MASTERSLAVEMODE_DISABLE;


  if (HAL_TIMEx_MasterConfigSynchronization(
          &htim2,
          &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }


  /*
   * Output Compare Mode
   */
  sConfigOC.OCMode =
      TIM_OCMODE_TIMING;

  /*
   * Compare value
   */
  sConfigOC.Pulse = 1248;

  sConfigOC.OCPolarity =
      TIM_OCPOLARITY_HIGH;

  sConfigOC.OCFastMode =
      TIM_OCFAST_DISABLE;


  if (HAL_TIM_OC_ConfigChannel(
          &htim2,
          &sConfigOC,
          TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }


  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */


  HAL_TIM_MspPostInit(&htim2);
}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};


  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */


  /* GPIO Ports Clock Enable */

  __HAL_RCC_GPIOA_CLK_ENABLE();

  __HAL_RCC_GPIOD_CLK_ENABLE();


  /*
   * Initially turn OFF all LEDs
   */

  HAL_GPIO_WritePin(
      GPIOD,
      GPIO_PIN_12 |
      GPIO_PIN_13 |
      GPIO_PIN_14 |
      GPIO_PIN_15,
      GPIO_PIN_RESET
  );


  /*
   * Configure PD12, PD13, PD14, PD15
   * as output
   */

  GPIO_InitStruct.Pin =
      GPIO_PIN_12 |
      GPIO_PIN_13 |
      GPIO_PIN_14 |
      GPIO_PIN_15;

  GPIO_InitStruct.Mode =
      GPIO_MODE_OUTPUT_PP;

  GPIO_InitStruct.Pull =
      GPIO_NOPULL;

  GPIO_InitStruct.Speed =
      GPIO_SPEED_FREQ_LOW;


  HAL_GPIO_Init(
      GPIOD,
      &GPIO_InitStruct
  );


  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}


/* USER CODE BEGIN 4 */


/**
  * @brief  Output Compare callback
  *
  * This function is called whenever
  * TIM2 reaches the compare value.
  */

void HAL_TIM_OC_DelayElapsedCallback(
    TIM_HandleTypeDef *htim)
{
    /*
     * Make sure the interrupt is from
     * TIM2 Channel 1
     */
    if (htim->Instance == TIM2 &&
        htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        /*
         * Turn OFF all LEDs first
         */
        HAL_GPIO_WritePin(
            GPIOD,
            GPIO_PIN_12 |
            GPIO_PIN_13 |
            GPIO_PIN_14 |
            GPIO_PIN_15,
            GPIO_PIN_RESET
        );


        /*
         * Anti-clockwise LED sequence
         *
         * PD12
         *   ↓
         * PD13
         *   ↓
         * PD14
         *   ↓
         * PD15
         *   ↓
         * PD12
         */

        if (led == 0)
        {
            HAL_GPIO_WritePin(
                GPIOD,
                GPIO_PIN_12,
                GPIO_PIN_SET
            );
        }

        else if (led == 1)
        {
            HAL_GPIO_WritePin(
                GPIOD,
                GPIO_PIN_13,
                GPIO_PIN_SET
            );
        }

        else if (led == 2)
        {
            HAL_GPIO_WritePin(
                GPIOD,
                GPIO_PIN_14,
                GPIO_PIN_SET
            );
        }

        else if (led == 3)
        {
            HAL_GPIO_WritePin(
                GPIOD,
                GPIO_PIN_15,
                GPIO_PIN_SET
            );
        }


        /*
         * Move to next LED
         */
        led++;

        /*
         * After PD15, go back to PD12
         */
        if (led >= 4)
        {
            led = 0;
        }
    }
}


/* USER CODE END 4 */


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */

  __disable_irq();

  while (1)
  {
  }

  /* USER CODE END Error_Handler_Debug */
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  */

void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */

  /* User can add his own implementation */

  /* USER CODE END 6 */
}

#endif /* USE_FULL_ASSERT */
