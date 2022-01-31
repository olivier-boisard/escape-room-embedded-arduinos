class ConfigurationNoCardState : public StateInterface {
  public:
    ConfigurationNoCardState(const AbstractPiccUidFactory* uidReader) : uidReader(uidReader) {}
    State run() {
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

   void addNewUidObserver(const NewUidObserverInterface* callback) {
      if (nObservers == MAX_N_CALLBACKS) {// TODO raise error somehow
        return;
      }
      observers[nObservers++] = callback;
   }

  private:
    constexpr static size_t MAX_N_CALLBACKS = 8;
    AbstractPiccUidFactory* uidReader;
    NewUidObserverInterface* observers[MAX_N_CALLBACKS];
    size_t nObservers = 0;
};
