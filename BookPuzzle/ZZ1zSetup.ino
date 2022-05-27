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
  mfrc522Board0ConfigurationNoPiccState.addNewUidCallback(mfrc522Board0UpdateUidChecker);
  mfrc522Board0ConfigurationNoPiccState.addNewUidCallback(mfrc522Board0WriteUid);
  mfrc522Board0StateMachine.addStateFunction(State::noPicc, mfrc522Board0NoPiccState);
  mfrc522Board0StateMachine.addStateFunction(State::piccIsPresent, mfrc522Board0PiccIsPresentState);
  mfrc522Board0StateMachine.addStateFunction(State::configurationNoPicc, mfrc522Board0ConfigurationNoPiccState);
  mfrc522Board0StateMachine.addStateFunction(State::configurationPiccIsPresent, mfrc522Board0ConfigurationPiccIsPresentState);
  mfrc522Board0StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board0NoPiccState.addCallback(mfrc522Board0HandleStatus);
  mfrc522Board0ConfigurationNoPiccState.addNewPiccReaderStatusCallback(mfrc522Board0HandleStatus);
  mfrc522Board0PiccIsPresentState.addCallback(mfrc522Board0HandleStatus);
  mfrc522Board0ConfigurationPiccIsPresentState.addCallback(mfrc522Board0HandleStatus);
  mfrc522Board0Mfrc522.PCD_Init();
  mfrc522Board0Mfrc522.PCD_SetAntennaGain(MFRC522_ANTENNA_GAIN);

  // Configuring PICC reader 1
  PiccUid mfrc522Board1ValidUid;
  if (mfrc522Board1ReadUidFromEeprom(&mfrc522Board1ValidUid)) {
    mfrc522Board1UidChecker.setExpectedUid(mfrc522Board1ValidUid);
  } else {
    //TODO raise error somehow
  }
  mfrc522Board1ConfigurationNoPiccState.addNewUidCallback(mfrc522Board1UpdateUidChecker);
  mfrc522Board1ConfigurationNoPiccState.addNewUidCallback(mfrc522Board1WriteUid);
  mfrc522Board1StateMachine.addStateFunction(State::noPicc, mfrc522Board1NoPiccState);
  mfrc522Board1StateMachine.addStateFunction(State::piccIsPresent, mfrc522Board1PiccIsPresentState);
  mfrc522Board1StateMachine.addStateFunction(State::configurationNoPicc, mfrc522Board1ConfigurationNoPiccState);
  mfrc522Board1StateMachine.addStateFunction(State::configurationPiccIsPresent, mfrc522Board1ConfigurationPiccIsPresentState);
  mfrc522Board1StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board1NoPiccState.addCallback(mfrc522Board1HandleStatus);
  mfrc522Board1ConfigurationNoPiccState.addNewPiccReaderStatusCallback(mfrc522Board1HandleStatus);
  mfrc522Board1PiccIsPresentState.addCallback(mfrc522Board1HandleStatus);
  mfrc522Board1ConfigurationPiccIsPresentState.addCallback(mfrc522Board1HandleStatus);
  mfrc522Board1Mfrc522.PCD_Init();
  mfrc522Board1Mfrc522.PCD_SetAntennaGain(MFRC522_ANTENNA_GAIN);

  // Configuring PICC reader 2
  PiccUid mfrc522Board2ValidUid;
  if (mfrc522Board2ReadUidFromEeprom(&mfrc522Board2ValidUid)) {
    mfrc522Board2UidChecker.setExpectedUid(mfrc522Board2ValidUid);
  } else {
    //TODO raise error somehow
  }
  mfrc522Board2ConfigurationNoPiccState.addNewUidCallback(mfrc522Board2UpdateUidChecker);
  mfrc522Board2ConfigurationNoPiccState.addNewUidCallback(mfrc522Board2WriteUid);
  mfrc522Board2StateMachine.addStateFunction(State::noPicc, mfrc522Board2NoPiccState);
  mfrc522Board2StateMachine.addStateFunction(State::piccIsPresent, mfrc522Board2PiccIsPresentState);
  mfrc522Board2StateMachine.addStateFunction(State::configurationNoPicc, mfrc522Board2ConfigurationNoPiccState);
  mfrc522Board2StateMachine.addStateFunction(State::configurationPiccIsPresent, mfrc522Board2ConfigurationPiccIsPresentState);
  mfrc522Board2StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board2NoPiccState.addCallback(mfrc522Board2HandleStatus);
  mfrc522Board2ConfigurationNoPiccState.addNewPiccReaderStatusCallback(mfrc522Board2HandleStatus);
  mfrc522Board2PiccIsPresentState.addCallback(mfrc522Board2HandleStatus);
  mfrc522Board2ConfigurationPiccIsPresentState.addCallback(mfrc522Board2HandleStatus);
  mfrc522Board2Mfrc522.PCD_Init();
  mfrc522Board2Mfrc522.PCD_SetAntennaGain(MFRC522_ANTENNA_GAIN);

  // Configuring PICC reader 3
  PiccUid mfrc522Board3ValidUid;
  if (mfrc522Board3ReadUidFromEeprom(&mfrc522Board3ValidUid)) {
    mfrc522Board3UidChecker.setExpectedUid(mfrc522Board3ValidUid);
  } else {
    //TODO raise error somehow
  }
  mfrc522Board3ConfigurationNoPiccState.addNewUidCallback(mfrc522Board3UpdateUidChecker);
  mfrc522Board3ConfigurationNoPiccState.addNewUidCallback(mfrc522Board3WriteUid);
  mfrc522Board3StateMachine.addStateFunction(State::noPicc, mfrc522Board3NoPiccState);
  mfrc522Board3StateMachine.addStateFunction(State::piccIsPresent, mfrc522Board3PiccIsPresentState);
  mfrc522Board3StateMachine.addStateFunction(State::configurationNoPicc, mfrc522Board3ConfigurationNoPiccState);
  mfrc522Board3StateMachine.addStateFunction(State::configurationPiccIsPresent, mfrc522Board3ConfigurationPiccIsPresentState);
  mfrc522Board3StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board3NoPiccState.addCallback(mfrc522Board3HandleStatus);
  mfrc522Board3ConfigurationNoPiccState.addNewPiccReaderStatusCallback(mfrc522Board3HandleStatus);
  mfrc522Board3PiccIsPresentState.addCallback(mfrc522Board3HandleStatus);
  mfrc522Board3ConfigurationPiccIsPresentState.addCallback(mfrc522Board3HandleStatus);
  mfrc522Board3Mfrc522.PCD_Init();
  mfrc522Board3Mfrc522.PCD_SetAntennaGain(MFRC522_ANTENNA_GAIN);

  // Configuring PICC reader 4
  PiccUid mfrc522Board4ValidUid;
  if (mfrc522Board4ReadUidFromEeprom(&mfrc522Board4ValidUid)) {
    mfrc522Board4UidChecker.setExpectedUid(mfrc522Board4ValidUid);
  } else {
    //TODO raise error somehow
  }
  mfrc522Board4ConfigurationNoPiccState.addNewUidCallback(mfrc522Board4UpdateUidChecker);
  mfrc522Board4ConfigurationNoPiccState.addNewUidCallback(mfrc522Board4WriteUid);
  mfrc522Board4StateMachine.addStateFunction(State::noPicc, mfrc522Board4NoPiccState);
  mfrc522Board4StateMachine.addStateFunction(State::piccIsPresent, mfrc522Board4PiccIsPresentState);
  mfrc522Board4StateMachine.addStateFunction(State::configurationNoPicc, mfrc522Board4ConfigurationNoPiccState);
  mfrc522Board4StateMachine.addStateFunction(State::configurationPiccIsPresent, mfrc522Board4ConfigurationPiccIsPresentState);
  mfrc522Board4StateMachine.addCallback(sendStatusRequestCommandWrapper);
  mfrc522Board4NoPiccState.addCallback(mfrc522Board4HandleStatus);
  mfrc522Board4ConfigurationNoPiccState.addNewPiccReaderStatusCallback(mfrc522Board4HandleStatus);
  mfrc522Board4PiccIsPresentState.addCallback(mfrc522Board4HandleStatus);
  mfrc522Board4ConfigurationPiccIsPresentState.addCallback(mfrc522Board4HandleStatus);
  mfrc522Board4Mfrc522.PCD_Init();
  mfrc522Board4Mfrc522.PCD_SetAntennaGain(MFRC522_ANTENNA_GAIN);

  // Lock control
  piccReaderStatusMonitor.addCallback(controlLock);
}
