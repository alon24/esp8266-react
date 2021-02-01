#ifndef CarCommand_h
#define CarCommand_h

// #include <functional>
#include <FunctionalInterrupt.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <StatefulService.h>
#include <WebSocketTxRx.h>

// http://www.smartarduino.com/2wd-wifi-rc-smart-car-with-nodemcu-shield-for-esp-12e_p94572.html
// https://smartarduino.gitbooks.io/user-manual-for-wifi-car-by-nodemcu-doitcar-/content/31_code_for_ap_case_on_doitcar.html
//--GPIO Define
// 2     function initGPIO()
// 3     --1,2EN     D1 GPIO5
// 4     --3,4EN     D2 GPIO4
// 5     --1A  ~2A   D3 GPIO0
// 6     --3A  ~4A   D4 GPIO2

// Direcrtion
#define FW 0
#define BK 1
#define STOP 2
//#define FW_NEUTRAL 3

// Turn
#define TL 4
#define TR 5
#define STRAIGHT 6

// Motor movements
#define MOTOR_FW 1
#define MOTOR_BK 0

#define headLights 12
#define ULTRASONIC_TRIG_PIN 4
#define ULTRASONIC_ECHO_PIN 5

#define BUTTON_PIN_INT 22

// struct Button {
//   const uint8_t PIN;
//   uint32_t numberKeyPresses;
//   bool pressed;
// };

// Button button1 = {BUTTON_PIN_INT, 0, false};

struct CarParamaters {
  int freq = 50;  // 30;
  int xConvertionRation = 10;
  bool useSteeringMotor = true;
};

template <class T>
class CarCommand {
 public:
  CarCommand(JsonStateReader<T> stateReader,
             JsonStateUpdater<T> stateUpdater,
             StatefulService<T>* statefulService,
             uint8_t leftMotorPWMpin,
             uint8_t rightMotorPWMpin,
             uint8_t leftMotorDirpin,
             uint8_t rightMotorDirpin);

  ~CarCommand() {
    detachInterrupt(BUTTON_PIN_INT);
  }

  void checkPressed();

  void initCommand();
  CarParamaters carParams;

  void begin();
  void loop();

  void IRAM_ATTR isr() {
    numberKeyPresses += 1;
    pressed = true;
  }

 private:
  JsonStateReader<T> _stateReader;
  JsonStateUpdater<T> _stateUpdater;
  StatefulService<T>* _statefulService;

  volatile uint32_t numberKeyPresses;
  volatile bool pressed;

  int lastY = 0;
  int lastX = 0;
  int currentX = 0;

  // Direction
  int dir = FW;

  // Turn Status
  int t = 0;
  int tdir = STRAIGHT;
  int tcount = 0;

  uint8_t leftMotorPWMpin;
  uint8_t rightMotorPWMpin;
  uint8_t leftMotorDirpin;
  uint8_t rightMotorDirpin;
};

#endif  // end CarCommand_h
