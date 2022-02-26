void setup() {
  // Start serial
  Serial.begin(9600);
  
  // Configuring PICC reader 1
  PiccUid mfrc522Board1ValidUid;
  if (mfrc522Board1ReadUidFromEeprom(&mfrc522Board1ValidUid)) {
    mfrc522Board1UidChecker.setExpectedUid(mfrc522Board1ValidUid);
  } else {
    //TODO raise error somehow
  }
  mfrc522Board1ConfigurationNoCardState.addNewUidCallback(mfrc522Board1UpdateUidChecker);
  mfrc522Board1ConfigurationNoCardState.addNewUidCallback(mfrc522Board1WriteUid);
  mfrc522Board1StateMachine.addStateFunction(State::noCard, mfrc522Board1NoCardState);
  mfrc522Board1StateMachine.addStateFunction(State::cardIsPresent, mfrc522Board1CardIsPresentState);
  mfrc522Board1StateMachine.addStateFunction(State::configurationNoCard, mfrc522Board1ConfigurationNoCardState);
  mfrc522Board1StateMachine.addStateFunction(State::configurationCardIsPresent, mfrc522Board1ConfigurationCardIsPresentState);
  mfrc522Board1StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board1NoCardState.addCallback(controlMagnetWithPicc);
  mfrc522Board1ConfigurationNoCardState.addNewPiccReaderStatusCallback(setPiccReaderZeroState);
  mfrc522Board1NoCardState.addCallback(setPiccReaderZeroState);
  mfrc522Board1CardIsPresentState.addCallback(setPiccReaderZeroState);
  mfrc522Board1ConfigurationCardIsPresentState.addCallback(setPiccReaderZeroState);
  mfrc522Board1Mfrc522.PCD_Init();

  // Set pin modes
  pinMode(MAGNET_CONTROL_OUTPUT_PIN, OUTPUT);

  // Initialize pin values
  digitalWrite(MAGNET_CONTROL_OUTPUT_PIN, LOW);
}
