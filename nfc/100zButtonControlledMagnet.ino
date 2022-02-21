class Toggler {
  public:
    Toggler(int controlPin) : controlPin(controlPin) {}
  
    void operator()() {
      if (locked) {
        digitalWrite(controlPin, HIGH);
        locked = false;
      } else {
        digitalWrite(controlPin, LOW);
        locked = true;
      }
    }

  private:
    const int controlPin;
    bool locked = true;
};
