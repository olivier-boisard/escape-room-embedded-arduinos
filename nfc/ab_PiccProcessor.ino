typedef enum {
  noCard,
  cardIsPresent,
  configuration
} State;

class PiccProcessor {
  public:
    PiccProcessor(MFRC522& mfrc522, const MFRC522::Uid& uid)
      : mfrc522(mfrc522), uidChecker(uid) {}

    void process() {
      switch (state) {
        case State::noCard:
          processNoCardState();
          break;
       case State::cardIsPresent:
          processCardIsPresentState();
          break;
       case State::configuration:
          digitalWrite(BLUE_LED_PIN, HIGH);
          break;
       default:
          break;
      }
    }

    void toggleConfigurationMode() {
      state = state != State::configuration ? State::configuration : State::noCard;
    }
  
  private:
    MFRC522& mfrc522;
    UidChecker uidChecker;
    State state = State::noCard;

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

   void processCardIsPresentState() {
      digitalWrite(BLUE_LED_PIN, LOW);
      bool cardIsPresentFlag = false;
      for (int i = 0 ; i < N_ABSENCE_CHECKS ; i++) {
        if (tryReadCardSerial(mfrc522)) {
          cardIsPresentFlag = true;
          break;
        }
      }
      if (!cardIsPresentFlag) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        state = State::noCard;
      }
   }
};
