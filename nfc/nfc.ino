/*
 * Pin layout
 * 
 * -------------------------------------
 * MFRC522      Arduino     
 * Reader/PCD   Uno/101     
 * Pin          Pin         
 * -------------------------------------
 * SDA(SS)      10          
 * MOSI         11
 * MISO         12
 * SCK          13
 * 
 * -------------------------------------
 * LED's          Arduino Uno/101 Pin
 * -------------------------------------
 * Green        9
 * Red          8
 */

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <MFRC522Constants.h>

#define SS_PIN 10
#define GREEN_LED_PIN 9
#define RED_LED_PIN 8

#define LOOP_DELAY_MS 100
#define BUFFER_SIZE 8

#define ATQA_BUFFER_SIZE 2

#define N_ABSENCE_CHECKS 10

MFRC522DriverPinSimple ss_pin = MFRC522DriverPinSimple(SS_PIN);
MFRC522DriverSPI driver = MFRC522DriverSPI{
  ss_pin,
  SPI,
  SPISettings(
    SPI_CLOCK_DIV4,
    MSBFIRST,
    SPI_MODE0
  )
};

MFRC522 mfrc522{driver};

typedef enum {
  noCard,
  cardIsPresent
} State;

void setup() {
  Serial.begin(115200);
  mfrc522.PCD_Init();
  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

bool uidIsValid(const MFRC522::Uid& uid) {
  size_t expectedSize = 7;
  if (uid.size != expectedSize) {
    return false;
  }

  bool output = true;
  static const byte expectedValue[] = {0x04, 0xCE, 0x89, 0xCA, 0x27, 0x73, 0x80};
  for (size_t i = 0 ; i < expectedSize ; i++) {
    if (uid.uidByte[i] != expectedValue[i]) {
      output = false;
      break;
    }
  }
  return output;
}

void loop() {
  // check this https://highvoltages.co/tutorial/arduino-tutorial/arduino-mfrc522-tutorial-is-rfid-tag-present-or-removed/

  static State state = State::noCard;
  static bool cardIsPresentFlag = false;
  static byte bufferATQA[ATQA_BUFFER_SIZE];
  static byte bufferSize = ATQA_BUFFER_SIZE;
  static MFRC522Constants::StatusCode status;
  switch (state) {
    case State::noCard:
      if (mfrc522.PICC_IsNewCardPresent() || mfrc522.PICC_ReadCardSerial()) {
        MFRC522Debug::PICC_DumpToSerial(mfrc522, Serial, &(mfrc522.uid));
        if (uidIsValid(mfrc522.uid)) {
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(RED_LED_PIN, LOW);
        } else {
          digitalWrite(GREEN_LED_PIN, LOW);
          digitalWrite(RED_LED_PIN, HIGH);
        }
        state = State::cardIsPresent;
      }
      Serial.println("State 1");
      break;
   case State::cardIsPresent:
      status = mfrc522.PICC_WakeupA(bufferATQA, &bufferSize);
      if (status != MFRC522Constants::StatusCode::STATUS_OK) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        state = State::noCard;
        Serial.println("State 2");
      }
      break;
   default:
      break;
  }
  
  delay(LOOP_DELAY_MS);
}
