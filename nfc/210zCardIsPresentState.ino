class CardIsPresentState : public StateFunction {
  public:
  
    CardIsPresentState(const function<bool()>& isCardPresent) : isCardPresent(isCardPresent) {}

    State run() override {
      State newState = State::cardIsPresent;
      digitalWrite(BLUE_LED_PIN, LOW);
      if (!isCardPresent()) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        newState = State::noCard;
      }
      return newState;
    }

  private:
    function<bool()> isCardPresent;
};
