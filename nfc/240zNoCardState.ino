class NoCardState : public CallbackStackMixin<PiccReaderStatus> {
  public:
    NoCardState(const function<bool(PiccUid*)>& readUid, const function<bool(const PiccUid& uid)>& checkUid)
      : readUid(readUid), checkUid(checkUid) {}
  
    State operator()() {
      State newState = State::noCard;
      //digitalWrite(BLUE_LED_PIN, LOW);
      PiccUid uid;
      PiccReaderStatus piccReaderSatus = noPicc;
      if (readUid(&uid)) {
        if (checkUid(uid)) {
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(RED_LED_PIN, LOW);
          piccReaderSatus = correctPicc;
        } else {
          digitalWrite(GREEN_LED_PIN, LOW);
          digitalWrite(RED_LED_PIN, HIGH);
          piccReaderSatus = wrongPicc;
        }
        newState = State::cardIsPresent;
      }
      callCallbacks(piccReaderSatus);
      return newState;
   }

  private:
   function<bool(PiccUid*)> readUid;
   function<bool(const PiccUid& uid)> checkUid;
};
