class ExpectedUidUpdater : public NewUidObserverInterface {
  public:
    ExpectedUidUpdater(UidChecker* uidChecker) : uidChecker(uidChecker) {}

    void run(const PiccUid& uid) {
      uidChecker->setExpectedUid(uid);
    }

  private:
    UidChecker* uidChecker;
};
