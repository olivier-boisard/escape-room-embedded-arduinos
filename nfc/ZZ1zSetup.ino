void setup() {
  // Start serial
  Serial.begin(9600);
  
  // Set expected UID
  PiccUid validUid;
  if (readUidFromEeprom(&validUid)) {
    uidChecker.setExpectedUid(validUid);
  } else {
    //TODO raise error somehow
  }

  // Wiring: connecting to PICC reader 0
  configurationNoCardState.addNewUidCallback(updateUidChecker);
  configurationNoCardState.addNewUidCallback(writeUid);
  stateMachine.addStateFunction(State::noCard, noCardState);
  stateMachine.addStateFunction(State::cardIsPresent, cardIsPresentState);
  stateMachine.addStateFunction(State::configurationNoCard, configurationNoCardState);
  stateMachine.addStateFunction(State::configurationCardIsPresent, configurationCardIsPresentState);
  stateMachine.addCallback(sendStatusRequestCommandWrapper);
  noCardState.addCallback(controlMagnetWithPicc);
  configurationNoCardState.addNewPiccReaderStatusCallback(setPiccReaderZeroState);
  noCardState.addCallback(setPiccReaderZeroState);
  cardIsPresentState.addCallback(setPiccReaderZeroState);
  configurationCardIsPresentState.addCallback(setPiccReaderZeroState);

  // Initialize MFRC522 driver
  mfrc522.PCD_Init();

  // Set pin modes
  pinMode(MAGNET_CONTROL_OUTPUT_PIN, OUTPUT);

  // Initialize pin values
  digitalWrite(MAGNET_CONTROL_OUTPUT_PIN, LOW);
}
