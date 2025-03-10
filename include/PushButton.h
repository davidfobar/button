// PushButton.h
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <Arduino.h>

// Define a callback type for simplicity.
typedef void (*Callback)();

class PushButton {
public:
  // Constructor:
  // - pin: The Arduino pin the button is connected to.
  // - activeLow: Set to true if the button is active when the pin reads LOW (using internal pull-up),
  //   or false if the button is active when the pin reads HIGH.
  // - debounceDelay: The debounce time in milliseconds.
  PushButton(uint8_t pin, bool activeLow = true, unsigned long debounceDelay = 50)
    : _pin(pin),
      _activeLow(activeLow),
      _debounceDelay(debounceDelay),
      _lastDebounceTime(0),
      _onPressCallback(nullptr),
      _onReleaseCallback(nullptr)
  {
    // Configure the pin mode.
    if (_activeLow) {
      pinMode(_pin, INPUT_PULLUP);
    } else {
      pinMode(_pin, INPUT);
    }
    // Initialize state.
    _currentState = getRawState();
    _lastState = _currentState;
  }

  // Callback registration methods.
  void attachOnPress(Callback callback)   { _onPressCallback = callback; }
  void attachOnRelease(Callback callback) { _onReleaseCallback = callback; }

  // Call this function in the main loop to poll the button.
  void process() {
    bool reading = getRawState();
    unsigned long now = millis();

    // If the reading changes, reset the debounce timer.
    if (reading != _lastState) {
      _lastDebounceTime = now;
    }

    // If the reading is stable for longer than the debounce delay, consider it valid.
    if ((now - _lastDebounceTime) > _debounceDelay) {
      // Only act if the state has changed.
      if (reading != _currentState) {
        _currentState = reading;
        // If the button is considered pressed, trigger the onPress callback.
        if (isPressed(_currentState)) {
          if (_onPressCallback) {
            _onPressCallback();
          }
        } else { // Otherwise, it's released.
          if (_onReleaseCallback) {
            _onReleaseCallback();
          }
        }
      }
    }
    _lastState = reading;
  }

private:
  uint8_t _pin;
  bool _activeLow;
  unsigned long _debounceDelay;
  bool _lastState;
  bool _currentState;
  unsigned long _lastDebounceTime;
  
  // Callback function pointers.
  Callback _onPressCallback;
  Callback _onReleaseCallback;

  // Reads the raw state of the pin.
  bool getRawState() {
    return digitalRead(_pin);
  }

  // Interprets the raw state based on the button's polarity.
  bool isPressed(bool state) {
    return _activeLow ? (state == LOW) : (state == HIGH);
  }
};

#endif // PUSHBUTTON_H
