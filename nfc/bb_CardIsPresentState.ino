class CardIsPresentState : public StateInterface {
  public:
  
    CardIsPresentState(const CardPresenceChecker* cardPresenceChecker)
      : cardPresenceChecker(cardPresenceChecker) {}

    State run() {
      State newState = State::cardIsPresent;
      digitalWrite(BLUE_LED_PIN, LOW);
      if (!cardPresenceChecker->cardIsPresent()) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        newState = State::noCard;
      }
      return newState;
    }

  private:
    CardPresenceChecker* cardPresenceChecker;
};
