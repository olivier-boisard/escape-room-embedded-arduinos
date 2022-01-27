#include <EEPROM.h>

void setup() {
  stateMachine.setUidReader(&uidReader);
  stateMachine.setUidWriter(&uidWriter);
  stateMachine.initialize();

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
