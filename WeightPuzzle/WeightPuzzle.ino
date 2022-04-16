#include "HX711.h"

#define LOADCELL_DOUT_PIN 7
#define LOADCELL_SCK_PIN 6
#define SCALE 95.0f
#define BAUDRATE 9600
#define MIN_DIFF 5
#define LONG_SIZE_BYTES 8
#define N_BITS_IN_BYTES 8
#define DELAY_MS 1000
#define EEPROM_ADDRESS 0x08
