void loop() {
  boardDriver.processInput();
  hx711Handler.process();
  handleUpdate();
  delay(DELAY_MS);
}
