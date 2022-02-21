class ConfigurationModeCommandProcessor {
  public:
    ConfigurationModeCommandProcessor(const function<bool()>& callback) : callback(callback) {}
  
    size_t operator()(const byte command[], size_t commandSize, byte* outputBuffer) {
      constexpr byte enabledStatus = 0x03;
      constexpr byte disabledStatus = 0x04;
      constexpr byte toggleCommand = 0x03;
      constexpr byte success = 0xF1;
      constexpr byte errorCode = 0xFF;
      constexpr byte response[] = {toggleCommand, success};
      size_t nWrittenBytes = 0;
      
      if (commandSize == 1 && command[0] == 0x03) {
        bool enabled = callback();
        for (size_t i = 0 ; i < sizeof(response) ; i++) {
          outputBuffer[nWrittenBytes++] = response[i];
        }
        outputBuffer[nWrittenBytes++] = enabled ? enabledStatus : disabledStatus;
      } else {
        outputBuffer[nWrittenBytes++] = errorCode;
      }
      
      return nWrittenBytes;
    }

  private:
    function<bool()> callback;
};
