#include "Settings.h"

#include <SPIFFS.h>

void replaceNewline(char* buf, uint8_t len) {
  for (uint8_t i = 0; i < len; ++i) {
    if (buf[i] == '\r') {
      buf[i] = '\0';
    }
    if (buf[i] == '\0') {
      return;
    }
  }
}

void Settings::load() {
  File file = SPIFFS.open(kWifiSettingsFilename_);

  if (!file) {
    printf("Opening '%s' for reading failed.\n", kWifiSettingsFilename_);
    return;
  }

  file.readBytesUntil('\n', ssid_, kSsidLength);
  file.readBytesUntil('\n', password_, kPasswordLength);
  file.close();

  replaceNewline(ssid_, kSsidLength);
  replaceNewline(password_, kPasswordLength);
}

void print(Print& stream, const Settings& settings) {
  stream.print("SSID: '");
  stream.print(settings.getSsid());
  stream.print("' Password: '");
  stream.print(settings.getPassword());
  stream.println("'");
}
