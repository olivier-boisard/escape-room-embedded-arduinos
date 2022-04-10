class PiccIsPresentState : public CallbackStackMixin<PiccReaderStatus> {
  public:
  
    PiccIsPresentState(const function<bool()>& isPiccPresent)
      : isPiccPresent(isPiccPresent) {}

    State operator()() {
      State newState = State::piccIsPresent;
      if (!isPiccPresent()) {
        newState = State::noPicc;
        callCallbacks(PiccReaderStatus::noPicc);
      }
      return newState;
    }

  private:
    function<bool()> isPiccPresent;
};
