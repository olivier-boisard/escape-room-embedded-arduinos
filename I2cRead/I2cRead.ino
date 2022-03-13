#include <Wire.h>

constexpr byte I2C_DEVICE_ADDRESS = 0x01;
byte lastReceivedByte = 0x00;

void onIc2ReceivedHandler(int) {
  while (Wire.available()) {
    lastReceivedByte = Wire.read();
  }
}

void onI2cRequestHandler() {
  Wire.write(lastReceivedByte + 1);
}

void setup() {
  Wire.begin(I2C_DEVICE_ADDRESS);
  Wire.onReceive(onIc2ReceivedHandler);
  Wire.onRequest(onI2cRequestHandler);
}

void loop() {}
