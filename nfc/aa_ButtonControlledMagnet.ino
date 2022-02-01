class ButtonControlledMagnet : public ButtonObserverInterface {
  public:
    ButtonControlledMagnet(int controlPin) : controlPin(controlPin) {}
  
    void onButtonPressedAndReleased() {
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
