class ActiveHighPinController {
  public:
    ActiveHighPinController(int pin) : pin(pin) {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }
  
    bool toggle() {
      if (active) {
        digitalWrite(pin, LOW);
        active = false;
      } else {
        digitalWrite(pin, HIGH);
        active = true;
      }
      return active;
    }

    void enable() {
      digitalWrite(pin, HIGH);
      active = true;
    }

    void disable() {
      digitalWrite(pin, LOW);
      active = false;
    }

  private:
    const int pin;
    bool active = true;
};
