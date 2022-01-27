class UidWriterInterface {
  public:
    virtual void write(const MFRC522::Uid& uid) = 0;

    virtual ~UidWriterInterface() {}
};
