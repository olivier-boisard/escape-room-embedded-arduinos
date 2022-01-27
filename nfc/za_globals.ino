#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Constants.h>

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
UidFromEepromReader uidReader(eepromAddress);
UidToEepromWriter uidWriter(eepromAddress);

UidChecker uidChecker;
NoCardState noCardState(&mfrc522, &uidChecker);
CardIsPresentState cardIsPresentState(&mfrc522);
ConfigurationNoCardState configurationNoCardState(&mfrc522);
StateMachine stateMachine(&mfrc522, &uidChecker, &noCardState, &cardIsPresentState, &configurationNoCardState);

ExpectedUidUpdater expectedUidUpdater(&uidChecker);
UidWriterWrapper uidWriterWrapper(&uidWriter);
