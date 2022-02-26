class UidFromEepromReader {
  public:
    UidFromEepromReader(int address) : address(address) {}

    virtual bool operator()(PiccUid* output) const {
      size_t uidSize = EEPROM.read(address);
      if (uidSize > PiccUid::MAX_SIZE) {
        //TODO raise error somehow
        return false;
      }
      for (size_t i = 0 ; i < uidSize ; i++) {
        output->value[i] = EEPROM.read(address + i + 1);
      }
      output->size = uidSize;
      return true;
    }

  private:
    const int address;
};
