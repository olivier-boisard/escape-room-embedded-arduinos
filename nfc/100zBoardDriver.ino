class BoardDriver {
  public:
    BoardDriver(
      CommunicationManager& communicationManager,
      const function<size_t(const byte[], size_t, byte*)>& processHandshakeCommand,
      const function<size_t(const byte[], size_t, byte*)>& processLockCommand
    ) : communicationManager(communicationManager),
        processHandshakeCommand(processHandshakeCommand),
        processLockCommand(processLockCommand) {}
  
    void processInput() {
      constexpr size_t bufferSize = 16;
      byte inputBuffer[bufferSize];
      byte outputBuffer[bufferSize];

      int readBytes = communicationManager.read(inputBuffer, bufferSize);
      if (readBytes > 0) {
        size_t nWrittenBytes = processCommand(inputBuffer, readBytes, outputBuffer);
        communicationManager.write(outputBuffer, nWrittenBytes);
        communicationManager.flush();
      }
    }

  private:
    CommunicationManager& communicationManager;
    function<size_t(const byte[], size_t, byte*)> processHandshakeCommand;
    function<size_t(const byte[], size_t, byte*)> processLockCommand;

    size_t processCommand(const byte inputBuffer[], size_t inputSize, byte* outputBuffer) {
      constexpr byte handshakeCode = 0x10;
      constexpr byte lockCode = 0x30;
      constexpr size_t commandArgOffset = 1;
      const byte command = inputBuffer[0];
      int nWrittenBytes = 0;

      outputBuffer[nWrittenBytes++] = command;
      function<size_t(const byte[], size_t, byte*)> commandProcessor;
      switch (command) {
        case handshakeCode:
          commandProcessor = processHandshakeCommand;
          break;
        case lockCode:
          commandProcessor = processLockCommand;
          break;
        default:
          break;
      }
      nWrittenBytes += commandProcessor(
        inputBuffer + commandArgOffset,
        inputSize - commandArgOffset,
        outputBuffer + nWrittenBytes
      );
      
      outputBuffer[nWrittenBytes++] = 0x00;
      return nWrittenBytes;
    }
};
