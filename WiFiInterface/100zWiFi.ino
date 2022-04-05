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
}

void writeIpAddress() {
  IPAddress ipAddress = WiFi.localIP();
  constexpr size_t ipAddressLength = 4;
  for (size_t i = 0 ; i < ipAddressLength ; i++) {
    Serial.write(ipAddress[i]);
  }
}

int attemptConnectToWifi(size_t eepromAddress) {
  int status = WL_CONNECT_FAILED;
  char ssid[SSID_MAX_LENGTH];
  char password[PASSWORD_MAX_LENGTH];
  
  resetBuffer(ssid, SSID_MAX_LENGTH);
  resetBuffer(password, PASSWORD_MAX_LENGTH);
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
    if (WiFi.status() == WL_CONNECTED) {
      WiFi.disconnect();
    }
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
