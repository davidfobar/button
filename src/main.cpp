#include <Arduino.h>

#define LED PB13

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  static unsigned long last = millis();
  if (millis() - last > 100) {
    last = millis();
    digitalWrite(LED, !digitalRead(LED));
  }
}
 