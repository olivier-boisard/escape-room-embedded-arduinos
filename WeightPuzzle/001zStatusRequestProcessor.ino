class StatusRequestProcessor {
  public:

    StatusRequestProcessor(size_t longAsStrNDigitsToWrite) : longAsStrNDigitsToWrite(longAsStrNDigitsToWrite) {}

    size_t operator()(const byte command[], size_t commandSize, byte* outputBuffer) {
      constexpr byte lockStatusCode = 0x03;
      constexpr byte currentWeightCode = 0x13;
      constexpr byte parametersCode = 0x23;
      constexpr byte errorCode = 0xFF;
      constexpr byte enabledCode = 0x03;
      constexpr byte disabledCode = 0x04;
      size_t nWrittenBytes = 0;

      bool success = true;
      if (commandSize != 0) {
        success = false;
      } else {
        // Lock
        outputBuffer[nWrittenBytes++] = lockStatusCode;
        outputBuffer[nWrittenBytes++] = lockEnabled ? enabledCode : disabledCode;

        // Current weight 
        outputBuffer[nWrittenBytes++] = currentWeightCode;
        nWrittenBytes += writeLongAsAscii(weightInGrams, outputBuffer + nWrittenBytes, longAsStrNDigitsToWrite);

        // Parameters
        outputBuffer[nWrittenBytes++] = parametersCode;
        nWrittenBytes += writeLongAsAscii(configuration.minWeightInGrams, outputBuffer + nWrittenBytes, longAsStrNDigitsToWrite);
        nWrittenBytes += writeLongAsAscii(configuration.maxWeightInGrams, outputBuffer + nWrittenBytes, longAsStrNDigitsToWrite);
        nWrittenBytes += writeLongAsAscii(configuration.holdingTimeInMs, outputBuffer + nWrittenBytes, longAsStrNDigitsToWrite);
      }

      // Handle error
      if (!success) {
        outputBuffer[nWrittenBytes++] = errorCode;
      }

      updated = false;
      return nWrittenBytes;
    }

    bool isStatusUpdated() {
      return updated;
    }

    void setLockEnabled(bool enabled) {
      lockEnabled = enabled;
      updated = true;
    }

    void setConfiguration(const Configuration& newValue) {
      configuration = newValue;
      updated = true;
    }
    void setWeightInGrams(long newValue) {
      weightInGrams = newValue > 0 ? newValue : 0;
      updated = true;
    }

  private:
    bool lockEnabled = true;
    Configuration configuration;
    long weightInGrams = 0;
    bool updated = true;
    const size_t longAsStrNDigitsToWrite;
};
