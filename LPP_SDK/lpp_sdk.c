/**
 ******************************************************************************
 * @file    lpp_sdk.c
 * @brief   Laser Printer Platform (LPP) — SDK core definitions
 *
 * This file is part of the LPP (Laser Printer Platform) SDK — 
 * a software development kit for embedded laser printer control,
 * designed for STM32 microcontrollers (Blue Pill, Black Pill, G4 series).
 *
 * Copyright (C) 2025  Dima
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Official channel: https://t.me/LPP_Printer
 * Community chat:    https://t.me/LPP_Printer_Chat
 ******************************************************************************
 */

#include <string.h>
#include "lpp_sdk.h"
// ============================================================================
// Переменные управления осью X
// ============================================================================

// Параметры управления движением по X

volatile int32_t W_X_SPEED_ERROR_INTEGRAL = 0;  // Накопленная интегральная ошибка
volatile int32_t W_X_SPEED_SET_POLAR;           // Скорость со знаком
volatile int32_t W_X_P_component;               // Пропорциональная составляющая
volatile int32_t W_X_I_component;               // Интегральная составляющая
volatile int32_t W_X_PI_sum;                    // Сумма P+I составляющих

volatile uint8_t needSendStatusReport = 0;  // Флаг необходимости отправки статуса

// Глобальные переменные для управления печатью
volatile uint8_t CURRENT_PRINT_DIRECTION = 0;  // 0-слева направо, 1-справа налево
volatile int32_t PRINT_LEFT_BORDER = 0;        // Левая граница зоны печати
volatile int32_t PRINT_RIGHT_BORDER = 0;       // Правая граница зоны пепати

// ============================================================================
// БЕЗОПАСНАЯ ОСТАНОВКА И СМЕНА НАПРАВЛЕНИЯ ДЛЯ ШАГОВОГО МОТОРА
// ============================================================================

volatile uint8_t X_STOPPING = 0;           // Флаг процесса остановки
volatile uint8_t X_TRACKING_ACTIVE = 0;  // Флаг активного трекинга
volatile uint8_t X_TRACKING_STARTED = 0;  // трекинг реально запущен

// ============================================================================
// Буферы для двойной буферизации данных печати
// ============================================================================

#define INTERPOL_MAX 4                           // Максимальный коэффициент интерполяции (X4)
volatile uint8_t nextPrintBit[2][INTERPOL_MAX];  // Двойной буфер для предварительно прочитанных битов
volatile uint8_t activeBuffer = 0;               // Активный буфер (читается таймером)
volatile uint8_t NextBuffer = 1;                 // Следующий буфер (заполняется данными)

// ============================================================================
// Переменные управления системой
// ============================================================================

// Переменные для интерполяции энкодера
volatile uint8_t INTERPOL_X = 1;      // Коэффициент интерполяции X (2 = кратное увеличение разрешения)
volatile uint8_t interp_counter = 0;  // Счетчик интерполированных импульсов
volatile uint32_t interp_period;  // Период интерполяции

// ============================================================================
// Основные структуры конфигурации
// ============================================================================

TYPE_PRINT_CONFIG PRINT_CONFIG = {0};
TYPE_PRINT_DATA PRINT_DATA = {0};
TYPE_USB_TUNING_X USB_TUNING_X = {0};
TYPE_USB_TUNING_Y USB_TUNING_Y = {0};
TYPE_APP_RESET APP_RESET = {0};
TYPE_TRACK TRACK = {0};
TYPE_LPP_ID LPP_ID = {0};
TYPE_SET_X SET_X = {0};
TYPE_SET_Y SET_Y = {0};
TYPE_SET_PARAM SET_PARAM = {0};
TYPE_LIGHT LIGHT = {0};
TYPE_LAZER LAZER = {0};
TYPE_APP_JAMP_TO APP_JAMP_TO = {0};
TYPE_APP_SPEED_TEST APP_SPEED_TEST = {0};
TYPE_APP_WRITE APP_WRITE = {0};
TYPE_APP_ERASE APP_ERASE = {0};
TYPE_APP_ID APP_ID = {0};
TYPE_SPEED_TEST SPEED_TEST = {0};

// ============================================================================
// Переменные управления осью X
// ============================================================================

// Параметры управления движением по X
volatile int16_t W_X_POWER_REAL = 0;      // Реальная мощность на моторе
volatile int8_t W_X_EN_DIRECT = 0;        // Направление движения каретки
volatile uint16_t W_X_SPEED_SET = 1000;   // Установленная скорость движения
volatile int32_t W_X_SPEED_FILTERED = 0;  // Скорость с учетом направления
volatile uint16_t W_X_POWER_MAX = 500;    // Максимальная мощность X
volatile uint16_t W_X_SPEED = 0;          // Скорость в тиках счетчика
volatile int32_t W_X_SPEED_ERROR = 0;     // Ошибка скорости

// PID коэффициенты для стабилизации скорости
volatile uint16_t X_Kp = 0;  // Пропорциональный коэффициент
volatile uint16_t X_Ki = 0;  // Интегральный коэффициент
volatile uint16_t X_Kd = 0;  // Дифференциальный коэффициент

// ============================================================================
// Переменные управления движением по X
// ============================================================================

MotorXMode_t motorXMode = MOTORX_MODE_START;  // Режимы работы мотора X

volatile int32_t X_GO_POS = 0;      // Целевая позиция каретки X
volatile int32_t X_POS = 0;         // Текущая позиция каретки X

volatile uint8_t X_POLAR_DYNAMIC = 0;        // Полярность при движении/треке
volatile uint8_t X_POLAR_STATIC = 0;         // Полярность при статике/позиции
volatile uint8_t X_START_STATIC_ACTIVE = 0;  // Флаг начала статического позиционирования    
volatile uint8_t X_TRACKING_STARTED_OLD = 0;    

// Полярность управления мотором X
volatile uint8_t W_X_POL_DIR = 0;  // Полярность направления
volatile uint8_t W_X_POL_PWM = 0;  // Полярность ШИМ

// Управление шаговым двигателем X (в режиме MOTORX_MODE_STEP)
volatile int32_t X_START_POS = 0;   // Начальная позиция X
volatile int32_t X_HALF_POS = 0;    // Половина пути X
volatile uint8_t X_PIN = 0;         // Состояние "виртуального" STEP (0/1)
volatile uint16_t X_REAL_SPED = 0;  // Реальная скорость X (период таймера)
volatile int16_t X_MIN_POW = 0;     // Минимальная мощность (период) для X
volatile int16_t X_ACCL = 0;        // Ускорение (длина разгона/торможения в шагах)

// Управление шаговым двигателем X (в режиме MOTORX_MODE_STEP)
volatile uint8_t X_DIR_HI = 0;   // Направление X (высокий уровень)
volatile uint8_t X_DIR_LO = 0;   // Направление X (низкий уровень)
volatile uint8_t X_STEP_HI = 0;  // Шаг X (высокий уровень)
volatile uint8_t X_STEP_LO = 0;  // Шаг X (низкий уровень)

uint16_t TUNING_X[1000] = {0};  // Массив тюнинга ускорения/торможения X

// ============================================================================
// Управление осью Y
// ============================================================================

Y_STATUS_T Y_STATUS = Y_STATUS_READY;  // Текущий статус готовности Y
Y_MOTION_T Y_MOTION = Y_MOTION_NONE;   // Текущее направление движения Y

// Позиционные переменные осей
volatile int32_t Y_START_POS = 0;   // Начальная позиция каретки Y
volatile int32_t Y_FINISH_POS = 0;  // Конечная позиция каретки Y
volatile int32_t Y_HALF_POS = 0;    // Половина трека Y
volatile int32_t Y_POS = 0;         // Текущая позиция каретки Y
volatile uint16_t Y_REAL_SPED = 0;  // Реальная скорость Y

// Управление шаговым двигателем Y
volatile uint8_t Y_DIR_HI = 0;   // Направление Y (высокий уровень)
volatile uint8_t Y_DIR_LO = 0;   // Направление Y (низкий уровень)
volatile uint8_t Y_STEP_HI = 0;  // Шаг Y (высокий уровень)
volatile uint8_t Y_STEP_LO = 0;  // Шаг Y (низкий уровень)

volatile int16_t Y_MIN_POW = 0;      // Минимальная мощность Y
volatile int16_t Y_ACCL = 0;         // Ускорение Y

volatile uint16_t ENCODER_A_PIN = 0;
volatile uint16_t ENCODER_B_PIN = 0;

uint16_t TUNING_Y[1000] = {0};  // Массив тюнинга ускорения/торможения Y

// ============================================================================
// Переменные процесса печати
// ============================================================================

volatile uint8_t START_PRINT = 0;         // Флаг начала печати
volatile uint8_t PRINT_ACTIVE = 0;        // Флаг активности печати
volatile uint8_t PRINT_ACTIVE_COUNT = 0;  // Счетчик проходов до активации печати

volatile uint8_t SetupPrintJob = 0;     // Настройка задания печати
volatile int32_t Y_LINES = 0;           // Число строк
volatile int32_t Y_IMAGE_POSITION = 0;  // Следующая позиция Y для передачи

// ============================================================================
// Системные переменные
// ============================================================================

volatile uint8_t X_POS_LAST_STATE = 0;  // Последнее состояние энкодера (0...255)
volatile uint8_t Y_PIN = 0;             // Состояние пина Y (1 или 0)

// ============================================================================
// Функции работы с энкодером (DWT-based)
// ============================================================================

static uint32_t last_time_cycles = 0;           // Время последнего импульса в тактах
volatile uint8_t g_encoder_timeout_active = 0;  // Флаг таймаута энкодера

// ============================================================================
// Функции работы с флеш
// ============================================================================
#include <string.h>  // Добавьте этот include для memset

// Определения для разных серий
#if defined(STM32F411xE)
// Функция определения сектора для F411
static uint32_t GET_SECTOR(uint32_t address) {  // Добавьте static
    if (address < 0x08004000) return 0;         // 16KB
    if (address < 0x08008000) return 1;         // 16KB
    if (address < 0x0800C000) return 2;         // 16KB
    if (address < 0x08010000) return 3;         // 16KB
    if (address < 0x08020000) return 4;         // 64KB
    if (address < 0x08040000) return 5;         // 128KB
    if (address < 0x08060000) return 6;         // 128KB
    return 7;                                   // 128KB
}
#endif

void JumpToApplication(uint32_t addr) {
    uint32_t JumpAddress;

    typedef void (*pFunction)(void);  // объявляем пользовательский тип
    pFunction Jump_To_Application;    // и создаём переменную этого типа

    JumpAddress = *(__IO uint32_t*)(addr + 4);  // извлекаем адрес перехода из вектора Reset
    Jump_To_Application = (pFunction)JumpAddress;  // приводим его к пользовательскому типу
    __set_MSP(*(__IO uint32_t*)addr);  // Инициализировать указатель стека пользовательского приложения
                                       // /устанавливаем SP приложения

    HAL_DeInit();  // Сброс всей переферии

    Jump_To_Application();  // Прыгаем по адресу
}

void flash_write(uint32_t Address, uint32_t Data) {
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data);
}

/**
 * @brief  Стирает область флеш-памяти
 * @param  start_address: начальный адрес
 * @param  size: размер области в байтах
 * @retval HAL status
 */
int flash_erase_area(uint32_t start_address, uint32_t size) {
    // Проверка адреса
    if (start_address < FLASH_BASE) {
        return HAL_ERROR;
    }

    HAL_FLASH_Unlock();

    uint32_t PageError = 0;
    FLASH_EraseInitTypeDef pEraseInit;
    memset(&pEraseInit, 0, sizeof(pEraseInit));

    uint32_t end_address = start_address + size;

#if defined(STM32F1)
    // F103 - страницы по 1КБ
    uint32_t start_page = (start_address - FLASH_BASE) / FLASH_PAGE_SIZE;
    uint32_t end_page = (end_address - FLASH_BASE + FLASH_PAGE_SIZE - 1) / FLASH_PAGE_SIZE;

    pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    pEraseInit.PageAddress = FLASH_BASE + (start_page * FLASH_PAGE_SIZE);
    pEraseInit.NbPages = end_page - start_page;

#elif defined(STM32F4)
    // F411 - сектора разного размера
    uint32_t start_sector = GET_SECTOR(start_address);
    uint32_t end_sector = GET_SECTOR(end_address - 1);  // -1 чтобы не выйти за границу

    pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    pEraseInit.Sector = start_sector;
    pEraseInit.NbSectors = end_sector - start_sector + 1;
    pEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;

#elif defined(STM32G4)
    // G431 - страницы по 2КБ
    uint32_t start_page = (start_address - FLASH_BASE) / FLASH_PAGE_SIZE;
    uint32_t end_page = (end_address - FLASH_BASE + FLASH_PAGE_SIZE - 1) / FLASH_PAGE_SIZE;

    pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    pEraseInit.Page = start_page;
    pEraseInit.NbPages = end_page - start_page;
    pEraseInit.Banks = FLASH_BANK_1;
#endif

    int result = HAL_FLASHEx_Erase(&pEraseInit, &PageError);
    HAL_FLASH_Lock();
    return result;
}

uint32_t flash_read(uint32_t address) { return (*(__IO uint32_t*)address); }
// ============================================================================
// Функции работы с флеш END
// ============================================================================

/**
 * @brief Инициализация счетчика циклов DWT
 * @retval None
 */
void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // Включаем DWT
    DWT->CYCCNT = 0;                                 // Сброс счетчика
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;             // Включение счетчика
    last_time_cycles = DWT->CYCCNT;                  // Инициализация базы времени
}

/**
 * @brief Быстрое преобразование тактов в микросекунды (оптимизировано)
 * @param cycles: количество тактов
 * @retval Время в микросекундах
 */
static uint16_t CyclesToMicroseconds(uint32_t cycles) {
#if defined(STM32F1)
    // F103 @ 72 MHz: cycles * 1000000 / 72000000 = cycles / 72
    // Fixed-point: cycles * 0x38E38E39UL >> 35
    return (uint16_t)(((uint64_t)cycles * 0x38E38E39UL) >> 35);

#elif defined(STM32F4)
    // F411 @ 100 MHz: cycles / 100
    return (uint16_t)(cycles / 100);

#elif defined(STM32G4)
    // G431 @ 170 MHz: cycles * 1000000 / 170000000 = cycles / 170
    // Fixed-point: cycles * 0xF0F0F0F1UL >> 36
    return (uint16_t)(((uint64_t)cycles * 0xF0F0F0F1UL) >> 36);

#else
    // Универсальная версия
    return (uint16_t)(((uint64_t)cycles * 1000000ULL) / SystemCoreClock);
#endif
}

/**
 * @brief Обновление данных энкодера с fixed-point арифметикой
 * @param pos_delta Изменение позиции (-1, 0, +1)
 * @retval None
 */
void EncoderX_Update_F103(int8_t pos_delta) {
    uint32_t now_cycles = DWT->CYCCNT;
    uint32_t elapsed_cycles = now_cycles - last_time_cycles;
    last_time_cycles = now_cycles;

    // УНИВЕРСАЛЬНОЕ преобразование тактов в микросекунды
    uint16_t raw_interval = CyclesToMicroseconds(elapsed_cycles);

    // Проверка таймаута
    if (raw_interval >= ENCODER_TIMEOUT_US) {
        W_X_SPEED = 0xFFFF;
        W_X_EN_DIRECT = 0;
        g_encoder_timeout_active = 1;
        return;
    }

    // Обновление глобальных переменных
    W_X_SPEED = raw_interval;
    W_X_EN_DIRECT = (pos_delta > 0) ? 1 : -1;
    g_encoder_timeout_active = 0;
}

/**
 * @brief 1 kHz обработчик для проверки таймаута энкодера
 */
void DWT_1kHz_Handler(void) {
    if (g_encoder_timeout_active) return;

    uint32_t now_cycles = DWT->CYCCNT;
    uint32_t elapsed_cycles = now_cycles - last_time_cycles;

    // Fixed-point преобразование в микросекунды
    uint16_t elapsed_us = CyclesToMicroseconds(elapsed_cycles);

    if (elapsed_us > ENCODER_TIMEOUT_US) {
        g_encoder_timeout_active = 1;
        W_X_SPEED = 0xFFFF;
        W_X_EN_DIRECT = 0;
    }
}

// ============================================================================
// FIFO
// ============================================================================

volatile TYPE_FIFO_POS_Y FIFO_POS_Y = {0};  // Глобальный FIFO для позиций Y
volatile TYPE_FIFO_DATA FIFO_DATA = {0};    // Глобальный FIFO для данных печати

// ============================================================================
// FIFO позиций Y
// ============================================================================

void FifoPosY_Init(void) {
    __disable_irq();       // Отключаем прерывания для атомарной операции
    FIFO_POS_Y.head = 0;   // Сброс индекса головы очереди
    FIFO_POS_Y.tail = 0;   // Сброс индекса хвоста очереди
    FIFO_POS_Y.count = 0;  // Сброс счетчика элементов

    // Очистка массива координат Y
    for (uint32_t i = 0; i < FIFO_POS_Y_SIZE; i++) {
        FIFO_POS_Y.POS_Y[i] = 0;  // Инициализация нулями
    }
    __enable_irq();  // Включаем прерывания
}

uint8_t FifoPosY_Push(volatile int32_t value) {
    __disable_irq();                            // Отключаем прерывания
    if (FIFO_POS_Y.count >= FIFO_POS_Y_SIZE) {  // Проверка переполнения
        __enable_irq();                         // Включаем прерывания
        return 0;                               // Очередь заполнена
    }

    FIFO_POS_Y.POS_Y[FIFO_POS_Y.head] = value;                  // Запись значения
    FIFO_POS_Y.head = (FIFO_POS_Y.head + 1) % FIFO_POS_Y_SIZE;  // Сдвиг головы
    FIFO_POS_Y.count++;                                         // Увеличение счетчика

    __enable_irq();  // Включаем прерывания
    return 1;        // Успешная запись
}

uint8_t FifoPosY_Pop(volatile int32_t* value) {
    __disable_irq();              // Отключаем прерывания
    if (FIFO_POS_Y.count == 0) {  // Проверка пустоты очереди
        __enable_irq();           // Включаем прерывания
        return 0;                 // Очередь пуста
    }

    *value = FIFO_POS_Y.POS_Y[FIFO_POS_Y.tail];                 // Чтение значения
    FIFO_POS_Y.tail = (FIFO_POS_Y.tail + 1) % FIFO_POS_Y_SIZE;  // Сдвиг хвоста
    FIFO_POS_Y.count--;                                         // Уменьшение счетчика

    __enable_irq();  // Включаем прерывания
    return 1;        // Успешное чтение
}

uint8_t FifoPosY_IsEmpty(void) {
    return (FIFO_POS_Y.count == 0);  // Проверка: очередь пуста
}

uint8_t FifoPosY_IsFull(void) {
    return (FIFO_POS_Y.count >= FIFO_POS_Y_SIZE);  // Проверка: очередь заполнена
}

uint8_t FifoPosY_FreeSpace(void) {
    return (uint8_t)(FIFO_POS_Y_SIZE - FIFO_POS_Y.count);  // Возвращает свободные слоты
}

// ============================================================================
// FIFO данных печати
// ============================================================================

void FifoData_Init(void) {
    __disable_irq();                            // Отключаем прерывания для атомарной инициализации
    FIFO_DATA.head = 0;                         // Сброс индекса головы
    FIFO_DATA.tail = 0;                         // Сброс индекса хвоста
    FIFO_DATA.count = 0;                        // Сброс счетчика элементов
    FIFO_DATA.capacity = FIFO_DATA_QUEUE_SIZE;  // Установка максимальной ёмкости
    FIFO_DATA.totalBitPos = 0;                  // Сброс счетчика бит
    FIFO_DATA.byteIndex = 0;                    // Сброс индекса текущего байта
    FIFO_DATA.currentByte = 0;                  // Сброс текущего байта

    // Очистка всех блоков данных
    for (uint32_t i = 0; i < FIFO_DATA_QUEUE_SIZE; i++) {
        for (uint32_t j = 0; j < FIFO_DATA_BLOCK_SIZE; j++) {
            FIFO_DATA.BLOCKS[i][j] = 0;  // Инициализация нулями
        }
    }
    __enable_irq();  // Включаем прерывания
}

uint8_t FifoData_IsEmpty(void) {
    return (FIFO_DATA.count == 0);  // Проверка: очередь пуста
}

uint8_t FifoData_IsFull(void) {
    return (FIFO_DATA.count >= FIFO_DATA.capacity);  // Проверка: очередь заполнена
}

uint8_t FifoData_ReadBit(void) {
    if (FifoData_IsEmpty()) return 0;  // Проверка: FIFO пуст, вернуть 0

    uint16_t fifoHead = FIFO_DATA.head;            // Локальная копия индекса головы
    uint8_t bitIndex = FIFO_DATA.totalBitPos % 8;  // Вычисление текущего бита в байте

    if (bitIndex == 0) {                                    // Если начинается новый байт
        if (FIFO_DATA.byteIndex >= FIFO_DATA_BLOCK_SIZE) {  // Проверка конца блока
            // Переход к следующему блоку данных
            if (FIFO_DATA.count > 0) {                                       // Если есть блоки в FIFO
                FIFO_DATA.head = (FIFO_DATA.head + 1) % FIFO_DATA.capacity;  // Сдвиг головы FIFO
                FIFO_DATA.count--;                                           // Уменьшение счетчика элементов
            }
            FIFO_DATA.byteIndex = 0;  // Сброс индекса байта

            if (FifoData_IsEmpty()) return 1;  // Если FIFO пуст, вернуть 1 (конец данных)
            fifoHead = FIFO_DATA.head;         // Обновление локальной головы
        }

        FIFO_DATA.currentByte = FIFO_DATA.BLOCKS[fifoHead][FIFO_DATA.byteIndex];  // Чтение нового байта
        FIFO_DATA.byteIndex++;                                                    // Увеличение индекса байта
    }

    uint8_t bit = (FIFO_DATA.currentByte >> bitIndex) & 1;  // Извлечение текущего бита
    FIFO_DATA.totalBitPos++;                                // Увеличение общего счетчика бит

    return bit;  // Возврат считанного бита
}

void FifoData_ReadBitReset(void) {
    FIFO_DATA.totalBitPos = 0;  // Сброс счетчика бит
    FIFO_DATA.byteIndex = 0;    // Сброс индекса текущего байта
    interp_counter = 0;         // Сброс интерполяции
    activeBuffer = 0;           // Сброс текущего активного буфера
    NextBuffer = 0;             // Сброс следующего буфера
}

// ============================================================================
// ЗАПУСК ТРЕКИНГА X
// ============================================================================
void XStartTracking(int32_t left_pos, int32_t right_pos) {
    if (X_TRACKING_ACTIVE == 0) {
        X_TRACKING_ACTIVE = 1;
				X_TRACKING_STARTED = 1; 			
				X_STOPPING = 0;        
        // Определяем ближайшую границу
        int32_t dist_to_left = (X_POS > left_pos) 
                                ? (X_POS - left_pos) 
                                : (left_pos - X_POS);
        int32_t dist_to_right = (X_POS > right_pos) 
                                 ? (X_POS - right_pos) 
                                 : (right_pos - X_POS);        
        // Едем к ближайшей границе
        if (dist_to_left < dist_to_right) {
            X_GO_POS = left_pos;
            X_POLAR_DYNAMIC = 0;  // Движение влево
        } else {
            X_GO_POS = right_pos;
            X_POLAR_DYNAMIC = 1;  // Движение вправо
        }
        // Сброс интегральной составляющей PID
        W_X_SPEED_ERROR_INTEGRAL = 0;
    }
}

// ============================================================================
// БЕЗОПАСНАЯ ОСТАНОВКА ТРЕКИНГА
// ============================================================================
void XStopTracking(void) {	
		X_STOPPING = 1;		
}

// ============================================================================
// Основной обработчик энкодера и логики печати
// ============================================================================
void PrintStep(void) {
///	if (motorXMode == MOTORX_MODE_STEP) return; // исключаем правку X_POS энкодером
    // Таблица направлений энкодера (Грей-код)
    static const int8_t increment[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
    uint16_t gpio_state = ReadEncoderPins();  // Чтение пинов энкодера
    uint8_t X_POS_STATE =
        ((gpio_state & ENCODER_B_PIN) ? 1 : 0) | (((gpio_state & ENCODER_A_PIN) ? 1 : 0) << 1);

    if (X_POS_STATE == X_POS_LAST_STATE) return;                          // Нет изменений — выход
    int8_t pos_delta = increment[X_POS_STATE | (X_POS_LAST_STATE << 2)];  // Расчет приращения
    X_POS += pos_delta;                                                   // Обновление позиции X
    X_POS_LAST_STATE = X_POS_STATE;                                       // Сохранение состояния
    if (pos_delta != 0) {
        EncoderX_Update_F103(pos_delta);  // Обновление времени в логике F103
        // --- Старт печати при достижении левой границы и движении вправо и 3 проходов---
        if (pos_delta > 0 && PRINT_ACTIVE && X_POS == PRINT_LEFT_BORDER - 1 && CURRENT_PRINT_DIRECTION == 0) {
            PRINT_ACTIVE_COUNT++;  // Счетчик активных шагов
            if (PRINT_ACTIVE_COUNT >= PRINT_ACTIVE_COUNT_THRESHOLD) {
                PRINT_ACTIVE = 0;  // Сброс активности
                START_PRINT = 1;   // Разрешение старта печати

                activeBuffer = 0;  // Сброс активного буфера
                NextBuffer = 0;    // Сброс следующего буфера
                // Предзагрузка первого буфера битов
                for (uint8_t i = 0; i < INTERPOL_X; i++) {
                    nextPrintBit[activeBuffer][i] = FifoData_ReadBit();
                }
                // Извлечение следующей координаты Y
                if (FifoPosY_Pop(&Y_FINISH_POS)) {
                    Y_IMAGE_POSITION = 0;  // Сброс позиции изображения
                } else {
                    PrintStopJob(PRINT_STATUS_END);  // Завершить печать при отсутствии данных
                    return;
                }
            }
        }
    }

    // --- Основной процесс печати ---
    if (START_PRINT) {
        // Проверка нахождения в зоне печати
        if (X_POS >= PRINT_LEFT_BORDER && X_POS <= PRINT_RIGHT_BORDER) {
            activeBuffer = NextBuffer;  // Переключение буфера
            // Управление лазером по текущему биту
            SetLaserPWM(nextPrintBit[activeBuffer][0] ? PRINT_CONFIG.DAT.W_SET_LAZER : 0);
            // Запуск интерполяции (дробных шагов)
            if (INTERPOL_X > 1) {
                interp_counter = 1;
                InterpTimerStart(W_X_SPEED / INTERPOL_X);
            }
            // Подготовка следующего буфера битов
            NextBuffer = activeBuffer ^ 1;
            for (uint8_t i = 0; i < INTERPOL_X; i++) {
                nextPrintBit[NextBuffer][i] = FifoData_ReadBit();
            }
        } else {
            // Вне области печати — лазер выключен
            SetLaserPWM(0);
        }

        // --- Смена направления движения (вправо → влево) ---
        if ((W_X_EN_DIRECT == 1) && (X_POS > PRINT_RIGHT_BORDER) && (CURRENT_PRINT_DIRECTION == 0)) {
            SetLaserPWM(0);
            if (FifoPosY_Pop(&Y_FINISH_POS)) {
                Y_IMAGE_POSITION++;           // Переход к следующей строке
                CURRENT_PRINT_DIRECTION = 1;  // Изменение направления
            } else {
                PrintStopJob(PRINT_STATUS_END);  // Нет данных — останов
                return;
            }
        }

        // --- Смена направления движения (влево → вправо) ---
        if ((W_X_EN_DIRECT == -1) && (X_POS < PRINT_LEFT_BORDER) && (CURRENT_PRINT_DIRECTION == 1)) {
            SetLaserPWM(0);
            if (FifoPosY_Pop(&Y_FINISH_POS)) {
                Y_IMAGE_POSITION++;           // Следующая строка
                CURRENT_PRINT_DIRECTION = 0;  // Направление вправо
            } else {
                PrintStopJob(PRINT_STATUS_END);  // Конец данных
                return;
            }
        }
    }
}

// ============================================================================
// Обработчик печати для STEPPER режима (без энкодера)
// ============================================================================
void PrintStepForStepper(int8_t direction) {
	  EncoderX_Update_F103(direction);  // Обновление времени в логике F103
    // --- Старт печати при достижении левой границы и движении вправо ---
    if (direction > 0 && PRINT_ACTIVE && X_POS == PRINT_LEFT_BORDER - 1 && CURRENT_PRINT_DIRECTION == 0) {
        PRINT_ACTIVE_COUNT++;
        if (PRINT_ACTIVE_COUNT >= PRINT_ACTIVE_COUNT_THRESHOLD) {
            PRINT_ACTIVE = 0;
            START_PRINT = 1;
            
            activeBuffer = 0;
            NextBuffer = 0;
            
            // Предзагрузка первого буфера битов
            for (uint8_t i = 0; i < INTERPOL_X; i++) {
                nextPrintBit[activeBuffer][i] = FifoData_ReadBit();
            }
            
            // Извлечение следующей координаты Y
            if (FifoPosY_Pop(&Y_FINISH_POS)) {
                Y_IMAGE_POSITION = 0;
            } else {
                PrintStopJob(PRINT_STATUS_END);
                return;
            }
        }
    }
    
    // --- Основной процесс печати ---
    if (START_PRINT) {
        // Проверка нахождения в зоне печати
        if (X_POS >= PRINT_LEFT_BORDER && X_POS <= PRINT_RIGHT_BORDER) {
            activeBuffer = NextBuffer;
            
            // Управление лазером по текущему биту
            SetLaserPWM(nextPrintBit[activeBuffer][0] ? PRINT_CONFIG.DAT.W_SET_LAZER : 0);
            
            // Запуск интерполяции (дробных шагов)
            if (INTERPOL_X > 1) {
                interp_counter = 1;
                InterpTimerStart(X_REAL_SPED / INTERPOL_X);
            }
            
            // Подготовка следующего буфера битов
            NextBuffer = activeBuffer ^ 1;
            for (uint8_t i = 0; i < INTERPOL_X; i++) {
                nextPrintBit[NextBuffer][i] = FifoData_ReadBit();
            }
        } else {
            // Вне области печати — лазер выключен
            SetLaserPWM(0);
        }
        
        // --- Смена направления движения (вправо → влево) ---
        if ((direction > 0) && (X_POS > PRINT_RIGHT_BORDER) && (CURRENT_PRINT_DIRECTION == 0)) {
            SetLaserPWM(0);
            if (FifoPosY_Pop(&Y_FINISH_POS)) {
                Y_IMAGE_POSITION++;
                CURRENT_PRINT_DIRECTION = 1;
            } else {
                PrintStopJob(PRINT_STATUS_END);
                return;
            }
        }
        
        // --- Смена направления движения (влево → вправо) ---
        if ((direction < 0) && (X_POS < PRINT_LEFT_BORDER) && (CURRENT_PRINT_DIRECTION == 1)) {
            SetLaserPWM(0);
            if (FifoPosY_Pop(&Y_FINISH_POS)) {
                Y_IMAGE_POSITION++;
                CURRENT_PRINT_DIRECTION = 0;
            } else {
                PrintStopJob(PRINT_STATUS_END);
                return;
            }
        }
    }
}

// ============================================================================
// Выполнение одного шага интерполяции
// Возвращает 1 — если серия интерполированных шагов завершена
// ============================================================================
uint8_t PrintStepInterp(void) {
    // Установка мощности лазера в зависимости от текущего бита
    if (nextPrintBit[activeBuffer][interp_counter]) {
        SetLaserPWM(PRINT_CONFIG.DAT.W_SET_LAZER);
    } else {
        SetLaserPWM(0);
    }
    interp_counter++;  // Переход к следующему биту
    if (interp_counter >= INTERPOL_X) {
        return 1;  // Серия интерполированных шагов завершена
    }
    return 0;  // Продолжаем выполнение серии
}

// ============================================================================
// Остановка задания печати и сброс параметров
// ============================================================================
void PrintStopJob(T_PRINT_STATUS PRINT_STATUS) {
    // Выключение лазера
    SetLaserPWM(0);
    
    // Сброс активных флагов процесса печати
    START_PRINT = 0;
    SetupPrintJob = 0;
    
    // ========================================================
    // БЕЗОПАСНАЯ ОСТАНОВКА ТРЕКИНГА
    // ========================================================
    XStopTracking();  
    
    // Обновление статуса печати
    PRINT_CONFIG.DAT.R_PRINT_STATUS = PRINT_STATUS;
    needSendStatusReport = 1;
}

// Приём и полная обработка 64-байтного пакета
void PacketReceive(uint8_t* buffer) {
    if (buffer == NULL) return;
    uint8_t event_idx = buffer[0];  // Первый байт — индекс команды
    uint8_t state = 0;              // Не используется в текущей логике, но сохранён для совместимости
    // ============================================================================
    // ОБРАБОТКА ПАКЕТА ДАННЫХ ПЕЧАТИ (IDX_PRINT_DATA)
    // ============================================================================
    if (event_idx == IDX_PRINT_DATA) {
        TYPE_PRINT_DATA* PRINT_DAT =
            (TYPE_PRINT_DATA*)(buffer - 1);  // Смещение на 1 байт (из-за структуры BIN[64])
        // ============================================================================
        // Обработка состояния FIFO данных и запуск DMA для новых данных
        // ============================================================================
        __disable_irq();
        if ((FIFO_DATA.count >= FIFO_DATA.capacity) || (PRINT_DAT->DAT.R_FIFO_FUL == 1)) {
            PRINT_DAT->DAT.R_FIFO_FUL = 1;
            PRINT_DAT->DAT.R_FIFO_COUNT = FIFO_DATA.count;
            __enable_irq();
        } else {
            uint16_t next_tail = (FIFO_DATA.tail + 1) % FIFO_DATA.capacity;
            __enable_irq();
            // Передаём
            FIFO_DATA_StartDma((uint32_t)PRINT_DAT->DAT.W_BUFFER, (uint32_t)FIFO_DATA.BLOCKS[FIFO_DATA.tail],
                               sizeof(FIFO_DATA.BLOCKS[0])  // или FIFO_DATA_BLOCK_SIZE, если определено
            );
            PRINT_DAT->DAT.R_FIFO_FUL = 0;
            PRINT_DAT->DAT.R_FIFO_COUNT = FIFO_DATA.count;
        }
        // ============================================================================
        // Обработка FIFO координат Y
        // ============================================================================
        __disable_irq();
        if (PRINT_DAT->DAT.R_FIFO_Y_COUNT == 1) {
            FifoPosY_Push(PRINT_DAT->DAT.W_Y_BUFFER);
        }
        PRINT_DAT->DAT.R_FIFO_Y_COUNT = FifoPosY_FreeSpace();
        __enable_irq();
        // Обновление параметров управления
        PRINT_CONFIG.DAT.W_SET_LAZER = PRINT_DAT->DAT.W_SET_LAZER;
        W_X_SPEED_SET = PRINT_DAT->DAT.W_X_SPEED;
				
            // Параметры разгона/торможения для степпера
            X_MIN_POW = PRINT_DAT->DAT.W_X_SPEED;  // Минимальный период (максимальная скорость)
            										
        // Обратная связь
        PRINT_DAT->DAT.W_X_SPEED = W_X_SPEED;
        PRINT_DAT->DAT.RW_Y_IMAGE_POSITION = Y_IMAGE_POSITION;

        if (PRINT_CONFIG.DAT.R_PRINT_STATUS == PRINT_STATUS_PRINT) {
            PacketSend(PRINT_DAT->BIN);
        }
    }
    // ============================================================================
    // ОБРАБОТКА КОНФИГУРАЦИИ ПЕЧАТИ (IDX_PRINT_CONFIG)
    // ============================================================================
    else if (event_idx == IDX_PRINT_CONFIG) {
        memcpy(PRINT_CONFIG.BIN + 1, buffer, 63);
        if (PRINT_CONFIG.DAT.R_PRINT_STATUS == PRINT_STATUS_PRINT) {
            SetupPrintJob = 1;
        } else if (PRINT_CONFIG.DAT.R_PRINT_STATUS > PRINT_STATUS_PRINT) {
            PrintStopJob(PRINT_CONFIG.DAT.R_PRINT_STATUS);
        }
    }
    // ============================================================================
    // ОБРАБОТКА ТЮНИНГА ОСИ X (IDX_USB_TUNING_X)
    // ============================================================================
    else if (event_idx == IDX_USB_TUNING_X) {
        memcpy(USB_TUNING_X.BIN + 1, buffer, 63);
        uint32_t Delitel = ((USB_TUNING_X.DAT.W_ADRES - 1) / 25) * 25;
        // Защита от выхода за границы массива
        if (Delitel < 1000) {
            for (int i = 0; i < 25 && (Delitel + i) < 1000; i++) {
                TUNING_X[Delitel + i] = USB_TUNING_X.DAT.TUNING_X[i];
            }
        }
        PacketSend(USB_TUNING_X.BIN);
    }    
    // ============================================================================
    // ОБРАБОТКА ТЮНИНГА ОСИ Y (IDX_USB_TUNING_Y)
    // ============================================================================
    else if (event_idx == IDX_USB_TUNING_Y) {
        memcpy(USB_TUNING_Y.BIN + 1, buffer, 63);
        uint32_t Delitel = ((USB_TUNING_Y.DAT.W_ADRES - 1) / 25) * 25;
        for (int i = 0; i < 25; i++) {
            TUNING_Y[Delitel + i] = USB_TUNING_Y.DAT.TUNING_Y[i];
        }
        PacketSend(USB_TUNING_Y.BIN);
    }    
    // ============================================================================
    // СБРОС СИСТЕМЫ (IDX_RESET)
    // ============================================================================
    else if (event_idx == IDX_RESET) {
        memcpy(APP_RESET.BIN + 1, buffer, 63);
        HAL_NVIC_SystemReset();
    }
    // ============================================================================
    // ЗАПРОС ИДЕНТИФИКАЦИИ (IDX_APP_ID)
    // ============================================================================
    else if (event_idx == IDX_APP_ID) {
        APP_ID.DAT.R_IDX = IDX_APP_ID;
        APP_ID.DAT.W_CURENT = 0;
        // Чтение и проверка BOOT прошивки
        uint32_t KEY0 = flash_read(BASE_BOOT_VER);
        uint32_t KEY1 = flash_read(BASE_BOOT_VER + 4);
        uint32_t KEY2 = flash_read(BASE_BOOT_VER + 8);
        uint32_t KEY3 = flash_read(BASE_BOOT_VER + 12);
        uint32_t _VER = flash_read(BASE_BOOT_VER + 16);
        APP_ID.DAT.W_B_NAME[0] = KEY0;
        APP_ID.DAT.W_B_NAME[1] = KEY1;
        APP_ID.DAT.W_B_NAME[2] = KEY2;
        APP_ID.DAT.W_B_NAME[3] = KEY3;
        if ((KEY0 == BOOT_SIG_KEY0) && (KEY1 == BOOT_SIG_KEY1) && (KEY2 == BOOT_SIG_KEY2) &&
            (KEY3 == BOOT_SIG_KEY3)) {
            APP_ID.DAT.W_B_VER = _VER;
        } else {
            APP_ID.DAT.W_B_VER = 0;
        }
        // Чтение и проверка APP прошивки
        KEY0 = flash_read(BASE_APP_VER);
        KEY1 = flash_read(BASE_APP_VER + 4);
        KEY2 = flash_read(BASE_APP_VER + 8);
        KEY3 = flash_read(BASE_APP_VER + 12);
        _VER = flash_read(BASE_APP_VER + 16);
        APP_ID.DAT.W_A_NAME[0] = KEY0;
        APP_ID.DAT.W_A_NAME[1] = KEY1;
        APP_ID.DAT.W_A_NAME[2] = KEY2;
        APP_ID.DAT.W_A_NAME[3] = KEY3;
        if ((KEY0 == APP_SIG_KEY0) && (KEY1 == APP_SIG_KEY1) && (KEY2 == APP_SIG_KEY2) &&
            (KEY3 == APP_SIG_KEY3)) {
            APP_ID.DAT.W_A_VER = _VER;
        } else {
            APP_ID.DAT.W_A_VER = 0;
        }
        // Уникальный ID микроконтроллера
        APP_ID.DAT.W_ID[0] = HAL_GetUIDw0();
        APP_ID.DAT.W_ID[1] = HAL_GetUIDw1();
        APP_ID.DAT.W_ID[2] = HAL_GetUIDw2();
        APP_ID.DAT.ID = 0;
				
				APP_ID.DAT.W_X_POS = X_POS;
				APP_ID.DAT.W_Y_POS = Y_POS;
				
        // Отправка данных хосту
        PacketSend(APP_ID.BIN);
    }
    // ============================================================================
    // СТИРАНИЕ ПАМЯТИ (IDX_ERASE)
    // ============================================================================
    else if (event_idx == IDX_ERASE) {
        memcpy(APP_ERASE.BIN + 1, buffer, 63);
        // flash_erase(APP_ERASE.DAT.W_START, APP_ERASE.DAT.W_COUNT);
        flash_erase_area(APP_ERASE.DAT.W_START, APP_ERASE.DAT.W_COUNT);
        PacketSend(APP_ERASE.BIN);
    }
    // ============================================================================
    // ЗАПИСЬ В ПАМЯТЬ (IDX_WRITE)
    // ============================================================================
    else if (event_idx == IDX_WRITE) {
        memcpy(APP_WRITE.BIN + 1, buffer, 63);
        uint8_t COUNT = (APP_WRITE.DAT.W_COUNT + 3) >> 2;  // байты → 32-битные слова

        HAL_FLASH_Unlock();
        for (int i = 0; i < COUNT; i++) {
            flash_write(APP_WRITE.DAT.W_ADRES + (i * 4), APP_WRITE.DAT.W_INFO[i]);
        }
        HAL_FLASH_Lock();

        PacketSend(APP_WRITE.BIN);
    }
    // ============================================================================
    // ТЕСТ СКОРОСТИ (IDX_APP_SPEED_TEST)
    // ============================================================================
    else if (event_idx == IDX_APP_SPEED_TEST) {
        memcpy(APP_SPEED_TEST.BIN + 1, buffer, 63);
        APP_SPEED_TEST.DAT.R_IDX = IDX_APP_SPEED_TEST;
        APP_SPEED_TEST.DAT.ID = 0;
        PacketSend(APP_SPEED_TEST.BIN);
    }
    // ============================================================================
    // ПЕРЕХОД В BOOTLOADER (IDX_JAMP_TO)
    // ============================================================================
    else if (event_idx == IDX_JAMP_TO) {
        memcpy(APP_JAMP_TO.BIN + 1, buffer, 63);
        HAL_FLASH_Unlock();
        flash_write(BASE_BOOT_JUMP_FLAG_ADDR, BOOT_JUMP_FLAG_SET);  // Флаг перехода в BOOT
        HAL_FLASH_Lock();
        HAL_NVIC_SystemReset();
    }
    // ============================================================================
    // УПРАВЛЕНИЕ ЛАЗЕРОМ (IDX_LAZER)
    // ============================================================================		
		else if (event_idx == IDX_LAZER) {
				memcpy(LAZER.BIN + 1, buffer, 63);
				SetLaserLightPWMFrequency(LAZER.DAT.W_SET_L_FREQ);
				SetLaserPWM(LAZER.DAT.W_SET_L);
		}		
    // ============================================================================
    // УПРАВЛЕНИЕ ПОДСВЕТКОЙ (IDX_LIGHT)
    // ============================================================================
    else if (event_idx == IDX_LIGHT) {
        memcpy(LIGHT.BIN + 1, buffer, 63);
        SetLightPWM(LIGHT.DAT.W_SET_L);
    }
    // ============================================================================
    // НАСТРОЙКА ОСИ X (IDX_SET_X)
    // ============================================================================
		else if (event_idx == IDX_SET_X) {
				memcpy(SET_X.BIN + 1, buffer, 63);
				
				W_X_POL_DIR = SET_X.DAT.W_X_POL_DIR;
				W_X_POL_PWM = SET_X.DAT.W_X_POL_PWM;
				MotorX_Init(SET_X.DAT.W_X_MODE);
				
				if (SET_X.DAT.W_X_POL_EN == 0) {
						ENCODER_A_PIN = 0x0040;
						ENCODER_B_PIN = 0x0100;
				} else {
						ENCODER_A_PIN = 0x0100;
						ENCODER_B_PIN = 0x0040;
				}
				
				if (SET_X.DAT.W_X_RESET == 1) {
						X_POS = 0;
						X_GO_POS = 0;
						SET_X.DAT.W_X_MOV_POS = 0; 
						SET_X.DAT.W_X_RESET = 0;
				}
				
				// ========================================================
				// ЛОГИКА ВКЛЮЧЕНИЯ/ВЫКЛЮЧЕНИЯ ТРЕКИНГА
				// ========================================================
				if (SET_X.DAT.W_X_TRECK == 1) {
						// Запуск трекинга
						W_X_POWER_MAX = SET_X.DAT.W_X_POWER_MAX;
						W_X_SPEED_SET = SET_X.DAT.W_X_SPEED_SET;
						X_Kp = SET_X.DAT.W_X_KP;
						X_Ki = SET_X.DAT.W_X_KI;
						X_Kd = SET_X.DAT.W_X_KD;
					
						XStartTracking(SET_X.DAT.W_X_L_POS, SET_X.DAT.W_X_R_POS);
				} 
				else 
				{
						// ========================================================
						// ВЫКЛЮЧЕНИЕ ТРЕКИНГА - БЕЗОПАСНАЯ ОСТАНОВКА
						// ========================================================
								
						XStopTracking(); // Трекинг был включен - останавливаем безопасно
						W_X_POWER_MAX = SET_X.DAT.W_X_POWER_MAX;
						W_X_SPEED_SET = SET_X.DAT.W_X_SPEED_SET;

				}
				
				// === Управление ENABLE пином оси X ===
				XSetEnablePin(SET_X.DAT.W_X_ENABLED_PIN);
				
				// Для степпера
				X_MIN_POW = SET_X.DAT.W_X_MIN_POW;
				X_ACCL = SET_X.DAT.W_X_ACCL;
				
				if (SET_X.DAT.W_X_POL_DIR == 1) {
						X_DIR_HI = 1;
						X_DIR_LO = 0;
				} else {
						X_DIR_HI = 0;
						X_DIR_LO = 1;
				}
				
				if (SET_X.DAT.W_X_POL_PWM == 1) {
						X_STEP_HI = 1;
						X_STEP_LO = 0;
				} else {
						X_STEP_HI = 0;
						X_STEP_LO = 1;
				}
				
				// === Отправляем пакет подтверждения ===
				SET_X.DAT.W_X_EN_POS = X_POS;
				SET_X.DAT.W_X_EN_SPEED = W_X_SPEED;
				SET_X.DAT.W_WRITE = 0;
				SET_X.DAT.R_IDX = IDX_SET_X;
				PacketSend(SET_X.BIN);
		}

    // ============================================================================
    // НАСТРОЙКА ОСИ Y (IDX_SET_Y)
    // ============================================================================
    else if (event_idx == IDX_SET_Y) {
        memcpy(SET_Y.BIN + 1, buffer, 63);
        Y_MIN_POW = SET_Y.DAT.W_Y_MIN_POW;
        Y_ACCL = SET_Y.DAT.W_Y_ACCL;
        Y_MOTION = SET_Y.DAT.W_Y_MOTION;

        if (SET_Y.DAT.W_Y_POS_WRITE == 1) {
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
				
				YSetEnablePin(SET_Y.DAT.W_Y_ENABLED);
				
				SET_Y.DAT.W_Y_EN_POS = Y_POS;
				
        SET_Y.DAT.W_WRITE = 0;
        SET_Y.DAT.R_IDX = IDX_SET_Y;
        PacketSend(SET_Y.BIN);
    }
    // ============================================================================
    // НАСТРОЙКА ОБЩИХ ПАРАМЕТРОВ (IDX_SET_PARAM)
    // ============================================================================
    else if (event_idx == IDX_SET_PARAM) {
        memcpy(SET_PARAM.BIN + 1, buffer, 63);
        // Установка делителя частоты PWM
        SetLaserLightPWMFrequency(SET_PARAM.DAT.W_SET_L_FREQ);
        // Установка уровня подсветки
        SetLightPWM(SET_PARAM.DAT.W_SET_LIGHT);
    }
    // ============================================================================
    // ДАННЫЕ ТРЕКИНГА (IDX_TRACK)
    // ============================================================================
    else if (event_idx == IDX_TRACK) {
        memcpy(TRACK.BIN + 1, buffer, 63);
        TRACK.DAT.W_X_EN_POS = X_POS;
        TRACK.DAT.W_X_EN_SPEED = W_X_SPEED;
        TRACK.DAT.W_X_POWER_REAL = W_X_POWER_REAL;
        TRACK.DAT.POLAR = X_POLAR_DYNAMIC;
        PacketSend(TRACK.BIN);
    }
    // ============================================================================
    // ТЕСТ СКОРОСТИ ЭХО (IDX_SPEED_TEST)
    // ============================================================================
    else if (event_idx == IDX_SPEED_TEST) {
        memcpy(SPEED_TEST.BIN + 1, buffer, 63);
        PacketSend(SPEED_TEST.BIN);
    }
}

// ============================================================================
// Функция завершения DMA (вызов из main.c при окончании копирования блока)
// ============================================================================
void FIFO_DATA_EndDma(void) {
    __disable_irq();  // Отключение прерываний для атомарного обновления FIFO
    // Обновление индексов FIFO после успешной DMA передачи
    if (FIFO_DATA.count < FIFO_DATA.capacity) {                      // Проверка, есть ли место в FIFO
        FIFO_DATA.tail = (FIFO_DATA.tail + 1) % FIFO_DATA.capacity;  // Сдвиг хвоста
        FIFO_DATA.count++;                                           // Увеличение счетчика элементов
    }
    __enable_irq();  // Включение прерываний
    // Активация печати при получении данных
    if (PRINT_CONFIG.DAT.R_PRINT_STATUS == PRINT_STATUS_PRINT &&  // Проверка, что идет печать
        PRINT_ACTIVE == 0 && START_PRINT == 0) {                  // Проверка флагов активности
        PRINT_ACTIVE = 1;                                         // Устанавливаем флаг активной печати
        PRINT_ACTIVE_COUNT = 0;                                   // Сброс счетчика активной печати
    }
}

// ============================================================================
// Инициализация SDK (вызов из main.c один раз при старте системы)
// ============================================================================
void Lpp_Init(void) {
    // Проверка флага перехода в BOOTloader.
    // Если приложение (APP) установило BOOT_JUMP_FLAG_SET,
    // выполняем прямой переход на старт BOOT (BASE_BOOT_START_ADDR)
    if ((*(__IO uint32_t*)BASE_BOOT_JUMP_FLAG_ADDR) == BOOT_JUMP_FLAG_SET) {
        JumpToApplication(BASE_BOOT_START_ADDR);
    }
		
		motorXMode = 255;  // Принудительная инициализация при первом вызове
    // Инициализация параметров печати
    PRINT_CONFIG.DAT.R_PRINT_STATUS = PRINT_STATUS_END;
    // Инициализация подсистем SDK
    FifoData_Init();  // Очистка FIFO данных печати
    FifoPosY_Init();  // Очистка FIFO координат Y
		HAL_Delay(100);
    DWT_Init();       // Инициализация таймера точного времени
    //    PRINT_ACTIVE = 0;     // Сброс флагов состояния
    //    START_PRINT = 0;
    //    SetupPrintJob = 0;

    // При необходимости можно добавить инициализацию лазера, мотора и т.п.
    // SetLaserPWM(0);
    // MotorX_Init(MOTORX_MODE_START);
}

// ============================================================================
// Основной цикл SDK (вызов из бесконечного while в main.c)
// ============================================================================
void Lpp_MainLoop(void) {
    
    HAL_Delay(1); 
    DWT_1kHz_Handler();    
    
    // Обработка отправки статуса печати
    if (needSendStatusReport) {
        needSendStatusReport = 0;
        // Попытка отправки с повторениями
        uint8_t retryCount = 3;
        while (retryCount-- > 0) {
            if (PacketSend(PRINT_CONFIG.BIN) == 0) {  // 0 - USBD_OK
                break;
            }
            HAL_Delay(10);  // Задержка между попытками
        }
    }

    // ========================================================
    // ИНИЦИАЛИЗАЦИЯ ЗАДАНИЯ ПЕЧАТИ
    // ========================================================
    if (SetupPrintJob == 1) {
        SetupPrintJob = 0;
        
        // Инициализация параметров печати
        Y_LINES = PRINT_CONFIG.DAT.W_Y_LINES;        // Число строк в изображении
        INTERPOL_X = PRINT_CONFIG.DAT.W_INTERPOL_X;  // Коэффициент интерполяции
        START_PRINT = 0;                             // Сброс флага начала
        
        FifoData_Init();  // Сброс FIFO данных печати
        FifoPosY_Init();  // Сброс FIFO позиций Y
        
        // Установка статуса "занят"
        PRINT_CONFIG.DAT.R_PRINT_STATUS = PRINT_STATUS_BUSY;
        Y_IMAGE_POSITION = 0;  // Сброс позиции строки
        
        // Инициализация переменных печати
        CURRENT_PRINT_DIRECTION = 0;  // Начальное направление слева направо
        
        // Определение границ зоны печати
        PRINT_LEFT_BORDER = PRINT_CONFIG.DAT.W_LASER_INITIAL_POSITION_X;
        PRINT_RIGHT_BORDER = PRINT_LEFT_BORDER + PRINT_CONFIG.DAT.W_BOARD_LENGTH_X - 1;
        
        // Позиционирование по оси Y
        Y_FINISH_POS = PRINT_CONFIG.DAT.W_LASER_INITIAL_POSITION_Y;
        
        // Ожидание достижения позиции Y
        uint8_t y_position_ready = 0;
        for (int i = 0; i < 100; i++) {
            HAL_Delay(100);
            if (Y_FINISH_POS == Y_POS) {
                y_position_ready = 1;
                break;
            }
        }
        
        // Проверка успешности позиционирования Y
        if (!y_position_ready) {
            PRINT_CONFIG.DAT.R_PRINT_STATUS = PRINT_STATUS_ERROR_Y;
            PacketSend(PRINT_CONFIG.BIN);
        } else {
            // ========================================================
            // УСПЕШНОЕ ПОЗИЦИОНИРОВАНИЕ Y - ЗАПУСК ПЕЧАТИ
            // ========================================================
            
            // Сброс флагов печати
            START_PRINT = 0;
            PRINT_ACTIVE = 0;
            PRINT_ACTIVE_COUNT = 0;
            CURRENT_PRINT_DIRECTION = 0;
            FifoData_ReadBitReset();  // Сброс состояния чтения битов

        if (motorXMode == MOTORX_MODE_STEP) {
            // ========================================================
            // ИНИЦИАЛИЗАЦИЯ ДЛЯ СТЕППЕРА
            // ========================================================
            // Параметры разгона/торможения для степпера
            X_MIN_POW = PRINT_CONFIG.DAT.W_X_SPEED_SET;  // Минимальный период (максимальная скорость)
            X_ACCL = PRINT_CONFIG.DAT.W_X_AXIS_ACCELERATION;  // Длина зоны разгона в шагах
            
            // Границы с учетом разгона/торможения
            SET_X.DAT.W_X_L_POS = PRINT_CONFIG.DAT.W_LASER_INITIAL_POSITION_X - X_ACCL;
            SET_X.DAT.W_X_R_POS = PRINT_CONFIG.DAT.W_LASER_INITIAL_POSITION_X +
                                  PRINT_CONFIG.DAT.W_BOARD_LENGTH_X + X_ACCL;
						
						XStartTracking(SET_X.DAT.W_X_L_POS, SET_X.DAT.W_X_R_POS); 		
				
        } else {
            // ========================================================
            // ИНИЦИАЛИЗАЦИЯ ДЛЯ DC МОТОРА
            // ========================================================
            // ========================================================
            // НАСТРОЙКА ПАРАМЕТРОВ УПРАВЛЕНИЯ ОСЬЮ X
            // ========================================================
            W_X_POWER_MAX = PRINT_CONFIG.DAT.W_X_POWER_MAX;  // Максимальная мощность
            W_X_SPEED_SET = PRINT_CONFIG.DAT.W_X_SPEED_SET;  // Скорость движения
            X_Kp = PRINT_CONFIG.DAT.W_X_KP;                  // Коэффициент P
            X_Ki = PRINT_CONFIG.DAT.W_X_KI;                  // Коэффициент I
            X_Kd = PRINT_CONFIG.DAT.W_X_KD;                  // Коэффициент D
            
            // Установка крайних позиций с учетом зоны разгона/торможения
            SET_X.DAT.W_X_L_POS = PRINT_CONFIG.DAT.W_LASER_INITIAL_POSITION_X - 
                                  PRINT_CONFIG.DAT.W_X_AXIS_ACCELERATION;
            SET_X.DAT.W_X_R_POS = PRINT_CONFIG.DAT.W_LASER_INITIAL_POSITION_X +
                                  PRINT_CONFIG.DAT.W_BOARD_LENGTH_X + 
                                  PRINT_CONFIG.DAT.W_X_AXIS_ACCELERATION;

            // ========================================================
            // ЗАПУСК ТРЕКИНГА (НОВАЯ ЛОГИКА)
            // ========================================================
            // Автоматический запуск трекинга с определением ближайшей границы
            XStartTracking(SET_X.DAT.W_X_L_POS, SET_X.DAT.W_X_R_POS); 														
				}					

        // ========================================================
        // ЗАВЕРШЕНИЕ ИНИЦИАЛИЗАЦИИ (общее для обоих режимов)
        // ========================================================        
        PRINT_CONFIG.DAT.R_PRINT_STATUS = PRINT_STATUS_PRINT;
        PacketSend(PRINT_CONFIG.BIN);
        }
    }
}

// ============================================================================
// Движение по оси Y
// direction: 1 = вверх, -1 = вниз
// ============================================================================
void YMove(int direction) {
    if (Y_PIN == 1) {
        Y_PIN = 0;
        YTimerStep(Y_STEP_HI);  // Фронт STEP
        Y_POS += direction;     // Обновляем позицию
    } else {
        Y_PIN = 1;
        // Установка направления перед импульсом
        if (direction == 1) {
            YTimerSetDir(Y_DIR_HI);  // Вверх
        } else {
            YTimerSetDir(Y_DIR_LO);  // Вниз
        }
        YTimerStep(Y_STEP_LO);  // Подготовка к следующему шагу
    }
}

// ============================================================================
// Расчет мощности (скорости) для оси Y
// ============================================================================
int YCalculatePower(void) {
    int index = 0;
    // Расчет середины пути между стартовой и конечной позицией
    Y_HALF_POS = Y_START_POS + ((Y_FINISH_POS - Y_START_POS) / 2);
    // --- Если целевая позиция ниже текущей — двигаемся вниз ---
    if (Y_FINISH_POS < Y_POS) {
        YMove(-1);  // Делаем один шаг вниз
        // Выбираем участок разгона или торможения по положению относительно середины
        index = (Y_POS > Y_HALF_POS) ? (Y_START_POS - Y_POS) : (Y_POS - Y_FINISH_POS);
    }
    // --- Если целевая позиция выше текущей — двигаемся вверх ---
    else if (Y_FINISH_POS > Y_POS) {
        YMove(1);  // Делаем один шаг вверх
        index = (Y_POS < Y_HALF_POS) ? (Y_POS - Y_START_POS) : (Y_FINISH_POS - Y_POS);
    }
    // --- Если достигнута целевая позиция ---
    else {
        index = 0;  // Скорость минимальная (остановка)
    }
    // Ограничение диапазона индекса, чтобы не выйти за границы массива TUNING_Y
    if (index < 0) index = 0;
    if (index >= Y_ACCL) index = Y_ACCL - 1;
    // Расчет мощности (скорости) на основе таблицы ускорения
    int power = Y_MIN_POW + TUNING_Y[index];
    // Возвращаем положительное значение мощности
    return (power > 0) ? power : 1;
}

// ============================================================================
// Обработчик таймера оси Y
// (вызывать из прерывания таймера в main.c)
// ============================================================================
void YTimerCallback(void) {
    // Определяем конечную позицию для текущего режима движения
    if (Y_MOTION == 1) Y_FINISH_POS = Y_POS + Y_ACCL;  // движение вверх
    if (Y_MOTION == 2) Y_FINISH_POS = Y_POS - Y_ACCL;  // движение вниз
    // Обновляем статус: 0 = BUSY, 1 = READY
    Y_STATUS = (Y_FINISH_POS == Y_POS) ? 1 : 0;
    // Если движение продолжается — вычисляем скорость/мощность, иначе ставим минимальную
    Y_REAL_SPED = (Y_FINISH_POS != Y_POS) ? YCalculatePower() : 1;
    // Если мы только начали или закончили движение — обновляем стартовую точку
    Y_START_POS = ((Y_POS == Y_START_POS) || (Y_POS == Y_FINISH_POS)) ? Y_POS : Y_START_POS;
    // Настраиваем таймер на новый период (зависит от скорости)
    // Это задаёт частоту вызовов YTimerCallback, а значит — частоту шагов
    YTimerSet(Y_REAL_SPED);
}

// ============================================================================
// Движение по оси X (в режиме MOTORX_MODE_STEP)
// direction: 1 = вправо, -1 = влево
// ============================================================================
void XMove(int direction) {
    if (X_PIN == 1) {
        X_PIN = 0;
        XTimerStep(X_STEP_HI);  // Фронт STEP
        X_POS += direction;
			
        // Обработка печати после каждого шага
        PrintStepForStepper(direction);			
			
    } else {
        X_PIN = 1;
        if (direction == 1) {
            XTimerSetDir(X_DIR_HI);  // Вправо
        } else {
            XTimerSetDir(X_DIR_LO);  // Влево
        }
        XTimerStep(X_STEP_LO);  // Подготовка к следующему шагу
    }
}

// ============================================================================
// Расчет периода (скорости) для оси X в шаговом режиме
// ============================================================================
int XCalculatePower(void) {
    int index = 0;
    // Расчет середины пути
    X_HALF_POS = X_START_POS + ((X_GO_POS - X_START_POS) / 2);

    if (X_GO_POS < X_POS) {
        // Движение влево
        XMove(-1);
        index = (X_POS > X_HALF_POS) ? (X_START_POS - X_POS) : (X_POS - X_GO_POS);
    } else if (X_GO_POS > X_POS) {
        // Движение вправо
        XMove(1);
        index = (X_POS < X_HALF_POS) ? (X_POS - X_START_POS) : (X_GO_POS - X_POS);
    } else {
        index = 0;  // Остановка
    }
    if (index < 0) index = 0;
    if (index >= X_ACCL) index = X_ACCL - 1;
    // Используем  массив TUNING_X
    int period = X_MIN_POW + TUNING_X[index];
    return (period > 0) ? period : 1;
}

// ============================================================================
// ОБРАБОТЧИК ЛОГИКИ ОСИ X - секция трекинга
// По сути сам ПИД X
// ============================================================================
void XTimerCallback(void) {
		// ========================================================
		// РЕЖИМ ШАГОВОГО МОТОРА
		// ========================================================
		if (motorXMode == MOTORX_MODE_STEP) {
				// --- Определяем стартовую позицию при начале движения ---
				if (X_POS == X_START_POS || X_POS == X_GO_POS) X_START_POS = X_POS; 
				
				// Если мы только начали или закончили движение — обновляем стартовую точку
				//Y_START_POS = ((Y_POS == Y_START_POS) || (Y_POS == Y_FINISH_POS)) ? Y_POS : Y_START_POS;
			
			
				// ========================================================
				// ОСТАНОВ ТРЕКИНГА ПРИ ДОСТИЖЕНИИ ЦЕЛЕВОЙ ПОЗИЦИИ
				// ========================================================			
				if (X_STOPPING) {
						if (X_POS == X_GO_POS) {
			        X_TRACKING_ACTIVE = 0;
							X_TRACKING_STARTED = 0;  							
						}									
				}	
				
				// ========================================================
				// РЕЖИМ ЦИКЛИЧЕСКОГО БЕГА (ТРЕКИНГ)
				// ========================================================
				if (X_TRACKING_STARTED) {
						if (X_POS <= SET_X.DAT.W_X_L_POS) {
								X_GO_POS = SET_X.DAT.W_X_R_POS;
						}
						if (X_POS >= SET_X.DAT.W_X_R_POS) {
								X_GO_POS = SET_X.DAT.W_X_L_POS;
						}
				}							

				// ========================================================
				// РЕЖИМ ПОЗИЦИОНИРОВАНИЯ 
				// ========================================================
				else {
						// Обычный режим позиционирования: двигаемся к W_X_MOV_POS
						if (X_GO_POS != SET_X.DAT.W_X_MOV_POS) {
								X_GO_POS = SET_X.DAT.W_X_MOV_POS;
						}
				}

				// ========================================================
				// ОБЩИЙ РАСЧЕТ СКОРОСТИ И УСТАНОВКА ТАЙМЕРА
				// ========================================================
				X_REAL_SPED = (X_GO_POS != X_POS) ? XCalculatePower() : 1;
				XTimerSet(X_REAL_SPED);

				X_TRACKING_STARTED_OLD = X_TRACKING_STARTED;
		}
		
    // ========================================================
    // РЕЖИМ DC МОТОРА
    // ========================================================
    else {
        // ========================================================
        // Режим циклического бега (трекинг)
        // ========================================================
        if (X_TRACKING_STARTED == 1) {
            // --- 1. Фильтрация скорости энкодера ---
            if (W_X_SPEED == 0 || W_X_SPEED == 0xFFFF) {
                W_X_SPEED_FILTERED = 0;
            } else if (W_X_SPEED >= SPEED_MIN_TICKS && W_X_SPEED <= SPEED_MAX_TICKS) {
                int32_t speed_val = 65535 / (int32_t)W_X_SPEED;
                W_X_SPEED_FILTERED = (W_X_EN_DIRECT == 1)    ? speed_val
                                     : (W_X_EN_DIRECT == -1) ? -speed_val
                                                             : 0;
            }
            
            // --- 2. ЖЕСТКАЯ проверка граничных позиций ---
            if (X_POS >= SET_X.DAT.W_X_R_POS) {
                if (X_POLAR_DYNAMIC != 1) {
                    X_POLAR_DYNAMIC = 1;  // Разворот влево
                    W_X_SPEED_ERROR_INTEGRAL = 0;  // Сброс интегратора
                }
            } 
            else if (X_POS <= SET_X.DAT.W_X_L_POS) {
                if (X_POLAR_DYNAMIC != 0) {
                    X_POLAR_DYNAMIC = 0;  // Разворот вправо
                    W_X_SPEED_ERROR_INTEGRAL = 0;
                }
            }
            
            // --- 3. Целевая скорость со знаком ---
            W_X_SPEED_SET_POLAR = (X_POLAR_DYNAMIC == 0) ? W_X_SPEED_SET : -W_X_SPEED_SET;
            
            // --- 4. PID-регулятор ---
            W_X_SPEED_ERROR = W_X_SPEED_SET_POLAR - W_X_SPEED_FILTERED;
            W_X_P_component = (int32_t)W_X_SPEED_ERROR * (int32_t)X_Kp;
            
            W_X_SPEED_ERROR_INTEGRAL += W_X_SPEED_ERROR;
            if (W_X_SPEED_ERROR_INTEGRAL > X_INTEGRAL_MAX)
                W_X_SPEED_ERROR_INTEGRAL = X_INTEGRAL_MAX;
            else if (W_X_SPEED_ERROR_INTEGRAL < X_INTEGRAL_MIN)
                W_X_SPEED_ERROR_INTEGRAL = X_INTEGRAL_MIN;
            
            W_X_I_component = (W_X_SPEED_ERROR_INTEGRAL * (int32_t)X_Ki) / 100;
            W_X_PI_sum = W_X_P_component + W_X_I_component;
            
            if (W_X_PI_sum > 32767)
                W_X_PI_sum = 32767;
            else if (W_X_PI_sum < -32768)
                W_X_PI_sum = -32768;
            
            W_X_POWER_REAL = (int16_t)W_X_PI_sum;
            
            if (W_X_POWER_REAL > W_X_POWER_MAX)
                W_X_POWER_REAL = W_X_POWER_MAX;
            else if (W_X_POWER_REAL < -W_X_POWER_MAX)
                W_X_POWER_REAL = -W_X_POWER_MAX;
            
            MotorX_Set(W_X_POWER_REAL);
        }
        
        // ========================================================
        // Режим позиционирования
        // ========================================================
        else {
					
						X_GO_POS = SET_X.DAT.W_X_MOV_POS;
					
            if (SET_X.DAT.W_X_ENABLED == 1) {
                if (W_X_SPEED == 0 || W_X_SPEED == 0xFFFF)
                    W_X_SPEED_FILTERED = 0;
                else
                    W_X_SPEED_FILTERED = 65535 / (int32_t)W_X_SPEED;
                
                int32_t position_error = X_GO_POS - X_POS;
                if (position_error == 0) {
                    W_X_POWER_REAL = 0;
                } else {
                    uint8_t target_polar = (position_error > 0) ? 1 : 0;
                    
                    if ((X_START_STATIC_ACTIVE == 1) || (X_POLAR_STATIC != target_polar)) {
                        X_POLAR_STATIC = target_polar;
                        W_X_POWER_REAL = 0;
                        X_START_STATIC_ACTIVE = 0;
                    }
                    
                    if (X_POLAR_STATIC == 0) {
                        W_X_POWER_REAL += (W_X_SPEED_FILTERED > W_X_SPEED_SET) 
                                          ? SET_X.DAT.W_X_POWER_STEP
                                          : -SET_X.DAT.W_X_POWER_STEP;
                    } else {
                        W_X_POWER_REAL += (W_X_SPEED_FILTERED > W_X_SPEED_SET) 
                                          ? -SET_X.DAT.W_X_POWER_STEP
                                          : SET_X.DAT.W_X_POWER_STEP;
                    }
                }
                
                if (W_X_POWER_REAL > W_X_POWER_MAX) W_X_POWER_REAL = W_X_POWER_MAX;
                if (W_X_POWER_REAL < -W_X_POWER_MAX) W_X_POWER_REAL = -W_X_POWER_MAX;
                MotorX_Set(W_X_POWER_REAL);
            } else {
                MotorX_Set(0);
            }
        }
    }
}



