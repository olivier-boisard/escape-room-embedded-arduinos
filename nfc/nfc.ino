/*
 * Pin layout
 * 
 * -------------------------------------
 * MFRC522      Arduino     
 * Reader/PCD   Uno/101     
 * Pin          Pin         
 * -------------------------------------
 * SDA(SS)      10          
 * MOSI         11
 * MISO         12
 * SCK          13
 * 
 * -------------------------------------
 * LED's          Arduino Uno/101 Pin
 * -------------------------------------
 * Green        9
 * Red          8
 */

#include <EEPROM.h>

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <MFRC522Constants.h>

// Config
#define SDA_PIN_0 10
#define SDA_PIN_1 9
#define SDA_PIN_2 8
#define SDA_PIN_3 7
#define SDA_PIN_4 6
#define MAGNET_CONTROL_OUTPUT_PIN 4
#define N_MFRC522_READERS 5
#define SERIAL_PORT_BAUDRATE 9600
