class SerialCommunicationManager : public CommunicationManager {
  public:
    virtual size_t read(byte inputBuffer[], size_t maxSize) override {
      return Serial.available() > 0 ? Serial.readBytesUntil(0x00, inputBuffer, maxSize) : 0;
    }
  
    virtual void write(const byte outputBuffer[], size_t size) override {
      Serial.write(outputBuffer, size);
    }

    virtual void flush() override {
      Serial.flush();
    }
};
