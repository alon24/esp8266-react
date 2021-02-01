#include "CarMqttSettingsService.h"

CarMqttSettingsService::CarMqttSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager) :
    _httpEndpoint(CarMqttSettings::read,
                  CarMqttSettings::update,
                  this,
                  server,
                  CAR_BROKER_SETTINGS_PATH,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _fsPersistence(CarMqttSettings::read, CarMqttSettings::update, this, fs, CAR_BROKER_SETTINGS_FILE) {
}

void CarMqttSettingsService::begin() {
  _fsPersistence.readFromFS();
}
