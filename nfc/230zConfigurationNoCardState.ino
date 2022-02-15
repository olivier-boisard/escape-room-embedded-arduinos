class ConfigurationNoCardState : public StateFunction, public UidObservable {
  public:
    ConfigurationNoCardState(const function<bool(PiccUid*)>& readUid) : readUid(readUid) {}
    
    State run() override {
      State newState = State::configurationNoCard;
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      PiccUid uid;
      if (readUid(&uid)) {
        notifyObservers(uid);
        newState = State::configurationCardIsPresent;
      }
      return newState;
   }

  private:
    function<bool(PiccUid*)> readUid;
};
