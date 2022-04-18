class WeightObserver {

  public:

    WeightObserver(const function<void()>& correctWeightCallback) :
      correctWeightCallback(correctWeightCallback) {}

    void process() {
      unsigned long currentTime = millis();
      if (isCurrentWeightWithinRange()) {
        if (previousTime <= currentTime) {
          elapsedTimeWithWeightInCorrectRangeInMs += currentTime - previousTime;
          if (elapsedTimeWithWeightInCorrectRangeInMs >= configuration.holdingTimeInMs) {
            if (!callbackCalledAlready) {
              correctWeightCallback();
              callbackCalledAlready = true;
            }
          }
        }
      } else {
        elapsedTimeWithWeightInCorrectRangeInMs = 0;
        callbackCalledAlready = false;
      }
      previousTime = currentTime;
    }

    void updateWeight(long newValue) {
      currentWeightInGrams = newValue;
    }

    void setConfiguration(const Configuration& newValue) {
      configuration = newValue;
    }

  private:
    Configuration configuration;
    long currentWeightInGrams = 0;
    unsigned long elapsedTimeWithWeightInCorrectRangeInMs = 0;
    unsigned long previousTime = 0;
    function<void()> correctWeightCallback;
    bool callbackCalledAlready = false;

    bool isCurrentWeightWithinRange() {
      return (currentWeightInGrams >= configuration.minWeightInGrams) && (currentWeightInGrams <= configuration.maxWeightInGrams);
    }
};
