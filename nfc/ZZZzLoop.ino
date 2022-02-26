void loop() {
  boardDriver.processInput();
  mfrc522Board0StateMachine.process();
  mfrc522Board1StateMachine.process();
  delay(LOOP_DELAY_MS);
}
