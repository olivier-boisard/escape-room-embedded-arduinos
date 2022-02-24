void loop() {
  boardDriver.processInput();
  configurationButton.process();
  stateMachine.process();
  delay(LOOP_DELAY_MS);
}
