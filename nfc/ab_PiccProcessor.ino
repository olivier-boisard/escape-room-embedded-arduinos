typedef enum {
  noCard,
  cardIsPresent
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
       default:
          break;
      }
    }
  
  private:
    MFRC522& mfrc522;
    UidChecker uidChecker;
    State state = State::noCard;

    void processNoCardState() {
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
