class ConfigurationNoCardState : private CallbackStackMixin<const PiccUid&>, private CallbackStackMixin<PiccReaderStatus> {
  public:
    ConfigurationNoCardState(const function<bool(PiccUid*)>& readUid) : readUid(readUid) {}
    
    State operator()() {
      State newState = State::configurationNoCard;
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      PiccUid uid;
      if (readUid(&uid)) {
        CallbackStackMixin<const PiccUid&>::callCallbacks(uid);
        newState = State::configurationCardIsPresent;
        CallbackStackMixin<PiccReaderStatus>::callCallbacks(PiccReaderStatus::newPicc);
      }
      return newState;
   }

   void addNewUidCallback(const function<void(const PiccUid& uid)>& callback) {
      CallbackStackMixin<const PiccUid&>::addCallback(callback);
   }

   void addNewPiccReaderStatusCallback(const function<void(PiccReaderStatus)>& callback) {
      CallbackStackMixin<PiccReaderStatus>::addCallback(callback);
   }

  private:
    function<bool(PiccUid*)> readUid;
};
