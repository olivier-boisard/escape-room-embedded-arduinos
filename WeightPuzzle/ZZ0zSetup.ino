void setup() {  
  // Wiring
  hx711Handler.addCallback(updateReadingInStatus);
  hx711Handler.addCallback(updateReadingInWeightObserver);
  configurationRequestProcessor.addCallback(updateStatusWithConfiguration);
  configurationRequestProcessor.addCallback(updateWeightObserverConfiguration);
  configurationRequestProcessor.addCallback(configurationToEepromWriter);

  // Initialize stuff
  Serial.begin(BAUDRATE);
  hx711Handler.init();
  Configuration configuration = configurationFromEepromReader();
  weightObserver.setConfiguration(configuration);
  statusRequestProcessor.setConfiguration(configuration);
}
