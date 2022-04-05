WiFiServer server(SERVER_PORT);
WiFiClient client;


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
    bool success = false;
    WiFi.begin(ssid, password);
    size_t nTries = 20;
    for (size_t i = 0 ; i < nTries ; i++) {
      status = WiFi.status();
      if (status == WL_CONNECTED) {
        success = true;
        break;
      }
      delay(500);
    }

    // Setup server
    if (success) {
      server.begin();
    }
  }
  return status;
}
