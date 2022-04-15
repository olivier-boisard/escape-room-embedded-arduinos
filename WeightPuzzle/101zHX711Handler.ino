class HX711Handler : public CallbackStackMixin<long> {
  public:
    HX711Handler(HX711& hx711, float scale, long minDiff) : hx711(hx711), scale(scale), minDiff(minDiff) {}

    void init() {
      hx711.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
      hx711.set_scale(scale);
      hx711.tare();
      previousReading = hx711.get_units();
    }

    void process() {
      if (hx711.is_ready()) {
        long reading = hx711.get_units();
        long diff = abs(reading - previousReading);
        if (diff >= minDiff) {
          previousReading = reading;
          callCallbacks(reading);
        }
      } else {
        //TODO handle error somehow
      }
    }

  private:
    HX711& hx711;
    long minDiff;
    float scale;
    long previousReading = 0;
};
