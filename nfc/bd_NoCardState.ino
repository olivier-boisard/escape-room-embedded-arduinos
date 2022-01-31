class NoCardState : public StateInterface {
  public:
    NoCardState(const AbstractPiccUidFactory* uidReader, const UidCheckerInterface* uidChecker)
      : uidReader(uidReader), uidChecker(uidChecker) {}
  
    State run() {
      State newState = State::noCard;
      digitalWrite(BLUE_LED_PIN, LOW);
      PiccUid readPicc;
      if (uidReader->generate(&readPicc)) {
        if (uidChecker->checkUid(readPicc)) {
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
   UidCheckerInterface* uidChecker;
   AbstractPiccUidFactory* uidReader;
};
