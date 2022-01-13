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

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <MFRC522Constants.h>

// Config
#define SS_PIN 10
#define GREEN_LED_PIN 9
#define RED_LED_PIN 8
#define LOOP_DELAY_MS 100
#define N_ABSENCE_CHECKS 2

// TODO this should be moved to another file, however this fails with "redeclared as different kind of symbol" error.
bool tryReadCardSerial(MFRC522& mfrc522) {
  return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}
