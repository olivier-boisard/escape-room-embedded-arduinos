#include <ESP8266WiFi.h>

void getAndSaveCredentialsFromSerialPort(size_t eepromAddress) {
  char ssid[SSID_MAX_LENGTH];
  char password[PASSWORD_MAX_LENGTH];
  
  // Get credentials
  size_t ssidSize = Serial.readBytesUntil(0x00, ssid, SSID_MAX_LENGTH);
  size_t passwordSize = Serial.readBytesUntil(0x00, password, PASSWORD_MAX_LENGTH);

  // Save credentials
  EEPROM.write(eepromAddress++, VALID_WIFI_CREDENTIALS_CODE);
  EEPROM.write(eepromAddress++, ssidSize);
  for (size_t i = 0 ; i < ssidSize ; i++) {
    EEPROM.write(eepromAddress++, ssid[i]);
  }
  EEPROM.write(eepromAddress++, passwordSize);
  for (size_t i = 0 ; i < passwordSize ; i++) {
    EEPROM.write(eepromAddress++, password[i]);
  }

  EEPROM.commit();
}

void writeIpAddress() {
  IPAddress ipAddress = WiFi.localIP();
  constexpr size_t ipAddressLength = 4;
  for (size_t i = 0 ; i < ipAddressLength ; i++) {
    Serial.write(ipAddress[i]);
  }
}
