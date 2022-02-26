class ActiveLowPinController {
  public:
    ActiveLowPinController(int pin) : pin(pin) {
      pinMode(pin, OUTPUT);
      enable();
    }
  
    bool toggle() {
      active ? disable() : enable();
      return active;
    }

    void enable() {
      digitalWrite(pin, LOW);
      active = true;
    }

    void disable() {
      digitalWrite(pin, HIGH);
      active = false;
    }

  private:
    const int pin;
    bool active;
};
