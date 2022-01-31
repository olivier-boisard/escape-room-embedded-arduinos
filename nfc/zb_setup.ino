#include <EEPROM.h>

void setup() {
  PiccUid validUid;
  if (uidFromEepromReader.generate(&validUid)) {
    uidChecker.setExpectedUid(validUid);
  } else {
    //TODO raise error somehow
  }
  
  configurationNoCardState.addNewUidObserver(&expectedUidUpdater);
  configurationNoCardState.addNewUidObserver(&uidWriterWrapper);

  mfrc522.PCD_Init();
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  pinMode(SWITCH_INPUT_PIN, INPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(BLUE_LED_PIN, LOW);
}
