void loop() {
  serialReader.read();
  configurationButton.process();
  magnetButton.process();
  stateMachine.process();
  delay(LOOP_DELAY_MS);
}
