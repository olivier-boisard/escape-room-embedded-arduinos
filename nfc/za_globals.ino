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
size_t validUidSize = 7;
MFRC522::Uid validUid{validUidSize, {0x04, 0xCE, 0x89, 0xCA, 0x27, 0x73, 0x80}, 0x00};
PiccProcessor piccProcessor(mfrc522, validUid);
