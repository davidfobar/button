#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include "PushButton.h"

// Set a maximum number of buttons that can be managed.
#define MAX_BUTTONS 10

class ButtonManager {
public:
  ButtonManager() : _buttonCount(0) {
    // Initialize the pointers array to nullptr.
    for (int i = 0; i < MAX_BUTTONS; i++) {
      _buttons[i] = nullptr;
    }
  }

  // Dynamically creates a new PushButton.
  // Returns the index of the new button or -1 if no space is available.
  int addButton(uint8_t pin, bool activeLow = true, unsigned long debounceDelay = 50) {
    if (_buttonCount >= MAX_BUTTONS) {
      return -1; // Manager is full.
    }
    _buttons[_buttonCount] = new PushButton(pin, activeLow, debounceDelay);
    return _buttonCount++;
  }

  // Attach the onPress callback for the button at the given index.
  void attachOnPress(int idx, Callback callback) {
    if (isValidIndex(idx)) {
      _buttons[idx]->attachOnPress(callback);
    }
  }

  // Attach the onRelease callback for the button at the given index.
  void attachOnRelease(int idx, Callback callback) {
    if (isValidIndex(idx)) {
      _buttons[idx]->attachOnRelease(callback);
    }
  }

  // Call this method in your main loop to update all buttons.
  void process() {
    for (int i = 0; i < _buttonCount; i++) {
      _buttons[i]->process();
    }
  }

private:
  PushButton* _buttons[MAX_BUTTONS];
  int _buttonCount;

  // Checks if the provided index is valid.
  bool isValidIndex(int idx) {
    return idx >= 0 && idx < _buttonCount;
  }
};

#endif // BUTTONMANAGER_H
