void loop() {
  // Read serial port
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
      Serial.write(END_MSG);
      Serial.flush();
    } else if (readByte == HANDSHAKE_CODE) {
      byte inputBuffer[MAX_BUFFER_SIZE];
      byte outputBuffer[MAX_BUFFER_SIZE];
      size_t incommingCodeSize = Serial.readBytesUntil(0x00, inputBuffer, MAX_BUFFER_SIZE);
      size_t nWrittenBytes = processHandshake(inputBuffer, incommingCodeSize, outputBuffer);
      outputBuffer[nWrittenBytes++] = END_MSG;
      Serial.write(outputBuffer, nWrittenBytes);
      Serial.flush();
    } else if (readByte == FORWARD_SERIAL_MESSAGE_COMMAND) {
      //Write WiFi
      byte buffer[MAX_BUFFER_SIZE];
      size_t nBytesToWrite = Serial.readBytesUntil(0x00, buffer, MAX_BUFFER_SIZE);
      buffer[nBytesToWrite++] = END_MSG;
      if (!client) {
        client = server.available();
      }

      if (client) {
        if (client.connected()) {
          for (size_t i = 0 ; i < nBytesToWrite ; i++) {
            client.write(buffer[i]);
          }
          client.flush();
        }
      }
    }
  }

  // Read WiFi
  if (WiFi.status() == WL_CONNECTED) {
    if (!client) {
      client = server.available();
    }
    
    if (client) {
      if (client.connected()) {
        byte buffer[MAX_BUFFER_SIZE];
        size_t nWrittenBytes = 0;
        byte readByte = 0x00;
        if (client.available() > 0) {
          do {
            readByte = client.read();
            buffer[nWrittenBytes++] = readByte;
          } while (readByte != END_MSG);
          Serial.write(buffer, nWrittenBytes);
          Serial.flush();
        }
      }
    }
  } else {
    attemptConnectToWifi(EEPROM_ADDRESS);
  }
}
