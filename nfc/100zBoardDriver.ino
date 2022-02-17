bool processHandshakeCommand(byte inputBuffer[], function<void(const byte[], size_t)> writeByteArray) {
  constexpr byte expectedIncomingCode[] = {0x01, 0xEE, 0x35, 0xD7, 0x2A, 0x80, 0x58, 0xEA};
  constexpr byte firmwareId[] = {0x85, 0xF2, 0x9E, 0xE3, 0x43, 0x19, 0xEA, 0xF6};

  bool isSuccess = arrayEquals(sizeof(expectedIncomingCode), inputBuffer, expectedIncomingCode);
  if (isSuccess) {
    writeByteArray(firmwareId, sizeof(firmwareId));
  }
  
  return isSuccess;
}

class BoardDriver {
  public:
    BoardDriver(
      const function<size_t(byte[], size_t)>& readByteArray,
      ByteArrayWriter& byteArrayWriter,
      function<bool(byte[])> processHandshakeCommand
    ) : readByteArray(readByteArray),
        byteArrayWriter(byteArrayWriter),
        processHandshakeCommand(processHandshakeCommand) {}
  
    void processInput() {
      constexpr size_t inputBufferSize = 16;
      byte inputBuffer[inputBufferSize];
      
      if (readByteArray(inputBuffer, inputBufferSize) > 0) {
        byte command = inputBuffer[0];
        byteArrayWriter.write(command);
        
        bool isSuccess = processCommand(command, inputBuffer + 1);
        handleErrorIfNeeded(isSuccess);
        
        byteArrayWriter.flush();
      }
    }

  private:
    function<size_t(byte[], size_t)> readByteArray;
    ByteArrayWriter& byteArrayWriter;
    function<bool(byte[], function<void(const byte[], size_t)>)> processHandshakeCommand;

    bool processCommand(byte command, byte args[]) {
      constexpr byte handshakeCode = 0x10;
      bool isSuccess = false;
      auto wrapper = [this] (byte dataToWrite[], size_t size) { this->byteArrayWriter.write(dataToWrite, size); };
      switch (command) {
        case handshakeCode:
          isSuccess = processHandshakeCommand(args, wrapper);
          break;
        default:
          isSuccess = false;
          break;
      }
      return isSuccess;
    }

    void handleErrorIfNeeded(bool isSuccess) {
      constexpr byte errorCode = 0xFF;
      if (!isSuccess) {
        byteArrayWriter.write(errorCode);
      }
    }
};
