class NoCardState : public StateFunction, public NiladicVoidFunctionCaller {
  public:
    NoCardState(const PiccUidFactory* uidReader, const UidChecker* uidChecker)
      : uidReader(uidReader), uidChecker(uidChecker) {}
  
    State run() override {
      State newState = State::noCard;
      digitalWrite(BLUE_LED_PIN, LOW);
      PiccUid readPicc;
      if (uidReader->generate(&readPicc)) {
        if (uidChecker->run(readPicc)) {
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(RED_LED_PIN, LOW);
          callCallbacks();
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
   PiccUidFactory* uidReader;
};
