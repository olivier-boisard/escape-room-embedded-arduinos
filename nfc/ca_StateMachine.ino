class StateMachine {
  public:
    StateMachine() {
      for (size_t i = 0 ; i < MAX_N_STATE_FUNCTIONS ; i++) {
        states[i] = 0;
      }
    }

    void addStateFunction(State state, const StateInterface* stateFunction) {
      states[state] = stateFunction;
    }

    void process() {
      StateInterface* stateFunction = states[state];
      if (stateFunction != 0) {
        state = stateFunction->run();
      } else {
        //TODO raise error somehow
      }
    }

    void toggleConfigurationMode() {
      state = state != State::configurationNoCard ? State::configurationNoCard : State::noCard;
    }
  
  private:
    State state = State::noCard;
    constexpr static size_t MAX_N_STATE_FUNCTIONS = 16;
    StateInterface* states[MAX_N_STATE_FUNCTIONS];
};
