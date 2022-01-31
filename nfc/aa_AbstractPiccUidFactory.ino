class AbstractPiccUidFactory {
  public: 
    virtual bool generate(PiccUid* output) = 0;
    
    bool uidIsReadable() {
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
