void setup() {
  // Wiring
  hx711Handler.addCallback(updateReadingInStatus);
  configurationRequestProcessor.addCallback(updateStatusWithConfiguration);
  configurationRequestProcessor.addCallback(configurationToEepromWriter);

  // Initialize stuff
  Serial.begin(BAUDRATE);
  hx711Handler.init();
  Configuration configuration = configurationFromEepromReader();
  statusRequestProcessor.setConfiguration(configuration);
}
