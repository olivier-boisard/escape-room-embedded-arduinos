#include <EEPROM.h>

void setup() {
  MFRC522::Uid validUid{0};
  int uidAddress = 0;
  size_t uidSize = EEPROM[uidAddress];
  for (size_t i = 0 ; i < uidSize ; i++) {
    validUid.uidByte[i] = EEPROM[uidAddress + i + 1];
  }
  piccProcessor.setValidUid(validUid);
  
  mfrc522.PCD_Init();
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  pinMode(SWITCH_INPUT_PIN, INPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(BLUE_LED_PIN, LOW);
}
