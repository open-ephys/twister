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


#ifndef TwisterClasses_h
#define TwisterClasses_h

#include "Arduino.h" // for IDE 1.0 and higher
// #include "WProgram.h" // if using IDE 0.X

class Buzzer
{
  public:
    Buzzer(int pin);
    void high();
    void low();
   private:
     int _pin;
};

class Inputs
{
  public:
    int buttonState, fwdTurns, revTurns;
    boolean isUpdated;
    Inputs(int pin1, int pin2, int pin3);
    void check(boolean isTurning, int versionNum);
  private:
    int _buttonPin, _knobPin1, _knobPin2;
};
    
    
class StateTracker
{
  public:
    int totalTurns;
    boolean isUpdated;
    boolean isTurning;
    boolean isTurningFWD;
    
    StateTracker();
    void respondToButton();
};
    
    
class Photocells
{
  public:
    int values[2];
    int thresh[2];
    unsigned int counter;
    
    Photocells(int pin1, int pin2);
    
    int update(boolean dir, long time);
    
  private:
    int pins[2];
    int nValues;
    int history1[25];
    int history2[25];
    int maxVal[2];
    int minVal[2];
    int quarterTurns;
    boolean canBeTriggered[2];
    unsigned long triggerTime[2];
    void checkThreshold();
};

#endif


