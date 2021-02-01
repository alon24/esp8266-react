#include "CarStateService.h"

CarStateService::CarStateService(AsyncWebServer* server, SecurityManager* securityManager) :
    _httpEndpoint(CarState::read,
                  CarState::update,
                  this,
                  server,
                  CAR_SETTINGS_ENDPOINT_PATH,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(CarState::read,
               CarState::update,
               this,
               server,
               CAR_SETTINGS_SOCKET_PATH,
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED),
    _carCommand(CarState::read,
                CarState::update,
                this,
                leftMotorPwmPin,
                rightMotorPwmPin,
                leftMotorDirPin,
                rightMotorDirPin) {
  // configure led to be output
  pinMode(LED_PIN, OUTPUT);

  // // configure button to be input
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
}

void CarStateService::begin() {
  _state.btnIntCount = 0x0;
  _state.btnMomemntary = !digitalRead(BUTTON_PIN);
  onConfigUpdated();
}

void CarStateService::loop() {
  // Serial.printf("in carservice loop[%s]: ", "test");
  int btnMomemntary = !digitalRead(BUTTON_PIN);
  if (btnMomemntary != _state.btnMomemntary) {
    // Serial.printf("!!! in carService loop buttonState=[%u], got:[%u]: \n", _state.btnMomemntary, btnMomemntary);
    _state.btnMomemntary = btnMomemntary;
    update(
        [&](CarState& state) {
          state.btnMomemntary = btnMomemntary;
          return StateUpdateResult::CHANGED;  // notify StatefulService by returning CHANGED
        },
        "ilan");
  }
  _carCommand.loop();
}

void CarStateService::onConfigUpdated() {
  // digitalWrite(LED_PIN, _state.ledOn ? LED_ON : LED_OFF);
  // Serial.printf("CarStateService::onConfigUpdated \n");
  // Serial.println(_state.ledOn);
  // Serial.println(_state.buttonOn);
}

// void CarStateService::registerConfig() {
//   if (!_mqttClient->connected()) {
//     return;
//   }
//   String configTopic;
//   String subTopic;
//   String pubTopic;

//   DynamicJsonDocument doc(256);
//   _carMqttSettingsService->read([&](CarMqttSettings& settings) {
//     configTopic = settings.mqttPath + "/config";
//     subTopic = settings.mqttPath + "/set";
//     pubTopic = settings.mqttPath + "/state";
//     doc["~"] = settings.mqttPath;
//     doc["name"] = settings.name;
//     doc["unique_id"] = settings.uniqueId;
//   });
//   doc["cmd_t"] = "~/set";
//   doc["stat_t"] = "~/state";
//   doc["schema"] = "json";
//   doc["brightness"] = false;

//   String payload;
//   serializeJson(doc, payload);
//   _mqttClient->publish(configTopic.c_str(), 0, false, payload.c_str());

//   _mqttPubSub.configureTopics(pubTopic, subTopic);
// }
