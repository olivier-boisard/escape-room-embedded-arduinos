class UidCheckerInterface {
  public:
    virtual bool checkUid(const PiccUid& uid) = 0;
    virtual ~UidCheckerInterface() {}
};

class UidChecker : public UidCheckerInterface {
  public:

    UidChecker() {}

    void setExpectedUid(const PiccUid& expectedUid) {
      this->expectedUid = expectedUid;
    }

    bool checkUid(const PiccUid& uid) {
      return expectedUid == uid;
    }
  
  private:
    PiccUid expectedUid;
    constexpr static size_t MAX_UID_SIZE = 4;
};
