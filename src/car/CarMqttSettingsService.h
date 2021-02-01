#ifndef CarMqttSettingsService_h
#define CarMqttSettingsService_h

#include <HttpEndpoint.h>
#include <FSPersistence.h>
#include <SettingValue.h>

#define CAR_BROKER_SETTINGS_FILE "/config/carBrokerSettings.json"
#define CAR_BROKER_SETTINGS_PATH "/rest/carBrokerSettings"

class CarMqttSettings {
 public:
  String mqttPath;
  String name;
  String uniqueId;

  static void read(CarMqttSettings& settings, JsonObject& root) {
    root["mqtt_path"] = settings.mqttPath;
    root["name"] = settings.name;
    root["unique_id"] = settings.uniqueId;
  }

  static StateUpdateResult update(JsonObject& root, CarMqttSettings& settings) {
    settings.mqttPath = root["mqtt_path"] | SettingValue::format("homeassistant/light/#{unique_id}");
    settings.name = root["name"] | SettingValue::format("light-#{unique_id}");
    settings.uniqueId = root["unique_id"] | SettingValue::format("light-#{unique_id}");
    return StateUpdateResult::CHANGED;
  }
};

class CarMqttSettingsService : public StatefulService<CarMqttSettings> {
 public:
  CarMqttSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager);
  void begin();

 private:
  HttpEndpoint<CarMqttSettings> 
  _httpEndpoint;
  FSPersistence<CarMqttSettings> _fsPersistence;
};

#endif  // end CarMqttSettingsService_h
