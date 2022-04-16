class StatusRequestProcessor {
  public:

    StatusRequestProcessor() : 
        lockEnabled(true),
        minWeightInGrams(0),
        maxWeightInGrams(0),
        minTimeIntervalInMs(0),
        weightInGrams(0),
        updated(true) {}

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
        nWrittenBytes += writeLongAsAscii(weightInGrams, outputBuffer + nWrittenBytes);

        // Parameters
        outputBuffer[nWrittenBytes++] = parametersCode;
        nWrittenBytes += writeLongAsAscii(minWeightInGrams, outputBuffer + nWrittenBytes);
        nWrittenBytes += writeLongAsAscii(maxWeightInGrams, outputBuffer + nWrittenBytes);
        nWrittenBytes += writeLongAsAscii(minTimeIntervalInMs, outputBuffer + nWrittenBytes);
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

    void setMinWeightInGrams(long newValue) {
      minWeightInGrams = newValue;
      updated = true;
    }

    void setMaxWeightInGrams(long newValue) {
      maxWeightInGrams = newValue;
      updated = true;
    }

    void setMinTimeIntervalInMs(long newValue) {
      minTimeIntervalInMs = newValue;
      updated = true;
    }

    void setWeightInGrams(long newValue) {
      weightInGrams = newValue > 0 ? newValue : 0;
      updated = true;
    }

  private:
    bool lockEnabled;
    long minWeightInGrams;
    long maxWeightInGrams;
    long minTimeIntervalInMs;
    long weightInGrams;
    bool updated;
};
