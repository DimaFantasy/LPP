#include "stm32f1xx_it.h"
#include "usb_hid.h"

void USB_LP_CAN1_RX0_IRQHandler(void) {
    USB_HID_Process();
}