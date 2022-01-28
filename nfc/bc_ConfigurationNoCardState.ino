#define MAX_N_CALLBACKS  8

class ConfigurationNoCardState : public StateInterface {
  public:
    ConfigurationNoCardState(const MFRC522* mfrc522) : mfrc522(mfrc522) {}
    State run() {
      State newState = State::configurationNoCard;
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      if (tryReadCardSerial(*mfrc522)) {
        for (size_t i = 0 ; i < nObservers ; i++) {
          observers[i]->run(mfrc522->uid);
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
    MFRC522* mfrc522;
    NewUidObserverInterface* observers[MAX_N_CALLBACKS];
    size_t nObservers = 0;
};
