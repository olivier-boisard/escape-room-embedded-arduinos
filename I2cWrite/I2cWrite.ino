#include <Wire.h>

constexpr byte I2C_SLAVE_ADDRESS = 0x08;
byte value = 0x01;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(5000);
  Serial.println("Start!");
}

void loop() {
  Wire.beginTransmission(I2C_SLAVE_ADDRESS);
  Wire.write(value++);
  Wire.endTransmission();
  
  delay(1000);
}
