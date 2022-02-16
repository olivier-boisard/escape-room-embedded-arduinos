class NoCardState : public StateFunction, public CallbackStackMixin<> {
  public:
    NoCardState(const function<bool(PiccUid*)>& readUid, const UidChecker* uidChecker)
      : readUid(readUid), uidChecker(uidChecker) {}
  
    State run() override {
      State newState = State::noCard;
      digitalWrite(BLUE_LED_PIN, LOW);
      PiccUid uid;
      if (readUid(&uid)) {
        if (uidChecker->run(uid)) {
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
   function<bool(PiccUid*)> readUid;
};
