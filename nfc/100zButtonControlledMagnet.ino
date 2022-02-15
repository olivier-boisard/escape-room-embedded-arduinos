class ButtonControlledMagnet {
  public:
    ButtonControlledMagnet(int controlPin) : controlPin(controlPin) {}
  
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
    int controlPin;
    bool locked = true;
};
