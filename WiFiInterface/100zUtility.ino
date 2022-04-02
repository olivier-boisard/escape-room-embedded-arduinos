void resetBuffer(char buffer[], size_t bufferSize) {
  for (size_t i = 0 ; i < SSID_MAX_LENGTH ; i++) {
    buffer[i] = 0x00;
  }
}

void attemptConnectToWifi(char ssid[], char password[], size_t eepromAddress) {
  if (EEPROM[eepromAddress++] == 0x01) {
    // Read SSID
    size_t ssidLength = EEPROM[eepromAddress++];
    if (ssidLength >= SSID_MAX_LENGTH) {
      return; //TODO raise error somehow
    }
    for (size_t i = 0 ; i < ssidLength ; i++) {
      ssid[i] = EEPROM[eepromAddress++];
    }

    // Read password
    size_t passwordLength = EEPROM[eepromAddress++];
    if (passwordLength >= PASSWORD_MAX_LENGTH) {
      return; // TODO raise error somehow
    }
    for (size_t i = 0 ; i < passwordLength ; i++) {
      password[i] = EEPROM[eepromAddress++];
    }

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
  }
}
