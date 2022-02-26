// MFRC522
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
int mfrc522Board1EepromAddress = 8;
UidFromEepromReader mfrc522Board1ReadUidFromEeprom(mfrc522Board1EepromAddress);
UidToEepromWriter mfrc522Board1WriteUid(mfrc522Board1EepromAddress);

////// Uid checker
UpdateableUidChecker mfrc522Board1UidChecker;
auto mfrc522Board1CheckUid = [&mfrc522Board1UidChecker] (const PiccUid& uid) {return mfrc522Board1UidChecker.checkUid(uid); };
auto mfrc522Board1UpdateUidChecker = [&mfrc522Board1UidChecker] (const PiccUid& uid) {return mfrc522Board1UidChecker.update(uid); };

////// State machine
MFRC522UidReader mfrc522Board1ReadUidFromMFRC522(mfrc522Board1Mfrc522);
UidIsReadableChecker mfrc522Board1IsUidReadable(mfrc522Board1ReadUidFromMFRC522);
NoCardState mfrc522Board1NoCardState(mfrc522Board1ReadUidFromMFRC522, mfrc522Board1CheckUid);
CardIsPresentState mfrc522Board1CardIsPresentState(mfrc522Board1IsUidReadable);
ConfigurationNoCardState mfrc522Board1ConfigurationNoCardState(mfrc522Board1ReadUidFromMFRC522);
ConfigurationCardIsPresentState mfrc522Board1ConfigurationCardIsPresentState(mfrc522Board1IsUidReadable);
StateMachine mfrc522Board1StateMachine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////

// Board driver
ActiveLowPinToggler toggleMagnet(MAGNET_CONTROL_OUTPUT_PIN);
StatusRequestProcessor statusRequestProcessor(N_MFRC522_READERS);
SerialAndInternalCommunicationManager serialAndInternalCommunicationManager;

auto sendStatusRequestCommand = [&serialAndInternalCommunicationManager] () {
  serialAndInternalCommunicationManager.setInternalMessage(&BoardDriver::STATUS_REQUEST_CODE, 1);
};
auto sendStatusRequestCommandWrapper = [&sendStatusRequestCommand] (State) {sendStatusRequestCommand(); };

// Magnet
auto toggleMagnetWrapper = [&toggleMagnet, &statusRequestProcessor] () {
  statusRequestProcessor.setMagnetEnabled(toggleMagnet());
  sendStatusRequestCommand();
};
auto controlMagnetWithPicc = [&toggleMagnetWrapper] (PiccReaderStatus status) {
  if (status == correctPicc) toggleMagnetWrapper();
};
auto configurationModeToggler = [&mfrc522Board1StateMachine, &statusRequestProcessor] () {
  bool enabled = mfrc522Board1StateMachine.toggleConfigurationMode();
  statusRequestProcessor.setConfigurationModeEnabled(enabled);
  return enabled;
};

LockCommandProcessor lockCommandProcessor(toggleMagnet);
ConfigurationModeCommandProcessor configurationModeCommandProcessor(configurationModeToggler);
BoardDriver boardDriver(
  serialAndInternalCommunicationManager,
  processHandshake,
  statusRequestProcessor,
  lockCommandProcessor,
  configurationModeCommandProcessor
);
auto setPiccReaderZeroState = [&statusRequestProcessor] (PiccReaderStatus status) {
  statusRequestProcessor.setPiccReaderStatus(0, status);
};
auto setConfigurationModeEnabled = [&statusRequestProcessor] (bool enabled) {
  statusRequestProcessor.setConfigurationModeEnabled(enabled);
};
