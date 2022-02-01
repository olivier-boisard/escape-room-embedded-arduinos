#include <EEPROM.h>

class UidToEepromWriter : public NewUidObserverInterface {
  public:
    UidToEepromWriter(int eepromAddress) : eepromAddress(eepromAddress) {}
  
    void update(const PiccUid& uid) override {
      int uidSize = uid.size;
      EEPROM.update(eepromAddress, uidSize);
      for (int i = 0 ; i < uidSize ; i++) {
        EEPROM.update(eepromAddress + i + 1, uid.value[i]);
      }
   }

  private:
   int eepromAddress;
};
