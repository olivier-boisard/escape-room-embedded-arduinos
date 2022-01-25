typedef enum {
  noCard,
  cardIsPresent,
  configurationNoCard,
  configurationCardIsPresent
} State;

class StateMachine {
  public:
    StateMachine(MFRC522& mfrc522) : mfrc522(mfrc522) {}

    void initialize() {
      MFRC522::Uid validUid{0};
      if (uidReader == 0) {
        //TODO raise error somehow
        return;
      }
      uidReader->read(&validUid);
      setExpectedUid(validUid);
    }

    void process() {
      switch (state) {
        case State::noCard:
          processNoCardState();
          break;
       case State::cardIsPresent:
          processCardIsPresentState();
          break;
       case State::configurationNoCard:
          processConfigurationNoCard();
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
    

    void processNoCardState() {
      digitalWrite(BLUE_LED_PIN, LOW);
      if (tryReadCardSerial(mfrc522)) {
        if (uidChecker.checkUid(mfrc522.uid)) {
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(RED_LED_PIN, LOW);
        } else {
          digitalWrite(GREEN_LED_PIN, LOW);
          digitalWrite(RED_LED_PIN, HIGH);
        }
        state = State::cardIsPresent;
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

   void processCardIsPresentState() {
      digitalWrite(BLUE_LED_PIN, LOW);
      if (!checkCardIsPresent()) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        state = State::noCard;
      }
   }

  void processConfigurationNoCard() {
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    if (tryReadCardSerial(mfrc522)) {
      MFRC522::Uid& uid = mfrc522.uid;
      setExpectedUid(uid);
      if (uidWriter == 0) {
        //TODO raise error somehow
        return;
      }
      uidWriter->write(uid);
      state = State::configurationCardIsPresent;
    }
  }

  void processConfigurationCardIsPresentState() {
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      if (!checkCardIsPresent()) {
        state = State::configurationNoCard;
      }
  }

  void setExpectedUid(const MFRC522::Uid& expectedUid) {
    uidChecker.setExpectedUid(expectedUid);
  }
};
