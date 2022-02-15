class CardIsPresentState : public StateFunction {
  public:
  
    CardIsPresentState(const NiladicBoolFunction* cardPresenceChecker)
      : cardPresenceChecker(cardPresenceChecker) {}

    State run() override {
      State newState = State::cardIsPresent;
      digitalWrite(BLUE_LED_PIN, LOW);
      if (!cardPresenceChecker->run()) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        newState = State::noCard;
      }
      return newState;
    }

  private:
    NiladicBoolFunction* cardPresenceChecker;
};
