class BoardDriver {
  public:

    BoardDriver(
      CommunicationManager& communicationManager,
      const function<size_t(const byte[], size_t, byte*)>& processHandshakeCommand,
      const function<size_t(const byte[], size_t, byte*)>& statusRequestCommand,
      const function<size_t(const byte[], size_t, byte*)>& processLockCommand,
      const function<size_t(const byte[], size_t, byte*)>& configureCommand
    ) : communicationManager(communicationManager),
        processHandshakeCommand(processHandshakeCommand),
        statusRequestCommand(statusRequestCommand),
        processLockCommand(processLockCommand),
        configureCommand(configureCommand) {}
  
    void processInput() {
      constexpr size_t bufferSize = 128;
      byte inputBuffer[bufferSize];
      byte outputBuffer[bufferSize];

      int readBytes = communicationManager.read(inputBuffer, bufferSize);
      if (readBytes > 0) {
        size_t nWrittenBytes = processCommand(inputBuffer, readBytes, outputBuffer);
        communicationManager.write(outputBuffer, nWrittenBytes);
        communicationManager.flush();
      }
    }

    constexpr static byte HANDSHAKE_CODE = 0x10;
    constexpr static byte STATUS_REQUEST_CODE = 0x20;
    constexpr static byte CONFIGURE_CODE = 0x21;
    constexpr static byte LOCK_CODE = 0x05;

  private:
    CommunicationManager& communicationManager;
    function<size_t(const byte[], size_t, byte*)> processHandshakeCommand;
    function<size_t(const byte[], size_t, byte*)> statusRequestCommand;
    function<size_t(const byte[], size_t, byte*)> processLockCommand;
    function<size_t(const byte[], size_t, byte*)> configureCommand;

    size_t processCommand(const byte inputBuffer[], size_t inputSize, byte* outputBuffer) {
      constexpr size_t commandArgOffset = 1;
      const byte command = inputBuffer[0];
      int nWrittenBytes = 0;

      outputBuffer[nWrittenBytes++] = command;
      function<size_t(const byte[], size_t, byte*)> commandProcessor;
      switch (command) {
        case HANDSHAKE_CODE:
          commandProcessor = processHandshakeCommand;
          break;
        case STATUS_REQUEST_CODE:
          commandProcessor = statusRequestCommand;
          break;
        case LOCK_CODE:
          commandProcessor = processLockCommand;
          break;
        case CONFIGURE_CODE:
          commandProcessor = configureCommand;
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
