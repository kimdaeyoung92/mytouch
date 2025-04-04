#pragma once

#include <LUFA/Drivers/USB/USB.h>

typedef struct {
    uint8_t Tip;
    uint16_t X;
    uint16_t Y;
} TouchPoint_t;

#define MAX_TOUCHES 16

typedef struct {
    TouchPoint_t touches[MAX_TOUCHES];
} USB_TouchReport_Data_t;
