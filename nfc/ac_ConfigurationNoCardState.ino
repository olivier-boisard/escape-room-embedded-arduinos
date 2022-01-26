#define MAX_N_CALLBACKS  8

class NewUidCallbackInterface {
  public:
    virtual void run(const MFRC522::Uid& expectedUid) = 0;
  
    virtual ~NewUidCallbackInterface() {}
};

class ConfigurationNoCardState : public StateInterface {
  public:
    ConfigurationNoCardState(MFRC522* mfrc522) : mfrc522(mfrc522) {}
  
    State run() {
      State newState = State::configurationNoCard;
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      if (tryReadCardSerial(*mfrc522)) {
        for (size_t i = 0 ; i < nCallbacks ; i++) {
          callbacks[i]->run(mfrc522->uid);
        }
        newState = State::configurationCardIsPresent;
        // TODO Callback 1
        //noCardState.setExpectedUid(uid);

        // TODO Callback 2
        //if (uidWriter == 0) {
          //TODO raise error somehow
        //  return;
        //}
        //uidWriter->write(uid);
        //newState = State::configurationCardIsPresent;
      }
      return newState;
   }

   void addNewUidCallback(const NewUidCallbackInterface& callback) {
      if (nCallbacks == MAX_N_CALLBACKS) {// TODO raise error somehow
        return;
      }
      callbacks[nCallbacks++] = &callback;
   }

   void setExpectedUid(const MFRC522::Uid& expectedUid) {
      uidChecker.setExpectedUid(expectedUid);
   }

  private:
    UidChecker uidChecker;
    MFRC522* mfrc522;
    NewUidCallbackInterface* callbacks[MAX_N_CALLBACKS];
    size_t nCallbacks = 0;
};
