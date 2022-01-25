#include <EEPROM.h>

class UidReaderInterface {
  public:
    virtual void read(MFRC522::Uid* output) = 0;

    virtual ~UidReaderInterface() {}
};

class UidFromEepromReader : public UidReaderInterface {
  public:
    UidFromEepromReader(int address) : address(address) {}

    virtual void read(MFRC522::Uid* output) {
      size_t uidSize = EEPROM.read(address);
      for (size_t i = 0 ; i < uidSize ; i++) {
        output->uidByte[i] = EEPROM.read(address + i + 1);
      }
      output->size = uidSize;
    }

  private:
    int address;
};
