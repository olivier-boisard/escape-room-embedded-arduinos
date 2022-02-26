// MFRC522
//// MFRC522 1
////// MFRC522 driver
MFRC522DriverPinSimple sdaPin = MFRC522DriverPinSimple(SDA_PIN_1);
MFRC522DriverSPI driver = MFRC522DriverSPI{
  sdaPin,
  SPI,
  SPISettings(
    SPI_CLOCK_DIV4,
    MSBFIRST,
    SPI_MODE0
  )
};
MFRC522 mfrc522{driver};

////// Persistency
int eepromAddress = 8;
UidFromEepromReader readUidFromEeprom(eepromAddress);
UidToEepromWriter writeUid(eepromAddress);

////// Uid checker
UpdateableUidChecker uidChecker;
auto checkUid = [&uidChecker] (const PiccUid& uid) {return uidChecker.checkUid(uid); };
auto updateUidChecker = [&uidChecker] (const PiccUid& uid) {return uidChecker.update(uid); };

////// State machine
MFRC522UidReader readUidFromMFRC522(mfrc522);
UidIsReadableChecker isUidReadable(readUidFromMFRC522);
NoCardState noCardState(readUidFromMFRC522, checkUid);
CardIsPresentState cardIsPresentState(isUidReadable);
ConfigurationNoCardState configurationNoCardState(readUidFromMFRC522);
ConfigurationCardIsPresentState configurationCardIsPresentState(isUidReadable);
StateMachine stateMachine;

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
auto configurationModeToggler = [&stateMachine, &statusRequestProcessor] () {
  bool enabled = stateMachine.toggleConfigurationMode();
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
