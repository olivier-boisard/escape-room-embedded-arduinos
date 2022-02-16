class UpdateableUidChecker : public UidObserver {
  public:

    bool checkUid(const PiccUid& uid) {
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
