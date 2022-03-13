class CardIsPresentState : public CallbackStackMixin<PiccReaderStatus> {
  public:
  
    CardIsPresentState(const function<bool()>& isCardPresent)
      : isCardPresent(isCardPresent) {}

    State operator()() {
      State newState = State::cardIsPresent;
      if (!isCardPresent()) {
        newState = State::noCard;
        callCallbacks(noPicc);
      }
      return newState;
    }

  private:
    function<bool()> isCardPresent;
};
