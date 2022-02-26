void loop() {
  boardDriver.processInput();
  mfrc522Board0StateMachine.process();
  mfrc522Board1StateMachine.process();
  mfrc522Board2StateMachine.process();
  mfrc522Board3StateMachine.process();
  mfrc522Board4StateMachine.process();
}
