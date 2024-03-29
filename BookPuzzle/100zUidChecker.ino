class UpdateableUidChecker {
  public:

    bool checkUid(const PiccUid& uid) const {
      return expectedUid == uid;
    }

    void setExpectedUid(const PiccUid& expectedUid) {
      this->expectedUid = expectedUid;
    }

    void update(const PiccUid& expectedUid) {
      setExpectedUid(expectedUid);
    }
  
  private:
    PiccUid expectedUid;
};
