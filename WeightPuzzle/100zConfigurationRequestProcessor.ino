class ConfigurationRequestProcessor : public CallbackStackMixin<const Configuration&> {

  public:
    ConfigurationRequestProcessor(size_t nDigitsPerLongToRead) : nDigitsPerLongToRead(nDigitsPerLongToRead) {}
  
    size_t operator()(const byte command[], size_t commandSize, byte* outputBuffer) {
      long minWeightInGrams = readLongFromAscii(command, nDigitsPerLongToRead);
      long maxWeightInGrams = readLongFromAscii(command + nDigitsPerLongToRead, nDigitsPerLongToRead);
      long holdingTimeInMs = readLongFromAscii(command + 2 * nDigitsPerLongToRead, nDigitsPerLongToRead);
      Configuration configuration(minWeightInGrams, maxWeightInGrams, holdingTimeInMs);
      callCallbacks(configuration);
    }

  private:
    const size_t nDigitsPerLongToRead;
  
};
