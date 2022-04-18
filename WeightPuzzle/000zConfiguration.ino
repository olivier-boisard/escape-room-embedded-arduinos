class Configuration {
  public:
    Configuration(long minWeightInGrams, long maxWeightInGrams, long holdingTimeInMs) :
      minWeightInGrams(minWeightInGrams),
      maxWeightInGrams(maxWeightInGrams),
      holdingTimeInMs(holdingTimeInMs) {}
  
    long minWeightInGrams;
    long maxWeightInGrams;
    long holdingTimeInMs;
};
