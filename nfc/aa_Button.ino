class Button : public NiladicVoidFunctionCaller {
  public:
    Button(int inputPin) : inputPin(inputPin) {}

    void process() {
      if (pressedAndReleased()) {
        callCallbacks();
      }
    }
  
  private:
    bool released = true;
    int inputPin;
    constexpr static size_t DEBOUNCE_DELAY_PER_CHECK_MS = 10;
    constexpr static size_t DEBOUNCE_N_CHECKS = 5;

    bool pressedAndReleased() {
      bool output = false;
      if (digitalRead(inputPin) == LOW) {
        bool pressed = true;
        for (int i = 0 ; i < DEBOUNCE_N_CHECKS ; i++) {
          delay(DEBOUNCE_DELAY_PER_CHECK_MS);
          if (digitalRead(inputPin) != LOW) {
            pressed = false;
            break;
          }
        }
        if (pressed && released) {
          released = false;
          output = true;
        }
      } else {
        released = true;
      }
      return output;
    }
};
