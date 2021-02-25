#ifndef __HAL__SETTINGS_H__
#define __HAL__SETTINGS_H__

#include <Arduino.h>

#include <string>

/*
 * \brief Class Settings
 */
class Settings {
 public:
  constexpr static const uint8_t kSsidLength = 32;
  constexpr static const uint8_t kPasswordLength = 63;

  constexpr static const char* kWifiSettingsFilename_ = "/WifiConfig.ini";

  void load();
  void print();

  const char* getSsid() const { return ssid_; }
  const char* getPassword() const { return password_; }

 private:
  char ssid_[kSsidLength + 1];
  char password_[kPasswordLength + 1];
};

void print(Print& stream, const Settings& settings);

#endif  // __HAL__SETTINGS_H__
