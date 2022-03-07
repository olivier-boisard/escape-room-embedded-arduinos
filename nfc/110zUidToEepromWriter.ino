class UidToEepromWriter {
  public:
    UidToEepromWriter(int eepromAddress) : eepromAddress(eepromAddress) {}
  
    void operator()(const PiccUid& uid) {
      int uidSize = uid.size;
      EEPROM.write(eepromAddress, uidSize);
      for (int i = 0 ; i < uidSize ; i++) {
        EEPROM.write(eepromAddress + i + 1, uid.value[i]);
      }
   }

  private:
   const int eepromAddress;
};
