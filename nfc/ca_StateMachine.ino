class StateMachine {
  public:
    StateMachine(
      const UidChecker* uidChecker,
      const NoCardState* noCardState,
      const CardIsPresentState* cardIsPresentState,
      const ConfigurationNoCardState* configurationNoCardState,
      const ConfigurationCardIsPresentState* configurationCardIsPresentState
    ) : uidChecker(uidChecker),
        noCardState(noCardState),
        cardIsPresentState(cardIsPresentState),
        configurationNoCardState(configurationNoCardState),
        configurationCardIsPresentState(configurationCardIsPresentState) {}

    void initialize() {
      PiccUid validUid;
      if (!uidLoader->generate(&validUid)) {
        //TODO raise error somehow
        return;
      }
      uidChecker->setExpectedUid(validUid);
    }

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

    void setUidLoader(const AbstractPiccUidFactory* uidLoader) {
      this->uidLoader = uidLoader;
    }

    void setUidWriter(const NewUidObserverInterface* uidWriter) {
      this->uidWriter = uidWriter;
    }

    void toggleConfigurationMode() {
      state = state != State::configurationNoCard ? State::configurationNoCard : State::noCard;
    }
  
  private:
    State state = State::noCard;
    UidChecker* uidChecker;
    AbstractPiccUidFactory* uidLoader = 0;
    NewUidObserverInterface* uidWriter = 0;
    NoCardState* noCardState;    
    CardIsPresentState* cardIsPresentState;
    ConfigurationNoCardState* configurationNoCardState;
    ConfigurationCardIsPresentState* configurationCardIsPresentState;
};
