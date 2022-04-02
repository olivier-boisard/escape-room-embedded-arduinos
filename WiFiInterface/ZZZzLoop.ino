void loop() {
  if (Serial.available() > 0) {
    byte readByte = Serial.read();
    if (readByte == CONFIG_WIFI_COMMAND) {
      size_t ssidSize = Serial.readBytesUntil(0x00, ssid, SSID_MAX_LENGTH);
      size_t passwordSize = Serial.readBytesUntil(0x00, password, PASSWORD_MAX_LENGTH);

      size_t eepromAddress = EEPROM_ADDRESS;
      EEPROM.write(eepromAddress++, ssidSize);
      for (size_t i = 0 ; i < ssidSize ; i++) {
        EEPROM.write(eepromAddress++, ssid[i]);
      }
      EEPROM.write(eepromAddress++, passwordSize);
      for (size_t i = 0 ; i < passwordSize ; i++) {
        EEPROM.write(eepromAddress++, password[i]);
      }
      
      attemptConnectToWifi(ssid, password, EEPROM_ADDRESS);
    }
  }
}
