class ButtonControlledMagnet : public NiladicVoidFunctionInterface {
  public:
    ButtonControlledMagnet(int controlPin) : controlPin(controlPin) {}
  
    void run() override {
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
