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
