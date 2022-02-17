class Button : public CallbackStackMixin<> {
  public:
    Button(int inputPin) : inputPin(inputPin) {}

    void process() const {
      if (pressedAndReleased()) {
        callCallbacks();
      }
    }
  
  private:
    const int inputPin;

    bool pressedAndReleased() const {
      constexpr size_t debounceDelayPerCheckMs = 10;
      constexpr size_t debounceNChecks = 5;
      static bool released = true;
      
      bool output = false;
      if (digitalRead(inputPin) == LOW) {
        bool pressed = true;
        for (int i = 0 ; i < debounceNChecks ; i++) {
          delay(debounceDelayPerCheckMs);
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
