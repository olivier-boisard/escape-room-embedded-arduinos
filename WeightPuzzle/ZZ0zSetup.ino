void setup() {
  Serial.begin(BAUDRATE);
  hx711Handler.addCallback(updateReadingInStatus);
  hx711Handler.init();
}
