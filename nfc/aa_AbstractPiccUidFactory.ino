//TODO this breaks the SIF
class AbstractPiccUidFactory {
  public: 
    virtual bool generate(PiccUid* output) = 0;
    
    bool cardIsPresent() {
      bool cardIsPresentFlag = false;
      PiccUid dummy;
      for (int i = 0 ; i < N_ABSENCE_CHECKS ; i++) {
        if (this->generate(&dummy)) {
          cardIsPresentFlag = true;
          break;
        }
      }
      return cardIsPresentFlag;
    }
    
   virtual ~AbstractPiccUidFactory() {}
};
