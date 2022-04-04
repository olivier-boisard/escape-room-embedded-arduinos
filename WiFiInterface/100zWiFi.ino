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
  Serial.write(IP_ADDRESS_CODE);
  IPAddress ipAddress = WiFi.localIP();
  constexpr size_t ipAddressLength = 4;
  for (size_t i = 0 ; i < ipAddressLength ; i++) {
    Serial.write(ipAddress[i]);
  }
  Serial.flush();
}

void handleConnectionResult(int connectionStatus) {
  byte result = connectionStatus == WL_CONNECTED ? CONNECTION_SUCCESS : CONNECTION_FAILURE;
  Serial.write(CONNECTION_RESULT);
  Serial.write(result);
  Serial.write(END_MSG);
}

void configWiFi(char ssid[], char password[], size_t eepromAddress) {
  int connectionStatus = attemptConnectToWifi(ssid, password, eepromAddress);
  handleConnectionResult(connectionStatus);
}
