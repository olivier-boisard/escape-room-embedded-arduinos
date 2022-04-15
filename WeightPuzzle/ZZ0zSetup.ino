void setup() {
  Serial.begin(BAUDRATE);
  hx711Handler.addCallback(sendReading);
  hx711Handler.init();
}
