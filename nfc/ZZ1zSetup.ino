void setup() {
  // Start serial
  Serial.begin(SERIAL_PORT_BAUDRATE);
  
  // Configuring PICC reader 0
  PiccUid mfrc522Board0ValidUid;
  if (mfrc522Board0ReadUidFromEeprom(&mfrc522Board0ValidUid)) {
    mfrc522Board0UidChecker.setExpectedUid(mfrc522Board0ValidUid);
  } else {
    //TODO raise error somehow
  }
  mfrc522Board0ConfigurationNoCardState.addNewUidCallback(mfrc522Board0UpdateUidChecker);
  mfrc522Board0ConfigurationNoCardState.addNewUidCallback(mfrc522Board0WriteUid);
  mfrc522Board0StateMachine.addStateFunction(State::noCard, mfrc522Board0NoCardState);
  mfrc522Board0StateMachine.addStateFunction(State::cardIsPresent, mfrc522Board0CardIsPresentState);
  mfrc522Board0StateMachine.addStateFunction(State::configurationNoCard, mfrc522Board0ConfigurationNoCardState);
  mfrc522Board0StateMachine.addStateFunction(State::configurationCardIsPresent, mfrc522Board0ConfigurationCardIsPresentState);
  mfrc522Board0StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board0NoCardState.addCallback(mfrc522Board0HandleStatus);
  mfrc522Board0ConfigurationNoCardState.addNewPiccReaderStatusCallback(mfrc522Board0HandleStatus);
  mfrc522Board0CardIsPresentState.addCallback(mfrc522Board0HandleStatus);
  mfrc522Board0ConfigurationCardIsPresentState.addCallback(mfrc522Board0HandleStatus);
  mfrc522Board0Mfrc522.PCD_Init();

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
  mfrc522Board1NoCardState.addCallback(mfrc522Board1HandleStatus);
  mfrc522Board1ConfigurationNoCardState.addNewPiccReaderStatusCallback(mfrc522Board1HandleStatus);
  mfrc522Board1CardIsPresentState.addCallback(mfrc522Board1HandleStatus);
  mfrc522Board1ConfigurationCardIsPresentState.addCallback(mfrc522Board1HandleStatus);
  mfrc522Board1Mfrc522.PCD_Init();

  // Magnet control
  piccReaderStatusMonitor.addCallback(controlMagnet);
}
