CorrectPiccStatusesObservable piccReaderStatusMonitor(N_MFRC522_READERS);

// MFRC522
//// MFRC522 0
////// MFRC522 driver
MFRC522DriverPinSimple mfrc522Board0SdaPin = MFRC522DriverPinSimple(SDA_PIN_0);
MFRC522DriverSPI mfrc522Board0Driver = MFRC522DriverSPI{
  mfrc522Board0SdaPin,
  SPI,
  SPISettings(
    SPI_CLOCK_DIV4,
    MSBFIRST,
    SPI_MODE0
  )
};
MFRC522 mfrc522Board0Mfrc522{mfrc522Board0Driver};

////// Persistency
int mfrc522Board0EepromAddress = 8;
UidFromEepromReader mfrc522Board0ReadUidFromEeprom(mfrc522Board0EepromAddress);
UidToEepromWriter mfrc522Board0WriteUid(mfrc522Board0EepromAddress);

////// Uid check
UpdateableUidChecker mfrc522Board0UidChecker;
auto mfrc522Board0CheckUid = [&mfrc522Board0UidChecker] (const PiccUid& uid) {return mfrc522Board0UidChecker.checkUid(uid); };
auto mfrc522Board0UpdateUidChecker = [&mfrc522Board0UidChecker] (const PiccUid& uid) {return mfrc522Board0UidChecker.update(uid); };

////// State machine
Mfrc522UidReader mfrc522Board0ReadUidFromMFRC522(mfrc522Board0Mfrc522);
UidIsReadableChecker mfrc522Board0IsUidReadable(mfrc522Board0ReadUidFromMFRC522);
NoPiccState mfrc522Board0NoPiccState(mfrc522Board0ReadUidFromMFRC522, mfrc522Board0CheckUid);
PiccIsPresentState mfrc522Board0PiccIsPresentState(mfrc522Board0IsUidReadable);
ConfigurationNoPiccState mfrc522Board0ConfigurationNoPiccState(mfrc522Board0ReadUidFromMFRC522);
ConfigurationPiccIsPresentState mfrc522Board0ConfigurationPiccIsPresentState(mfrc522Board0IsUidReadable);
StateMachine mfrc522Board0StateMachine;

//// MFRC522 1
////// MFRC522 driver
MFRC522DriverPinSimple mfrc522Board1SdaPin = MFRC522DriverPinSimple(SDA_PIN_1);
MFRC522DriverSPI mfrc522Board1Driver = MFRC522DriverSPI{
  mfrc522Board1SdaPin,
  SPI,
  SPISettings(
    SPI_CLOCK_DIV4,
    MSBFIRST,
    SPI_MODE0
  )
};
MFRC522 mfrc522Board1Mfrc522{mfrc522Board1Driver};

////// Persistency
int mfrc522Board1EepromAddress = 16;
UidFromEepromReader mfrc522Board1ReadUidFromEeprom(mfrc522Board1EepromAddress);
UidToEepromWriter mfrc522Board1WriteUid(mfrc522Board1EepromAddress);

////// Uid check
UpdateableUidChecker mfrc522Board1UidChecker;
auto mfrc522Board1CheckUid = [&mfrc522Board1UidChecker] (const PiccUid& uid) {return mfrc522Board1UidChecker.checkUid(uid); };
auto mfrc522Board1UpdateUidChecker = [&mfrc522Board1UidChecker] (const PiccUid& uid) {return mfrc522Board1UidChecker.update(uid); };

////// State machine
Mfrc522UidReader mfrc522Board1ReadUidFromMFRC522(mfrc522Board1Mfrc522);
UidIsReadableChecker mfrc522Board1IsUidReadable(mfrc522Board1ReadUidFromMFRC522);
NoPiccState mfrc522Board1NoPiccState(mfrc522Board1ReadUidFromMFRC522, mfrc522Board1CheckUid);
PiccIsPresentState mfrc522Board1PiccIsPresentState(mfrc522Board1IsUidReadable);
ConfigurationNoPiccState mfrc522Board1ConfigurationNoPiccState(mfrc522Board1ReadUidFromMFRC522);
ConfigurationPiccIsPresentState mfrc522Board1ConfigurationPiccIsPresentState(mfrc522Board1IsUidReadable);
StateMachine mfrc522Board1StateMachine;

//// MFRC522 2
////// MFRC522 driver
MFRC522DriverPinSimple mfrc522Board2SdaPin = MFRC522DriverPinSimple(SDA_PIN_2);
MFRC522DriverSPI mfrc522Board2Driver = MFRC522DriverSPI{
  mfrc522Board2SdaPin,
  SPI,
  SPISettings(
    SPI_CLOCK_DIV4,
    MSBFIRST,
    SPI_MODE0
  )
};
MFRC522 mfrc522Board2Mfrc522{mfrc522Board2Driver};

////// Persistency
int mfrc522Board2EepromAddress = 24;
UidFromEepromReader mfrc522Board2ReadUidFromEeprom(mfrc522Board2EepromAddress);
UidToEepromWriter mfrc522Board2WriteUid(mfrc522Board2EepromAddress);

////// Uid check
UpdateableUidChecker mfrc522Board2UidChecker;
auto mfrc522Board2CheckUid = [&mfrc522Board2UidChecker] (const PiccUid& uid) {return mfrc522Board2UidChecker.checkUid(uid); };
auto mfrc522Board2UpdateUidChecker = [&mfrc522Board2UidChecker] (const PiccUid& uid) {return mfrc522Board2UidChecker.update(uid); };

////// State machine
Mfrc522UidReader mfrc522Board2ReadUidFromMFRC522(mfrc522Board2Mfrc522);
UidIsReadableChecker mfrc522Board2IsUidReadable(mfrc522Board2ReadUidFromMFRC522);
NoPiccState mfrc522Board2NoPiccState(mfrc522Board2ReadUidFromMFRC522, mfrc522Board2CheckUid);
PiccIsPresentState mfrc522Board2PiccIsPresentState(mfrc522Board2IsUidReadable);
ConfigurationNoPiccState mfrc522Board2ConfigurationNoPiccState(mfrc522Board2ReadUidFromMFRC522);
ConfigurationPiccIsPresentState mfrc522Board2ConfigurationPiccIsPresentState(mfrc522Board2IsUidReadable);
StateMachine mfrc522Board2StateMachine;

//// MFRC522 3
////// MFRC522 driver
MFRC522DriverPinSimple mfrc522Board3SdaPin = MFRC522DriverPinSimple(SDA_PIN_3);
MFRC522DriverSPI mfrc522Board3Driver = MFRC522DriverSPI{
  mfrc522Board3SdaPin,
  SPI,
  SPISettings(
    SPI_CLOCK_DIV4,
    MSBFIRST,
    SPI_MODE0
  )
};
MFRC522 mfrc522Board3Mfrc522{mfrc522Board3Driver};

////// Persistency
int mfrc522Board3EepromAddress = 32;
UidFromEepromReader mfrc522Board3ReadUidFromEeprom(mfrc522Board3EepromAddress);
UidToEepromWriter mfrc522Board3WriteUid(mfrc522Board3EepromAddress);

////// Uid check
UpdateableUidChecker mfrc522Board3UidChecker;
auto mfrc522Board3CheckUid = [&mfrc522Board3UidChecker] (const PiccUid& uid) {return mfrc522Board3UidChecker.checkUid(uid); };
auto mfrc522Board3UpdateUidChecker = [&mfrc522Board3UidChecker] (const PiccUid& uid) {return mfrc522Board3UidChecker.update(uid); };

////// State machine
Mfrc522UidReader mfrc522Board3ReadUidFromMFRC522(mfrc522Board3Mfrc522);
UidIsReadableChecker mfrc522Board3IsUidReadable(mfrc522Board3ReadUidFromMFRC522);
NoPiccState mfrc522Board3NoPiccState(mfrc522Board3ReadUidFromMFRC522, mfrc522Board3CheckUid);
PiccIsPresentState mfrc522Board3PiccIsPresentState(mfrc522Board3IsUidReadable);
ConfigurationNoPiccState mfrc522Board3ConfigurationNoPiccState(mfrc522Board3ReadUidFromMFRC522);
ConfigurationPiccIsPresentState mfrc522Board3ConfigurationPiccIsPresentState(mfrc522Board3IsUidReadable);
StateMachine mfrc522Board3StateMachine;

//// MFRC522 4
////// MFRC522 driver
MFRC522DriverPinSimple mfrc522Board4SdaPin = MFRC522DriverPinSimple(SDA_PIN_4);
MFRC522DriverSPI mfrc522Board4Driver = MFRC522DriverSPI{
  mfrc522Board4SdaPin,
  SPI,
  SPISettings(
    SPI_CLOCK_DIV4,
    MSBFIRST,
    SPI_MODE0
  )
};
MFRC522 mfrc522Board4Mfrc522{mfrc522Board4Driver};

////// Persistency
int mfrc522Board4EepromAddress = 40;
UidFromEepromReader mfrc522Board4ReadUidFromEeprom(mfrc522Board4EepromAddress);
UidToEepromWriter mfrc522Board4WriteUid(mfrc522Board4EepromAddress);

////// Uid check
UpdateableUidChecker mfrc522Board4UidChecker;
auto mfrc522Board4CheckUid = [&mfrc522Board4UidChecker] (const PiccUid& uid) {return mfrc522Board4UidChecker.checkUid(uid); };
auto mfrc522Board4UpdateUidChecker = [&mfrc522Board4UidChecker] (const PiccUid& uid) {return mfrc522Board4UidChecker.update(uid); };

////// State machine
Mfrc522UidReader mfrc522Board4ReadUidFromMFRC522(mfrc522Board4Mfrc522);
UidIsReadableChecker mfrc522Board4IsUidReadable(mfrc522Board4ReadUidFromMFRC522);
NoPiccState mfrc522Board4NoPiccState(mfrc522Board4ReadUidFromMFRC522, mfrc522Board4CheckUid);
PiccIsPresentState mfrc522Board4PiccIsPresentState(mfrc522Board4IsUidReadable);
ConfigurationNoPiccState mfrc522Board4ConfigurationNoPiccState(mfrc522Board4ReadUidFromMFRC522);
ConfigurationPiccIsPresentState mfrc522Board4ConfigurationPiccIsPresentState(mfrc522Board4IsUidReadable);
StateMachine mfrc522Board4StateMachine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
ActiveLowPinController lockController(LOCK_CONTROL_OUTPUT_PIN);

// Board driver
StatusRequestProcessor statusRequestProcessor(N_MFRC522_READERS);
SerialAndInternalCommunicationManager serialAndInternalCommunicationManager;

auto sendStatusRequestCommand = [&serialAndInternalCommunicationManager] () {
  serialAndInternalCommunicationManager.setInternalMessage(&BoardDriver::STATUS_REQUEST_CODE, 1);
};
auto sendStatusRequestCommandWrapper = [&sendStatusRequestCommand] (State) {sendStatusRequestCommand(); };

// Lock
auto controlLock = [&lockController, &statusRequestProcessor] (bool allPiccCorrect) {
  bool disableLock = allPiccCorrect;
  if (disableLock) {
    lockController.disable();
    statusRequestProcessor.setLockEnabled(false);
  }
};
auto toggleLock = [&lockController, &statusRequestProcessor] () {
  bool lockEnabled = lockController.toggle();
  statusRequestProcessor.setLockEnabled(lockEnabled);
  return lockEnabled;
};
auto configurationModeToggler = [&mfrc522Board0StateMachine, &mfrc522Board1StateMachine, &mfrc522Board2StateMachine, &mfrc522Board3StateMachine, &mfrc522Board4StateMachine, &statusRequestProcessor] () {
  bool enabled = mfrc522Board0StateMachine.toggleConfigurationMode();
  mfrc522Board1StateMachine.toggleConfigurationMode();
  mfrc522Board2StateMachine.toggleConfigurationMode();
  mfrc522Board3StateMachine.toggleConfigurationMode();
  mfrc522Board4StateMachine.toggleConfigurationMode();
  statusRequestProcessor.setConfigurationModeEnabled(enabled);
  return enabled;
};
LockCommandProcessor lockCommandProcessor(toggleLock);
ConfigurationModeCommandProcessor configurationModeCommandProcessor(configurationModeToggler);
BoardDriver boardDriver(
  serialAndInternalCommunicationManager,
  processHandshake,
  statusRequestProcessor,
  lockCommandProcessor,
  configurationModeCommandProcessor
);

auto setConfigurationModeEnabled = [&statusRequestProcessor] (bool enabled) {
  statusRequestProcessor.setConfigurationModeEnabled(enabled);
};

/////
auto mfrc522Board0HandleStatus = [&piccReaderStatusMonitor, &statusRequestProcessor] (PiccReaderStatus status) {
  piccReaderStatusMonitor.updatePiccReaderStatus(0, status);
  statusRequestProcessor.setPiccReaderStatus(0, status);
  sendStatusRequestCommand();
};
auto mfrc522Board1HandleStatus = [&piccReaderStatusMonitor, &statusRequestProcessor] (PiccReaderStatus status) {
  piccReaderStatusMonitor.updatePiccReaderStatus(1, status);
  statusRequestProcessor.setPiccReaderStatus(1, status);
  sendStatusRequestCommand();
};
auto mfrc522Board2HandleStatus = [&piccReaderStatusMonitor, &statusRequestProcessor] (PiccReaderStatus status) {
  piccReaderStatusMonitor.updatePiccReaderStatus(2, status);
  statusRequestProcessor.setPiccReaderStatus(2, status);
  sendStatusRequestCommand();
};
auto mfrc522Board3HandleStatus = [&piccReaderStatusMonitor, &statusRequestProcessor] (PiccReaderStatus status) {
  piccReaderStatusMonitor.updatePiccReaderStatus(3, status);
  statusRequestProcessor.setPiccReaderStatus(3, status);
  sendStatusRequestCommand();
};
auto mfrc522Board4HandleStatus = [&piccReaderStatusMonitor, &statusRequestProcessor] (PiccReaderStatus status) {
  piccReaderStatusMonitor.updatePiccReaderStatus(4, status);
  statusRequestProcessor.setPiccReaderStatus(4, status);
  sendStatusRequestCommand();
};
