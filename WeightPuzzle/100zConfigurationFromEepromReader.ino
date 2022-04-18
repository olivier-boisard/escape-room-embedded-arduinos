class ConfigurationFromEepromReader {
  public:
    ConfigurationFromEepromReader(size_t eepromAddress) : eepromAddress(eepromAddress) {}
  
    Configuration operator()() {
      constexpr size_t longSizeInBytes = 4;
      long minWeightInGrams = 0;
      long maxWeightInGrams = 0;
      long holdingTimeInMs = 0;
      EEPROM.get(eepromAddress, minWeightInGrams);
      EEPROM.get(eepromAddress + longSizeInBytes, maxWeightInGrams);
      EEPROM.get(eepromAddress + 2* longSizeInBytes, holdingTimeInMs);
      return Configuration(minWeightInGrams, maxWeightInGrams, holdingTimeInMs);
    }

  private:
    const size_t eepromAddress;
};
