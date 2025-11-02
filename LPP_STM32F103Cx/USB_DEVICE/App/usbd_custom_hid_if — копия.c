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
#include "main.h"

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
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END = {
    /* USER CODE BEGIN 0 */
    0x06, 0x00, 0xFF,  // Usage Page = 0xFF00 (Vendor Defined Page 1)
    0x09, 0x01,        // Usage (Vendor Usage 1)
    0xA1, 0x01,        // Collection (Application)

    // Output report
    0x09, 0x01,        //   USAGE (Vendor Usage 1)
    0x15, 0x00,        //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,  //   LOGICAL_MAXIMUM (255)
    0x95, 64,          //   REPORT_COUNT (64)
    0x75, 0x08,        //   REPORT_SIZE (8)
    0x91, 0x82,        //   FEATURE (Data,Var,Abs,Vol)

    // Input report
    0x09, 0x01,        //  USAGE (Vendor Usage 1)
    0x15, 0x00,        //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,  //   LOGICAL_MAXIMUM (255)
    0x95, 64,          //   REPORT_COUNT (64)
    0x75, 0x08,        //   REPORT_SIZE (8)
    0x81, 0x82,        //   INPUT (Data,Var,Abs,Vol)

    /* USER CODE END 0 */
    0xC0 /*     END_COLLECTION	             */
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

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS = {CUSTOM_HID_ReportDesc_FS, CUSTOM_HID_Init_FS,
                                                     CUSTOM_HID_DeInit_FS, CUSTOM_HID_OutEvent_FS};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
 * @brief Private functions.
 * @{
 */

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Initializes the CUSTOM HID media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_Init_FS(void) {
    /* USER CODE BEGIN 4 */
    return (USBD_OK);
    /* USER CODE END 4 */
}

/**
 * @brief  DeInitializes the CUSTOM HID media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_DeInit_FS(void) {
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
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state) {
    /* USER CODE BEGIN 6 */
    USBD_CUSTOM_HID_HandleTypeDef* hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;
    uint32_t KEY0;
    uint32_t KEY1;
    uint32_t KEY2;
    uint32_t KEY3;
    uint32_t _VER;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Обработка команды добавления данных в буфер печати
    if (event_idx == IDX_PRINT_DATA) {
        TYPE_PRINT_DATA* PRINT_DAT = (TYPE_PRINT_DATA*)(&hhid->Report_buf[0] - 1);
        // Отключаем прерывания для атомарного доступа к FIFO
        __disable_irq();
        // Проверяем, есть ли место в буфере для новых данных или пришло что все прочли
        if ((FIFO_SETTING.count >= FIFO_SETTING.capacity) || (PRINT_DAT->DAT.R_FIFO_FUL == 1)) {
            // Просто передаем информацию о размере буфера
            PRINT_DAT->DAT.R_FIFO_FUL = 1;                     // Устанавливаем флаг переполнения буфера
            PRINT_DAT->DAT.R_FIFO_COUNT = FIFO_SETTING.count;  // Возвращаем текущее количество элементов
            // Включаем прерывания
            __enable_irq();
        } else {
            // Буфер не полон - можем добавить данные
            uint16_t next_tail = (FIFO_SETTING.tail + 1) % FIFO_SETTING.capacity;
            // Включаем прерывания перед запуском DMA
            __enable_irq();
            // Запускаем DMA для копирования данных в следующую свободную позицию хвоста
            HAL_DMA_Start_IT(
                &hdma_memtomem_dma1_channel1,
                (uint32_t)PRINT_DAT->DAT.W_BUFFER,  // Источник: данные из USB пакета
                (uint32_t)FIFO_SETTING.FIFO_PRINT[FIFO_SETTING.tail]
                    .W_BUFFER,  // Назначение: текущая позиция хвоста
                sizeof(
                    FIFO_SETTING.FIFO_PRINT[FIFO_SETTING.tail].W_BUFFER));  // Размер данных для копирования
            // Важно! НЕ обновляем индексы FIFO здесь - это сделает callback DMA
            // Сообщаем клиенту об успешном добавлении данных
            PRINT_DAT->DAT.R_FIFO_FUL = 0;                     // Буфер не переполнен
            PRINT_DAT->DAT.R_FIFO_COUNT = FIFO_SETTING.count;  // Возвращаем текущее количество элементов
        }

        __disable_irq();
        // --- FIFO координаты Y ---
        if (PRINT_DAT->DAT.R_FIFO_Y_COUNT == 1) {
            YPosFifo_Push(PRINT_DAT->DAT.W_Y_BUFFER);
        }
        // Отправляем клиенту, сколько места осталось
        PRINT_DAT->DAT.R_FIFO_Y_COUNT =
            YPosFifo_FreeSpace();  // Y_POS_BUFFER_SIZE - FIFO_YPOS.count;//YPosFifo_FreeSpace(); //
                                   // Y_POS_BUFFER_SIZE - FIFO_YPOS.count - 1
        // --- FIFO координаты Y ---
        __enable_irq();

        // Обновляем параметры управления лазером
        PRINT_CONFIG.DAT.W_SET_LAZER = PRINT_DAT->DAT.W_SET_LAZER;  // Устанавливаем ток лазера
        // Устанавливаем скорости движения каретки влево/вправо
        W_X_SPEED_SET = PRINT_DAT->DAT.W_X_SPEED;  // Положительная скорость
        // Передаем обратно текущие фактические значения для обратной связи
        PRINT_DAT->DAT.W_X_SPEED = W_X_SPEED;  // Передаем в PS реальную скорость X	//W_X_EN_SPEED;
        PRINT_DAT->DAT.RW_Y_IMAGE_POSITION = Y_IMAGE_POSITION;  // Передаем позицию Y в имедже
        // Отправляем пакет с подтверждением и актуальной информацией клиенту, если не ошибка или стоп
        if (PRINT_CONFIG.DAT.R_PRINT_STATUS == PRINT_STATUS_PRINT)
            USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, PRINT_DAT->BIN, 64);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_PRINT_CONFIG) {
        // for ( int i = 0; i < 63; i++ ) {PRINTOR_CONFIG.BIN[i+1] = hhid->Report_buf[i];} // копируем с
        // буфера / Теряет 1 байт с начала
				// Копируем данные, начиная с индекса 1
        memcpy((uint8_t*)(PRINT_CONFIG.BIN + 1), hhid->Report_buf, 63);  

        if (PRINT_CONFIG.DAT.R_PRINT_STATUS == PRINT_STATUS_PRINT) {  // Если начало печати
            // нициализацию печати принтора, далее по прерываню в колбеке
            SetupPrintJob = 1;  // Остальное в теле main нужно жать
        }
        if (PRINT_CONFIG.DAT.R_PRINT_STATUS > PRINT_STATUS_PRINT) {  // Если конец печати
            StopPrintJob(PRINT_CONFIG.DAT.R_PRINT_STATUS);
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_USB_TUNING_Y) {
        for (int i = 0; i < 63; i++) {
            USB_TUNING_Y.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
        // Ostatok = USB_TUNING_Y.DAT.W_ADRES % 25;
        Delitel = ((USB_TUNING_Y.DAT.W_ADRES - 1) / 25) * 25;
        for (int i = 0; i < 25; i++) {
            TUNING_Y[Delitel + i] = USB_TUNING_Y.DAT.TUNING_Y[i];
        };
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, USB_TUNING_Y.BIN, 64);  // Добовлчет байт в начало
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_RESET) {
        for (int i = 0; i < 63; i++) {
            APP_RESET.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
        HAL_NVIC_SystemReset();  // Перегружаем программу что бы очистить стек и все подобное
                                 // Далее не будет нечего прыгаем в другую программу
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_APP_ID) {
        //	for ( int i = 0; i < 63; i++ ) {APP_ID.BIN[i+1] = hhid->Report_buf[i];} //копируем с буфера /
        // Теряет 1 байт с начала
        APP_ID.DAT.R_IDX = IDX_APP_ID;
        APP_ID.DAT.W_CURENT = 0;  // Говорим что работает APP
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
        if ((KEY0 == 0x10300000U) & (KEY1 == 0x7AE58357U) & (KEY2 == 0x58D8422BU) & (KEY3 == 0xF940ACB1U)) {
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

        if ((KEY0 == 0x10300000U) & (KEY1 == 0x244F9766U) & (KEY2 == 0x884016F2U) & (KEY3 == 0x0C4F36FAU)) {
            APP_ID.DAT.W_A_VER = _VER;
        } else {
            APP_ID.DAT.W_A_VER = 0;
        };
        //
        APP_ID.DAT.W_ID[0] = HAL_GetUIDw0();
        APP_ID.DAT.W_ID[1] = HAL_GetUIDw1();
        APP_ID.DAT.W_ID[2] = HAL_GetUIDw2();

        APP_ID.DAT.ID = 0;
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, APP_ID.BIN, 64);  // Добов байт в начало
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_ERASE) {
        for (int i = 0; i < 63; i++) {
            APP_ERASE.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
           // Стираем страницы
        flash_erase(APP_ERASE.DAT.W_START, APP_ERASE.DAT.W_COUNT);
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, APP_ERASE.BIN,
                                   64);  // Передаем данные, потверждаем стирание
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_WRITE) {
        for (int i = 0; i < 63; i++) {
            APP_WRITE.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
        uint8_t COUNT;
        COUNT = APP_WRITE.DAT.W_COUNT;
        COUNT = COUNT + 3;   // Сколько по 4 байта
        COUNT = COUNT >> 2;  // Сколько по 4 байта
        COUNT = COUNT + 0;
        HAL_FLASH_Unlock();
        // пишеm флеш
        for (int i = 0; i < COUNT; i++) {
            flash_write(APP_WRITE.DAT.W_ADRES + (i * 4), APP_WRITE.DAT.W_INFO[i]);
        };
        HAL_FLASH_Lock();
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, APP_WRITE.BIN, 64);  // Передаем данные, потверждаем запись
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_APP_SPEED_TEST) {
        for (int i = 0; i < 63; i++) {
            APP_SPEED_TEST.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
        APP_SPEED_TEST.DAT.R_IDX = IDX_APP_SPEED_TEST;
        APP_SPEED_TEST.DAT.ID = 0;
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, APP_SPEED_TEST.BIN,
                                   64);  // Передаем данные, потверждаем запись
        //		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_JAMP_TO) {
        for (int i = 0; i < 63; i++) {
            APP_JAMP_TO.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
           // JumpToApplication(0x800C000);
        HAL_FLASH_Unlock();
        flash_write(0x0800BFE8, 0xFFFFFFF0U);  // При старте прыгнуть в BOOT
        HAL_FLASH_Lock();
        HAL_NVIC_SystemReset();  // Перегружаем программу что бы очистить стек и все подобное
                                 // Далее не будет нечего прыгаем в другую программу
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_MOTOR_X) {
        for (int i = 0; i < 63; i++) {
            MOTOR_X.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
        if ((MOTOR_X.DAT.W_SET_T < 990) && (MOTOR_X.DAT.W_SET_T > 10)) {
        }
        // TIM1->CCR1 = MOTOR_X.DAT.W_SET_T;
        // TIM1->CCR2 = 1000 - TIM1->CCR1;
        //		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

        // MotorX_Init(MOTOR_MODE_TWO_PWM);
        // MotorX_Set(MOTOR_X.DAT.W_SET_T);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_LAZER) {
        for (int i = 0; i < 63; i++) {
            LAZER.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
        //         TIM2->CCR1 = LAZER.DAT.W_SET_L;
        //	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        // Используем HAL API вместо прямого доступа к регистру

        // Меняем Prescaler
        htim2.Instance->PSC = LAZER.DAT.W_SET_L_PRESCALER;
        // Обновляем скважность
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, LAZER.DAT.W_SET_L);
        // Обнуляем счётчик таймера
        //			__HAL_TIM_SET_COUNTER(&htim2, 0);
        // При необходимости перезапускаем канал PWM
        // HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
        // HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_LIGHT) {
        for (int i = 0; i < 63; i++) {
            LIGHT.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
        TIM2->CCR2 = LIGHT.DAT.W_SET_L;
        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
    if (event_idx == IDX_SET_X) {
        for (int i = 0; i < 63; i++) {
            SET_X.BIN[i + 1] = hhid->Report_buf[i];  // Копируем с буфера / Теряет 1 байт с начала
        }

        // Полярность H мсота
        W_X_POL_DIR = SET_X.DAT.W_X_POL_DIR;
        W_X_POL_PWM = SET_X.DAT.W_X_POL_PWM;
        MotorX_Init(SET_X.DAT.W_X_MODE);

        // Полярность энкодера
        if (SET_X.DAT.W_X_POL_EN == 0) {
            ENCODER_A_PIN = ((uint16_t)0x0040); /* Pin 6 selected    */
            ENCODER_B_PIN = ((uint16_t)0x0100); /* Pin 8 selected    */
        } else {
            ENCODER_A_PIN = ((uint16_t)0x0100); /* Pin 8 selected    */
            ENCODER_B_PIN = ((uint16_t)0x0040); /* Pin 6 selected    */
        };

        // Ели скоректировать позицию
        if (SET_X.DAT.W_X_RESET == 1) {  // Если ресет всех позиций
            X_POS = 0;                   // Установим позицию каретки X
            X_GO_POS = 0;
            SET_X.DAT.W_X_RESET = 0;
        }

        if (SET_X.DAT.W_X_TRECK == 1) {  // Если бегаем  TR
            // Толкнем
            if (SET_X.DAT.W_INITIAL_PUSH == 1) {  // "начальное толкание" в режиме печати
                X_GO_POS = (W_X_POWER_REAL < 0) ? SET_X.DAT.W_X_L_POS : SET_X.DAT.W_X_R_POS;
                SET_X.DAT.W_INITIAL_PUSH = 0;
            }
            // Расчитаем мощность для оси X
            W_X_POWER_MAX = SET_X.DAT.W_X_POWER_MAX;      // Максимальная мощность X -5000..5000
                                                      // Скорость
            W_X_SPEED_SET = SET_X.DAT.W_X_SPEED_SET;  // Скорость движения каретки
            // Установим переменные
            X_Kp = SET_X.DAT.W_X_KP;
            X_Ki = SET_X.DAT.W_X_KI;
            X_Kd = SET_X.DAT.W_X_KD;
        }

        if (SET_X.DAT.W_X_TRECK == 0) {  // Если двигаем ST
            // Расчитаем мощность для оси X
            W_X_POWER_MAX = SET_X.DAT.W_X_POWER_MAX;  // Максимальная мощность X 0..5000
            W_X_SPEED_SET = SET_X.DAT.W_X_SPEED_SET;  // Скорость движения каретки

            if (SET_X.DAT.W_X_POS_WRITE == 1) {  // Если команда записать позицию X каретки
                // Ели двинутся к позиции
                X_GO_POS = SET_X.DAT.W_X_MOV_POS;  // Двигаемся к месту
                SET_X.DAT.W_X_POS_WRITE = 0;       // Только 1 раз записываем позицию
            } else {
                SET_X.DAT.W_X_MOV_POS = X_GO_POS;  // Передаем позицию в пакет
            }
        };

        // Проверяем переход "трек -> статика"
        if ((SET_X_W_X_TRECK_OLD == 1) && (SET_X.DAT.W_X_TRECK == 0)) {
            X_START_STATIC_ACTIVE = 1;  // При входе в статический режим сбросить скорость
        }
        // Запоминаем текущее состояние для следующего цикла
        SET_X_W_X_TRECK_OLD = SET_X.DAT.W_X_TRECK;

        ///////////////////////////////////////// Передаем
        SET_X.DAT.W_X_EN_POS = X_POS;        // Передаем рельную позицию X
        SET_X.DAT.W_X_EN_SPEED = W_X_SPEED;  // Передаем рельную скорость X //W_X_EN_SPEED;
        SET_X.DAT.W_WRITE = 0;               // Пакет записали в МК, Передаем обратно

        // Передаем данные обратно
        SET_X.DAT.R_IDX = IDX_SET_X;
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, SET_X.BIN, 64);  // Передаем данные
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_SET_Y) {
        for (int i = 0; i < 63; i++) {
            SET_Y.BIN[i + 1] = hhid->Report_buf[i];  // Копируем с буфера / Теряет 1 байт с начала
        }

        Y_MAX_POW = SET_Y.DAT.W_Y_MAX_POW;  // Максимальная мощность Y
        Y_MIN_POW = SET_Y.DAT.W_Y_MIN_POW;  // Минимальная мощность Y
        Y_ACCL = SET_Y.DAT.W_Y_ACCL;        // Ускорение Y

        Y_MOTION = SET_Y.DAT.W_Y_MOTION;  // Принимаем команды

        SET_Y.DAT.W_Y_EN_POS = Y_POS;  // Реальная позиция каретки

        // Обработка данных для оси Y
        if (SET_Y.DAT.W_Y_POS_WRITE == 1) {  // Если команда записать позицию Y каретки
            Y_FINISH_POS = SET_Y.DAT.W_Y_MOV_POS;
            SET_Y.DAT.W_Y_POS_WRITE = 0;
        } else {
            SET_Y.DAT.W_Y_MOV_POS = Y_FINISH_POS;
        }

        if (SET_Y.DAT.W_Y_RESET == 1) {
            Y_POS = 0;
            Y_FINISH_POS = 0;
            SET_Y.DAT.W_Y_MOV_POS = 0;
            SET_Y.DAT.W_Y_RESET = 0;
        }

        SET_Y.DAT.W_Y_STATUS = Y_STATUS;

        // Обработка данных для оси Y
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

        // Включаем контролер
        if (SET_Y.DAT.W_Y_ENABLED == 1) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);  // Включаем контролер Y
        } else if (SET_Y.DAT.W_Y_ENABLED == 0) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);  // Выключаем контролер Y
        }

        SET_Y.DAT.W_WRITE = 0;  // Пакет записали в МК, Передаем обратно
        // Передаем данные обратно
        SET_Y.DAT.R_IDX = IDX_SET_Y;
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, SET_Y.BIN, 64);  // Передаем данные
    }

    if (event_idx == IDX_SET_PARAM) {
        for (int i = 0; i < 63; i++) {
            SET_PARAM.BIN[i + 1] = hhid->Report_buf[i];  // Копируем с буфера / Теряет 1 байт с начала
        }

        // Устанавливаем параметры
        // Установить ток подсветки
        //        TIM2->CCR2 = SET_PARAM.DAT.W_SET_LIGHT;

        // Обновляем скважность
        //			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, SET_PARAM.DAT.W_SET_LAZER); // Лазер
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, SET_PARAM.DAT.W_SET_LIGHT);
        // Меняем Prescaler
        htim2.Instance->PSC = SET_PARAM.DAT.W_SET_L_PRESCALER;
        // Обнуляем счётчик таймера
        __HAL_TIM_SET_COUNTER(&htim2, 0);
        // При необходимости перезапускаем канал PWM
        // HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
        // HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

        //		SET_PARAM.DAT.W_WRITE = 0; // Пакет записали в МК, Передаем обратно
        // Передаем данные обратно
        //    SET_PARAM.DAT.R_IDX = IDX_SET_PARAM;
        //    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, SET_PARAM.BIN, 64);  // Передаем данные
    }

    //////////////////////////////////////////
    if (event_idx == IDX_TRACK) {
        for (int i = 0; i < 63; i++) {
            TRACK.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала
        TRACK.DAT.W_X_EN_POS = X_POS;
        TRACK.DAT.W_X_EN_SPEED = W_X_SPEED;  // W_X_EN_SPEED;
        TRACK.DAT.W_X_POWER_REAL = W_X_POWER_REAL;
        TRACK.DAT.POLAR = X_POLAR_DYNAMIC;
        // Посылаем обратно
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, TRACK.BIN, 64);  // Передаем данные, потверждаем стирание
        //	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    if (event_idx == IDX_SPEED_TEST) {
        for (int i = 0; i < 63; i++) {
            SPEED_TEST.BIN[i + 1] = hhid->Report_buf[i];
        }  // копируем с буфера / Теряет 1 байт с начала

        // Посылаем обратно
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, SPEED_TEST.BIN,
                                   64);  // Передаем данные, потверждаем стирание
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
