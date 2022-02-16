class StateMachine {
  public:
  
    void addStateFunction(State state, const function<State()>& stateFunction) {
      stateFunctions[state] = stateFunction;
      if (!isRegistered(state)) {
        registeredStates[nRegisteredStates++] = state;
      }
    }

    void process() {
      if (isRegistered(state)) {
        state = stateFunctions[state]();
      } else {
        //TODO manage error
      }
    }

    void toggleConfigurationMode() {
      state = state != State::configurationNoCard ? State::configurationNoCard : State::noCard;
    }
    
  private:
    State state = State::noCard;
    const static size_t MAX_N_STATE_FUNCTIONS = 16;
    function<State()> stateFunctions[MAX_N_STATE_FUNCTIONS];
    State registeredStates[MAX_N_STATE_FUNCTIONS];
    size_t nRegisteredStates = 0;

    bool isRegistered(State stateToCheck) {
      bool output = false;
      for (size_t i = 0 ; i < nRegisteredStates ; i++) {
        if (stateToCheck == registeredStates[i]) {
          output = true;
          break;
        }
      }
      return output;
    }
};
