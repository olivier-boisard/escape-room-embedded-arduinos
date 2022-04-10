class UidIsReadableChecker {
  public:
    UidIsReadableChecker(const function<bool(PiccUid*)>& readUid) : readUid(readUid) {}

    bool operator()() {
      constexpr size_t nAbsenceChecks = 2;
      bool piccIsPresentFlag = false;
      PiccUid dummy;
      for (int i = 0 ; i < nAbsenceChecks ; i++) {
        if (readUid(&dummy)) {
          piccIsPresentFlag = true;
          break;
        }
      }
      return piccIsPresentFlag;
    }

  private:
    function<bool(PiccUid*)> readUid;
};
