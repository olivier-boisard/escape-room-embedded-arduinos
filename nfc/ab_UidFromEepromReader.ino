class UidFromEepromReader : public PiccUidFactory {
  public:
    UidFromEepromReader(int address) : address(address) {}

    virtual bool generate(PiccUid* output) override {
      size_t uidSize = EEPROM.read(address);
      for (size_t i = 0 ; i < uidSize ; i++) {
        output->value[i] = EEPROM.read(address + i + 1);
      }
      output->size = uidSize;
      return true;
    }

  private:
    int address;
};
