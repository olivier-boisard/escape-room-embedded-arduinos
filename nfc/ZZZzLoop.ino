void loop() {
  boardDriver.processInput();
  stateMachine.process();
  delay(LOOP_DELAY_MS);
}
