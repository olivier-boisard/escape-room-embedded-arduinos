void getAndSaveCredentialsFromSerialPort(char ssidOutputBuffer[], char passwordOutputBuffer[]) {
  // Get credentials
  size_t ssidSize = Serial.readBytesUntil(0x00, ssidOutputBuffer, SSID_MAX_LENGTH);
  size_t passwordSize = Serial.readBytesUntil(0x00, passwordOutputBuffer, PASSWORD_MAX_LENGTH);

  // Save credentials
  size_t eepromAddress = EEPROM_ADDRESS;
  EEPROM.write(eepromAddress++, VALID_WIFI_CREDENTIALS_CODE);
  EEPROM.write(eepromAddress++, ssidSize);
  for (size_t i = 0 ; i < ssidSize ; i++) {
    EEPROM.write(eepromAddress++, ssidOutputBuffer[i]);
  }
  EEPROM.write(eepromAddress++, passwordSize);
  for (size_t i = 0 ; i < passwordSize ; i++) {
    EEPROM.write(eepromAddress++, passwordOutputBuffer[i]);
  }
}

void writeIpAddress() {
  IPAddress ipAddress = WiFi.localIP();
  constexpr size_t ipAddressLength = 4;
  for (size_t i = 0 ; i < ipAddressLength ; i++) {
    Serial.write(ipAddress[i]);
  }
}

int attemptConnectToWifi(char ssid[], char password[], size_t eepromAddress) {
  int status = WL_CONNECT_FAILED;
  if (EEPROM.read(eepromAddress++) == VALID_WIFI_CREDENTIALS_CODE) {
    // Read SSID
    size_t ssidLength = EEPROM.read(eepromAddress++);
    if (ssidLength >= SSID_MAX_LENGTH) {
      return WL_NO_SSID_AVAIL; //TODO raise error somehow
    }
    for (size_t i = 0 ; i < ssidLength ; i++) {
      ssid[i] = EEPROM.read(eepromAddress++);
    }

    // Read password
    size_t passwordLength = EEPROM.read(eepromAddress++);
    if (passwordLength >= PASSWORD_MAX_LENGTH) {
      return WL_NO_SSID_AVAIL; // TODO raise error somehow
    }
    for (size_t i = 0 ; i < passwordLength ; i++) {
      password[i] = EEPROM.read(eepromAddress++);
    }

    // Connect to WiFi
    WiFi.begin(ssid, password);
    size_t nTries = 20;
    for (size_t i = 0 ; i < nTries ; i++) {
      status = WiFi.status();
      if (status == WL_CONNECTED) {
        break;
      }
      delay(500);
    }
  }
  return status;
}
