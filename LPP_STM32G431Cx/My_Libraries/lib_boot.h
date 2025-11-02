#ifndef __LIBBOOT_H
#define __LIBBOOT_H

#include "main.h"

#define APPLICATION_ADDRESS    0x08000000//адрес начала 
#define BOOT_ADDRESS    0x0800C000//адрес начала 

void JumpToApplication(uint32_t addr); // Прыгнуть по адресу
void SetVector(uint32_t addr); // Установить вектор стека// Установить начало в maim если стартуем не с 0x08000000
void SystemR(void); // Ресет, полная перегрузка

void flash_unlock(void); // Разблокировать флеш
void flash_lock(void); //Заблокировать флеш
uint8_t flash_lock_status(void);  // Проверка статуса блокировки. Если 1 - заблокирована. if (Flash_Lock_Status() == 0)

int flash_erase(uint32_t PageAddress, uint32_t Pages);
uint32_t flash_read(uint32_t address);
void flash_write(uint32_t Address, uint64_t Data); //Data 64 бита

int factor_digits(int num, int *digits, int limit);

#endif /* __LIBBOOT_H */
