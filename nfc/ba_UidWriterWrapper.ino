class UidWriterWrapper : public NewUidObserverInterface {
  public:
    UidWriterWrapper(const UidWriterInterface* uidWriter) : uidWriter(uidWriter) {}

    void run(const MFRC522::Uid& uid) {
      uidWriter->write(uid);
    }

  private:
    UidWriterInterface* uidWriter;
};
