class SerialByteArrayWriter : public ByteArrayWriter {
  public:
    virtual void write(byte outputBuffer[], size_t size) override {
      Serial.write(outputBuffer, size);
    }

    virtual void flush() override {
      Serial.flush();
    }
};
