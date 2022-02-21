// MFRC522 driver
MFRC522DriverPinSimple ss_pin = MFRC522DriverPinSimple(SS_PIN);
MFRC522DriverSPI driver = MFRC522DriverSPI{
  ss_pin,
  SPI,
  SPISettings(
    SPI_CLOCK_DIV4,
    MSBFIRST,
    SPI_MODE0
  )
};
MFRC522 mfrc522{driver};

// Persistency
int eepromAddress = 8;
UidFromEepromReader readUidFromEeprom(eepromAddress);
UidToEepromWriter writeUid(eepromAddress);

// Uid checker
UpdateableUidChecker uidChecker;
auto checkUid = [&uidChecker] (const PiccUid& uid) {return uidChecker.checkUid(uid); };
auto updateUidChecker = [&uidChecker] (const PiccUid& uid) {return uidChecker.update(uid); };

// State machine
MFRC522UidReader readUidFromMFRC522(mfrc522);
UidIsReadableChecker isUidReadable(readUidFromMFRC522);
NoCardState noCardState(readUidFromMFRC522, checkUid);
CardIsPresentState cardIsPresentState(isUidReadable);
ConfigurationNoCardState configurationNoCardState(readUidFromMFRC522);
ConfigurationCardIsPresentState configurationCardIsPresentState(isUidReadable);
StateMachine stateMachine;
StatusRequestProcessor statusRequestProcessor(N_MFRC522_READERS);
auto configurationModeToggler = [&stateMachine, &statusRequestProcessor] () {
  statusRequestProcessor.setConfigurationModeEnabled(stateMachine.toggleConfigurationMode());
};

// Configuration
Button configurationButton(CONFIG_BUTTON_INPUT_PIN);

// Magnet
Button magnetButton(MAGNET_BUTTON_INPUT_PIN);
ActiveLowPinToggler toggleMagnet(MAGNET_CONTROL_OUTPUT_PIN);
auto toggleMagnetWrapper = [&toggleMagnet, &statusRequestProcessor] () {
  statusRequestProcessor.setMagnetEnabled(toggleMagnet());
};
auto controlMagnetWithPicc = [&toggleMagnetWrapper] (PiccReaderStatus status) {
  if (status == correctPicc) toggleMagnetWrapper();
};

// Communication
SerialCommunicationManager communicationManager;
LockCommandProcessor lockCommandProcessor(toggleMagnet);
ConfigurationModeCommandProcessor configurationModeCommandProcessor(configurationModeToggler);
BoardDriver boardDriver(
  communicationManager,
  processHandshake,
  statusRequestProcessor,
  lockCommandProcessor,
  configurationModeCommandProcessor
);
auto setPiccReaderZeroState = [&statusRequestProcessor] (PiccReaderStatus status) {statusRequestProcessor.setPiccReaderStatus(0, status); };
auto setConfigurationModeEnabled = [&statusRequestProcessor] (bool enabled) {statusRequestProcessor.setConfigurationModeEnabled(enabled); };
