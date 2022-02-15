class ByteArrayWriter {
  public:
    virtual void write(byte outputBuffer[], size_t size) = 0;
    virtual void flush() = 0;
    
    void write(byte singleByte) { this->write(&singleByte, 1); }
    
    virtual ~ByteArrayWriter() {}
};
