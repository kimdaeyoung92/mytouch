#include "Descriptors.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include <string.h>
#include <util/delay.h>

#define READ_PIN(port, bit) (!(port & (1 << bit)))

void SetupHardware(void) {
    wdt_disable();
    USB_Init(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL);

    DDRD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
    PORTD |= ((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));

    DDRB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
    PORTB |= ((1 << PB0) | (1 << PB1) | (1 << PB2));

    DDRF &= ~((1 << PF0) | (1 << PF1) | (1 << PF4) | (1 << PF5) | (1 << PF6) | (1 << PF7));
    PORTF |= ((1 << PF0) | (1 << PF1) | (1 << PF4) | (1 << PF5) | (1 << PF6) | (1 << PF7));
}

void EVENT_USB_Device_ConfigurationChanged(void) { USB_Device_EnableSOFEvents(); }
void EVENT_USB_Device_ControlRequest(void) {}

void SendTouchReport(void) {
    USB_TouchReport_Data_t report;
    memset(&report, 0, sizeof(report));

    Endpoint_SelectEndpoint(ENDPOINT_DIR_IN | 1);
    if (Endpoint_IsINReady()) {
        Endpoint_Write_Stream_LE(&report, sizeof(report), NULL);
        Endpoint_ClearIN();
    }
}

int main(void) {
    SetupHardware();
    GlobalInterruptEnable();

    while (true) {
        USB_USBTask();
        SendTouchReport();
        _delay_ms(5);
    }
}
