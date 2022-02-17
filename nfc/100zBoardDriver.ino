size_t processHandShake(const byte incommingCode[], size_t incommingCodeSize, byte* outputBuffer) {
  constexpr byte expectedIncomingCode[] = {0x01, 0xEE, 0x35, 0xD7, 0x2A, 0x80, 0x58, 0xEA};
  constexpr byte firmwareId[] = {0x85, 0xF2, 0x9E, 0xE3, 0x43, 0x19, 0xEA, 0xF6};
  constexpr byte firmwareIdSize = sizeof(firmwareId);
  constexpr byte errorCode = 0xFF;

  size_t nWrittenBytes = 0;
  if (sizeof(expectedIncomingCode) == incommingCodeSize) {
    if (arrayEquals(incommingCodeSize, incommingCode, expectedIncomingCode)) {
      for (size_t i = 0 ; i < firmwareIdSize ; i++) {
        outputBuffer[nWrittenBytes++] = firmwareId[i];
      }
    } else {
      outputBuffer[nWrittenBytes++] = errorCode;
    }
  }
  
  return nWrittenBytes;
}

class BoardDriver {
  public:
    BoardDriver(
      const function<size_t(byte[], size_t)>& readByteArray,
      ByteArrayWriter& byteArrayWriter,
      const function<size_t(const byte[], size_t, byte*)>& processHandshakeCommand
    ) : readByteArray(readByteArray),
        byteArrayWriter(byteArrayWriter),
        processHandshakeCommand(processHandshakeCommand) {}
  
    void processInput() {
      constexpr size_t bufferSize = 16;
      byte inputBuffer[bufferSize];
      byte outputBuffer[bufferSize];

      int readBytes = readByteArray(inputBuffer, bufferSize);
      if (readBytes > 0) {
        size_t nWrittenBytes = processCommand(inputBuffer, readBytes, outputBuffer);
        byteArrayWriter.write(outputBuffer, nWrittenBytes);
        byteArrayWriter.flush();
      }
    }

  private:
    function<size_t(byte[], size_t)> readByteArray;
    ByteArrayWriter& byteArrayWriter;
    function<size_t(const byte[], size_t, byte*)> processHandshakeCommand;

    size_t processCommand(const byte inputBuffer[], size_t inputSize, byte* outputBuffer) {
      constexpr byte handshakeCode = 0x10;
      constexpr size_t commandArgOffset = 1;
      const byte command = inputBuffer[0];
      int nWrittenBytes = 0;
            
      outputBuffer[nWrittenBytes++] = command;
      switch (command) {
        case handshakeCode:
          nWrittenBytes += processHandshakeCommand(
            inputBuffer + commandArgOffset,
            inputSize - commandArgOffset,
            outputBuffer + nWrittenBytes
          );
          break;
        default:
          break;
      }
      return nWrittenBytes;
    }

    bool isSuccess(int status) {
      return status >= 0;
    }
};
