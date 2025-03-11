// PushButton.h
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <Arduino.h>
#include <functional> // Include for std::function

typedef std::function<void()> Callback;

class PushButton {
public:
  PushButton(uint8_t pin, bool activeLow = true, unsigned long debounceDelay = 50)
    : _pin(pin),
      _activeLow(activeLow),
      _debounceDelay(debounceDelay),
      _lastDebounceTime(0),
      _onPressCallback(nullptr),
      _onReleaseCallback(nullptr)
  {
    if (_activeLow) {
      pinMode(_pin, INPUT_PULLUP);
    } else {
      pinMode(_pin, INPUT);
    }
    _currentState = getRawState();
    _lastState = _currentState;
  }

  void attachOnPress(Callback callback)   { _onPressCallback = callback; }
  void attachOnRelease(Callback callback) { _onReleaseCallback = callback; }

  uint8_t getPin() const { return _pin; }

  void process() {
    bool reading = getRawState();
    unsigned long now = millis();

    if (reading != _lastState) {
      _lastDebounceTime = now;
    }

    if ((now - _lastDebounceTime) > _debounceDelay) {
      if (reading != _currentState) {
        _currentState = reading;
        if (isPressed(_currentState)) {
          if (_onPressCallback) { _onPressCallback(); }
        } else {
          if (_onReleaseCallback) { _onReleaseCallback(); }
        }
      }
    }
    _lastState = reading;
  }

  // Setter for debounce delay.
  void setDebounceDelay(unsigned long delay) { _debounceDelay = delay; }

  // Setter for activeLow; reconfigure the pin mode.
  void setActiveLow(bool activeLow) {
    _activeLow = activeLow;
    if (_activeLow) {
      pinMode(_pin, INPUT_PULLUP);
    } else {
      pinMode(_pin, INPUT);
    }
  }

private:
  uint8_t _pin;
  bool _activeLow;
  unsigned long _debounceDelay;
  bool _lastState;
  bool _currentState;
  unsigned long _lastDebounceTime;

  Callback _onPressCallback;
  Callback _onReleaseCallback;

  bool getRawState() { return digitalRead(_pin); }
  bool isPressed(bool state) { return _activeLow ? (state == LOW) : (state == HIGH); }
};

#endif // PUSHBUTTON_H
