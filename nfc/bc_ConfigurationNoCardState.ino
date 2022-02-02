class ConfigurationNoCardState : public StateFunction, public UidObservable {
  public:
    ConfigurationNoCardState(const PiccUidFactory* uidReader) : uidReader(uidReader) {}
    
    State run() override {
      State newState = State::configurationNoCard;
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      PiccUid readUid;
      if (uidReader->generate(&readUid)) {
        notifyObservers(readUid);
        newState = State::configurationCardIsPresent;
      }
      return newState;
   }

  private:
    PiccUidFactory* uidReader;
};
