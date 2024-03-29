class UidToEepromWriter {
  public:
    UidToEepromWriter(int eepromAddress) : eepromAddress(eepromAddress) {}
  
    void operator()(const PiccUid& uid) {
      int uidSize = uid.size;
      EEPROM.update(eepromAddress, uidSize);
      for (int i = 0 ; i < uidSize ; i++) {
        EEPROM.update(eepromAddress + i + 1, uid.value[i]);
      }
   }

  private:
   const int eepromAddress;
};
