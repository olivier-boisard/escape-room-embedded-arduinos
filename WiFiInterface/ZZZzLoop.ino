void loop() {
  if (Serial.available() > 0) {
    byte readByte = Serial.read();
    if (readByte == CONFIG_WIFI_COMMAND) {
      getAndSaveCredentialsFromSerialPort(ssid, password);
      configWiFi(ssid, password, EEPROM_ADDRESS);
    }
  }
}
