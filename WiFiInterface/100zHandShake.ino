size_t processHandshake(const byte incommingCode[], size_t incommingCodeSize, byte* outputBuffer) {
  constexpr byte expectedIncomingCode[] = {0x5A, 0x40, 0x8F, 0x02, 0x3E, 0x7B, 0xC8, 0xD2};
  constexpr byte firmwareId[] = {0x7F, 0xE0, 0x04, 0xB2, 0x7C, 0xE1, 0x0A, 0x2A};
  constexpr byte firmwareIdSize = sizeof(firmwareId);
  constexpr byte errorCode = 0xFF;

  size_t nWrittenBytes = 0;
  bool success = false;
  if (sizeof(expectedIncomingCode) == incommingCodeSize) {
    if (arrayEquals(incommingCodeSize, incommingCode, expectedIncomingCode)) {
      success = true;
      for (size_t i = 0 ; i < firmwareIdSize ; i++) {
        outputBuffer[nWrittenBytes++] = firmwareId[i];
      }
    }
  }
  
  if (!success) {
    outputBuffer[nWrittenBytes++] = errorCode;
  }
  
  return nWrittenBytes;
}
