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


#include "TwisterClasses.h"

// Buzzer methods:

Buzzer::Buzzer(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Buzzer::high()
{
  tone(_pin,2000,200);
}

void Buzzer::low()
{
  tone(_pin,1000,200);
}

// Inputs methods:

Inputs::Inputs(int pin1, int pin2, int pin3)
{
  pinMode(pin1, INPUT);
  _buttonPin = pin1;
  _knobPin1 = pin2;
  _knobPin2 = pin3;
  buttonState = 0;
  fwdTurns = 0;
  revTurns = 0;
  isUpdated = true;
}

void Inputs::check(boolean isTurning, int verPCB)
{
  buttonState = digitalRead(_buttonPin); // read button state
  int knob1;
  int knob2;


  if (!isTurning) { // allow changes only if twister isn't turning

      if (verPCB) {
      // Board ver 1.1:
      knob1 = analogRead(_knobPin1) / 4 * 100 / 255;
      knob2 = analogRead(_knobPin2) / 4 * 100 / 255;
    } 
    else {
      // Board ver 1.0:
      knob1 = (255-(analogRead(_knobPin1) / 4)) * 100 / 255;
      knob2 = (255-(analogRead(_knobPin2) / 4)) * 100 / 255;
    }

    // constrain values to be between 0 and 100
    knob1 = min(knob1,100); 
    knob1 = max(knob1,0);
    knob2 = min(knob2,100); 
    knob2 = max(knob2,0);

    if (knob1 != fwdTurns || knob2 != revTurns) { // check to see if values have been updated
      isUpdated = true;
    }
    fwdTurns = knob1;
    revTurns = knob2;
  }
}


// StateTracker methods:

StateTracker::StateTracker()
{
  isTurning = false;
  isTurningFWD = true;
  isUpdated = false;
  totalTurns = 0;

}

void StateTracker::respondToButton()
{
  isTurning = !(isTurning);
}


// Photocells methods

Photocells::Photocells(int pin1, int pin2)
{
  pins[0] = pin1;
  pins[1] = pin2;
  maxVal[0] = 0; 
  maxVal[1] = 0;
  minVal[0] = 1023; 
  minVal[1] = 1023;
  counter = 0;
  nValues = 25;
  canBeTriggered[0] = true;
  canBeTriggered[1] = true; 
}


int Photocells::update(boolean dir, long time)
{
  // read in data
  values[0] = analogRead(pins[0]);
  values[1] = analogRead(pins[1]);

  checkThreshold(); // use history to dynamically set the threshold

    // check photocell 1
  if (values[0] > thresh[0] && canBeTriggered[0] && time - triggerTime[0] > 200) {
    quarterTurns += 1;
    canBeTriggered[0] = false;
    canBeTriggered[1] = true;
    triggerTime[0] = millis();
  }

  // check photocell 2
  if (values[1] > thresh[1] && canBeTriggered[1] && time - triggerTime[1] > 200) {
    quarterTurns += 1;
    canBeTriggered[1] = false;
    canBeTriggered[0] = true;
    triggerTime[1] = millis();
  }

  // check for a full rotation
  if (quarterTurns == 4) {
    quarterTurns = 0;
    if (dir) {
      return 1;
    } 
    else {
      return -1;
    }

  } 
  else {
    return 0;
  }

}

void Photocells::checkThreshold() {

  int index = counter % nValues;

  // store values in history
  history1[index] = values[0];
  history2[index] = values[1];

  if (index == 0) {
    maxVal[0] = 0;
    maxVal[1] = 0;
    minVal[0] = 1023;
    minVal[1] = 1023;
  }

  // search for max and min
  for (int n = 0; n < nValues; n++) {
    maxVal[0] = max(history1[n],maxVal[0]);
    maxVal[1] = max(history2[n],maxVal[1]);
    minVal[0] = min(history1[n],minVal[0]);
    minVal[1] = min(history2[n],minVal[1]);
  }

  // set threshold at 80% boundary between min and max
  thresh[0] = (maxVal[0] - minVal[0])*0.8 + minVal[0];
  thresh[1] = (maxVal[1] - minVal[1])*0.8 + minVal[1];

  counter += 1;

  delay(10); // wait for 10 milliseconds to make the sampling rate reasonable

}







