class StateMachine : public NiladicVoidFunction {
  public:
    StateMachine() {
      for (size_t i = 0 ; i < MAX_N_STATE_FUNCTIONS ; i++) {
        states[i] = 0;
      }
    }

    void addStateFunction(State state, const StateFunction* stateFunction) {
      states[state] = stateFunction;
    }

    void process() {
      StateFunction* stateFunction = states[state];
      if (stateFunction != 0) {
        state = stateFunction->run();
      } else {
        //TODO raise error somehow
      }
    }

    void run() override {
      toggleConfigurationMode();
    }
  
  private:
    State state = State::noCard;
    const static size_t MAX_N_STATE_FUNCTIONS = 16;
    StateFunction* states[MAX_N_STATE_FUNCTIONS];

    void toggleConfigurationMode() {
      state = state != State::configurationNoCard ? State::configurationNoCard : State::noCard;
    }
};
