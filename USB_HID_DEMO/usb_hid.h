#ifndef USB_HID_H
#define USB_HID_H

#include "stm32f1xx.h"

// Типы callback функций
typedef void (*USB_DataReceivedCallback)(uint8_t* data, uint16_t length);
typedef void (*USB_DataSentCallback)(void);
typedef void (*USB_StatusCallback)(uint8_t status);

// Структура для callbackов
typedef struct {
    USB_DataReceivedCallback DataReceived;  // 📥 Прием данных
    USB_DataSentCallback DataSent;          // 📤 Отправка данных  
    USB_StatusCallback DeviceConfigured;    // ⚙️  Устройство сконфигурировано
    USB_StatusCallback DeviceReset;         // 🔄 Сброс устройства
} USB_CallbackTypeDef;

// Функции инициализации
void USB_HID_Init(void);
void USB_HID_Process(void);
void USB_HID_RegisterCallbacks(USB_CallbackTypeDef *cb);
void USB_HID_SendData(uint8_t* data, uint16_t length);

// Внешние переменные
extern uint8_t USB_HID_Data[64];
extern volatile uint32_t USB_HID_Counter;
extern volatile uint8_t USB_Device_Configured;

#endif