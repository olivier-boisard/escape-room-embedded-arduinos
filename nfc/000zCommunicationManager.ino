class CommunicationManager {
  public:
    virtual size_t read(byte inputBuffer[], size_t maxSize) = 0;
    virtual void write(const byte outputBuffer[], size_t size) = 0;
    virtual void flush() = 0;
    
    void write(byte singleByte) {
      this->write(&singleByte, 1);
    }
    
    virtual ~CommunicationManager() = default;
};
