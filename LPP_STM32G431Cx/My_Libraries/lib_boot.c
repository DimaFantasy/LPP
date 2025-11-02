#include "lib_boot.h"
#include "stm32g4xx_hal.h"

/* === Переход в пользовательское приложение === */
void JumpToApplication(uint32_t addr)
{
    uint32_t JumpAddress;
    typedef void (*pFunction)(void);
    pFunction Jump_To_Application;

    JumpAddress = *(__IO uint32_t*) (addr + 4);
    Jump_To_Application = (pFunction) JumpAddress;

    __set_MSP(*(__IO uint32_t*) addr);   // установить SP приложения
    HAL_DeInit();                        // сброс всей периферии
    Jump_To_Application();               // прыжок
}

/* === Перенос таблицы векторов === */
void SetVector(uint32_t addr)
{
    __disable_irq();
    SCB->VTOR = addr;  // указываем новый адрес таблицы прерываний
    __DSB();
    __enable_irq();
}

/* === Системный ресет === */
void SystemR(void)
{
    NVIC_SystemReset();
}

/* === Работа с FLASH === */
void flash_unlock(void) {
    HAL_FLASH_Unlock();
}

void flash_lock(void) {
    HAL_FLASH_Lock();
}

/* --- Стирание N страниц начиная с номера страницы --- */
int flash_erase(uint32_t Page, uint32_t NbPages)
{
    uint32_t PageError = 0;
    FLASH_EraseInitTypeDef pEraseInit;

    pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    pEraseInit.Banks     = FLASH_BANK_1;
    pEraseInit.Page      = Page;
    pEraseInit.NbPages   = NbPages;

    return HAL_FLASHEx_Erase(&pEraseInit, &PageError);
}

/* --- Стирание страницы по адресу --- */
int flash_erase_page(uint32_t address)
{
    uint32_t PageError = 0;
    FLASH_EraseInitTypeDef pEraseInit;

    uint32_t page = (address - FLASH_BASE) / FLASH_PAGE_SIZE;

    pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    pEraseInit.Banks     = FLASH_BANK_1;
    pEraseInit.Page      = page;
    pEraseInit.NbPages   = 1;

    return HAL_FLASHEx_Erase(&pEraseInit, &PageError);
}

/* --- Запись 64-битного слова (8 байт) --- */
void flash_write(uint32_t Address, uint64_t Data)
{
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, Data);
}

/* --- Чтение 32-битного слова --- */
uint32_t flash_read(uint32_t address)
{
    return (*(__IO uint32_t*) address);
}

/* === Вспомогательная функция: раскладывает число на цифры === */
int factor_digits(int num, int *digits, int limit)
{
    int digits_count = 0;

    if (num == 0) {
        digits[0] = 0;
        return 1;
    }

    while (num > 0 && limit) {
        digits[digits_count++] = num % 10;
        num /= 10;
        limit--;
    }
    return num ? 0 : digits_count;
}
