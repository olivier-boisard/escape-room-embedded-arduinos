size_t processHandshake(const byte incommingCode[], size_t incommingCodeSize, byte* outputBuffer) {
  constexpr byte expectedIncomingCode[] = {0x4F, 0x2E, 0xC9, 0x1A, 0x31, 0x58, 0x61, 0x47};
  constexpr byte firmwareId[] = {0x30, 0x2B, 0x2A, 0x74, 0xCC, 0xAF, 0x59, 0x86};
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
