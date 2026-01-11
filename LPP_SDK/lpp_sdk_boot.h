#ifndef LPP_SDK_BOOT_H
#define LPP_SDK_BOOT_H

#include <stdint.h>

#if defined(STM32F103xB)
#include "configs/lpp_config_f103.h"
#elif defined(STM32G431xx)
#if defined(USE_LPP_G431_ALT)
#include "configs/lpp_config_g431_alt.h"
#else
#include "configs/lpp_config_g431.h"
#endif
#elif defined(STM32F411xE)
#include "configs/lpp_config_f411.h"
#else
#error "Define before including lpp_globals.h"
#endif

/* ================= MCU ADAPT ================= */

#if defined(STM32F103xB)
#define LPP_FLASH_PAGE_SIZE 1024
#elif defined(STM32F411xE)
#define LPP_FLASH_PAGE_SIZE 16384
#elif defined(STM32G431xx)
#define LPP_FLASH_PAGE_SIZE 2048
#else
#error "Unsupported MCU"
#endif

/* ================= PROTOCOL IDX (SDK compatible) ================= */

#define IDX_APP_ID 21
#define IDX_ERASE 22
#define IDX_WRITE 23
#define IDX_RESET 32  // Идентификатор пакета сброса

/* ================= SDK TYPES (COPIED) ================= */

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
        int32_t W_X_POS;       // Позиция X
        int32_t W_Y_POS;       // Позиция Y
    } DAT;
    uint8_t BIN[64];
} TYPE_APP_ID;

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

#define IDX_RESET 32  // Идентификатор пакета сброса
// Структура для перезагрузки контроллера
typedef union {
    struct {
        uint8_t ID;        // Идентификатор
        uint8_t R_IDX;     // ID пакета
        uint8_t W_WRITE;   // Режим записи
        uint8_t W_CURENT;  // Режим работы
    } DAT;
    uint8_t BIN[64];
} TYPE_APP_RESET;

// Отправка 64-байтного пакета хосту (реализуется в main.c, но вызывается из SDK)
extern uint8_t PacketSend(uint8_t* buffer);
// Приём и обработка 64-байтного пакета от хоста
void PacketReceive(uint8_t* buffer);

#endif
