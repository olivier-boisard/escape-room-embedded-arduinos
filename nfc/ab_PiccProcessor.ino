#include <EEPROM.h>

typedef enum {
  noCard,
  cardIsPresent,
  configurationNoCard,
  configurationCardIsPresent
} State;

class PiccProcessor {
  public:
    PiccProcessor(MFRC522& mfrc522, int eepromSaveAddress) :
          mfrc522(mfrc522), eepromSaveAddress(eepromSaveAddress) {}

    void initialize() {
      MFRC522::Uid validUid{0};
      int uidAddress = 0;
      size_t uidSize = EEPROM.read(uidAddress);
      Serial.println(uidSize);
      for (size_t i = 0 ; i < uidSize ; i++) {
        validUid.uidByte[i] = EEPROM.read(uidAddress + i + 1);
        Serial.println(validUid.uidByte[i]);
      }
      Serial.println("OK");
      setValidUid(validUid);
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
          //TODO update uid and write it in EEPROM
          digitalWrite(BLUE_LED_PIN, HIGH);
          digitalWrite(GREEN_LED_PIN, LOW);
          if (tryReadCardSerial(mfrc522)) {
            setValidUid(mfrc522.uid);
            MFRC522::Uid& uid = mfrc522.uid;
            int uidSize = uid.size;
            Serial.println("UID SIZE");
            Serial.println(uidSize);
            EEPROM.update(eepromSaveAddress, uidSize);
            for (int i = 0 ; i < uidSize ; i++) {
              EEPROM.update(eepromSaveAddress + i + 1, uid.uidByte[i]);
              Serial.println(uid.uidByte[i]);
            }
            state = State::configurationCardIsPresent;
          }
          break;
       case State::configurationCardIsPresent:
          processConfigurationCardIsPresentState();
          break;
       default:
          break;
      }
    }

    void setValidUid(const MFRC522::Uid& uid) {
      uidChecker.setExpectedUid(uid);
    }

    void toggleConfigurationMode() {
      state = state != State::configurationNoCard ? State::configurationNoCard : State::noCard;
    }
  
  private:
    MFRC522& mfrc522;
    UidChecker uidChecker;
    State state = State::noCard;
    int eepromSaveAddress;

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

   void processConfigurationCardIsPresentState() {
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      if (!checkCardIsPresent()) {
        state = State::configurationNoCard;
      }
   }

   
};
