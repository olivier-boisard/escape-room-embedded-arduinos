void loop() {
  boardDriver.read();
  configurationButton.process();
  magnetButton.process();
  stateMachine.process();
  delay(LOOP_DELAY_MS);
}
