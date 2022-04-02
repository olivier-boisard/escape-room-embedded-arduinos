#include <ESP8266WiFi.h>
#include <EEPROM.h>

#define SERIAL_PORT_BAUDRATE 9600
#define EEPROM_ADDRESS 8
#define SSID_MAX_LENGTH 256
#define PASSWORD_MAX_LENGTH 256
#define CONFIG_WIFI_COMMAND 0x01
#define VALID_WIFI_CREDENTIALS_CODE 0x01
#define CONNECTION_RESULT 0x32
#define CONNECTION_SUCCESS 0x02
#define CONNECTION_FAILURE 0x01
#define END_MSG 0x00
