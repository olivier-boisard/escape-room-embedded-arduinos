class UpdateableUidChecker : public UidChecker, public UidObserver {
  public:

    bool run(const PiccUid& uid) override {
      return expectedUid == uid;
    }

    void setExpectedUid(const PiccUid& expectedUid) {
      this->expectedUid = expectedUid;
    }

    void update(const PiccUid& expectedUid) override {
      setExpectedUid(expectedUid);
    }
  
  private:
    PiccUid expectedUid;
};
