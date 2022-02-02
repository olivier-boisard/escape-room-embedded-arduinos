class UidChecker {
  public:
    virtual bool run(const PiccUid& uid) = 0;
    virtual ~UidChecker() {}
};
