void resetBuffer(char buffer[], size_t bufferSize) {
  for (size_t i = 0 ; i < SSID_MAX_LENGTH ; i++) {
    buffer[i] = 0x00;
  }
}

int attemptConnectToWifi(char ssid[], char password[], size_t eepromAddress) {
  if (EEPROM[eepromAddress++] == VALID_WIFI_CREDENTIALS_CODE) {
    // Read SSID
    size_t ssidLength = EEPROM[eepromAddress++];
    if (ssidLength >= SSID_MAX_LENGTH) {
      return WL_NO_SSID_AVAIL; //TODO raise error somehow
    }
    for (size_t i = 0 ; i < ssidLength ; i++) {
      ssid[i] = EEPROM[eepromAddress++];
    }

    // Read password
    size_t passwordLength = EEPROM[eepromAddress++];
    if (passwordLength >= PASSWORD_MAX_LENGTH) {
      return WL_NO_SSID_AVAIL; // TODO raise error somehow
    }
    for (size_t i = 0 ; i < passwordLength ; i++) {
      password[i] = EEPROM[eepromAddress++];
    }

    // Connect to WiFi
    WiFi.begin(ssid, password);
    int status = 0;
    size_t nTries = 20;
    for (size_t i = 0 ; i < nTries ; i++) {
      status = WiFi.status();
      if (status == WL_CONNECTED) {
        break;
      }
      delay(500);
    }
    
    return status;
  }
}
