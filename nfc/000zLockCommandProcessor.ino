class LockCommandProcessor {
  public:
    LockCommandProcessor(const function<bool()>& callback) : callback(callback) {}
  
    size_t operator()(const byte command[], size_t commandSize, byte* outputBuffer) {
      constexpr byte openStatus = 0x01;
      constexpr byte closedStatus = 0x02;
      constexpr byte toggleCommand = 0x03;
      constexpr byte success = 0xF1;
      constexpr byte errorCode = 0xFF;
      constexpr byte response[] = {toggleCommand, success};//TODO remove
      size_t nWrittenBytes = 0;
      
      if (commandSize == 1 && command[0] == 0x03) {
        bool locked = callback();
        for (size_t i = 0 ; i < sizeof(response) ; i++) {
          outputBuffer[nWrittenBytes++] = response[i];
        }
        outputBuffer[nWrittenBytes++] = locked ? 0x02 : 0x01;
      } else {
        outputBuffer[nWrittenBytes++] = errorCode;
      }
      
      return nWrittenBytes;
    }

  private:
    function<bool()> callback;
};
