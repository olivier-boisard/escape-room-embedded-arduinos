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

  // Configuring PICC reader 2
  PiccUid mfrc522Board2ValidUid;
  if (mfrc522Board2ReadUidFromEeprom(&mfrc522Board2ValidUid)) {
    mfrc522Board2UidChecker.setExpectedUid(mfrc522Board2ValidUid);
  } else {
    //TODO raise error somehow
  }
  mfrc522Board2ConfigurationNoCardState.addNewUidCallback(mfrc522Board2UpdateUidChecker);
  mfrc522Board2ConfigurationNoCardState.addNewUidCallback(mfrc522Board2WriteUid);
  mfrc522Board2StateMachine.addStateFunction(State::noCard, mfrc522Board2NoCardState);
  mfrc522Board2StateMachine.addStateFunction(State::cardIsPresent, mfrc522Board2CardIsPresentState);
  mfrc522Board2StateMachine.addStateFunction(State::configurationNoCard, mfrc522Board2ConfigurationNoCardState);
  mfrc522Board2StateMachine.addStateFunction(State::configurationCardIsPresent, mfrc522Board2ConfigurationCardIsPresentState);
  mfrc522Board2StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board2NoCardState.addCallback(mfrc522Board2HandleStatus);
  mfrc522Board2ConfigurationNoCardState.addNewPiccReaderStatusCallback(mfrc522Board2HandleStatus);
  mfrc522Board2CardIsPresentState.addCallback(mfrc522Board2HandleStatus);
  mfrc522Board2ConfigurationCardIsPresentState.addCallback(mfrc522Board2HandleStatus);
  mfrc522Board2Mfrc522.PCD_Init();

  // Configuring PICC reader 3
  PiccUid mfrc522Board3ValidUid;
  if (mfrc522Board3ReadUidFromEeprom(&mfrc522Board3ValidUid)) {
    mfrc522Board3UidChecker.setExpectedUid(mfrc522Board3ValidUid);
  } else {
    //TODO raise error somehow
  }
  mfrc522Board3ConfigurationNoCardState.addNewUidCallback(mfrc522Board3UpdateUidChecker);
  mfrc522Board3ConfigurationNoCardState.addNewUidCallback(mfrc522Board3WriteUid);
  mfrc522Board3StateMachine.addStateFunction(State::noCard, mfrc522Board3NoCardState);
  mfrc522Board3StateMachine.addStateFunction(State::cardIsPresent, mfrc522Board3CardIsPresentState);
  mfrc522Board3StateMachine.addStateFunction(State::configurationNoCard, mfrc522Board3ConfigurationNoCardState);
  mfrc522Board3StateMachine.addStateFunction(State::configurationCardIsPresent, mfrc522Board3ConfigurationCardIsPresentState);
  mfrc522Board3StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board3NoCardState.addCallback(mfrc522Board3HandleStatus);
  mfrc522Board3ConfigurationNoCardState.addNewPiccReaderStatusCallback(mfrc522Board3HandleStatus);
  mfrc522Board3CardIsPresentState.addCallback(mfrc522Board3HandleStatus);
  mfrc522Board3ConfigurationCardIsPresentState.addCallback(mfrc522Board3HandleStatus);
  mfrc522Board3Mfrc522.PCD_Init();

  // Configuring PICC reader 4
  PiccUid mfrc522Board4ValidUid;
  if (mfrc522Board4ReadUidFromEeprom(&mfrc522Board4ValidUid)) {
    mfrc522Board4UidChecker.setExpectedUid(mfrc522Board4ValidUid);
  } else {
    //TODO raise error somehow
  }
  mfrc522Board4ConfigurationNoCardState.addNewUidCallback(mfrc522Board4UpdateUidChecker);
  mfrc522Board4ConfigurationNoCardState.addNewUidCallback(mfrc522Board4WriteUid);
  mfrc522Board4StateMachine.addStateFunction(State::noCard, mfrc522Board4NoCardState);
  mfrc522Board4StateMachine.addStateFunction(State::cardIsPresent, mfrc522Board4CardIsPresentState);
  mfrc522Board4StateMachine.addStateFunction(State::configurationNoCard, mfrc522Board4ConfigurationNoCardState);
  mfrc522Board4StateMachine.addStateFunction(State::configurationCardIsPresent, mfrc522Board4ConfigurationCardIsPresentState);
  mfrc522Board4StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board4NoCardState.addCallback(mfrc522Board4HandleStatus);
  mfrc522Board4ConfigurationNoCardState.addNewPiccReaderStatusCallback(mfrc522Board4HandleStatus);
  mfrc522Board4CardIsPresentState.addCallback(mfrc522Board4HandleStatus);
  mfrc522Board4ConfigurationCardIsPresentState.addCallback(mfrc522Board4HandleStatus);
  mfrc522Board4Mfrc522.PCD_Init();

  // Magnet control
  piccReaderStatusMonitor.addCallback(controlMagnet);
}
