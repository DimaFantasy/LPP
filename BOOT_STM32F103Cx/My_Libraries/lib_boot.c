#include "lib_boot.h"


void JumpToApplication(uint32_t addr)
{	
//HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
//HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
	
	uint32_t JumpAddress;	
	
	typedef void (*pFunction)(void); //объявляем пользовательский тип
	pFunction Jump_To_Application;   //и создаём переменную этого типа
	
	JumpAddress = *(__IO uint32_t*) (addr + 4); //извлекаем адрес перехода из вектора Reset
	Jump_To_Application = (pFunction) JumpAddress; //приводим его к пользовательскому типу
	__set_MSP(*(__IO uint32_t*) addr); // Инициализировать указатель стека пользовательского приложения /устанавливаем SP приложения
	
	HAL_DeInit();// Сброс всей переферии
	
	Jump_To_Application(); // Прыгаем по адресу
}

void SetVector(uint32_t addr)
{
	__disable_irq(); //запрещаем прерывания
	//__set_PRIMASK(1); //запрещаем прерывания
	SCB->VTOR = BOOT_ADDRESS;//переносим начало вектора прерываний по указанному адресу
	__DSB();// позволяет быть уверенным, что все выполняемые обращения к памяти будут завершены до начала выполнения следующей инструкции.
	//__set_PRIMASK(0);//разрешаем прерывания
	 __enable_irq();	 //разрешаем прерывания
}

// Ресет, полная перегрузка
void SystemR(void)
{
	NVIC_SystemReset();
}

void flash_unlock(void) {
	FLASH->KEYR = FLASH_KEY1;
	FLASH->KEYR = FLASH_KEY2;
}

void flash_lock() {	
	SET_BIT(FLASH->CR, FLASH_CR_LOCK);
}

void flash_erase_page(uint32_t address) {
	//while(!flash_ready()); //Ожидаем готовности флеша к записи
	FLASH->CR|= FLASH_CR_PER; //Устанавливаем бит стирания одной страницы
	FLASH->AR = address; // Задаем её адрес
	FLASH->CR|= FLASH_CR_STRT; // Запускаем стирание
	while(!(FLASH->SR & FLASH_SR_EOP)); //Ждем пока страница сотрется. //Ожидаем готовности флеша к записи
	FLASH->CR&= ~FLASH_CR_PER; //Сбрасываем бит обратно //Сбрасываем бит стирания одной страницы
}

// Проверка статуса блокировки. Если 1 - заблокирована. if (Flash_Lock_Status() == 0)
uint8_t flash_lock_status(void) 
{
	while (FLASH->SR & FLASH_SR_BSY); // Ждем если занят 
	return ((FLASH->CR & FLASH_CR_LOCK) & 0xFF);
//  return  READ_BIT(FLASH->CR, FLASH_CR_LOCK); // Или так
// if(READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET) Если ФЛЕШ заблокирован
};

void flash_write(uint32_t Address,uint32_t Data)
{
//Для записи данных, также необходим адрес и понимание того, что данные пишутся блоками по 16 бит.	
//	FLASH->CR |= FLASH_CR_PG; //Разрешаем программирование флеша
//	while(!(FLASH->SR & FLASH_SR_EOP)); //Ожидаем готовности флеша к записи
//	*(__IO uint16_t*)address = (uint16_t)data;   //Пишем младшие 2 байта
//	while(!(FLASH->SR & FLASH_SR_EOP)); //Ждем завершения операции
//	address+=2;
//	data>>=16;
//	*(__IO uint16_t*)address = (uint16_t)data; //Пишем старшие 2 байта
//	while(!(FLASH->SR & FLASH_SR_EOP)); //Ждем завершения операции
//	FLASH->CR &= ~(FLASH_CR_PG); //Запрещаем программирование флеша	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data);
}

//* Get the number of pages to erase */
//NbrOfPages = (FLASH_BASE + FLASH_SIZE - APP_ADDRESS) / FLASH_PAGE_SIZE;
int flash_erase(uint32_t PageAddress, uint32_t NbPages)
{
	HAL_FLASH_Unlock();	
	// заполняем структуру записи сектора и стираем
	uint32_t PageError = 0;
	FLASH_EraseInitTypeDef pEraseInit;
	pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	pEraseInit.PageAddress = PageAddress;
	pEraseInit.NbPages = NbPages;
	return HAL_FLASHEx_Erase(&pEraseInit, &PageError);
//	HAL_FLASH_Lock();
}	

uint32_t flash_read(uint32_t address) {
	return (*(__IO uint32_t*) address);
}

/**
 * Раскладывает целое число в массив цифр
 *
 * Функция factor_digits извлекает цифры числа и размещает в заданном
 * массиве в обратной последовательности, в соответствии с нумерацией
 * разрядов, то есть элемент массива с индексом нуль получит значение
 * нулевого разряда (крайней правой цифры) и т.д. В случае, если при
 * разложении достигнуто заданное третьим параметром максимальное
 * количество цифр, функция прекращает работу, возвращая нуль, в
 * противном случае возвращает количество цифр в разложении.
 *
 * @param num    Число для разложения
 * @param digits Массив для размещения результата разложения
 * @param limit  Максимально допустимое количество цифр  
 * @returns      количество полученных цифр в разложении,
 *               0, если превышено предельное количество цифр
 */
int factor_digits(int num, int *digits, int limit)
{
    int digits_count = 0;

    // Отдельно обрабатываем ситуацию, когда число изначально равно нулю
    if (num == 0) {
        digits[0] = 0;
        return 1;
    }

    // Последовательно извлекаем цифры числа, пока они есть
    while (num > 0 && limit) {
        // Копируем очередную цифру в массив
        digits[digits_count++] = num % 10;
        // Переходим к следующей цифре
        num /= 10;
        // Уменьшаем допустимое количество оставшихся цифр
        limit--;
   }
   return num ? 0 : digits_count;
}

/*
// Тестовая программа, демонстрирующая разложение числа на цифры
int main()
{
    int n = 123456789;          // Разложим для примера число 123456789 
    int factored_number[10];    // Массив для хранения результата
    int factored_number_len;    // Количество цифр в числе
    int i;

    // Выполняем разложение
    factored_number_len = factor_digits(n, factored_number, 10);

    // Выводим результат на экран
    for (i = factored_number_len - 1; i >= 0; i--) {
        printf("%d\n", factored_number[i]);
    }

    return 0;
}
*/
