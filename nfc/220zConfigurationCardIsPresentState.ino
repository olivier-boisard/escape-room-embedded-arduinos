class ConfigurationCardIsPresentState : public CallbackStackMixin<PiccReaderStatus> {
  public:
    ConfigurationCardIsPresentState(const function<bool()>& isCardPresent)
      : isCardPresent(isCardPresent) {}
  
    State operator()() {
      State newState = State::configurationCardIsPresent;
      if (!isCardPresent()) {
        newState = State::configurationNoCard;
        callCallbacks(noPicc);
      }
      return newState;
    }

  private:
    function<bool()> isCardPresent;
};
