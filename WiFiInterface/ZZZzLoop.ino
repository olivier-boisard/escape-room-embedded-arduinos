void loop() {
  if (Serial.available() > 0) {
    byte readByte = Serial.read();
    if (readByte == CONFIG_WIFI_COMMAND) {
      getAndSaveCredentialsFromSerialPort(ssid, password);
      configWiFi(ssid, password, EEPROM_ADDRESS);
    } else if (readByte == HANDSHAKE_CODE) {
      byte inputBuffer[MAX_BUFFER_SIZE];
      byte outputBuffer[MAX_BUFFER_SIZE];
      size_t incommingCodeSize = Serial.readBytesUntil(0x00, inputBuffer, MAX_BUFFER_SIZE);
      size_t nWrittenBytes = processHandshake(inputBuffer, incommingCodeSize, outputBuffer);
      outputBuffer[nWrittenBytes++] = END_MSG;
      Serial.write(outputBuffer, nWrittenBytes);
    }
  }
}
