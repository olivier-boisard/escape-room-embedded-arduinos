class UidWriterWrapper : public NewUidObserverInterface {
  public:
    UidWriterWrapper(const NewUidObserverInterface* uidWriter) : uidWriter(uidWriter) {}

    void run(const PiccUid& uid) {
      uidWriter->run(uid);
    }

  private:
    NewUidObserverInterface* uidWriter;
};
