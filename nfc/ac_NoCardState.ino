class NoCardState : public StateInterface {
  public:
    NoCardState(MFRC522* mfrc522) : mfrc522(mfrc522) {}
  
    State run() {
      State newState = State::noCard;
      digitalWrite(BLUE_LED_PIN, LOW);
      if (tryReadCardSerial(*mfrc522)) {
        if (uidChecker.checkUid(mfrc522->uid)) {
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(RED_LED_PIN, LOW);
        } else {
          digitalWrite(GREEN_LED_PIN, LOW);
          digitalWrite(RED_LED_PIN, HIGH);
        }
        newState = State::cardIsPresent;
      }
      return newState;
   }

   void setExpectedUid(const MFRC522::Uid& expectedUid) {
      uidChecker.setExpectedUid(expectedUid);
   }

  private:
   UidChecker uidChecker;
   MFRC522* mfrc522;
};
