class ConfigurationCardIsPresentState : public StateFunction {
  public:
    ConfigurationCardIsPresentState(const function<bool()>& isCardPresent)
      : isCardPresent(isCardPresent) {}
  
    State run() override {
      State newState = State::configurationCardIsPresent;
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      if (!isCardPresent()) {
        newState = State::configurationNoCard;
      }
      return newState;
    }

  private:
    function<bool()> isCardPresent;
};
