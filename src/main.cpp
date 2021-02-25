#include <Arduino.h>

#include <SPIFFS.h>

#include "Settings.h"
#include "wifiManager.h"

constexpr static const uint8_t kLedPin = 2;

void setup() {
  Serial.begin(115200);

  Serial.println("Wifi OTA Base starting.");

  pinMode(kLedPin, OUTPUT);

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
  if (isWifiAvailable()) {
    digitalWrite(kLedPin, HIGH);
  } else {
    digitalWrite(kLedPin, LOW);
  }
}