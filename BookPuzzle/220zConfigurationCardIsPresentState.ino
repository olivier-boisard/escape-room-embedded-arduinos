class ConfigurationPiccIsPresentState : public CallbackStackMixin<PiccReaderStatus> {
  public:
    ConfigurationPiccIsPresentState(const function<bool()>& isPiccPresent)
      : isPiccPresent(isPiccPresent) {}
  
    State operator()() {
      State newState = State::configurationPiccIsPresent;
      if (!isPiccPresent()) {
        newState = State::configurationNoPicc;
        callCallbacks(PiccReaderStatus::noPicc);
      }
      return newState;
    }

  private:
    function<bool()> isPiccPresent;
};
