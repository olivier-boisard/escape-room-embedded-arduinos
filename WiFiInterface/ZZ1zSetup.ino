void setup() {
  Serial.begin(SERIAL_PORT_BAUDRATE);

  // Init buffers
  resetBuffer(ssid, SSID_MAX_LENGTH);
  resetBuffer(password, PASSWORD_MAX_LENGTH);

  // Attempt connection to WiFi
  attemptConnectToWifi(EEPROM_ADDRESS);
}
