class Button {
  public:
    bool pressedAndReleased() {
      bool output = false;
      if (digitalRead(BUTTON_INPUT_PIN) == LOW) {
        bool pressed = true;
        for (int i = 0 ; i < DEBOUNCE_N_CHECKS ; i++) {
          delay(DEBOUNCE_DELAY_PER_CHECK_MS);
          if (digitalRead(BUTTON_INPUT_PIN) != LOW) {
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
  
  private:
    bool released = true;
    constexpr static size_t DEBOUNCE_DELAY_PER_CHECK_MS = 10;
    constexpr static size_t DEBOUNCE_N_CHECKS = 5;
};
