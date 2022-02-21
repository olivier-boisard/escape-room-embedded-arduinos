class ActiveLowPinToggler {
  public:
    ActiveLowPinToggler(int pin) : pin(pin) {}
  
    bool operator()() {
      if (active) {
        digitalWrite(pin, HIGH);
        active = false;
      } else {
        digitalWrite(pin, LOW);
        active = true;
      }
      return active;
    }

  private:
    const int pin;
    bool active = true;
};
