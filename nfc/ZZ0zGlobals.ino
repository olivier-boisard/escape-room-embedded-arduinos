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

int eepromAddress = 8;
UidFromEepromReader readUidFromEeprom(eepromAddress);
UidToEepromWriter uidWriter(eepromAddress);
UpdateableUidChecker uidChecker;
MFRC522UidReader readUidFromMFRC522(&mfrc522);
UidIsReadableChecker isUidReadable(readUidFromMFRC522);
NoCardState noCardState(readUidFromMFRC522, &uidChecker);
CardIsPresentState cardIsPresentState(isUidReadable);
ConfigurationNoCardState configurationNoCardState(readUidFromMFRC522);
ConfigurationCardIsPresentState configurationCardIsPresentState(isUidReadable);
StateMachine stateMachine;

Button configurationButton(CONFIG_BUTTON_INPUT_PIN);

Button magnetButton(MAGNET_BUTTON_INPUT_PIN);
ButtonControlledMagnet magnet(MAGNET_CONTROL_OUTPUT_PIN);

SerialByteArrayWriter serialByteArrayWriter;
BoardDriver boardDriver(readNullTerminatedByteArrayFromSerial, serialByteArrayWriter);

auto configurationModeToggler = [&stateMachine] () {stateMachine.toggleConfigurationMode(); };
auto magnetToggler = [&magnet] () {magnet.toggle(); };
