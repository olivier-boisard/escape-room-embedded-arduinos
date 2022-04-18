void setup() {
  Serial.begin(BAUDRATE);
  
  hx711Handler.addCallback(updateReadingInStatus);
  configurationRequestProcessor.addCallback(updateStatusWithConfiguration);
  
  hx711Handler.init();
}
