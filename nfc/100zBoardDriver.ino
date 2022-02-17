int processHandShake(const byte inputBuffer[], size_t inputBufferSize, byte* outputBuffer) {
  constexpr byte expectedIncomingCode[] = {0x01, 0xEE, 0x35, 0xD7, 0x2A, 0x80, 0x58, 0xEA};
  constexpr byte firmwareId[] = {0x85, 0xF2, 0x9E, 0xE3, 0x43, 0x19, 0xEA, 0xF6};
  constexpr byte firmwareIdSize = 8;
  constexpr int errorReturnCode = -1;

  bool isSuccess = false;
  if (sizeof(firmwareId) == inputBufferSize) {
    isSuccess = arrayEquals(sizeof(expectedIncomingCode), inputBuffer, expectedIncomingCode);
    if (isSuccess) {
      for (size_t i = 0 ; i < firmwareIdSize ; i++) {
        outputBuffer[i] = firmwareId[i];
      }
    }
  }
  
  return isSuccess ? sizeof(firmwareId) : errorReturnCode;
}

class BoardDriver {
  public:
    BoardDriver(
      const function<size_t(byte[], size_t)>& readByteArray,
      ByteArrayWriter& byteArrayWriter,
      const function<int(const byte[], size_t, byte*)>& processHandshakeCommand
    ) : readByteArray(readByteArray),
        byteArrayWriter(byteArrayWriter),
        processHandshakeCommand(processHandshakeCommand) {}
  
    void processInput() {
      constexpr size_t bufferSize = 16;
      byte inputBuffer[bufferSize];

      int readBytes = readByteArray(inputBuffer, bufferSize);
      if (readBytes > 0) {
        byte outputBuffer[bufferSize];
        int status = processCommand(inputBuffer, readBytes, outputBuffer);
        if (status > 0) {
          byteArrayWriter.write(outputBuffer, status);
        } else {
          constexpr byte errorCode = 0xFF;
          byteArrayWriter.write(errorCode);
        }
        byteArrayWriter.flush();
      }
    }

  private:
    function<size_t(byte[], size_t)> readByteArray;
    ByteArrayWriter& byteArrayWriter;
    function<int(const byte[], size_t, byte*)> processHandshakeCommand;

    bool processCommand(const byte inputBuffer[], size_t size, byte* outputBuffer) {
      constexpr byte handshakeCode = 0x10;
      
      int status = 0;
      const byte command = inputBuffer[0];
      outputBuffer[0] = command;
      switch (command) {
        case handshakeCode:
          status = processHandshakeCommand(inputBuffer + 1, size - 1, outputBuffer + 1);
          break;
        default:
          break;
      }

      return status > 0;
    }
};
