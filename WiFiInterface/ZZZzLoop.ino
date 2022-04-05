void loop() {
  if (Serial.available() > 0) {
    byte readByte = Serial.read();
    
    if (readByte == CONFIG_WIFI_COMMAND) {
      getAndSaveCredentialsFromSerialPort(EEPROM_ADDRESS);
      
      int status = attemptConnectToWifi(EEPROM_ADDRESS);
      Serial.write(CONNECTION_RESULT);
      if (status == WL_CONNECTED) {
        Serial.write(CONNECTION_SUCCESS);
        writeIpAddress();
      } else {
        Serial.write(CONNECTION_FAILURE);
      }
      Serial.flush();
    } else if (readByte == HANDSHAKE_CODE) {
      byte inputBuffer[MAX_BUFFER_SIZE];
      byte outputBuffer[MAX_BUFFER_SIZE];
      size_t incommingCodeSize = Serial.readBytesUntil(0x00, inputBuffer, MAX_BUFFER_SIZE);
      size_t nWrittenBytes = processHandshake(inputBuffer, incommingCodeSize, outputBuffer);
      outputBuffer[nWrittenBytes++] = END_MSG;
      Serial.write(outputBuffer, nWrittenBytes);
      Serial.flush();
    }
  }
}