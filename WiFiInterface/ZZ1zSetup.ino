void setup() {
  Serial.begin(SERIAL_PORT_BAUDRATE);
  EEPROM.begin(EEPROM_SIZE);
  attemptConnectToWifi(EEPROM_ADDRESS);
}
