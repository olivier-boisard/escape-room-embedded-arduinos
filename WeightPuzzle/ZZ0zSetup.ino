void setup() {
  // Wiring
  hx711Handler.addCallback(updateReadingInStatus);
  hx711Handler.addCallback(updateReadingInWeightObserver);
  configurationRequestProcessor.addCallback(updateStatusWithConfiguration);
  configurationRequestProcessor.addCallback(configurationToEepromWriter);

  // Initialize stuff
  Serial.begin(BAUDRATE);
  hx711Handler.init();
  Configuration configuration = configurationFromEepromReader();
  statusRequestProcessor.setConfiguration(configuration);
}
