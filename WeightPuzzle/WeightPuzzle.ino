#include "HX711.h"
#include <EEPROM.h>

#define LOADCELL_DOUT_PIN 7
#define LOADCELL_SCK_PIN 6
#define SCALE 95.0f
#define BAUDRATE 9600
#define MIN_DIFF 5
#define LONG_SIZE_BYTES 8
#define N_BITS_IN_BYTES 8
#define DELAY_MS 100
#define EEPROM_ADDRESS 0x08
#define LONG_AS_STR_N_DIGITS 10
#define EEPROM_ADDRESS 0x08
