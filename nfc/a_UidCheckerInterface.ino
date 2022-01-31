class UidCheckerInterface {
  public:
    virtual bool checkUid(const PiccUid& uid) = 0;
    virtual ~UidCheckerInterface() {}
};
