void loop() {
  boardDriver.processInput();
  hx711Handler.process();
  delay(DELAY_MS);
}
 
