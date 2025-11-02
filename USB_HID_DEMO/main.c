#include "main.h"
#include "usb_hid.h"

// ==================== ПЕРЕМЕННЫЕ ПРИМЕРА ====================
uint8_t tx_data[64];
uint32_t packet_counter = 0;

// ==================== CALLBACK ФУНКЦИИ ====================

/* 📥 CALLBACK: Прием данных от хоста */
void USB_DataReceived_Callback(uint8_t* data, uint16_t length) {
    // 🎯 АВТОМАТИЧЕСКИ ВЫЗЫВАЕТСЯ при получении данных
    
    // Пример 1: Управление светодиодом
    if (data[0] == 0x01) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET); // ВКЛ
    } else if (data[0] == 0x00) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // ВЫКЛ
    }
    
    // Пример 2: Эхо - отправляем данные обратно
    // USB_HID_SendData(data, length);
    
    // Пример 3: Обработка команд
    switch(data[0]) {
        case 0x10: // Команда 1
            // Выполняем действие
            break;
        case 0x20: // Команда 2  
            // Другое действие
            break;
    }
    
    // Пример 4: Вывод в отладочный UART (если есть)
    // printf("Received %d bytes\n", length);
}

/* 📤 CALLBACK: Завершение отправки данных */
void USB_DataSent_Callback(void) {
    // 🎯 ВЫЗЫВАЕТСЯ когда данные успешно отправлены хосту
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_14); // Мигаем другим светодиодом
}

/* ⚙️ CALLBACK: Устройство сконфигурировано */
void USB_DeviceConfigured_Callback(uint8_t status) {
    if (status) {
        // 🎯 Устройство готово к работе!
        for(int i = 0; i < 5; i++) {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            HAL_Delay(100);
        }
    }
}

/* 🔄 CALLBACK: Сброс устройства */
void USB_DeviceReset_Callback(uint8_t status) {
    // 🎯 Устройство было сброшено
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
}

// ==================== ОСНОВНАЯ ПРОГРАММА ====================
int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    // Настройка светодиодов
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
    
    // 1. 📝 РЕГИСТРАЦИЯ CALLBACK ФУНКЦИЙ
    USB_CallbackTypeDef callbacks = {
        .DataReceived = USB_DataReceived_Callback,
        .DataSent = USB_DataSent_Callback,
        .DeviceConfigured = USB_DeviceConfigured_Callback,
        .DeviceReset = USB_DeviceReset_Callback
    };
    
    // 2. 🔧 ИНИЦИАЛИЗАЦИЯ USB HID
    USB_HID_Init();
    USB_HID_RegisterCallbacks(&callbacks);
    
    // 3. 🚀 ЗАПУСК
    printf("USB HID Device Started!\r\n");
    
    uint32_t last_led_toggle = 0;
    uint32_t last_data_send = 0;
    
    while(1) {
        uint32_t current_time = HAL_GetTick();
        
        // 💡 Индикация работы (мигаем если подключено)
        if (USB_Device_Configured) {
            if (current_time - last_led_toggle > 1000) {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                last_led_toggle = current_time;
            }
        }
        
        // 📤 Периодическая отправка данных (пример)
        if (USB_Device_Configured && (current_time - last_data_send > 2000)) {
            // Подготавливаем данные
            for(int i = 0; i < 64; i++) {
                tx_data[i] = i + packet_counter;
            }
            tx_data[0] = 0xAA; // Маркер пакета
            tx_data[1] = packet_counter & 0xFF;
            
            // Отправляем данные
            USB_HID_SendData(tx_data, 64);
            packet_counter++;
            last_data_send = current_time;
            
            printf("Sent packet %lu\r\n", packet_counter);
        }
        
        HAL_Delay(10);
    }
}

// ==================== ФУНКЦИИ CUBEMX ====================
void SystemClock_Config(void) {
    // Настройка тактирования для USB (48 MHz)
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);
    
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // PC13, PC14 - светодиоды
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    // PA11, PA12 - USB
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}