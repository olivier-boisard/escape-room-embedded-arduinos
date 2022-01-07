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

#define SS_PIN 10
#define GREEN_LED_PIN 9
#define RED_LED_PIN 8

#define LOOP_DELAY_MS 100
#define BUFFER_SIZE 8

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

void setup() {
  mfrc522.PCD_Init();
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
  byte expectedValue[] = {0x04, 0xCE, 0x89, 0xCA, 0x27, 0x73, 0x80};
  for (size_t i = 0 ; i < expectedSize ; i++) {
    if (uid.uidByte[i] != expectedValue[i]) {
      output = false;
      break;
    }
  }
  return output;
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    //digitalWrite(GREEN_LED_PIN, LOW);
    //digitalWrite(RED_LED_PIN, LOW);
  } else if (uidIsValid(mfrc522.uid)) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  } else {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }
  
  delay(LOOP_DELAY_MS);
}
