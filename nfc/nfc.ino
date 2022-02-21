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
#define SS_PIN 10
#define BLUE_LED_PIN 6
#define GREEN_LED_PIN 9
#define RED_LED_PIN 8
#define LOOP_DELAY_MS 100
#define CONFIG_BUTTON_INPUT_PIN 7
#define MAGNET_BUTTON_INPUT_PIN 5
#define MAGNET_CONTROL_OUTPUT_PIN 4
#define N_MFRC522_READERS 1
