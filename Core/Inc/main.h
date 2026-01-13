/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DCC_P_Pin GPIO_PIN_0
#define DCC_P_GPIO_Port GPIOC
#define DCC_M_Pin GPIO_PIN_1
#define DCC_M_GPIO_Port GPIOC
#define POWER_ON_Pin GPIO_PIN_2
#define POWER_ON_GPIO_Port GPIOA
#define PWR_HOLD_Pin GPIO_PIN_3
#define PWR_HOLD_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define BATT_SEL_Pin GPIO_PIN_4
#define BATT_SEL_GPIO_Port GPIOC
#define AC_ON_SIG_Pin GPIO_PIN_0
#define AC_ON_SIG_GPIO_Port GPIOB
#define KEY_ON_SIG_Pin GPIO_PIN_1
#define KEY_ON_SIG_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define SPI2_EN_Pin GPIO_PIN_6
#define SPI2_EN_GPIO_Port GPIOC
#define ERR_LED_Pin GPIO_PIN_7
#define ERR_LED_GPIO_Port GPIOC
#define FULL_LED_Pin GPIO_PIN_8
#define FULL_LED_GPIO_Port GPIOC
#define ERR_BUZZ_Pin GPIO_PIN_9
#define ERR_BUZZ_GPIO_Port GPIOC
#define BUZZER_Pin GPIO_PIN_8
#define BUZZER_GPIO_Port GPIOA
#define BAT_20p_Pin GPIO_PIN_10
#define BAT_20p_GPIO_Port GPIOC
#define BAT_40p_Pin GPIO_PIN_11
#define BAT_40p_GPIO_Port GPIOC
#define BAT_60p_Pin GPIO_PIN_12
#define BAT_60p_GPIO_Port GPIOC
#define BAT_80p_Pin GPIO_PIN_2
#define BAT_80p_GPIO_Port GPIOD
#define BAT_100p_Pin GPIO_PIN_3
#define BAT_100p_GPIO_Port GPIOB
#define HEATER_M_Pin GPIO_PIN_4
#define HEATER_M_GPIO_Port GPIOB
#define HEATER_P_Pin GPIO_PIN_5
#define HEATER_P_GPIO_Port GPIOB
#define CHARGE_M_Pin GPIO_PIN_6
#define CHARGE_M_GPIO_Port GPIOB
#define CHARGE_P_Pin GPIO_PIN_7
#define CHARGE_P_GPIO_Port GPIOB
#define DISCHARGE_M_Pin GPIO_PIN_8
#define DISCHARGE_M_GPIO_Port GPIOB
#define DISCHARGE_P_Pin GPIO_PIN_9
#define DISCHARGE_P_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
