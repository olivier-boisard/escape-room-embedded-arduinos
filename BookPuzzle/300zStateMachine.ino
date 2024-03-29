class StateMachine : public CallbackStackMixin<State> {
  public:
  
    void addStateFunction(State state, const function<State()>& stateFunction) {
      stateFunctions[(int) state] = stateFunction;
      if (!isRegistered(state)) {
        registeredStates[nRegisteredStates++] = state;
      }
    }

    void process() {
      if (isRegistered(state)) {
        State newState = stateFunctions[(int) state]();
        updateState(newState);
      } else {
        //TODO manage error
      }
    }

    bool toggleConfigurationMode() {
      State newState = state != State::configurationNoPicc ? State::configurationNoPicc : State::noPicc;
      updateState(newState);
      return state == State::configurationNoPicc;
    }
    
  private:
    State state = State::noPicc;
    constexpr static size_t MAX_N_STATE_FUNCTIONS = 4;
    function<State()> stateFunctions[MAX_N_STATE_FUNCTIONS];
    State registeredStates[MAX_N_STATE_FUNCTIONS];
    size_t nRegisteredStates = 0;

    void updateState(State newState) {
      if (newState != state) {
        callCallbacks(newState);
      }
      state = newState;
    }

    bool isRegistered(State stateToCheck) const {
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
