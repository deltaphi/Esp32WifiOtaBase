#include <Arduino.h>

#include <SPIFFS.h>

#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include <TelnetStream.h>

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
  print(Serial, settings);

  setupWifi();
  startWifi(settings.getSsid(), settings.getPassword());

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Wifi Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("WiFi connected, continuing Setup!");

  ArduinoOTA
      .onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
          type = "sketch";
        else  // U_SPIFFS
          type = "filesystem";

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        SPIFFS.end();
        Serial.println("Start updating " + type);
      })
      .onEnd([]() { Serial.println("\nEnd"); })
      .onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      })
      .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR)
          Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR)
          Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR)
          Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR)
          Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR)
          Serial.println("End Failed");
      });

  ArduinoOTA.begin();

  TelnetStream.begin(23);
  TelnetStream.println("Hello from Wifi OTA Base!");
  Serial.println("Ready!");
}

void loop() {
  if (isWifiAvailable()) {
    digitalWrite(kLedPin, HIGH);
  } else {
    digitalWrite(kLedPin, LOW);
  }

  ArduinoOTA.handle();
  TelnetStream.println("loop ");
}