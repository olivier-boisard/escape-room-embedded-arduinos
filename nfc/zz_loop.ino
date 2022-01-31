void loop() {
  button.process();
  stateMachine.process();
  delay(LOOP_DELAY_MS);
}
