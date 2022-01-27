class NoCardState : public StateInterface {
  public:
    NoCardState(const MFRC522* mfrc522, const UidChecker* uidChecker)
      : mfrc522(mfrc522), uidChecker(uidChecker) {}
  
    State run() {
      State newState = State::noCard;
      digitalWrite(BLUE_LED_PIN, LOW);
      if (tryReadCardSerial(*mfrc522)) {
        if (uidChecker->checkUid(mfrc522->uid)) {
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

  private:
   UidChecker* uidChecker;
   MFRC522* mfrc522;
};
