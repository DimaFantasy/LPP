#include "lpp_sdk_boot.h"

#include <string.h>

/* ================= HAL INCLUDE ================= */

#if defined(STM32F103xB)
#include "stm32f1xx_hal.h"
#elif defined(STM32F411xE)
#include "stm32f4xx_hal.h"
#elif defined(STM32G431xx)
#include "stm32g4xx_hal.h"
#else
#error "Unsupported HAL"
#endif

#if defined(STM32F411xE)
static uint32_t GET_SECTOR(uint32_t address)
{
    if (address < 0x08004000) return FLASH_SECTOR_0;
    if (address < 0x08008000) return FLASH_SECTOR_1;
    if (address < 0x0800C000) return FLASH_SECTOR_2;
    if (address < 0x08010000) return FLASH_SECTOR_3;
    if (address < 0x08020000) return FLASH_SECTOR_4;
    if (address < 0x08040000) return FLASH_SECTOR_5;
    if (address < 0x08060000) return FLASH_SECTOR_6;
    return FLASH_SECTOR_7;
}
#endif

TYPE_APP_ID APP_ID = {0};
TYPE_APP_ERASE APP_ERASE = {0};
TYPE_APP_WRITE APP_WRITE = {0};
TYPE_APP_RESET APP_RESET = {0};

/* ================= FLASH ================= */

static uint32_t flash_read(uint32_t addr) { return *(__IO uint32_t*)addr; }

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

#if defined(STM32F103xB)
    // F103 - страницы по 1КБ
    uint32_t start_page = (start_address - FLASH_BASE) / FLASH_PAGE_SIZE;
    uint32_t end_page = (end_address - FLASH_BASE + FLASH_PAGE_SIZE - 1) / FLASH_PAGE_SIZE;

    pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    pEraseInit.PageAddress = FLASH_BASE + (start_page * FLASH_PAGE_SIZE);
    pEraseInit.NbPages = end_page - start_page;

#elif defined(STM32F411xE)
    // F411 - сектора разного размера
    uint32_t start_sector = GET_SECTOR(start_address);
    uint32_t end_sector = GET_SECTOR(end_address - 1);  // -1 чтобы не выйти за границу

    pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    pEraseInit.Sector = start_sector;
    pEraseInit.NbSectors = end_sector - start_sector + 1;
    pEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;

#elif defined(STM32G431xx)
    // G431 - страницы по 2КБ
    uint32_t start_page = (start_address - FLASH_BASE) / FLASH_PAGE_SIZE;
    uint32_t end_page = (end_address - 1 - FLASH_BASE) / FLASH_PAGE_SIZE;  // вычитаем 1

    pEraseInit.NbPages = end_page - start_page + 1;
    pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    pEraseInit.Page = start_page;
    pEraseInit.Banks = FLASH_BANK_1;
#endif

    int result = HAL_FLASHEx_Erase(&pEraseInit, &PageError);
    HAL_FLASH_Lock();
    return result;
}

/**
 * @brief  Запись буфера данных во Flash-память
 *
 * Выполняет запись данных во Flash с учётом требований разных серий STM32:
 * STM32F1/F4 — запись 32-битными словами,
 * STM32G4 — запись 64-битными словами с сохранением соседних данных.
 *
 * @param  addr: начальный адрес (выровнен по 4 байтам)
 * @param  data: буфер данных
 * @param  len:  размер данных в байтах
 *
 * @retval  0   — OK
 * @retval -1   — неверные параметры
 * @retval -2   — ошибка записи Flash
 */
int flash_write_buffer(uint32_t addr, const uint8_t* data, uint32_t len) {
    // Проверка входных параметров:
    // адрес должен быть выровнен по 4 байтам,
    // длина не нулевая,
    // указатель данных валиден
    if ((addr & 3) != 0 || (len == 0) || data == NULL) return -1;

    // Разблокируем контроллер Flash для записи
    HAL_FLASH_Unlock();

#if defined(STM32F103xB) || defined(STM32F411xE)

    // STM32F1 / STM32F4:
    // запись производится 32-битными словами (WORD)
    for (uint32_t i = 0; i < len; i += 4) {
        // Формируем 32-битное слово из буфера данных
        uint32_t word = *(uint32_t*)(data + i);

        // Записываем слово во Flash по адресу addr + i
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + i, word) != HAL_OK) {
            // При ошибке сразу блокируем Flash и выходим
            HAL_FLASH_Lock();
            return -2;
        }
    }

#elif defined(STM32G431xx)

    // STM32G4:
    // запись возможна только 64-битными двойными словами (DOUBLEWORD)

    // Конечный адрес записи
    uint32_t end = addr + len;

    // Адрес начала, выровненный по 8 байтам
    uint32_t aligned_start = addr & ~7U;

    // Адрес конца, выровненный по 8 байтам (в большую сторону)
    uint32_t aligned_end = (end + 7) & ~7U;

    // Проходим по Flash блоками по 8 байт
    for (uint32_t a = aligned_start; a < aligned_end; a += 8) {
        // Читаем текущее 64-битное значение из Flash
        uint64_t current = *(volatile uint64_t*)a;

        // Подготавливаем новое значение (изначально текущее)
        uint64_t new_val = current;

        // -------------------------------
        // Младшие 32 бита (адрес a)
        // -------------------------------
        // Если этот участок попадает в диапазон записи —
        // подменяем младшее слово данными из буфера
        if (a >= addr && a < end) {
            uint32_t lo = *(uint32_t*)(data + (a - addr));
            new_val = (new_val & 0xFFFFFFFF00000000ULL) | lo;
        }

        // -------------------------------
        // Старшие 32 бита (адрес a + 4)
        // -------------------------------
        // Аналогично для старшего слова
        if ((a + 4) >= addr && (a + 4) < end) {
            uint32_t hi = *(uint32_t*)(data + (a + 4 - addr));
            new_val = (new_val & 0x00000000FFFFFFFFULL) | ((uint64_t)hi << 32);
        }

        // Если новое значение отличается от текущего —
        // выполняем запись во Flash
        if (new_val != current) {
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, a, new_val) != HAL_OK) {
                // При ошибке блокируем Flash и выходим
                HAL_FLASH_Lock();
                return -2;
            }
        }
    }

#else
#error "Unsupported STM32 series"
#endif

    // Блокируем Flash после завершения записи
    HAL_FLASH_Lock();

    // Успешное завершение
    return 0;
}

/* ================= BOOT CORE ================= */

void PacketReceive(uint8_t* buffer) {
    uint8_t event_idx = buffer[0];

    if (event_idx == IDX_RESET) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);  // Включение USB
        HAL_NVIC_SystemReset();
    } else if (event_idx == IDX_APP_ID) {
        APP_ID.DAT.R_IDX = IDX_APP_ID;
        APP_ID.DAT.W_CURENT = 1;

        // Чтение BOOT
        uint32_t KEY0 = flash_read(BOOT_SIG_BLOCK_ADDR + 0);
        uint32_t KEY1 = flash_read(BOOT_SIG_BLOCK_ADDR + 4);
        uint32_t KEY2 = flash_read(BOOT_SIG_BLOCK_ADDR + 8);
        uint32_t KEY3 = flash_read(BOOT_SIG_BLOCK_ADDR + 12);
        uint32_t _VER = flash_read(BOOT_SIG_BLOCK_ADDR + 16);

        APP_ID.DAT.W_B_NAME[0] = KEY0;
        APP_ID.DAT.W_B_NAME[1] = KEY1;
        APP_ID.DAT.W_B_NAME[2] = KEY2;
        APP_ID.DAT.W_B_NAME[3] = KEY3;
        APP_ID.DAT.W_B_VER =
            (KEY0 == BOOT_SIG_KEY0 && KEY1 == BOOT_SIG_KEY1 && KEY2 == BOOT_SIG_KEY2 && KEY3 == BOOT_SIG_KEY3)
                ? _VER
                : 0;

        // Чтение APP
        KEY0 = flash_read(APP_SIG_BLOCK_ADDR + 0);   // 0x08007FEC
        KEY1 = flash_read(APP_SIG_BLOCK_ADDR + 4);   // 0x08007FF0
        KEY2 = flash_read(APP_SIG_BLOCK_ADDR + 8);   // 0x08007FF4
        KEY3 = flash_read(APP_SIG_BLOCK_ADDR + 12);  // 0x08007FF8
        _VER = flash_read(APP_SIG_BLOCK_ADDR + 16);  // 0x08007FFC

        APP_ID.DAT.W_A_NAME[0] = KEY0;
        APP_ID.DAT.W_A_NAME[1] = KEY1;
        APP_ID.DAT.W_A_NAME[2] = KEY2;
        APP_ID.DAT.W_A_NAME[3] = KEY3;
        APP_ID.DAT.W_A_VER =
            (KEY0 == APP_SIG_KEY0 && KEY1 == APP_SIG_KEY1 && KEY2 == APP_SIG_KEY2 && KEY3 == APP_SIG_KEY3)
                ? _VER
                : 0;

        APP_ID.DAT.W_ID[0] = HAL_GetUIDw0();
        APP_ID.DAT.W_ID[1] = HAL_GetUIDw1();
        APP_ID.DAT.W_ID[2] = HAL_GetUIDw2();
        APP_ID.DAT.ID = 0;
        APP_ID.DAT.W_X_POS = 0;
        APP_ID.DAT.W_Y_POS = 0;

        PacketSend(APP_ID.BIN);
    } else if (event_idx == IDX_ERASE) {
        memcpy(APP_ERASE.BIN + 1, buffer, 63);
        flash_erase_area(APP_ERASE.DAT.W_START, APP_ERASE.DAT.W_COUNT);
        PacketSend(APP_ERASE.BIN);
    }
    // ============================================================================
    // ЗАПИСЬ В ПАМЯТЬ (IDX_WRITE)
    // ============================================================================
    else if (event_idx == IDX_WRITE) {
        memcpy(APP_WRITE.BIN + 1, buffer, 63);

        // Проверка: W_COUNT не должен превышать доступные данные (макс 56 байт)
        if (APP_WRITE.DAT.W_COUNT == 0 || APP_WRITE.DAT.W_COUNT > 56) {
            // Можно отправить ошибку, но для совместимости просто ограничим
            APP_WRITE.DAT.W_COUNT = (APP_WRITE.DAT.W_COUNT > 56) ? 56 : APP_WRITE.DAT.W_COUNT;
        }

        // Выравнивание адреса по 4 байта — обязательно
        if ((APP_WRITE.DAT.W_ADRES & 3) != 0) {
            // Опционально: отправить ошибку
        } else {
            // Запись всего блока за один вызов
            flash_write_buffer(APP_WRITE.DAT.W_ADRES, (uint8_t*)APP_WRITE.DAT.W_INFO, APP_WRITE.DAT.W_COUNT);
        }

        PacketSend(APP_WRITE.BIN);
    }
}
