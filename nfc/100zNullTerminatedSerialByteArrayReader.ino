class NullTerminatedSerialByteArrayReader : public ByteArrayReader {
  public:
    virtual size_t read(byte inputBuffer[], size_t maxSize) override {
      return Serial.available() > 0 ? Serial.readBytesUntil(0x00, inputBuffer, maxSize) : 0;
    }
};
