class ButtonObserverInterface {
  public:
    virtual void onButtonPressedAndReleased() = 0;
    virtual ~ButtonObserverInterface() {}
};
