void loop() {
  boardDriver.processInput();
#if N_MFRC522_READERS >= 1
  mfrc522Board0StateMachine.process();
#endif
#if N_MFRC522_READERS >= 2
  mfrc522Board1StateMachine.process();
#endif
#if N_MFRC522_READERS >= 3
  mfrc522Board2StateMachine.process();
#endif
#if N_MFRC522_READERS >= 4
  mfrc522Board3StateMachine.process();
#endif
#if N_MFRC522_READERS >= 5
  mfrc522Board4StateMachine.process();
#endif
}
