class CommandProcessors {
  static bool processHandshakeCommandFunction(const byte inputBuffer[], function<void(const byte[], size_t)> writeByteArray) {
    constexpr byte expectedIncomingCode[] = {0x01, 0xEE, 0x35, 0xD7, 0x2A, 0x80, 0x58, 0xEA};
    constexpr byte firmwareId[] = {0x85, 0xF2, 0x9E, 0xE3, 0x43, 0x19, 0xEA, 0xF6};
  
    bool isSuccess = arrayEquals(sizeof(expectedIncomingCode), inputBuffer, expectedIncomingCode);
    if (isSuccess) {
      writeByteArray(firmwareId, sizeof(firmwareId));
    }
    
    return isSuccess;
  }
};
