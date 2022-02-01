class CardIsPresentState : public StateInterface {
  public:
  
    CardIsPresentState(const AbstractPiccUidFactory* cardPresenceChecker)
      : cardPresenceChecker(cardPresenceChecker) {}

    State run() override {
      State newState = State::cardIsPresent;
      digitalWrite(BLUE_LED_PIN, LOW);
      if (!cardPresenceChecker->uidIsReadable()) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        newState = State::noCard;
      }
      return newState;
    }

  private:
    AbstractPiccUidFactory* cardPresenceChecker;
};
