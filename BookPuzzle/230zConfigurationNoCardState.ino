class ConfigurationNoPiccState : private CallbackStackMixin<const PiccUid&>, private CallbackStackMixin<PiccReaderStatus> {
  public:
    ConfigurationNoPiccState(const function<bool(PiccUid*)>& readUid) : readUid(readUid) {}
    
    State operator()() {
      State newState = State::configurationNoPicc;
      PiccUid uid;
      if (readUid(&uid)) {
        CallbackStackMixin<const PiccUid&>::callCallbacks(uid);
        newState = State::configurationPiccIsPresent;
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
