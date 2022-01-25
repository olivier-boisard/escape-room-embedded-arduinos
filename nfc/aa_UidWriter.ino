class UidWriterInterface {
  public:
    virtual void write(const MFRC522::Uid& uid) = 0;

    virtual ~UidWriterInterface() {}
};

class UidToEepromWriter : public UidWriterInterface {
  public:
    UidToEepromWriter(int eepromAddress) : eepromAddress(eepromAddress) {}
  
    void write(const MFRC522::Uid& uid) {
      int uidSize = uid.size;
      EEPROM.update(eepromAddress, uidSize);
      for (int i = 0 ; i < uidSize ; i++) {
        EEPROM.update(eepromAddress + i + 1, uid.uidByte[i]);
      }
   }

  private:
   int eepromAddress;
};
