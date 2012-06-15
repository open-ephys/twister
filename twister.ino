 //    Tetrode Twister Control Software
//    Copyright (C) 2011 Josh Siegle
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


// ------------------------------ //
//    SOFTWARE VERSION NUMBER:
int ver[2] = {
  3, 1};
// ------------------------------ //
//    PCB VERSION NUMBER:
int verPCB = 1; 

// -------------------------------------------------------------------- //
/*    DEBUG MODE?
 
 If debugMode is set to 'true', photocell values and thresholds
 will be printed to the serial port. These can be visualized 
 using the accompanying Processing sketch, 'PhotocellVisualization.pde'
 
 If printState is set to 'true', total turns, forward turns, reverse turns,
 button state, and counter state will be printed to the serial port.
 
 */
 
boolean debugMode = false;
boolean printState = false;

/*   SAVE STATE?

 If saveState is set to true, the Arduino will save its current status
 after each turn. The state can then be restored if the Arduino loses
 power or is reset while turning.

*/

boolean saveState = false;

// -------------------------------------------------------------------- //

// BEGIN ACTUAL CODE:

// Includes
#include <Servo.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "TwisterClasses.h"

// Initialize servo and LCD
Servo myservo;
const int servoPin = 9;
LiquidCrystal lcd(12,11,5,4,3,2);

// Initialize twister classes

//Board 1.1
Buzzer buzzer(6); // Board 1.1 = 6, Board 1.0 = 7
Inputs inputs(7,0,1); // Board 1.1 = 7, Board 1.0 = 6

StateTracker twister;
Photocells photocells(2, 3);

// EEPROM variables
int remainingTurns;
int turnDirection;

void setup()
{

  // start up servo and LCD screen
  myservo.attach(servoPin);
  lcd.begin(16,2);

  if (debugMode || printState) {
    Serial.begin(9600);
  }

  // Read from EEPROM to determine if an error occurred during the last twist:
  if (saveState) {
    remainingTurns = EEPROM.read(0);
    turnDirection = EEPROM.read(1);
  }

  //if (remainingTurns == 0 || remainingTurns == 255) {
    startupScreen(ver[0],ver[1]);  // Display the welcome message

  //} // NOT CURRENTLY IMPLEMENTED:
  //       if Arduino loses power or is reset while turning, 
  //       the program will read stored values from EEPROM
  //       and keep turning where it left off.
  
  //else { // restart turning
  //  resumeDialog();  //Display the interactive dialog
  //}

}

void loop()
{
  inputs.check(twister.isTurning, verPCB);

  if (twister.isTurning) { // only update photocells if twister is spinning
    int turns = photocells.update(twister.isTurningFWD,millis());

    if (turns) {
      twister.totalTurns += turns;
      twister.isUpdated = true; // necessary to update LCD

      if (printState) {
        printVariables();
      }
    }
  }

  showTurns(); // update LCD screen

  if (inputs.buttonState == LOW) { // check for button press
    twister.respondToButton();
    delay(250);
  }

  updateServo();
  
  if (saveState) {
    updateEEPROM();
  }

  if (debugMode) {
    printPhotocellInfo();
  }

}





