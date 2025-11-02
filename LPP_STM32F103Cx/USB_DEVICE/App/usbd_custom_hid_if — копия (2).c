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
#include "main.h"  // Добавлен основной заголовочный файл для доступа к структурам
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

// Вспомогательные переменные для работы с памятью
extern int16_t X_P;
uint16_t StartAdress;
uint16_t Ostatok;
uint16_t Delitel;

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
    0x06, 0x00, 0xFF,  // Usage Page = 0xFF00 (Vendor Defined Page 1)
    0x09, 0x01,        // Usage (Vendor Usage 1)
    0xA1, 0x01,        // Collection (Application)

    // Output report (64 bytes)
    0x09, 0x01,        //   USAGE (Vendor Usage 1)
    0x15, 0x00,        //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,  //   LOGICAL_MAXIMUM (255)
    0x95, 64,          //   REPORT_COUNT (64)
    0x75, 0x08,        //   REPORT_SIZE (8)
    0x91, 0x82,        //   FEATURE (Data,Var,Abs,Vol)

    // Input report (64 bytes)
    0x09, 0x01,        //  USAGE (Vendor Usage 1)
    0x15, 0x00,        //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,  //   LOGICAL_MAXIMUM (255)
    0x95, 64,          //   REPORT_COUNT (64)
    0x75, 0x08,        //   REPORT_SIZE (8)
    0x81, 0x82,        //   INPUT (Data,Var,Abs,Vol)

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
    USBD_CUSTOM_HID_HandleTypeDef* hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;
    
    // Вспомогательные переменные для работы с прошивкой
    uint32_t KEY0, KEY1, KEY2, KEY3, _VER;

    // ============================================================================
    // ОБРАБОТКА ПАКЕТА ДАННЫХ ПЕЧАТИ (IDX_PRINT_DATA)
    // ============================================================================
    if (event_idx == IDX_PRINT_DATA) {
        TYPE_PRINT_DATA* PRINT_DAT = (TYPE_PRINT_DATA*)(&hhid->Report_buf[0] - 1);
        
        // Атомарная обработка FIFO буфера
        __disable_irq();
        
        // Проверка переполнения буфера или запроса статуса
        if ((FIFO_SETTING.count >= FIFO_SETTING.capacity) || (PRINT_DAT->DAT.R_FIFO_FUL == 1)) {
            // Возврат информации о состоянии буфера
            PRINT_DAT->DAT.R_FIFO_FUL = 1;                     // Флаг переполнения
            PRINT_DAT->DAT.R_FIFO_COUNT = FIFO_SETTING.count;  // Текущее количество элементов
            __enable_irq();
        } else {
            // Буфер не полон - добавление новых данных через DMA
            uint16_t next_tail = (FIFO_SETTING.tail + 1) % FIFO_SETTING.capacity;
            __enable_irq();
            
            // Запуск DMA для копирования данных в FIFO
            HAL_DMA_Start_IT(
                &hdma_memtomem_dma1_channel1,
                (uint32_t)PRINT_DAT->DAT.W_BUFFER,  // Источник: данные из USB пакета
                (uint32_t)FIFO_SETTING.FIFO_PRINT[FIFO_SETTING.tail].W_BUFFER,  // Назначение: FIFO
                sizeof(FIFO_SETTING.FIFO_PRINT[FIFO_SETTING.tail].W_BUFFER)  // Размер данных
            );
            
            // Подтверждение успешного приема данных
            PRINT_DAT->DAT.R_FIFO_FUL = 0;                     // Буфер не переполнен
            PRINT_DAT->DAT.R_FIFO_COUNT = FIFO_SETTING.count;  // Текущее количество элементов
        }

        // Обработка FIFO координат Y
        __disable_irq();
        if (PRINT_DAT->DAT.R_FIFO_Y_COUNT == 1) {
            YPosFifo_Push(PRINT_DAT->DAT.W_Y_BUFFER);  // Добавление координаты Y в буфер
        }
        PRINT_DAT->DAT.R_FIFO_Y_COUNT = YPosFifo_FreeSpace();  // Возврат свободного места
        __enable_irq();

        // Обновление параметров управления
        PRINT_CONFIG.DAT.W_SET_LAZER = PRINT_DAT->DAT.W_SET_LAZER;  // Установка тока лазера
        W_X_SPEED_SET = PRINT_DAT->DAT.W_X_SPEED;                   // Установка скорости движения

        // Обратная связь с текущими значениями
        PRINT_DAT->DAT.W_X_SPEED = W_X_SPEED;               // Текущая скорость X
        PRINT_DAT->DAT.RW_Y_IMAGE_POSITION = Y_IMAGE_POSITION;  // Текущая позиция Y в изображении

        // Отправка подтверждения если печать активна
        if (PRINT_CONFIG.DAT.R_PRINT_STATUS == PRINT_STATUS_PRINT) {
            USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, PRINT_DAT->BIN, 64);
        }
    }

    // ============================================================================
    // ОБРАБОТКА КОНФИГУРАЦИИ ПЕЧАТИ (IDX_PRINT_CONFIG)
    // ============================================================================
    else if (event_idx == IDX_PRINT_CONFIG) {
        // Копирование данных конфигурации (с учетом смещения на 1 байт)
        memcpy((uint8_t*)(PRINT_CONFIG.BIN + 1), hhid->Report_buf, 63);

        // Запуск задания печати
        if (PRINT_CONFIG.DAT.R_PRINT_STATUS == PRINT_STATUS_PRINT) {
            SetupPrintJob = 1;  // Активация инициализации печати в main loop
        }
        // Остановка задания печати
        else if (PRINT_CONFIG.DAT.R_PRINT_STATUS > PRINT_STATUS_PRINT) {
            StopPrintJob(PRINT_CONFIG.DAT.R_PRINT_STATUS);
        }
    }

    // ============================================================================
    // ОБРАБОТКА ТЮНИНГА ОСИ Y (IDX_USB_TUNING_Y)
    // ============================================================================
    else if (event_idx == IDX_USB_TUNING_Y) {
        // Копирование данных тюнинга
        for (int i = 0; i < 63; i++) {
            USB_TUNING_Y.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Расчет индексов и обновление массива тюнинга
        Delitel = ((USB_TUNING_Y.DAT.W_ADRES - 1) / 25) * 25;
        for (int i = 0; i < 25; i++) {
            TUNING_Y[Delitel + i] = USB_TUNING_Y.DAT.TUNING_Y[i];
        }

        // Подтверждение приема данных
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, USB_TUNING_Y.BIN, 64);
    }

    // ============================================================================
    // ОБРАБОТКА СБРОСА СИСТЕМЫ (IDX_RESET)
    // ============================================================================
    else if (event_idx == IDX_RESET) {
        // Копирование данных сброса
        for (int i = 0; i < 63; i++) {
            APP_RESET.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Выполнение системного сброса
        HAL_NVIC_SystemReset();
    }

    // ============================================================================
    // ОБРАБОТКА ЗАПРОСА ИДЕНТИФИКАЦИИ (IDX_APP_ID)
    // ============================================================================
    else if (event_idx == IDX_APP_ID) {
        // Настройка пакета ответа
        APP_ID.DAT.R_IDX = IDX_APP_ID;
        APP_ID.DAT.W_CURENT = 0;  // Указание что работает APP

        // Чтение ключей и версии BOOT прошивки
        KEY0 = flash_read(BASE_BOOT_VER);
        KEY1 = flash_read(BASE_BOOT_VER + 4);
        KEY2 = flash_read(BASE_BOOT_VER + 8);
        KEY3 = flash_read(BASE_BOOT_VER + 12);
        _VER = flash_read(BASE_BOOT_VER + 16);

        // Сохранение ключей BOOT
        APP_ID.DAT.W_B_NAME[0] = KEY0;
        APP_ID.DAT.W_B_NAME[1] = KEY1;
        APP_ID.DAT.W_B_NAME[2] = KEY2;
        APP_ID.DAT.W_B_NAME[3] = KEY3;

        // Проверка валидности BOOT прошивки
        if ((KEY0 == 0x10300000U) && (KEY1 == 0x7AE58357U) && 
            (KEY2 == 0x58D8422BU) && (KEY3 == 0xF940ACB1U)) {
            APP_ID.DAT.W_B_VER = _VER;
        } else {
            APP_ID.DAT.W_B_VER = 0;
        }

        // Чтение ключей и версии APP прошивки
        KEY0 = flash_read(BASE_APP_VER);
        KEY1 = flash_read(BASE_APP_VER + 4);
        KEY2 = flash_read(BASE_APP_VER + 8);
        KEY3 = flash_read(BASE_APP_VER + 12);
        _VER = flash_read(BASE_APP_VER + 16);

        // Сохранение ключей APP
        APP_ID.DAT.W_A_NAME[0] = KEY0;
        APP_ID.DAT.W_A_NAME[1] = KEY1;
        APP_ID.DAT.W_A_NAME[2] = KEY2;
        APP_ID.DAT.W_A_NAME[3] = KEY3;

        // Проверка валидности APP прошивки
        if ((KEY0 == 0x10300000U) && (KEY1 == 0x244F9766U) && 
            (KEY2 == 0x884016F2U) && (KEY3 == 0x0C4F36FAU)) {
            APP_ID.DAT.W_A_VER = _VER;
        } else {
            APP_ID.DAT.W_A_VER = 0;
        }

        // Получение уникального идентификатора микроконтроллера
        APP_ID.DAT.W_ID[0] = HAL_GetUIDw0();
        APP_ID.DAT.W_ID[1] = HAL_GetUIDw1();
        APP_ID.DAT.W_ID[2] = HAL_GetUIDw2();

        APP_ID.DAT.ID = 0;
        
        // Отправка идентификационной информации
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, APP_ID.BIN, 64);
    }

    // ============================================================================
    // ОБРАБОТКА СТИРАНИЯ ПАМЯТИ (IDX_ERASE)
    // ============================================================================
    else if (event_idx == IDX_ERASE) {
        // Копирование параметров стирания
        for (int i = 0; i < 63; i++) {
            APP_ERASE.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Выполнение стирания flash памяти
        flash_erase(APP_ERASE.DAT.W_START, APP_ERASE.DAT.W_COUNT);
        
        // Подтверждение выполнения
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, APP_ERASE.BIN, 64);
    }

    // ============================================================================
    // ОБРАБОТКА ЗАПИСИ В ПАМЯТЬ (IDX_WRITE)
    // ============================================================================
    else if (event_idx == IDX_WRITE) {
        // Копирование данных для записи
        for (int i = 0; i < 63; i++) {
            APP_WRITE.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Расчет количества 32-битных слов для записи
        uint8_t COUNT = APP_WRITE.DAT.W_COUNT;
        COUNT = (COUNT + 3) >> 2;  // Преобразование байтов в 32-битные слова

        // Запись данных в flash память
        HAL_FLASH_Unlock();
        for (int i = 0; i < COUNT; i++) {
            flash_write(APP_WRITE.DAT.W_ADRES + (i * 4), APP_WRITE.DAT.W_INFO[i]);
        }
        HAL_FLASH_Lock();

        // Подтверждение записи
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, APP_WRITE.BIN, 64);
    }

    // ============================================================================
    // ТЕСТ СКОРОСТИ (IDX_APP_SPEED_TEST)
    // ============================================================================
    else if (event_idx == IDX_APP_SPEED_TEST) {
        // Копирование тестовых данных
        for (int i = 0; i < 63; i++) {
            APP_SPEED_TEST.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Настройка и отправка ответа
        APP_SPEED_TEST.DAT.R_IDX = IDX_APP_SPEED_TEST;
        APP_SPEED_TEST.DAT.ID = 0;
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, APP_SPEED_TEST.BIN, 64);
    }

    // ============================================================================
    // ПЕРЕХОД В ДРУГОЕ ПРИЛОЖЕНИЕ (IDX_JAMP_TO)
    // ============================================================================
    else if (event_idx == IDX_JAMP_TO) {
        // Копирование параметров перехода
        for (int i = 0; i < 63; i++) {
            APP_JAMP_TO.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Установка флага перехода в BOOT и сброс системы
        HAL_FLASH_Unlock();
        flash_write(0x0800BFE8, 0xFFFFFFF0U);  // Установка флага перехода
        HAL_FLASH_Lock();
        HAL_NVIC_SystemReset();  // Перезагрузка с переходом в BOOT
    }

    // ============================================================================
    // УПРАВЛЕНИЕ МОТОРОМ X (IDX_MOTOR_X)
    // ============================================================================
    else if (event_idx == IDX_MOTOR_X) {
        // Копирование параметров мотора
        for (int i = 0; i < 63; i++) {
            MOTOR_X.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Проверка и установка параметров мотора (закомментировано)
        if ((MOTOR_X.DAT.W_SET_T < 990) && (MOTOR_X.DAT.W_SET_T > 10)) {
            // TIM1->CCR1 = MOTOR_X.DAT.W_SET_T;
            // TIM1->CCR2 = 1000 - TIM1->CCR1;
        }
    }

    // ============================================================================
    // УПРАВЛЕНИЕ ЛАЗЕРОМ (IDX_LAZER)
    // ============================================================================
    else if (event_idx == IDX_LAZER) {
        // Копирование параметров лазера
        for (int i = 0; i < 63; i++) {
            LAZER.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Настройка таймера лазера
        htim2.Instance->PSC = LAZER.DAT.W_SET_L_PRESCALER;  // Установка предделителя
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, LAZER.DAT.W_SET_L);  // Установка скважности
    }

    // ============================================================================
    // УПРАВЛЕНИЕ ПОДСВЕТКОЙ (IDX_LIGHT)
    // ============================================================================
    else if (event_idx == IDX_LIGHT) {
        // Копирование параметров подсветки
        for (int i = 0; i < 63; i++) {
            LIGHT.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Установка яркости подсветки
        TIM2->CCR2 = LIGHT.DAT.W_SET_L;
    }

    // ============================================================================
    // НАСТРОЙКА ОСИ X (IDX_SET_X)
    // ============================================================================
    else if (event_idx == IDX_SET_X) {
        // Копирование параметров оси X
        for (int i = 0; i < 63; i++) {
            SET_X.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Настройка полярности и режима мотора
        W_X_POL_DIR = SET_X.DAT.W_X_POL_DIR;
        W_X_POL_PWM = SET_X.DAT.W_X_POL_PWM;
        MotorX_Init(SET_X.DAT.W_X_MODE);

        // Настройка полярности энкодера
        if (SET_X.DAT.W_X_POL_EN == 0) {
            ENCODER_A_PIN = ((uint16_t)0x0040);  // Pin 6
            ENCODER_B_PIN = ((uint16_t)0x0100);  // Pin 8
        } else {
            ENCODER_A_PIN = ((uint16_t)0x0100);  // Pin 8  
            ENCODER_B_PIN = ((uint16_t)0x0040);  // Pin 6
        }

        // Сброс позиции при необходимости
        if (SET_X.DAT.W_X_RESET == 1) {
            X_POS = 0;
            X_GO_POS = 0;
            SET_X.DAT.W_X_RESET = 0;
        }

        // Обработка режима трекинга (бег)
        if (SET_X.DAT.W_X_TRECK == 1) {
            // Начальное позиционирование
            if (SET_X.DAT.W_INITIAL_PUSH == 1) {
                X_GO_POS = (W_X_POWER_REAL < 0) ? SET_X.DAT.W_X_L_POS : SET_X.DAT.W_X_R_POS;
                SET_X.DAT.W_INITIAL_PUSH = 0;
            }
            
            // Установка параметров управления
            W_X_POWER_MAX = SET_X.DAT.W_X_POWER_MAX;      // Максимальная мощность
            W_X_SPEED_SET = SET_X.DAT.W_X_SPEED_SET;      // Скорость движения
            
            // PID коэффициенты
            X_Kp = SET_X.DAT.W_X_KP;
            X_Ki = SET_X.DAT.W_X_KI;
            X_Kd = SET_X.DAT.W_X_KD;
        }

        // Обработка режима позиционирования (статический)
        if (SET_X.DAT.W_X_TRECK == 0) {
            W_X_POWER_MAX = SET_X.DAT.W_X_POWER_MAX;      // Максимальная мощность
            W_X_SPEED_SET = SET_X.DAT.W_X_SPEED_SET;      // Скорость движения

            // Установка целевой позиции
            if (SET_X.DAT.W_X_POS_WRITE == 1) {
                X_GO_POS = SET_X.DAT.W_X_MOV_POS;
                SET_X.DAT.W_X_POS_WRITE = 0;
            } else {
                SET_X.DAT.W_X_MOV_POS = X_GO_POS;  // Обратная связь текущей позиции
            }
        }

        // Обработка перехода между режимами
        if ((SET_X_W_X_TRECK_OLD == 1) && (SET_X.DAT.W_X_TRECK == 0)) {
            X_START_STATIC_ACTIVE = 1;  // Сброс при переходе в статический режим
        }
        SET_X_W_X_TRECK_OLD = SET_X.DAT.W_X_TRECK;  // Сохранение состояния

        // Подготовка ответа с текущими значениями
        SET_X.DAT.W_X_EN_POS = X_POS;        // Текущая позиция X
        SET_X.DAT.W_X_EN_SPEED = W_X_SPEED;  // Текущая скорость X
        SET_X.DAT.W_WRITE = 0;               // Флаг завершения обработки
        SET_X.DAT.R_IDX = IDX_SET_X;         // Идентификатор пакета

        // Отправка ответа
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, SET_X.BIN, 64);
    }

    // ============================================================================
    // НАСТРОЙКА ОСИ Y (IDX_SET_Y)
    // ============================================================================
    else if (event_idx == IDX_SET_Y) {
        // Копирование параметров оси Y
        for (int i = 0; i < 63; i++) {
            SET_Y.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Установка параметров управления осью Y
        Y_MAX_POW = SET_Y.DAT.W_Y_MAX_POW;  // Максимальная мощность
        Y_MIN_POW = SET_Y.DAT.W_Y_MIN_POW;  // Минимальная мощность  
        Y_ACCL = SET_Y.DAT.W_Y_ACCL;        // Ускорение
        Y_MOTION = SET_Y.DAT.W_Y_MOTION;    // Режим движения

        // Обратная связь текущей позиции
        SET_Y.DAT.W_Y_EN_POS = Y_POS;

        // Обработка команд позиционирования
        if (SET_Y.DAT.W_Y_POS_WRITE == 1) {
            Y_FINISH_POS = SET_Y.DAT.W_Y_MOV_POS;
            SET_Y.DAT.W_Y_POS_WRITE = 0;
        } else {
            SET_Y.DAT.W_Y_MOV_POS = Y_FINISH_POS;
        }

        // Сброс позиции
        if (SET_Y.DAT.W_Y_RESET == 1) {
            Y_POS = 0;
            Y_FINISH_POS = 0;
            SET_Y.DAT.W_Y_MOV_POS = 0;
            SET_Y.DAT.W_Y_RESET = 0;
        }

        // Обратная связь статуса
        SET_Y.DAT.W_Y_STATUS = Y_STATUS;

        // Настройка полярности управления шаговым двигателем
        if (SET_Y.DAT.W_Y_POL_DIR == 1) {
            Y_DIR_HI = 1;
            Y_DIR_LO = 0;
        } else {
            Y_DIR_HI = 0;
            Y_DIR_LO = 1;
        }

        if (SET_Y.DAT.W_Y_POL_STEP == 1) {
            Y_STEP_HI = 1;
            Y_STEP_LO = 0;
        } else {
            Y_STEP_HI = 0;
            Y_STEP_LO = 1;
        }

        // Управление питанием контроллера Y
        if (SET_Y.DAT.W_Y_ENABLED == 1) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);    // Включение
        } else if (SET_Y.DAT.W_Y_ENABLED == 0) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);  // Выключение
        }

        // Подготовка и отправка ответа
        SET_Y.DAT.W_WRITE = 0;
        SET_Y.DAT.R_IDX = IDX_SET_Y;
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, SET_Y.BIN, 64);
    }

    // ============================================================================
    // НАСТРОЙКА ОБЩИХ ПАРАМЕТРОВ (IDX_SET_PARAM)
    // ============================================================================
    else if (event_idx == IDX_SET_PARAM) {
        // Копирование общих параметров
        for (int i = 0; i < 63; i++) {
            SET_PARAM.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Настройка параметров лазера и подсветки
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, SET_PARAM.DAT.W_SET_LIGHT);  // Подсветка
        htim2.Instance->PSC = SET_PARAM.DAT.W_SET_L_PRESCALER;  // Предделитель частоты
        __HAL_TIM_SET_COUNTER(&htim2, 0);  // Сброс счетчика таймера
    }

    // ============================================================================
    // ДАННЫЕ ТРЕКИНГА (IDX_TRACK)
    // ============================================================================
    else if (event_idx == IDX_TRACK) {
        // Копирование данных трекинга
        for (int i = 0; i < 63; i++) {
            TRACK.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Заполнение данных текущего состояния
        TRACK.DAT.W_X_EN_POS = X_POS;               // Текущая позиция X
        TRACK.DAT.W_X_EN_SPEED = W_X_SPEED;         // Текущая скорость X
        TRACK.DAT.W_X_POWER_REAL = W_X_POWER_REAL;  // Текущая мощность
        TRACK.DAT.POLAR = X_POLAR_DYNAMIC;          // Текущая полярность

        // Отправка данных трекинга
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, TRACK.BIN, 64);
    }

    // ============================================================================
    // ТЕСТ СКОРОСТИ (IDX_SPEED_TEST)
    // ============================================================================
    else if (event_idx == IDX_SPEED_TEST) {
        // Копирование тестовых данных
        for (int i = 0; i < 63; i++) {
            SPEED_TEST.BIN[i + 1] = hhid->Report_buf[i];
        }

        // Эхо-ответ для теста скорости
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, SPEED_TEST.BIN, 64);
    }

    return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
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

