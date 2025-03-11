#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include "PushButton.h"

// Maximum number of buttons to manage.
#define MAX_BUTTONS 10

class ButtonManager {
public:
  ButtonManager() : _buttonCount(0) {
    // Initialize the array pointers to nullptr.
    for (int i = 0; i < MAX_BUTTONS; i++) {
      _buttons[i] = nullptr;
    }
  }

  // assignFunction creates a new button for a given pin if it does not exist,
  // sets the callbacks, and returns true if successful.
  bool assignFunction(uint8_t pin, Callback onPress, Callback onRelease,
                      bool activeLow = true, unsigned long debounceDelay = 50) {
    PushButton* btn = findButton(pin);
    if (btn == nullptr) {
      // Create a new button if there's room.
      if (_buttonCount >= MAX_BUTTONS) {
        return false; // No space available.
      }
      btn = new PushButton(pin, activeLow, debounceDelay);
      _buttons[_buttonCount++] = btn;
    }
    // Attach the callbacks.
    btn->attachOnPress(onPress);
    btn->attachOnRelease(onRelease);
    return true;
  }

  // modify locates an existing button by pin and modifies its parameters.
  // Returns true if the button was found and modified, false otherwise.
  bool modify(uint8_t pin, Callback onPress, Callback onRelease,
              bool activeLow, unsigned long debounceDelay) {
    PushButton* btn = findButton(pin);
    if (btn == nullptr) {
      return false; // No button found with the specified pin.
    }
    btn->setActiveLow(activeLow);
    btn->setDebounceDelay(debounceDelay);
    btn->attachOnPress(onPress);
    btn->attachOnRelease(onRelease);
    return true;
  }

  // Call this method in your main loop to update all buttons.
  void process() {
    for (int i = 0; i < _buttonCount; i++) {
      if (_buttons[i] != nullptr) {
        _buttons[i]->process();
      }
    }
  }

private:
  PushButton* _buttons[MAX_BUTTONS];
  int _buttonCount;

  // Searches for an existing button by its pin.
  PushButton* findButton(uint8_t pin) {
    for (int i = 0; i < _buttonCount; i++) {
      if (_buttons[i] && _buttons[i]->getPin() == pin) {
        return _buttons[i];
      }
    }
    return nullptr;
  }
};

#endif // BUTTONMANAGER_H
