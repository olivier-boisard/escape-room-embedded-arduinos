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

    bool pressedAndReleased() {
      size_t debounceDelayPerCheckMs = 10;
      size_t debounceNChecks = 5;
      
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
