#include <Arduino.h>

#include <SPIFFS.h>

#include "Settings.h"
#include "wifiManager.h"

void setup() {
  Serial.begin(115200);

  Serial.println("Wifi OTA Base starting.");

  if (!SPIFFS.begin()) {
    Serial.println("Error: Could not mount SPIFFS.");
  }

  Settings settings;
  settings.load();
  settings.print();

  setupWifi();
  startWifi(settings.getSsid(), settings.getPassword());
}

void loop() {
  // put your main code here, to run repeatedly:
}