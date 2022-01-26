class CardIsPresentState : public StateInterface {
  public:
    CardIsPresentState(MFRC522* mfrc522) : mfrc522(mfrc522) {}

    State run() {
      State newState = State::cardIsPresent;
      digitalWrite(BLUE_LED_PIN, LOW);
      if (!checkCardIsPresent()) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        newState = State::noCard;
      }
      return newState;
    }

  private:
    MFRC522* mfrc522;
    
    //TODO this is duplicate code
    bool checkCardIsPresent() {
      bool cardIsPresentFlag = false;
      for (int i = 0 ; i < N_ABSENCE_CHECKS ; i++) {
        if (tryReadCardSerial(*mfrc522)) {
          cardIsPresentFlag = true;
          break;
        }
      }
      return cardIsPresentFlag;
   }
};
