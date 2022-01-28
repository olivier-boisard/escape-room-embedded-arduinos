class CardPresenceChecker : public CardPresenceCheckerInterface {
  public:
    CardPresenceChecker(MFRC522* mfrc522) : mfrc522(mfrc522) {}
  
    bool cardIsPresent() {
      bool cardIsPresentFlag = false;
      for (int i = 0 ; i < N_ABSENCE_CHECKS ; i++) {
        if (tryReadCardSerial(*mfrc522)) {
          cardIsPresentFlag = true;
          break;
        }
      }
      return cardIsPresentFlag;
    }

  private:
    MFRC522* mfrc522;
};
