class ByteArrayReader {
  public:
    virtual size_t read(byte inputBuffer[], size_t maxSize) = 0;
    virtual ~ByteArrayReader() {}
};
