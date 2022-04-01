#include <EEPROM.h>

void setup() {
  for (size_t i = 0 ; i < 512 ; i++) {
    EEPROM[i] = 0x00;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
