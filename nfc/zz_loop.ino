void loop() {
  if (button.pressedAndReleased()) {
    stateMachine.toggleConfigurationMode();
  }
  stateMachine.process();
  delay(LOOP_DELAY_MS);
}
