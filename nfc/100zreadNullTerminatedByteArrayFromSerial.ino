size_t readNullTerminatedByteArrayFromSerial(byte inputBuffer[], size_t maxSize) {
  return Serial.available() > 0 ? Serial.readBytesUntil(0x00, inputBuffer, maxSize) : 0;
}
