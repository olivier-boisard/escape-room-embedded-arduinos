class StateMachine {
  public:
    StateMachine(
      const NoCardState* noCardState,
      const CardIsPresentState* cardIsPresentState,
      const ConfigurationNoCardState* configurationNoCardState,
      const ConfigurationCardIsPresentState* configurationCardIsPresentState
    ) : noCardState(noCardState),
        cardIsPresentState(cardIsPresentState),
        configurationNoCardState(configurationNoCardState),
        configurationCardIsPresentState(configurationCardIsPresentState) {}

    void process() {
      switch (state) {
        case State::noCard:
          state = noCardState->run();
          break;
       case State::cardIsPresent:
          state = cardIsPresentState->run();
          break;
       case State::configurationNoCard:
          state = configurationNoCardState->run();
          break;
       case State::configurationCardIsPresent:
          state = configurationCardIsPresentState->run();
          break;
       default:
          break;
      }
    }

    void toggleConfigurationMode() {
      state = state != State::configurationNoCard ? State::configurationNoCard : State::noCard;
    }
  
  private:
    State state = State::noCard;
    NoCardState* noCardState;    
    CardIsPresentState* cardIsPresentState;
    ConfigurationNoCardState* configurationNoCardState;
    ConfigurationCardIsPresentState* configurationCardIsPresentState;
};
