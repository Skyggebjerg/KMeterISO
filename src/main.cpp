#include <Arduino.h>
#include "M5AtomS3.h"
#include "M5UnitKmeterISO.h"

M5UnitKmeterISO kmeter;
uint8_t error_status = 0;
long delay_time      = 0;
float temp;

void setup() {
    Serial.begin(115200);
    auto cfg = M5.config();
    AtomS3.begin(cfg);

    while (!kmeter.begin(&Wire, KMETER_DEFAULT_ADDR, 2, 1, 100000L)) {
      Serial.println("Unit KmeterISO not found");
      }

    AtomS3.Display.setTextColor(GREEN);
    //AtomS3.Display.setTextDatum(middle_center);
    AtomS3.Display.setFont(&fonts::Orbitron_Light_24);
    AtomS3.Display.setTextSize(1);
    AtomS3.Display.drawString("Click!", AtomS3.Display.width() / 2, AtomS3.Display.height() / 2);
}

void loop() {
        error_status = kmeter.getReadyStatus();
        if (error_status == 0) {
          temp = (float)(kmeter.getCelsiusTempValue())/100;
          AtomS3.Display.clear();
          AtomS3.Display.drawString(String(temp), 30, 5);
          //Serial.printf("Chip Celsius Temp: %.2fC\r\n", ((float)(kmeter.getInternalCelsiusTempValue())) / 100);
        } 
        else {
          Serial.printf("Error: %d", kmeter.getReadyStatus());
        }
        delay(500);
}