class BoardDriver {
  public:
    BoardDriver(
      const function<size_t(byte[], size_t)>& readByteArray,
      ByteArrayWriter& byteArrayWriter,
      function<bool(const byte[], function<void(const byte[], size_t)>&)>& processHandshakeCommand
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
    function<bool(const byte[], function<void(const byte[], size_t)>&)> processHandshakeCommand;

    bool processCommand(byte command, const byte args[]) {
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
