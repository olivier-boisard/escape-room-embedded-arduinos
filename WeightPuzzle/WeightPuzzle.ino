#include "HX711.h"

constexpr int LOADCELL_DOUT_PIN = 3;
constexpr int LOADCELL_SCK_PIN = 2;
constexpr float SCALE = 95.0f;
constexpr int BAUDRATE = 9600;

HX711 scale;
void setup() {
  Serial.begin(BAUDRATE);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(SCALE);
  scale.tare();
}

void loop() {
  if (scale.is_ready()) {
    long reading = scale.get_units();
    
    Serial.print("Reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }
  delay(100);
}
