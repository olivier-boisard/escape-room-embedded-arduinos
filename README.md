# Escape room embedded systems 
This piece of code contains the drivers for the Arduino cards deployed in an escape room.
The project is organized as follows:
* BookPuzzle: contains the code related to a puzzle involving books to be sorted properly in a shelf
* EepromClear: contains the code of a firmware allowing to clear the EEPROM (i.e., internal storage space) of an Arduino
* WeightPuzzle: contains the code related to a puzzle involving weighing the ingredients for a meal.
* WiFiInterface: contains the code for the WiFi modules

You will notice that the file are named following this convention: <3 digits number>z<module name>.ino. Reason for this is that the Arduino IDE looks
at the alphabetical order of the files to decide which ones should be compiled first. Using this naming convention allows to ensure that dependencies
are compiled before the modules that depend on them.
