void loop() {
  boardDriver.processInput();
  hx711Handler.process();
  weightObserver.process();
  handleUpdate();
  delay(DELAY_MS);
}
