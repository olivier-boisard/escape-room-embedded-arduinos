class UidIsReadableChecker : public NiladicBoolFunction {
  public:
    UidIsReadableChecker(const PiccUidFactory* piccUidFactory) : piccUidFactory(piccUidFactory) {}

    bool run() override {
      bool cardIsPresentFlag = false;
      PiccUid dummy;
      for (int i = 0 ; i < N_ABSENCE_CHECKS ; i++) {
        if (piccUidFactory->generate(&dummy)) {
          cardIsPresentFlag = true;
          break;
        }
      }
      return cardIsPresentFlag;
    }

  private:
    PiccUidFactory* piccUidFactory;
    constexpr static size_t N_ABSENCE_CHECKS = 2;
};
