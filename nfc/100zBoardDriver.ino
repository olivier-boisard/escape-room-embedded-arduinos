class BoardDriver {
  public:

    //TODO reduce number of parameters
    BoardDriver(
      CommunicationManager& communicationManager,
      const function<size_t(const byte[], size_t, byte*)>& processHandshakeCommand,
      const function<size_t(const byte[], size_t, byte*)>& statusRequestCommand,
      const function<size_t(const byte[], size_t, byte*)>& processLockCommand,
      const function<size_t(const byte[], size_t, byte*)>& processConfigurationModeCommand
    ) : communicationManager(communicationManager),
        statusRequestCommand(statusRequestCommand),
        processHandshakeCommand(processHandshakeCommand),
        processLockCommand(processLockCommand),
        processConfigurationModeCommand(processConfigurationModeCommand) {}
  
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

    constexpr static byte HANDSHAKE_CODE = 0x10;
    constexpr static byte STATUS_REQUEST_CODE = 0x20;
    constexpr static byte LOCK_CODE = 0x30;
    constexpr static byte CONFIGURATION_CODE = 0x40;

  private:
    CommunicationManager& communicationManager;
    function<size_t(const byte[], size_t, byte*)> processHandshakeCommand;
    function<size_t(const byte[], size_t, byte*)> statusRequestCommand;
    function<size_t(const byte[], size_t, byte*)> processLockCommand;
    function<size_t(const byte[], size_t, byte*)> processConfigurationModeCommand;

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
        case CONFIGURATION_CODE:
          commandProcessor = processConfigurationModeCommand;
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
