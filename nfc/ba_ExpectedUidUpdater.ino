class ExpectedUidUpdater : public NewUidObserverInterface {
  public:
    ExpectedUidUpdater(UidChecker* uidChecker) : uidChecker(uidChecker) {}

    void run(const MFRC522::Uid& uid) {
      uidChecker->setExpectedUid(uid);
    }

  private:
    UidChecker* uidChecker;
};
