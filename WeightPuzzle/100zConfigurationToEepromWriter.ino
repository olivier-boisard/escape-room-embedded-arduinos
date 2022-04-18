class ConfigurationToEepromWriter {
  public:
    ConfigurationToEepromWriter(size_t eepromAddress) : eepromAddress(eepromAddress) {}

    void operator()(const Configuration& configuration) {
      constexpr size_t longSizeInBytes = 4;
      size_t index = eepromAddress;
      EEPROM.put(eepromAddress, configuration.minWeightInGrams);
      EEPROM.put(eepromAddress + longSizeInBytes, configuration.maxWeightInGrams);
      EEPROM.put(eepromAddress + 2 * longSizeInBytes, configuration.holdingTimeInMs);
    }

  private:
    const size_t eepromAddress;
};
