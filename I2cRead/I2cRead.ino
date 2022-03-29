#include <Wire.h>

constexpr byte I2C_DEVICE_ADDRESS = 0x08;
byte lastReceivedByte = 0x00;

void onIc2ReceivedHandler(int) {
  while (Wire.available()) {
    lastReceivedByte = Wire.read();
    Serial.println("Read byte");
  }
  Serial.println("Done");
}

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_DEVICE_ADDRESS);
  Wire.onReceive(onIc2ReceivedHandler);
}

void loop() {
  delay(1000);
  Serial.println("Yay");
}
