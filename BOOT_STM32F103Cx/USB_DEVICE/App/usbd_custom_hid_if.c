/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */
#include "lib_boot.h"
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
			0x06, 0x00, 0xFF,      // Usage Page = 0xFF00 (Vendor Defined Page 1)
			0x09, 0x01,            // Usage (Vendor Usage 1)
			0xA1, 0x01,            // Collection (Application)

// Output report  
			0x09, 0x01,            //   USAGE (Vendor Usage 1)
			0x15, 0x00,            //   LOGICAL_MINIMUM (0)
			0x26, 0xff, 0x00,      //   LOGICAL_MAXIMUM (255)
			0x95, 64,              //   REPORT_COUNT (64)	
			0x75, 0x08,            //   REPORT_SIZE (8)
			0x91, 0x82,            //   FEATURE (Data,Var,Abs,Vol)	
	
// Input report	
			0x09, 0x01,            //  USAGE (Vendor Usage 1)
			0x15, 0x00,            //   LOGICAL_MINIMUM (0)
			0x26, 0xff, 0x00,      //   LOGICAL_MAXIMUM (255)
			0x95, 64,              //   REPORT_COUNT (64)
			0x75, 0x08,            //   REPORT_SIZE (8)
			0x81, 0x82,            //   INPUT (Data,Var,Abs,Vol)	

  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
	USBD_CUSTOM_HID_HandleTypeDef  *hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;	
	uint32_t KEY0; 
	uint32_t KEY1; 
	uint32_t KEY2; 
	uint32_t KEY3; 
	uint32_t _VER;			
	if (event_idx == IDX_APP_ID) {
//	for ( int i = 0; i < 63; i++ ) {APP_ID.BIN[i+1] = hhid->Report_buf[i];} // копируем с буфера / Теряет 1 байт с начала		
		APP_ID.DAT.R_IDX = IDX_APP_ID;
		APP_ID.DAT.W_CURENT = 1; // Говорим что работает 	BOOT
		/////////////////////////////Читаем ключи BOOT		
		KEY0 = flash_read(BASE_BOOT_VER);
		KEY1 = flash_read(BASE_BOOT_VER + 4);
		KEY2 = flash_read(BASE_BOOT_VER + 8);
		KEY3 = flash_read(BASE_BOOT_VER + 12);
		_VER = flash_read(BASE_BOOT_VER + 16);	
		
// BOOT ключи -> W_B_NAME
APP_ID.DAT.W_B_NAME[0] = KEY0;
APP_ID.DAT.W_B_NAME[1] = KEY1;
APP_ID.DAT.W_B_NAME[2] = KEY2;
APP_ID.DAT.W_B_NAME[3] = KEY3;		
		
// Если есть версия BOOT		
		if (
				(KEY0 == 0x10300000U) &
				(KEY1 == 0x7AE58357U) & 
				(KEY2 == 0x58D8422BU) &  
				(KEY3 == 0xF940ACB1U)
				) {
					APP_ID.DAT.W_B_VER = _VER;
			} else {
					APP_ID.DAT.W_B_VER = 0; 	
			};
// Если есть версия APP	
		/////////////////////////////Читаем ключи APP		
		KEY0 = flash_read(BASE_APP_VER);
		KEY1 = flash_read(BASE_APP_VER + 4);
		KEY2 = flash_read(BASE_APP_VER + 8);
		KEY3 = flash_read(BASE_APP_VER + 12);
		_VER = flash_read(BASE_APP_VER + 16);		

// APP ключи -> W_A_NAME
APP_ID.DAT.W_A_NAME[0] = KEY0;
APP_ID.DAT.W_A_NAME[1] = KEY1;
APP_ID.DAT.W_A_NAME[2] = KEY2;
APP_ID.DAT.W_A_NAME[3] = KEY3;
			
		if (
				(KEY0 == 0x10300000U) &
				(KEY1 == 0x244F9766U) & 
				(KEY2 == 0x884016F2U) &  
				(KEY3 == 0x0C4F36FAU)
				) {
					APP_ID.DAT.W_A_VER = _VER;
			} else {
					APP_ID.DAT.W_A_VER = 0; 	
			};				
//			
		APP_ID.DAT.W_ID[0] = HAL_GetUIDw0();
		APP_ID.DAT.W_ID[1] = HAL_GetUIDw1();
		APP_ID.DAT.W_ID[2] = HAL_GetUIDw2();		
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS  ,APP_ID.BIN, 64); // Доб байт в начало
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);	
	}
//////////////////////////////////////////////////////////////////////////////////////////////////		
	if (event_idx == IDX_ERASE) {
	for ( int i = 0; i < 63; i++ ) {APP_ERASE.BIN[i+1] = hhid->Report_buf[i];} // копируем с буфера / Теряет 1 байт с начала	
// Стираем страницы
	flash_erase(APP_ERASE.DAT.W_START, APP_ERASE.DAT.W_COUNT);	
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS  ,APP_ERASE.BIN, 64); //Передаем данные, потверждаем стирание 
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////
	if (event_idx == IDX_WRITE) {
	for ( int i = 0; i < 63; i++ ) {APP_WRITE.BIN[i+1] = hhid->Report_buf[i];} // копируем с буфера / Теряет 1 байт с начала
	uint8_t COUNT;
	COUNT = APP_WRITE.DAT.W_COUNT;
	COUNT = COUNT + 3;   // Сколько по 4 байта
	COUNT = COUNT >> 2; // Сколько по 4 байта
	COUNT = COUNT + 0;
	HAL_FLASH_Unlock();	
// пишеm флеш	
	for ( int i = 0; i < COUNT; i++ ){	
		flash_write(APP_WRITE.DAT.W_ADRES + (i*4), APP_WRITE.DAT.W_INFO[i]);		
	};	
	HAL_FLASH_Lock();
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS  ,APP_WRITE.BIN, 64); //Передаем данные, потверждаем запись
//	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////
	if (event_idx == IDX_APP_SPEED_TEST) {
		for ( int i = 0; i < 63; i++ ) {APP_SPEED_TEST.BIN[i+1] = hhid->Report_buf[i];} // копируем с буфера / Теряет 1 байт с начала
		APP_SPEED_TEST.DAT.R_IDX = IDX_APP_SPEED_TEST;
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS  ,APP_SPEED_TEST.BIN, 64); //Передаем данные, потверждаем запись
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////
	if (event_idx == IDX_JAMP_TO) {
		for ( int i = 0; i < 63; i++ ) {APP_JAMP_TO.BIN[i+1] = hhid->Report_buf[i];} // копируем с буфера / Теряет 1 байт с начал
		HAL_NVIC_SystemReset();		
		// Далее не будет нечего прыгаем в другую программу
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////		
  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

