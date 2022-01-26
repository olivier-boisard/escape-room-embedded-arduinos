class StateMachine {
  public:
    StateMachine(MFRC522& mfrc522)
      : mfrc522(mfrc522),
        noCardState(&mfrc522),
        cardIsPresentState(&mfrc522),
        configurationNoCardState(&mfrc522) {}

    void initialize() {
      MFRC522::Uid validUid{0};
      if (uidReader == 0) {
        //TODO raise error somehow
        return;
      }
      uidReader->read(&validUid);
      noCardState.setExpectedUid(validUid);
    }

    void process() {
      switch (state) {
        case State::noCard:
          state = noCardState.run();
          break;
       case State::cardIsPresent:
          state = cardIsPresentState.run();
          break;
       case State::configurationNoCard:
          state = configurationNoCardState.run();
          break;
       case State::configurationCardIsPresent:
          processConfigurationCardIsPresentState();
          break;
       default:
          break;
      }
    }

    void setUidReader(UidReaderInterface* uidReader) {
      this->uidReader = uidReader;
    }

    void setUidWriter(UidWriterInterface* uidWriter) {
      this->uidWriter = uidWriter;
    }

    void toggleConfigurationMode() {
      state = state != State::configurationNoCard ? State::configurationNoCard : State::noCard;
    }
  
  private:
    MFRC522& mfrc522;
    UidChecker uidChecker;
    State state = State::noCard;
    UidReaderInterface* uidReader = 0;
    UidWriterInterface* uidWriter = 0;
    NoCardState noCardState;    
    CardIsPresentState cardIsPresentState;
    ConfigurationNoCardState configurationNoCardState;
  
    void processConfigurationCardIsPresentState() {
        digitalWrite(BLUE_LED_PIN, HIGH);
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);
        if (!checkCardIsPresent()) {
          state = State::configurationNoCard;
        }
    }

    bool checkCardIsPresent() {
      bool cardIsPresentFlag = false;
      for (int i = 0 ; i < N_ABSENCE_CHECKS ; i++) {
        if (tryReadCardSerial(mfrc522)) {
          cardIsPresentFlag = true;
          break;
        }
      }
      return cardIsPresentFlag;
   }
};
