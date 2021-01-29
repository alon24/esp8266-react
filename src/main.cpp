#include <ESP8266React.h>
#include <LightMqttSettingsService.h>
#include <LightStateService.h>
#include "car/CarStateService.h"
#include "car/CarStateService.h"

#define SERIAL_BAUD_RATE 115200

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
LightMqttSettingsService lightMqttSettingsService =
    LightMqttSettingsService(&server, esp8266React.getFS(), esp8266React.getSecurityManager());

LightStateService lightStateService = LightStateService(&server,
                                                        esp8266React.getSecurityManager(),
                                                        esp8266React.getMqttClient(),
                                                        &lightMqttSettingsService);

CarMqttSettingsService carMqttSettingsService =
    CarMqttSettingsService(&server, esp8266React.getFS(), esp8266React.getSecurityManager());
CarStateService carStateService = CarStateService(&server,
                                  esp8266React.getSecurityManager(),
                                  esp8266React.getMqttClient(),
                                  &carMqttSettingsService);                              
void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // start the framework and demo project
  esp8266React.begin(); 

  // load the initial light settings
  lightStateService.begin();

  // start the light service
  lightMqttSettingsService.begin();

  // load the initial light settings
  carStateService.begin();
  // start the light service
  carMqttSettingsService.begin();


  // start the server
  server.begin();
}

void loop() {

  //do the work, for car service
  carStateService.loop();

  // run the framework's loop function
  esp8266React.loop();

}
