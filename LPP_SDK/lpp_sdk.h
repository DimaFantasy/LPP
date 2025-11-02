/**
 ******************************************************************************
 * @file    lpp_sdk.h
 * @brief   Laser Printer Platform (LPP) — SDK global declarations
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


#ifndef LPP_SDK_H
#define LPP_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

// Includes ------------------------------------------------------------------
#include <stdint.h>

#if defined(STM32F103xB)
#include "configs/lpp_config_f103.h"
#elif defined(STM32G431xx)
#include "configs/lpp_config_g431.h"
#elif defined(STM32F411xE)
#include "configs/lpp_config_f411.h"
#else
#error "Define before including lpp_globals.h"
#endif

// Базовые константы системы

#define LEFT 1   // Направление движения: влево
#define RIGHT 0  // Направление движения: вправо

#define MK_WRITE 1  // Режим записи данных в память
#define MK_READ 0   // Режим чтения данных из памяти

// Буферы для двойной буферизации данных печати

#define PRINT_ACTIVE_COUNT_THRESHOLD 3  // Количество проходов каретки для активации печати

#define INTERPOL_MAX 4  // Максимальный коэффициент интерполяции (X8)

// Режимы работы мотора X
typedef enum {
    MOTORX_MODE_START = 0,    // Отключение пинов (высокий импеданс)
    MOTORX_MODE_ONE_PWM = 1,  // Режим: один ШИМ (PB13 = TIM1_CH1N) + DIR (PB14 = GPIO)
    MOTORX_MODE_TWO_PWM = 2,  // Режим: два ШИМ канала (PB13 = TIM1_CH1N, PB14 = TIM1_CH2N)
    MOTORX_MODE_STEP = 3      // Режим шагового двигателя: PB13 = STEP, PB14 = DIR (GPIO)
} MotorXMode_t;

// Состояния движения по оси Y
typedef enum {
    MOVE_HALT = 0,            // Остановка
    MOVE_DOWN = 1,            // Движение вниз
    MOVE_UP = 2,              // Движение вверх
    MOVE_CONTINUOUS_UP = 3,   // Непрерывное движение вверх
    MOVE_CONTINUOUS_DOWN = 4  // Непрерывное движение вниз
} Y_MOVE_STATES;

// Статусы процесса печати
typedef enum {
    PRINT_STATUS_PRINT = 0,    // Печать в процессе
    PRINT_STATUS_END = 1,      // Печать успешно окончена
    PRINT_STATUS_ABORT = 3,    // Отмена пользователем
    PRINT_STATUS_ERROR = 2,    // Общая ошибка
    PRINT_STATUS_ERROR_Y = 4,  // Ошибка позиционирования по Y
    PRINT_STATUS_ERROR_X = 5,  // Ошибка позиционирования по X
    PRINT_STATUS_BUSY = 6      // Занят (инициализация)
} T_PRINT_STATUS;

// Статус готовности оси Y
typedef enum {
    Y_STATUS_BUSY = 0,  // Ось занята: выполняется команда
    Y_STATUS_READY = 1  // Ось готова: можно отправлять новую команду
} Y_STATUS_T;

// Направление движения оси Y
typedef enum {
    Y_MOTION_NONE = 0,  // Нет движения
    Y_MOTION_UP = 1,    // Движение вверх
    Y_MOTION_DOWN = 2   // Движение вниз
} Y_MOTION_T;


#define IDX_PRINT_CONFIG 35  // Идентификатор пакета конфигурации печати
// Структура конфигурации параметров печати
typedef union {
    struct {
        // Заголовок пакета
        uint8_t ID;        // Идентификатор структуры
        uint8_t R_IDX;     // ID пакета
        uint8_t W_WRITE;   // Режим записи/чтения (1 - запись, 0 - чтение)
        uint8_t W_CURENT;  // Режим работы (0 - APP, 1 - BOOT)
        // Настройки оси X
        uint16_t W_X_SPEED;  // Скорость движения каретки при перемещении
        // Настройки лазера
        uint16_t W_SET_LAZER;  // Установка тока лазера
        // Параметры позиционирования
        int32_t W_LASER_INITIAL_POSITION_X;  // Начальная позиция лазера по X
        int32_t W_LASER_INITIAL_POSITION_Y;  // Начальная позиция лазера по Y
        int32_t W_BOARD_LENGTH_X;            // Длина платы по X
        int32_t W_X_AXIS_ACCELERATION;       // Откат для торможения и разгона по оси X
        // Статус и управление печатью
        uint8_t R_PRINT_STATUS;  // Текущий статус печати
        uint8_t W_INTERPOL_X;    // Коэффициент интерполяции X
        uint32_t W_Y_LINES;      // Число строк по Y
        // Настройки частоты
//        uint16_t W_SET_L_PRESCALER;  // Установка частоты, предделитель
        // Параметры управления осью X
        uint16_t W_X_POWER_MAX;  // Максимальная мощность X (0..500)
        uint16_t W_X_SPEED_SET;  // Скорость движения каретки
        uint8_t W_X_KP;          // Коэффициент пропорционального управления
        uint8_t W_X_KI;          // Коэффициент интегрального управления
        uint8_t W_X_KD;          // Коэффициент дифференциального управления
    } DAT;
    uint8_t BIN[64];  // Бинарное представление структуры
} TYPE_PRINT_CONFIG;

#define IDX_PRINT_DATA 34  // Идентификатор пакета данных печати
// Структура данных печати для передачи через USB
typedef union {
    struct {
        // Заголовок пакета
        uint8_t ID;            // Идентификатор пакета
        uint8_t R_IDX;         // ID пакета
        uint8_t R_FIFO_FUL;    // Флаг переполнения FIFO
        uint8_t R_FIFO_COUNT;  // Количество элементов в FIFO
        // Позиционные данные
        int32_t RW_Y_IMAGE_POSITION;  // Текущая/следующая позиция Y в изображении
        int32_t W_Y_BUFFER;           // Данные буфера Y
        // Параметры управления
        uint16_t W_X_SPEED;    // Скорость движения каретки
        uint16_t W_SET_LAZER;  // Ток лазера
        // Статус FIFO Y
        int8_t R_FIFO_Y_COUNT;  // Количество записанных данных Y
        // Выравнивание
        uint8_t RESERVED1;  // Резервный байт
        uint8_t RESERVED2;  // Резервный байт
        uint8_t RESERVED3;  // Резервный байт
        // Буфер данных
        uint8_t W_BUFFER[44];  // Буфер FIFO данных печати
    } DAT;
    uint8_t BIN[64];  // Бинарное представление
} TYPE_PRINT_DATA;

#define IDX_USB_TUNING_X 39  // Идентификатор пакета тюнинга X
// Структура для тюнинга ускорения/торможения оси X
typedef union {
    struct {
        uint8_t ID;             // Идентификатор
        uint8_t R_IDX;          // ID пакета
        uint8_t W_WRITE;        // Режим записи/чтения
        uint8_t W_CURENT;       // Режим работы
        uint16_t W_ADRES;       // Адрес/параметр
        uint16_t TUNING_X[25];  // Массив настроек ускорения мотора
    } DAT;
    uint8_t BIN[64];
} TYPE_USB_TUNING_X;

#define IDX_USB_TUNING_Y 33  // Идентификатор пакета тюнинга Y
// Структура для тюнинга ускорения/торможения оси Y
typedef union {
    struct {
        uint8_t ID;             // Идентификатор
        uint8_t R_IDX;          // ID пакета
        uint8_t W_WRITE;        // Режим записи/чтения
        uint8_t W_CURENT;       // Режим работы
        uint16_t W_ADRES;       // Адрес/параметр
        uint16_t TUNING_Y[25];  // Массив настроек ускорения мотора
    } DAT;
    uint8_t BIN[64];
} TYPE_USB_TUNING_Y;

#define IDX_RESET 32  // Идентификатор пакета сброса
// Структура для перезагрузки контроллера
typedef union {
    struct {
        uint8_t ID;        // Идентификатор
        uint8_t R_IDX;     // ID пакета
        uint8_t W_WRITE;   // Режим записи
        uint8_t W_CURENT;  // Режим работы
        uint32_t W_ADRES;  // Адрес для сброса
    } DAT;
    uint8_t BIN[64];
} TYPE_APP_RESET;

#define IDX_TRACK 31  // Идентификатор пакета трекера
// Структура данных трекера движения
typedef union {
    struct {
        uint8_t ID;              // Идентификатор
        uint8_t R_IDX;           // ID пакета
        uint8_t W_WRITE;         // Режим записи
        uint8_t W_CURENT;        // Режим работы
        int32_t W_X_EN_POS;      // Положение каретки
        uint16_t W_X_EN_SPEED;   // Скорость движения каретки
        int16_t W_X_POWER_REAL;  // Реальная мощность на моторе
        uint8_t POLAR;           // Направление движения каретки
    } DAT;
    uint8_t BIN[64];
} TYPE_TRACK;

#define IDX_LPP_ID 15  // Идентификатор пакета уникального идентификатора
// Структура уникального идентификатора
typedef union {
    struct {
        uint8_t R_IDX;    // ID пакета
        uint8_t W_WRITE;  // Режим записи/чтения
        uint8_t R_SW0;    // Номер прошивки 1
        uint8_t R_SW1;    // Номер прошивки 2
        uint8_t R_SW2;    // Номер прошивки 3
        uint8_t R_SW3;    // Номер прошивки 4
        uint32_t R_ID0;   // Серийный номер чипа 1
        uint32_t R_ID1;   // Серийный номер чипа 2
        uint32_t R_ID2;   // Серийный номер чипа 3
    } DAT;
    uint8_t BIN[64];
} TYPE_LPP_ID;

#define IDX_SET_X 36  // Идентификатор пакета настройки X
// Структура настройки параметров оси X
typedef union {
    struct {
        uint8_t ID;              // Идентификатор
        uint8_t R_IDX;           // ID пакета
        uint8_t W_WRITE;         // Режим записи
        uint8_t W_ANSVER;        // Флаг ответа
        int32_t W_X_L_POS;       // Позиция слева X
        int32_t W_X_R_POS;       // Позиция справа X
        int32_t W_X_MOV_POS;     // Целевая позиция движения
        uint16_t W_X_POWER_MAX;  // Максимальная мощность X
        uint16_t W_X_SPEED_SET;  // Скорость движения оси X
        uint8_t W_X_POWER_STEP;  // Коррекция скорости на шаг
        uint8_t W_X_ENABLED;     // Включение контроля движения
        uint8_t W_X_TRECK;       // Старт трека
        uint8_t W_X_POS_WRITE;   // Запись позиции энкодера
        int32_t W_X_EN_POS;      // Положение энкодера
        uint16_t W_X_EN_SPEED;   // Скорость энкодера
        int16_t W_DIV_X_TR;      // Делитель частоты (движение)
        int16_t W_DIV_X_ST;      // Делитель частоты (стояние)
        uint8_t W_X_KP;          // Коэффициент P
        uint8_t W_X_KI;          // Коэффициент I
        uint8_t W_X_KD;          // Коэффициент D
        uint8_t W_X_RESET;       // Сброс позиции каретки
        uint8_t W_X_POL_EN;      // Полярность энкодера
        uint8_t W_X_POL_PWM;     // Полярность H-моста
        uint8_t W_X_POL_DIR;     // Полярность DIR
        uint8_t W_X_MODE;        // Режим энкодера
				
        int16_t W_X_ACCL;       // Ускорение X						
        int16_t W_X_MIN_POW;    // Минимальная мощность X
        uint8_t W_X_ENABLED_PIN;// Включить контролер				
		
				
    } DAT;
    uint8_t BIN[64];
} TYPE_SET_X;

#define IDX_SET_Y 37  // Идентификатор пакета настройки Y
// Структура настройки параметров оси Y
typedef union {
    struct {
        uint8_t ID;             // Идентификатор
        uint8_t R_IDX;          // ID пакета
        uint8_t W_WRITE;        // Режим записи
        uint8_t W_ANSVER;       // Флаг ответа
        int32_t W_Y_EN_POS;     // Реальная позиция каретки Y
        uint8_t W_Y_POS_WRITE;  // Запись позиции Y
        int32_t W_Y_MOV_POS;    // Целевая позиция Y
        int16_t W_Y_MAX_POW;    // Максимальная мощность Y
        int16_t W_Y_MIN_POW;    // Минимальная мощность Y
        int16_t W_Y_ACCL;       // Ускорение Y
        uint8_t W_Y_POL_DIR;    // Направление движения
        uint8_t W_Y_POL_STEP;   // Положительный перепад
        uint8_t W_Y_ENABLED;    // Включение контроллера
        uint8_t W_Y_MOTION;     // Принудительное движение
        uint8_t W_Y_STATUS;     // Статус оси Y
        uint8_t W_Y_RESET;      // Сброс позиции Y
    } DAT;
    uint8_t BIN[64];
} TYPE_SET_Y;

#define IDX_SET_PARAM 38  // Идентификатор пакета общих параметров
// Структура общих параметров системы
typedef union {
    struct {
        uint8_t ID;                  // Идентификатор
        uint8_t R_IDX;               // ID пакета
        uint8_t W_WRITE;             // Режим записи
        uint8_t W_ANSVER;            // Флаг ответа
        uint16_t W_SET_LIGHT;        // Установка тока подсветки
        uint16_t W_SET_LAZER;        // Установка тока лазера
        uint32_t W_SET_L_FREQ;  			// Установка частоты, предделитель
    } DAT;
    uint8_t BIN[64];
} TYPE_SET_PARAM;

#define IDX_LIGHT 19  // Идентификатор пакета подсветки
// Структура управления подсветкой
typedef union {
    struct {
        uint8_t ID;        // Идентификатор
        uint8_t R_IDX;     // ID пакета
        uint8_t W_WRITE;   // Режим записи
        uint8_t W_CURENT;  // Режим работы
        uint16_t W_SET_L;  // Установка тока подсветки
    } DAT;
    uint8_t BIN[64];
} TYPE_LIGHT;

#define IDX_LAZER 17  // Идентификатор пакета лазера
// Структура управления лазером
typedef union {
    struct {
        uint8_t ID;                  // Идентификатор
        uint8_t R_IDX;               // ID пакета
        uint8_t W_WRITE;             // Режим записи
        uint8_t W_CURENT;            // Режим работы
        uint16_t W_SET_L;            // Мощность лазера
        uint32_t W_SET_L_FREQ;  // Установка частоты, предделитель
    } DAT;
    uint8_t BIN[64];
} TYPE_LAZER;

#define IDX_JAMP_TO 25  // Идентификатор пакета перехода
// Структура перехода по адресу
typedef union {
    struct {
        uint8_t ID;        // Идентификатор
        uint8_t R_IDX;     // ID пакета
        uint8_t W_WRITE;   // Режим записи
        uint8_t W_CURENT;  // Режим работы
        uint8_t W_ADRES;   // Адрес назначения
    } DAT;
    uint8_t BIN[64];
} TYPE_APP_JAMP_TO;

#define IDX_APP_SPEED_TEST 24  // Идентификатор пакета теста скорости
// Структура теста скорости
typedef union {
    struct {
        uint8_t ID;          // Идентификатор
        uint8_t R_IDX;       // ID пакета
        uint8_t W_WRITE;     // Режим записи
        uint8_t W_CURENT;    // Режим работы
        uint8_t W_INFO[55];  // Массив данных
    } DAT;
    uint8_t BIN[64];
} TYPE_APP_SPEED_TEST;

#define IDX_WRITE 23  // Идентификатор пакета записи
// Структура записи в FLASH память
typedef union {
    struct {
        uint8_t ID;           // Идентификатор
        uint8_t R_IDX;        // ID пакета
        uint8_t W_CURENT;     // Режим работы
        uint8_t W_COUNT;      // Число прошитых байт
        uint32_t W_ADRES;     // Адрес начала
        uint32_t W_INFO[14];  // Данные для записи
    } DAT;
    uint8_t BIN[64];
} TYPE_APP_WRITE;

#define IDX_ERASE 22  // Идентификатор пакета стирания
// Структура стирания FLASH памяти
typedef union {
    struct {
        uint8_t ID;        // Идентификатор
        uint8_t R_IDX;     // ID пакета
        uint8_t W_WRITE;   // Режим записи
        uint8_t W_CURENT;  // Режим работы
        uint32_t W_START;  // Адрес начала
        uint32_t W_COUNT;  // Число данных для стирания
    } DAT;
    uint8_t BIN[64];
} TYPE_APP_ERASE;

#define IDX_APP_ID 21
typedef union {
    struct {
        uint8_t ID;            // Идентификатор
        uint8_t R_IDX;         // ID пакета
        uint8_t W_WRITE;       // Режим записи
        uint8_t W_CURENT;      // Режим работы
        uint32_t W_ID[3];      // Идентификаторы
        uint32_t W_A_VER;      // Версия APP
        uint32_t W_B_VER;      // Версия BOOT
        uint32_t W_A_NAME[4];  // Имя APP
        uint32_t W_B_NAME[4];  // Имя BOOT
				int32_t W_X_POS; // Позиция X
				int32_t W_Y_POS; // Позиция Y
    } DAT;
    uint8_t BIN[64];
} TYPE_APP_ID;

#define IDX_SPEED_TEST 24
typedef union {
    struct {
        uint8_t ID;        // Идентификатор
        uint8_t R_IDX;     // ID пакета
        uint8_t W_WRITE;   // Режим записи
        uint8_t W_CURENT;  // Режим работы
    } DAT;
    uint8_t BIN[64];
} TYPE_SPEED_TEST;


// Константы работы с энкодером (DWT-based)
#define ENCODER_TIMEOUT_US 60000  // Таймаут энкодера в микросекундах
#define SPEED_MIN_TICKS 50        // Минимальный допустимый период
#define SPEED_MAX_TICKS 60000     // Максимальный допустимый период

// Константы для ограничения интегральной составляющей PID
#define X_INTEGRAL_MAX 10000   // Максимальное значение интеграла
#define X_INTEGRAL_MIN -10000  // Минимальное значение интеграла

// Константы работы FIFO данных печати
#define FIFO_DATA_BLOCK_SIZE 44  // Размер блока данных изображения, байт
#define FIFO_DATA_QUEUE_SIZE 30  // Количество блоков в очереди печати

typedef struct {
    uint8_t BLOCKS[FIFO_DATA_QUEUE_SIZE][FIFO_DATA_BLOCK_SIZE];  // Очередь блоков данных
    uint8_t head;                                                // Индекс головы очереди
    uint8_t tail;                                                // Индекс хвоста очереди
    uint8_t count;                                               // Текущее количество элементов
    uint8_t capacity;      // Ёмкость очереди (обычно FIFO_DATA_QUEUE_SIZE)
    uint32_t totalBitPos;  // Общая битовая позиция для потока данных
    uint16_t byteIndex;    // Индекс текущего байта внутри блока
    uint16_t currentByte;  // Текущий байт в процессе обработки
} TYPE_FIFO_DATA;

// FIFO позиций Y

#define FIFO_POS_Y_SIZE 10  // Количество элементов в очереди позиций Y

typedef struct {
    int32_t POS_Y[FIFO_POS_Y_SIZE];  // Очередь значений позиций Y
    uint8_t head;                    // Индекс головы очереди
    uint8_t tail;                    // Индекс хвоста очереди
    uint8_t count;                   // Текущее количество элементов
} TYPE_FIFO_POS_Y;

// ============================================================================
// Колбэки и управление печатью
// ============================================================================

// Полярность управления мотором X
extern volatile uint8_t W_X_POL_DIR;  // Полярность направления
extern volatile uint8_t W_X_POL_PWM;  // Полярность ШИМ

extern MotorXMode_t motorXMode;

// Пины энкодера
extern volatile uint16_t ENCODER_A_PIN;  // Пин энкодера A
extern volatile uint16_t ENCODER_B_PIN;  // Пин энкодера B

void DWT_Init(void);
void DWT_1kHz_Handler(void);
void EncoderX_Update_F103(int8_t pos_delta);

// Управление лазером и подсветкой (реализуется в main.c)
extern void SetLaserPWM(uint16_t pwm_value);      // Установка мощности лазера (ШИМ)
extern void SetLightPWM(uint16_t pwm_value);      // Установка мощности подсветки (ШИМ)
extern void SetLaserLightPWMFrequency(uint32_t prescaler);  // Установка делителя частоты PWM лазера и подсветки

extern void InterpTimerStart(uint32_t period);  // Запуск таймера интерполяции
extern uint16_t ReadEncoderPins(void);          // Чтение состояния выводов энкодера

// Основной обработчик энкодера и печати
void PrintStep(void);  

// Один шаг интерполяции. Возвращает 1 — если серия интерполированных шагов завершена
uint8_t PrintStepInterp(void);  

// Остановка задания печати и сброс параметров
void PrintStopJob(T_PRINT_STATUS PRINT_STATUS);  

// Отправка 64-байтного пакета хосту (реализуется в main.c, но вызывается из SDK)
extern uint8_t PacketSend(uint8_t* buffer);
// Приём и обработка 64-байтного пакета от хоста
void PacketReceive(uint8_t* buffer);

// Функция запуска DMA (реализуется в main.c, но вызывается из SDK)
extern void FIFO_DATA_StartDma(uint32_t src_addr, uint32_t dst_addr, uint16_t size);
// Функция завершения DMA
void FIFO_DATA_EndDma(void);

// Инициализация SDK (вызов из main.c один раз при старте системы)
void Lpp_Init(void);
// Основной цикл SDK (вызов из бесконечного while в main.c)
void Lpp_MainLoop(void);

// Управление мотором Y

// Таймерный обработчик оси Y, вызывается 1 кГц
// Рассчитывает скорость, управляет шагами и ускорением
// Логика реализована в SDK
void YTimerCallback(void);
// Установить период таймера Y, управляет частотой вызова YTimerCallback()
// **Реализовать в main.c**
extern void YTimerSet(uint16_t period);
// Установить физическое направление мотора Y (DIR)
// **Реализовать в main.c**
extern void YTimerSetDir(uint8_t dir_pin_state);
// Сгенерировать импульс STEP для мотора Y
// **Реализовать в main.c**
extern void YTimerStep(uint8_t step_pin_state);
// Управление сигналом ENABLE (включение/выключение драйвера)
// **Реализовать в main.c**
extern void YSetEnablePin(uint8_t enabled);

// Управление мотором X

// Таймерный обработчик X, вызывается циклически (примерно, 1 кГц)
// Рассчитывает PID, позицию и управляет реальной мощностью
// Логика реализована в SDK
void XTimerCallback(void);
// Инициализация мотора X с указанным режимом работы
// MOTORX_MODE_START/ONE_PWM/TWO_PWM/STEP
// **Реализовать в main.c**
extern void MotorX_Init(MotorXMode_t mode);
// Установка мощности мотора X с учетом направления и полярности
// power = [-W_X_POWER_MAX..+W_X_POWER_MAX]
// **Реализовать в main.c**
extern void MotorX_Set(int power);

// Установка периода и запуск TIM1 для шагов X (в режиме MOTORX_MODE_STEP)
extern void XTimerSet(uint16_t period);
// Установить физическое направление мотора X (DIR) (в режиме MOTORX_MODE_STEP)
// **Реализовать в main.c**
extern void XTimerSetDir(uint8_t dir_pin_state);
// Сгенерировать импульс STEP для мотора Y (в режиме MOTORX_MODE_STEP)
// **Реализовать в main.c**
extern void XTimerStep(uint8_t step_pin_state);
// Управление сигналом ENABLE (включение/выключение драйвера)
// **Реализовать в main.c**
extern void XSetEnablePin(uint8_t enabled);

#ifdef __cplusplus
}
#endif

#endif /* LPP_GLOBALS_H */