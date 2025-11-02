#include "usb_hid.h"
#include <string.h>
#include "main.h"

// Добавляем недостающие определения
#define USB_DESC_TYPE_DEVICE 0x01
#define USB_DESC_TYPE_CONFIGURATION 0x02
#define USB_DESC_TYPE_INTERFACE 0x04
#define USB_DESC_TYPE_ENDPOINT 0x05
#define HID_DESCRIPTOR_TYPE 0x21

#define LOBYTE(x) ((uint8_t)((x) & 0x00FF))
#define HIBYTE(x) ((uint8_t)(((x) & 0xFF00) >> 8))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// VID/PID
#define USB_VID 0x0483
#define USB_PID 0x5711

// HID параметры
#define HID_REPORT_SIZE 64
#define HID_EPIN_SIZE HID_REPORT_SIZE
#define HID_EPOUT_SIZE HID_REPORT_SIZE
#define REPORT_DESC_SIZE 34  // Input (23) + Output (11) = 34

// ==================== РЕГИСТРЫ USB ====================
#define USB_BASE_ADDR 0x40005C00
#define USB_PMA_ADDR 0x40006000
#define REG(x) (*((volatile uint16_t*)(x)))  // 16-битные регистры

#define EP0R REG(USB_BASE_ADDR + 0x00)
#define EP1R REG(USB_BASE_ADDR + 0x04)
#define CNTR REG(USB_BASE_ADDR + 0x40)
#define ISTR REG(USB_BASE_ADDR + 0x44)
#define DADDR REG(USB_BASE_ADDR + 0x4C)
#define BTABLE REG(USB_BASE_ADDR + 0x50)

// Биты ISTR
#define ISTR_CTR (1 << 15)
#define ISTR_RESET (1 << 10)
#define ISTR_ERR (1 << 13)

// Биты EPxR
#define EP_CTR_RX (1 << 15)
#define EP_CTR_TX (1 << 7)
#define EP_STAT_RX (3 << 12)  // 0x3000
#define EP_STAT_TX (3 << 4)   // 0x0030

// Адреса в PMA (выравнены по 16-битной границе)
#define EP0_RX_ADDR 128
#define EP1_TX_ADDR 192
#define EP1_RX_ADDR 256

// ==================== ДЕСКРИПТОРЫ ====================
__ALIGN_BEGIN uint8_t DeviceDescriptor[18] __ALIGN_END = {
    0x12,
    USB_DESC_TYPE_DEVICE,
    0x10,
    0x01,
    0x00,
    0x00,
    0x00,
    0x40,
    LOBYTE(USB_VID),
    HIBYTE(USB_VID),
    LOBYTE(USB_PID),
    HIBYTE(USB_PID),
    0x00,
    0x01,
    0x01,
    0x02,
    0x03,
    0x01};

__ALIGN_BEGIN uint8_t ConfigDescriptor[41] __ALIGN_END = {
    // Configuration
    0x09, USB_DESC_TYPE_CONFIGURATION, 41, 0x00, 0x01, 0x01, 0x00, 0xE0, 0x32,
    // Interface
    0x09, USB_DESC_TYPE_INTERFACE, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00,
    // HID
    0x09, HID_DESCRIPTOR_TYPE, 0x01, 0x01, 0x00, 0x01, 0x22, REPORT_DESC_SIZE, 0x00,
    // EP IN
    0x07, USB_DESC_TYPE_ENDPOINT, 0x81, 0x03, LOBYTE(HID_EPIN_SIZE), HIBYTE(HID_EPIN_SIZE), 0x20,
    // EP OUT
    0x07, USB_DESC_TYPE_ENDPOINT, 0x01, 0x03, LOBYTE(HID_EPOUT_SIZE), HIBYTE(HID_EPOUT_SIZE), 0x20};

__ALIGN_BEGIN uint8_t ReportDescriptor[REPORT_DESC_SIZE] __ALIGN_END = {
    0x06, 0x00, 0xFF,  // Usage Page (Vendor 0xFF00)
    0x09, 0x01,        // Usage
    0xA1, 0x01,        // Collection (Application)

    // Input Report (64 bytes)
    0x15, 0x00,             // Logical Minimum
    0x26, 0xFF, 0x00,       // Logical Maximum
    0x75, 0x08,             // Report Size
    0x95, HID_REPORT_SIZE,  // Report Count
    0x09, 0x01,             // Usage
    0x81, 0x02,             // Input (Data, Var, Abs)

    // Output Report (64 bytes)
    0x15, 0x00, 0x26, 0xFF, 0x00, 0x75, 0x08, 0x95, HID_REPORT_SIZE, 0x09, 0x01, 0x91,
    0x02,  // Output (Data, Var, Abs)

    0xC0  // End Collection
};

// ==================== ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ ====================
uint8_t USB_HID_Data[HID_REPORT_SIZE];
volatile uint32_t USB_HID_Counter = 0;
volatile uint8_t USB_Device_Configured = 0;

static USB_CallbackTypeDef USBD_Callbacks = {0};

// ==================== PMA ФУНКЦИИ ====================
void USB_WritePMA(uint8_t* src, uint16_t offset, uint16_t len) {
    volatile uint16_t* pma = (volatile uint16_t*)(USB_PMA_ADDR + offset);
    for (uint16_t i = 0; i < (len + 1) / 2; i++) {
        uint16_t word = (i * 2 < len) ? src[i * 2] : 0;
        if (i * 2 + 1 < len) word |= (uint16_t)src[i * 2 + 1] << 8;
        pma[i] = word;
    }
}

void USB_ReadPMA(uint16_t offset, uint8_t* dst, uint16_t len) {
    volatile uint16_t* pma = (volatile uint16_t*)(USB_PMA_ADDR + offset);
    for (uint16_t i = 0; i < (len + 1) / 2; i++) {
        uint16_t word = pma[i];
        if (i * 2 < len) dst[i * 2] = word & 0xFF;
        if (i * 2 + 1 < len) dst[i * 2 + 1] = (word >> 8) & 0xFF;
    }
}

// ==================== CALLBACK ИНТЕРФЕЙС ====================
void USB_HID_RegisterCallbacks(USB_CallbackTypeDef* cb) {
    if (cb) memcpy(&USBD_Callbacks, cb, sizeof(USB_CallbackTypeDef));
}

static void invoke_callback(void (*cb)(void)) {
    if (cb) cb();
}

static void invoke_data_callback(void (*cb)(uint8_t*, uint16_t), uint8_t* d, uint16_t l) {
    if (cb) cb(d, l);
}

// ==================== ОБРАБОТЧИКИ ====================
void USB_HandleReset(void) {
    RCC->APB1ENR |= RCC_APB1ENR_USBEN;
    CNTR = 0;
    BTABLE = 0;

    // EP0: RX=128, TX=64
    volatile uint16_t* pma = (volatile uint16_t*)USB_PMA_ADDR;
    pma[0] = 64;      // TX0 count
    pma[1] = 0;       // TX0 addr
    pma[2] = 128;     // RX0 count
    pma[3] = 0x8400;  // RX0 addr + flags

    // EP1 IN
    pma[4] = EP1_TX_ADDR;  // TX1 addr
    pma[5] = 0;
    // EP1 OUT
    pma[6] = EP1_RX_ADDR;  // RX1 addr
    pma[7] = 0x8400;       // RX1 count + flags

    EP0R = 0x0200 | 0x3000;  // Control, RX=VALID
    EP1R = 0x0200 | 0x3000;  // Interrupt, RX=VALID

    DADDR = 0x80;  // enable
    USB_Device_Configured = 0;
    invoke_callback(USBD_Callbacks.DeviceReset);
}

void USB_HandleSetupRequest(void) {
    uint8_t setup[8];
    USB_ReadPMA(EP0_RX_ADDR, setup, 8);

    uint8_t req_type = setup[0];
    uint8_t bRequest = setup[1];
    uint16_t wValue = (setup[3] << 8) | setup[2];
    uint16_t wLength = (setup[7] << 8) | setup[6];
    uint16_t req = (bRequest << 8) | req_type;

    switch (req) {
        case 0x0680:  // GET_DESCRIPTOR
            switch (wValue >> 8) {
                case 0x01:  // Device
                    USB_WritePMA(DeviceDescriptor, 64, MIN(wLength, 18));
                    *((volatile uint16_t*)(USB_PMA_ADDR + 2)) = MIN(wLength, 18);
                    EP0R = (EP0R & ~EP_STAT_TX) | 0x0040;
                    break;
                case 0x02:  // Configuration
                    USB_WritePMA(ConfigDescriptor, 64, MIN(wLength, 41));
                    *((volatile uint16_t*)(USB_PMA_ADDR + 2)) = MIN(wLength, 41);
                    EP0R = (EP0R & ~EP_STAT_TX) | 0x0040;
                    break;
                case 0x22:  // Report
                    USB_WritePMA(ReportDescriptor, 64, MIN(wLength, REPORT_DESC_SIZE));
                    *((volatile uint16_t*)(USB_PMA_ADDR + 2)) = MIN(wLength, REPORT_DESC_SIZE);
                    EP0R = (EP0R & ~EP_STAT_TX) | 0x0040;
                    break;
            }
            break;

        case 0x0500:  // SET_ADDRESS
            *((volatile uint16_t*)(USB_PMA_ADDR + 2)) = 0;
            EP0R = (EP0R & ~EP_STAT_TX) | 0x0040;  // Готовим TX для отправки пустого пакета
            for (volatile uint32_t i = 0; i < 100000; i++) {
                if (EP0R & EP_CTR_TX) break;  // Ждём завершения передачи
            }
            EP0R &= ~EP_CTR_TX;  // Сбрасываем флаг прерывания TX
            asm volatile("nop");
            asm volatile("nop");               // 🔸 Добавлена задержка (2 такта CPU)
            DADDR = 0x80 | (setup[2] & 0x7F);  // Устанавливаем адрес И ВКЛЮЧАЕМ устройство
            break;

        case 0x0900:  // SET_CONFIGURATION
            USB_Device_Configured = 1;
            invoke_callback(USBD_Callbacks.DeviceConfigured);
            *((volatile uint16_t*)(USB_PMA_ADDR + 2)) = 0;
            EP0R = (EP0R & ~EP_STAT_TX) | 0x0040;
            break;

        case 0x0921:  // SET_REPORT
            EP0R = (EP0R & ~EP_STAT_RX) | 0x3000;
            for (volatile uint32_t i = 0; i < 100000; i++) {
                if (EP0R & EP_CTR_RX) break;
            }
            EP0R &= ~EP_CTR_RX;
            USB_ReadPMA(EP0_RX_ADDR, USB_HID_Data, 64);
            *((volatile uint16_t*)(USB_PMA_ADDR + 2)) = 0;
            EP0R = (EP0R & ~EP_STAT_TX) | 0x0040;
            break;

        case 0x01A1:  // GET_REPORT
            USB_WritePMA(USB_HID_Data, 64, 64);
            *((volatile uint16_t*)(USB_PMA_ADDR + 2)) = 64;
            EP0R = (EP0R & ~EP_STAT_TX) | 0x0040;
            break;
    }
    EP0R &= ~EP_CTR_RX;
}

void USB_HandleEP1_DataReceived(void) {
    uint16_t rx_count = *((volatile uint16_t*)(USB_PMA_ADDR + 16 + 6)) & 0x3FF;
    if (rx_count > HID_REPORT_SIZE) rx_count = HID_REPORT_SIZE;
    USB_ReadPMA(EP1_RX_ADDR, USB_HID_Data, rx_count);
    USB_HID_Counter++;
    invoke_data_callback(USBD_Callbacks.DataReceived, USB_HID_Data, rx_count);
    *((volatile uint16_t*)(USB_PMA_ADDR + 16 + 6)) = 0x8400;
    EP1R = (EP1R & ~EP_STAT_RX) | 0x3000;
    EP1R &= ~EP_CTR_RX;
}

void USB_HandleEP1_DataSent(void) {
    invoke_callback(USBD_Callbacks.DataSent);
    EP1R &= ~EP_CTR_TX;
}

// ==================== ПУБЛИЧНЫЙ ИНТЕРФЕЙС ====================
void USB_HID_SendData(uint8_t* data, uint16_t length) {
    if (!USB_Device_Configured || !data) return;
    if (length > HID_REPORT_SIZE) length = HID_REPORT_SIZE;
    USB_WritePMA(data, EP1_TX_ADDR, length);
    *((volatile uint16_t*)(USB_PMA_ADDR + 8 + 2)) = length;
    EP1R = (EP1R & ~EP_STAT_TX) | 0x0040;  // VALID
}

void USB_HID_Process(void) {
    uint16_t istr = ISTR;

    if (istr & ISTR_RESET) {
        USB_HandleReset();
    }

    if (istr & ISTR_CTR) {
        uint16_t ep0r = EP0R;
        if (ep0r & EP_CTR_RX) USB_HandleSetupRequest();
        if (ep0r & EP_CTR_TX) EP0R &= ~EP_CTR_TX;

        uint16_t ep1r = EP1R;
        if (ep1r & EP_CTR_RX) USB_HandleEP1_DataReceived();
        if (ep1r & EP_CTR_TX) USB_HandleEP1_DataSent();
    }

    if (istr & ISTR_ERR) {
        USB_HandleReset();  // перезапуск при ошибке
    }
}

void USB_HID_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_USBEN;
    CNTR = ISTR_CTR | ISTR_RESET | ISTR_ERR;  // включить прерывания
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 2);
}

// Обработчик прерывания в stm32f1xx_it.с
// void USB_LP_CAN1_RX0_IRQHandler(void) { USB_HID_Process(); }

// // В callback'е приёма
// void MyDataReceivedCallback(uint8_t* data, uint16_t len) {
//     memcpy(response_buffer, data, len);
//     response_ready = 1;
// }

// // В main()
// if (response_ready) {
//     USB_HID_SendData(response_buffer, 64);
//     response_ready = 0;
// }

