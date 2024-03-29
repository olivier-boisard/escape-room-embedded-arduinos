class InternalCommunicationManagerMixin {
  public:
    void setInternalMessage(const byte inputBuffer[], size_t messageSize) {
      if (messageSize > BUFFER_SIZE) {
        return; //TODO handle error
      }

      this->messageSize = messageSize;
      for (size_t i = 0 ; i < messageSize ; i++) {
        buffer[i] = inputBuffer[i];
      }
    }

    size_t removeInternalMessage(byte* outputBuffer) {
      for (size_t i = 0 ; i < messageSize ; i++) {
        outputBuffer[i] = buffer[i];
      }
      size_t nWrittenBytes = messageSize;
      messageSize = 0;
      return nWrittenBytes;
    }
  
    virtual ~InternalCommunicationManagerMixin() = default;

  private:
    constexpr static size_t BUFFER_SIZE = 32;
    byte buffer[BUFFER_SIZE];
    size_t messageSize = 0;
};

class SerialCommunicationManager : public CommunicationManager {
  public:
    virtual size_t read(byte inputBuffer[], size_t maxSize) override {
      return Serial.available() > 0 ? Serial.readBytesUntil(0x00, inputBuffer, maxSize) : 0;
    }
  
    virtual void write(const byte buffer[], size_t size) override {
      byte outputBuffer[MAX_BUFFER_SIZE];
      size_t nWrittenBytes = 0;
      outputBuffer[nWrittenBytes++] = MESSAGE_START_CODE;
      for (size_t i = 0 ; i < size ; i++) {
        outputBuffer[nWrittenBytes++] = buffer[i];
      }
      Serial.write(outputBuffer, nWrittenBytes);
    }

    virtual void flush() override {
      Serial.flush();
    }

    constexpr static size_t MAX_BUFFER_SIZE = 64;
    constexpr static byte MESSAGE_START_CODE = 0x99;
};

class SerialAndInternalCommunicationManager : public SerialCommunicationManager, public InternalCommunicationManagerMixin {
  public:
    virtual size_t read(byte inputBuffer[], size_t maxSize) override {
      size_t messageSize = removeInternalMessage(inputBuffer);
      if (messageSize == 0) {
        messageSize = SerialCommunicationManager::read(inputBuffer, maxSize);
      }
      return messageSize;
    };
};
