class NoCardState : public StateFunction, public CallbackStackMixin<> {
  public:
    NoCardState(const function<bool(PiccUid*)>& readUid, const function<bool(const PiccUid& uid)>& checkUid)
      : readUid(readUid), checkUid(checkUid) {}
  
    State run() override {
      State newState = State::noCard;
      digitalWrite(BLUE_LED_PIN, LOW);
      PiccUid uid;
      if (readUid(&uid)) {
        if (checkUid(uid)) {
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
   function<bool(PiccUid*)> readUid;
   function<bool(const PiccUid& uid)> checkUid;
};
