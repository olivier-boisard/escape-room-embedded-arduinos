class LockCommandProcessor {
  public:
    ToggleLockCommandProcessor(const function<void()>& callback) : callback(callback) {}
  
    size_t operator()(const byte command[], size_t commandSize, byte* outputBuffer) {
      constexpr byte toggleCommand = 0x03;
      constexpr byte success = 0xF1;
      constexpr byte errorCode = 0xFF;
      constexpr byte response[] = {toggleCommand, success};
      size_t nWrittenBytes = 0;
      
      if (commandSize == 1 && command[0] == 0x03) {
        callback();
        for (size_t i = 0 ; i < sizeof(response) ; i++) {
          outputBuffer[nWrittenBytes++] = response[i];
        }
      } else {
        outputBuffer[nWrittenBytes++] = errorCode;
      }
      
      return nWrittenBytes;
    }

  private:
    function<void()> callback;
};
