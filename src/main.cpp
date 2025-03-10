#include <Arduino.h>
#include "PushButton.h"
#include "ButtonManager.h"

#define LED PB13
#define BLINK_DELAY 100

#define BUTTON1_PIN PC0
#define BUTTON2_PIN PC1
#define BUTTON3_PIN PC2
#define BUTTON4_PIN PC3
#define BUTTON5_PIN PA0
#define BUTTON6_PIN PA1

// Create a ButtonManager instance.
ButtonManager buttons;

// Example callback functions.
void onPressButton1() {
  Serial.println("Button 1 Pressed");
}

void onReleaseButton1() {
  Serial.println("Button 1 Released");
}

void onPressButton2() {
  Serial.println("Button 2 Pressed");
}

void onReleaseButton2() {
  Serial.println("Button 2 Released");
}

void onPressButton3() {
  Serial.println("Button 3 Pressed");
}

void onReleaseButton3() {
  Serial.println("Button 3 Released");
}

void onPressButton4() {
  Serial.println("Button 4 Pressed");
}

void onReleaseButton4() {
  Serial.println("Button 4 Released");
}

void onPressButton5() {
  Serial.println("Button 5 Pressed");
}

void onReleaseButton5() {
  Serial.println("Button 5 Released");
}

void onPressButton6() {
  Serial.println("Button 6 Pressed");
}

void onReleaseButton6() {
  Serial.println("Button 6 Released");
}


void setup() {
  pinMode(LED, OUTPUT);

  int idx = 0;

  // Add buttons to the manager.
  idx = buttons.addButton(BUTTON1_PIN);
  buttons.attachOnPress(idx, onPressButton1);
  buttons.attachOnRelease(idx, onReleaseButton1);
  idx = buttons.addButton(BUTTON2_PIN);
  buttons.attachOnPress(idx, onPressButton2);
  buttons.attachOnRelease(idx, onReleaseButton2);
  idx = buttons.addButton(BUTTON3_PIN);
  buttons.attachOnPress(idx, onPressButton3);
  buttons.attachOnRelease(idx, onReleaseButton3);
  idx = buttons.addButton(BUTTON4_PIN);
  buttons.attachOnPress(idx, onPressButton4);
  buttons.attachOnRelease(idx, onReleaseButton4);
  idx = buttons.addButton(BUTTON5_PIN);
  buttons.attachOnPress(idx, onPressButton5);
  buttons.attachOnRelease(idx, onReleaseButton5);
  idx = buttons.addButton(BUTTON6_PIN);
  buttons.attachOnPress(idx, onPressButton6);
  buttons.attachOnRelease(idx, onReleaseButton6);

  Serial.begin(115200);
  Serial.println("Button Manager Example");
}

void loop() {
  static unsigned long last = millis();
  if (millis() - last > BLINK_DELAY) {
    last = millis();
    digitalWrite(LED, !digitalRead(LED));
  }

  // Process all buttons each loop cycle.
  buttons.process();
}
