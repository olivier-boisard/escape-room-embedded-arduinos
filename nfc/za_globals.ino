class SerialReader {
  public:
    void read() {
      byte handshakeCode = 0x10;
      byte errorCode = 0xFF;
      byte expectedIncomingCode[] = {0x01, 0xEE, 0x35, 0xD7, 0x2A, 0x80, 0x58, 0xEA};
      byte firmwareId[] = {0x85, 0xF2, 0x9E, 0xE3, 0x43, 0x19, 0xEA, 0xF6};
      size_t inputBufferSize = 16;
      byte inputBuffer[inputBufferSize];
      
      if (Serial.available() > 0) {
        size_t nReadBytes = Serial.readBytesUntil(0x00, inputBuffer, inputBufferSize);
        if (inputBuffer[0] == handshakeCode) {
            Serial.write(handshakeCode);
          if (arrayEquals(sizeof(expectedIncomingCode), inputBuffer + 1, expectedIncomingCode)) {
            Serial.write(firmwareId, sizeof(firmwareId));
          } else {
            Serial.write(errorCode);
          }
        } else {
          Serial.write(errorCode);
        }
        Serial.flush();
      }
    }
};

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
UidIsReadableChecker uidIsReadableChecker(&uidFromSerialCardReader);
NoCardState noCardState(&uidFromSerialCardReader, &uidChecker);
CardIsPresentState cardIsPresentState(&uidIsReadableChecker);
ConfigurationNoCardState configurationNoCardState(&uidFromSerialCardReader);
ConfigurationCardIsPresentState configurationCardIsPresentState(&uidIsReadableChecker);
StateMachine stateMachine;

Button configurationButton(CONFIG_BUTTON_INPUT_PIN);

Button magnetButton(MAGNET_BUTTON_INPUT_PIN);
ButtonControlledMagnet magnet(MAGNET_CONTROL_OUTPUT_PIN);

SerialReader serialReader;
