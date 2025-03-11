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
  buttons.assignFunction(BUTTON1_PIN, onPressButton1, onReleaseButton1);
  buttons.assignFunction(BUTTON2_PIN, onPressButton2, onReleaseButton2);
  buttons.assignFunction(BUTTON3_PIN, onPressButton3, onReleaseButton3);
  buttons.assignFunction(BUTTON4_PIN, onPressButton4, onReleaseButton4);
  buttons.assignFunction(BUTTON5_PIN, onPressButton5, onReleaseButton5);
  buttons.assignFunction(BUTTON6_PIN, onPressButton6, onReleaseButton6);

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
