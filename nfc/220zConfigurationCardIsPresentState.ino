class ConfigurationCardIsPresentState : public StateFunction {
  public:
    ConfigurationCardIsPresentState(const NiladicBoolFunction* cardPresenceChecker)
      : cardPresenceChecker(cardPresenceChecker) {}
  
    State run() override {
      State newState = State::configurationCardIsPresent;
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      if (!cardPresenceChecker->run()) {
        newState = State::configurationNoCard;
      }
      return newState;
    }

  private:
    NiladicBoolFunction* cardPresenceChecker;
};
