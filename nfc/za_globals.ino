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
UidFromEepromReader uidFromEepromReader(eepromAddress);
UidToEepromWriter uidWriter(eepromAddress);

UidChecker uidChecker;
MFRC522UidReader uidFromSerialCardReader(&mfrc522);
NoCardState noCardState(&uidFromSerialCardReader, &uidChecker);
CardIsPresentState cardIsPresentState(&uidFromSerialCardReader);
ConfigurationNoCardState configurationNoCardState(&uidFromSerialCardReader);
ConfigurationCardIsPresentState configurationCardIsPresentState(&uidFromSerialCardReader);
StateMachine stateMachine(&noCardState, &cardIsPresentState, &configurationNoCardState, &configurationCardIsPresentState);

ExpectedUidUpdater expectedUidUpdater(&uidChecker);
UidWriterWrapper uidWriterWrapper(&uidWriter);
