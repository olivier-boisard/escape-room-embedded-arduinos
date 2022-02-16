void loop() {
  boardDriver.processInput();
  configurationButton.process();
  magnetButton.process();
  stateMachine.process();
  delay(LOOP_DELAY_MS);
}
