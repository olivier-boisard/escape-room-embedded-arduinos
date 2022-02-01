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
UidFromEepromReader uidFromEepromReader(eepromAddress);
UidToEepromWriter uidWriter(eepromAddress);
UpdateableUidChecker uidChecker;
MFRC522UidReader uidFromSerialCardReader(&mfrc522);
NoCardState noCardState(&uidFromSerialCardReader, &uidChecker);
CardIsPresentState cardIsPresentState(&uidFromSerialCardReader);
ConfigurationNoCardState configurationNoCardState(&uidFromSerialCardReader);
ConfigurationCardIsPresentState configurationCardIsPresentState(&uidFromSerialCardReader);
StateMachine stateMachine;

Button configurationButton(CONFIG_BUTTON_INPUT_PIN);

Button magnetButton(MAGNET_BUTTON_INPUT_PIN);
ButtonControlledMagnet magnet(MAGNET_CONTROL_OUTPUT_PIN);
