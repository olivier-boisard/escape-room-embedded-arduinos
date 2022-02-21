size_t processHandShake(const byte incommingCode[], size_t incommingCodeSize, byte* outputBuffer) {
  constexpr byte expectedIncomingCode[] = {0x01, 0xEE, 0x35, 0xD7, 0x2A, 0x80, 0x58, 0xEA};
  constexpr byte firmwareId[] = {0x85, 0xF2, 0x9E, 0xE3, 0x43, 0x19, 0xEA, 0xF6};
  constexpr byte firmwareIdSize = sizeof(firmwareId);
  constexpr byte errorCode = 0xFF;

  size_t nWrittenBytes = 0;
  bool success = false;
  if (sizeof(expectedIncomingCode) == incommingCodeSize) {
    if (arrayEquals(incommingCodeSize, incommingCode, expectedIncomingCode)) {
      for (size_t i = 0 ; i < firmwareIdSize ; i++) {
        outputBuffer[nWrittenBytes++] = firmwareId[i];
      }
    } else {
      success = false;
    }
  } else {
    success = false;
  }
  
  if (!success) {
    outputBuffer[nWrittenBytes++] = errorCode;
  }
  
  return nWrittenBytes;
}
