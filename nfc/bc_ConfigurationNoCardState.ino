class ConfigurationNoCardState : public StateFunction {
  public:
    ConfigurationNoCardState(const PiccUidFactory* uidReader) : uidReader(uidReader) {}
    
    State run() override {
      State newState = State::configurationNoCard;
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      PiccUid readUid;
      if (uidReader->generate(&readUid)) {
        for (size_t i = 0 ; i < nObservers ; i++) {
          observers[i]->update(readUid);
        }
        newState = State::configurationCardIsPresent;
      }
      return newState;
   }

   void addUidObserver(const UidObserver* callback) {
      if (nObservers == MAX_N_CALLBACKS) {// TODO raise error somehow
        return;
      }
      observers[nObservers++] = callback;
   }

  private:
    constexpr static size_t MAX_N_CALLBACKS = 8;
    PiccUidFactory* uidReader;
    UidObserver* observers[MAX_N_CALLBACKS];
    size_t nObservers = 0;
};
