#include "Arduino.h"
#include "pico/stdlib.h"
#include "tusb.h"           // For TinyUSB HID functions

void setup()
{
    Serial.begin(9600);
    tusb_init();
    delay(10000);
    Serial.println("setup ready");
}

void loop()
{
    tud_task();
    uint8_t report[6] = {0};
    report[0] = HID_KEY_E;
    tud_hid_keyboard_report(0,0,report);
    if (tud_hid_n_ready)
    {
        Serial.println("tud_hid_n_ready");
    }
    if (tud_hid_ready())
    {
        Serial.print("tud_hid_ready");
    }
    delay(500);
}

// TinyUSB callbacks (required for HID)
extern "C" 
{
    // Invoked when USB HID gets a report request from host
    uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
    {
        Serial.print("callback 1");
        // No report to send by default
        return 0;
    }

    // Invoked when USB HID receives a report from host
    void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
    {
        Serial.print("callback 222");
        // Handle received report (not needed in this example)
    }
}