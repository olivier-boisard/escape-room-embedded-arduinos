class Configuration {
  public:
    Configuration() : minWeightInGrams(0), maxWeightInGrams(0), holdingTimeInMs(0) {}
  
    Configuration(long minWeightInGrams, long maxWeightInGrams, long holdingTimeInMs) :
      minWeightInGrams(minWeightInGrams),
      maxWeightInGrams(maxWeightInGrams),
      holdingTimeInMs(holdingTimeInMs) {}
  
    long minWeightInGrams;
    long maxWeightInGrams;
    long holdingTimeInMs;
};
