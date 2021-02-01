#ifndef CarStateService_h
#define CarStateService_h

#include "CarMqttSettingsService.h"
#include "CarCommand.h"
#include "CarCommand.cpp"

#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>
#include <Arduino.h>
#include <ArduinoJson.h>

#define LED_PIN 2
#define BUTTON_PIN 23

#ifdef ESP32
// PINS
#define BUTTON_PIN_INT 22
#define leftMotorPwmPin 4
#define rightMotorPwmPin 5
#define leftMotorDirPin 2
#define rightMotorDirPin 0
#elif defined(ESP8266)
// PINS
#define leftMotorPwmPin 4
#define rightMotorPwmPin 5
#define leftMotorDirPin 2
#define rightMotorDirPin 0
#endif

#define PRINT_DELAY 5000

#define DEFAULT_LED_STATE false
#define DEFAULT_BUTTON_STATE false
#define OFF_STATE "OFF"
#define ON_STATE "ON"

// Note that the built-in LED is on when the pin is low on most NodeMCU boards.
// This is because the anode is tied to VCC and the cathode to the GPIO 4 (Arduino pin 2).
#ifdef ESP32
#define LED_ON 0x1
#define LED_OFF 0x0
#elif defined(ESP8266)
#define LED_ON 0x0
#define LED_OFF 0x1
#endif

#define CAR_SETTINGS_ENDPOINT_PATH "/rest/carState"
#define CAR_SETTINGS_SOCKET_PATH "/ws/carState"

class CarState {
 public:
  bool carOn;
  bool lightsOn;
  bool ultraSoundOn;
  uint8_t x;
  uint8_t y;
  uint8_t power;
  uint8_t pwmModulation;
  bool useSteeringMotor;
  bool btnMomemntary;
  uint8_t btnIntCount;

  static void read(CarState& settings, JsonObject& root) {
    // serializeJson(root, Serial);  // this prints entry
    root["carOn"] = settings.carOn;
    root["lightsOn"] = settings.lightsOn;
    root["ultraSoundOn"] = settings.ultraSoundOn;
    root["x"] = settings.x;
    root["y"] = settings.y;
    root["power"] = settings.power;
    root["btnIntCount"] = settings.btnIntCount;
    // serializeJson(root, Serial);  // this prints after
    // root["theData"] = settings.theData;
  }

  static StateUpdateResult update(JsonObject& root, CarState& carState) {
    Serial.println("StateUpdateResult update:");
    // serializeJson(root, Serial);
    carState.carOn = root["carOn"] | 0x1;
    carState.lightsOn = root["lightsOn"] | 0x0;
    carState.ultraSoundOn = root["ultraSoundOn"] | 0x1;
    carState.x = root["x"];
    carState.y = root["y"];
    carState.power = root["power"];
    carState.btnIntCount = root["btnIntCount"];
    return StateUpdateResult::CHANGED;
  }
};

class CarStateService : public StatefulService<CarState> {
 public:
  CarStateService(AsyncWebServer* server, SecurityManager* securityManager);
  void begin();
  void loop();

 private:
  HttpEndpoint<CarState> _httpEndpoint;
  WebSocketTxRx<CarState> _webSocket;
  CarCommand<CarState> _carCommand;

  // void registerConfig();
  void onConfigUpdated();
};

#endif
