#include "CarCommand.h"

template <class T>
CarCommand<T>::CarCommand(JsonStateReader<T> stateReader,
                          JsonStateUpdater<T> stateUpdater,
                          StatefulService<T>* statefulService,
                          uint8_t leftMotorPWMpin,
                          uint8_t rightMotorPWMpin,
                          uint8_t leftMotorDirpin,
                          uint8_t rightMotorDirpin) :
    _stateReader(stateReader), _stateUpdater(stateUpdater), _statefulService(statefulService) {
  pinMode(BUTTON_PIN_INT, INPUT_PULLDOWN);
  attachInterrupt(BUTTON_PIN_INT, std::bind(&CarCommand::isr, this), CHANGE);

  this->leftMotorPWMpin = leftMotorPWMpin;
  this->rightMotorPWMpin = rightMotorPWMpin;
  this->leftMotorDirpin = leftMotorDirpin;
  this->rightMotorDirpin = rightMotorDirpin;
  // uint8_t pins[8] = {(uint8_t)leftMotorPWM, (uint8_t)rightMotorPWM};  // List of pins that you want to connect to pwm

  //   // pwmMotors = new HardwarePWM(pins, 2);
  //   // setFreq(carParams.freq);
  //   // debugf("CarCommand Instantiating");
}

template <class T>
void CarCommand<T>::checkPressed() {
  if (pressed) {
    Serial.printf("Button on pin %u has been pressed %u times\n", BUTTON_PIN_INT, numberKeyPresses);
    pressed = false;

    _statefulService->update(
        [&](T& state) {
          state.btnIntCount = numberKeyPresses;
          return StateUpdateResult::CHANGED;  // notify StatefulService by returning CHANGED
        },
        "CarCommand");
  }
}

template <class T>
void CarCommand<T>::begin() {
}

template <class T>
void CarCommand<T>::loop() {
  checkPressed();
  // if (button1.pressed) {
  //   Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
  //   button1.pressed = false;
  // }
}
