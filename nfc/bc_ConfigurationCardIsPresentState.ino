class ConfigurationCardIsPresentState : public StateInterface {
  public:
    ConfigurationCardIsPresentState(const AbstractPiccUidFactory* cardPresenceChecker)
      : cardPresenceChecker(cardPresenceChecker) {}
  
    State run() override {
      State newState = State::configurationCardIsPresent;
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      if (!cardPresenceChecker->uidIsReadable()) {
        newState = State::configurationNoCard;
      }
      return newState;
    }

  private:
    AbstractPiccUidFactory* cardPresenceChecker;
};
