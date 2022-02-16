class UidIsReadableChecker {
  public:
    UidIsReadableChecker(const function<bool(PiccUid*)>& readUid) : readUid(readUid) {}

    bool operator()() {
      size_t nAbsenceChecks = 2;
      bool cardIsPresentFlag = false;
      PiccUid dummy;
      for (int i = 0 ; i < nAbsenceChecks ; i++) {
        if (readUid(&dummy)) {
          cardIsPresentFlag = true;
          break;
        }
      }
      return cardIsPresentFlag;
    }

  private:
    function<bool(PiccUid*)> readUid;
};
