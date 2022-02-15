class NullTerminatedSerialByteArrayReader {
  public:
    virtual size_t operator()(byte inputBuffer[], size_t maxSize) {
      return Serial.available() > 0 ? Serial.readBytesUntil(0x00, inputBuffer, maxSize) : 0;
    }
};
