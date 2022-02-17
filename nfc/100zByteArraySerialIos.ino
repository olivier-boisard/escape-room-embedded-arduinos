size_t readNullTerminatedByteArrayFromSerial(byte inputBuffer[], size_t maxSize) {
  return Serial.available() > 0 ? Serial.readBytesUntil(0x00, inputBuffer, maxSize) : 0;
}

class SerialByteArrayWriter : public ByteArrayWriter {
  public:
    virtual void write(const byte outputBuffer[], size_t size) override {
      Serial.write(outputBuffer, size);
    }

    virtual void flush() override {
      Serial.flush();
    }
};
