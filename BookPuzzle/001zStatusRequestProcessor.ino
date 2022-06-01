class StatusRequestProcessor {
  public:
    StatusRequestProcessor(size_t nPiccReaders) : nPiccReaders(nPiccReaders) {
      if (nPiccReaders > piccReaderStatusBufferSize) {
        //TODO reader
      }
      for (size_t i = 0 ; i < piccReaderStatusBufferSize ; i++) {
        piccReaderStatus[i] = PiccReaderStatus::noPicc;
      }
    }

    size_t operator()(const byte command[], size_t commandSize, byte* outputBuffer) {
      constexpr byte piccReaderStatusCode = 0x01;
      constexpr byte configurationModeStatusCode = 0x02;
      constexpr byte lockStatusCode = 0x03;
      constexpr byte errorCode = 0xFF;
      constexpr byte enabledCode = 0x03;
      constexpr byte disabledCode = 0x04;
      size_t nWrittenBytes = 0;

      bool success = true;
      if (commandSize != 0) {
        success = false;
      } else {
        if (nPiccReaders > 0) {
          // Copy PICC readers status
          outputBuffer[nWrittenBytes++] = piccReaderStatusCode;
          outputBuffer[nWrittenBytes++] = (byte) nPiccReaders;
          for (size_t i = 0 ; i < nPiccReaders ; i++) {
            outputBuffer[nWrittenBytes++] = (byte) piccReaderStatus[i];
          }
        }

        // Configuration mode
        outputBuffer[nWrittenBytes++] = configurationModeStatusCode;
        outputBuffer[nWrittenBytes++] = configurationModeEnabled ? enabledCode : disabledCode;

        // Lock
        outputBuffer[nWrittenBytes++] = lockStatusCode;
        outputBuffer[nWrittenBytes++] = lockEnabled ? enabledCode : disabledCode;
      }

      // Handle error
      if (!success) {
        outputBuffer[nWrittenBytes++] = errorCode;
      }
      
      return nWrittenBytes;
    }

    void setPiccReaderStatus(size_t piccReaderIndex, PiccReaderStatus status) {
      if (piccReaderIndex > nPiccReaders) {
        return; //TODO handle error
      }
      piccReaderStatus[piccReaderIndex] = status;
    }

    void setConfigurationModeEnabled(bool enabled) {
      configurationModeEnabled = enabled;
    }

    void setLockEnabled(bool enabled) {
      lockEnabled = enabled;
    }

  private:
    constexpr static size_t piccReaderStatusBufferSize = 8;
    PiccReaderStatus piccReaderStatus[piccReaderStatusBufferSize];
    size_t nPiccReaders;
    bool configurationModeEnabled = false;
    bool lockEnabled = true;
};
