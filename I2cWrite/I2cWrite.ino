#include <Wire.h>

constexpr byte I2C_SLAVE_ADDRESS = 0x01;
int value = 1;


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
  
  Wire.requestFrom(I2C_SLAVE_ADDRESS, 1);
  while (Wire.available()) {
    byte b = Wire.read();
    Serial.println(b);
  }
  Serial.println("Empty!");
  
  delay(1000);
}
