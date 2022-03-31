#include <Wire.h>

#define SDA_PIN 4
#define SCL_PIN 5

constexpr byte I2C_DEVICE_ADDRESS = 0x08;
byte lastReceivedByte = 0x00;

void onIc2ReceivedHandler(int) {
  while (Wire.available()) {
    lastReceivedByte = Wire.read();
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN, I2C_DEVICE_ADDRESS);
  Wire.onReceive(onIc2ReceivedHandler);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  delay(1000);
  Serial.println(lastReceivedByte);
  digitalWrite(LED_BUILTIN, HIGH);
}
