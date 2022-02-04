class UidIsReadableChecker : public NiladicBoolFunction {
  public:
    UidIsReadableChecker(const PiccUidFactory* piccUidFactory) : piccUidFactory(piccUidFactory) {}

    bool run() override {
      size_t nAbsenceChecks = 2;
      bool cardIsPresentFlag = false;
      PiccUid dummy;
      for (int i = 0 ; i < nAbsenceChecks ; i++) {
        if (piccUidFactory->generate(&dummy)) {
          cardIsPresentFlag = true;
          break;
        }
      }
      return cardIsPresentFlag;
    }

  private:
    PiccUidFactory* piccUidFactory;
};
