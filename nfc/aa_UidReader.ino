#include <EEPROM.h>

class UidReaderInterface {
  public:
    virtual void read(MFRC522::Uid* output) = 0;

    virtual ~UidReaderInterface() {}
};
