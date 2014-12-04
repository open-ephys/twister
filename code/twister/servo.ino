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

void updateServo() {

  // settings for rotation speed
  const int fwdspeed = 1000;
  const int stopped = 1500;
  const int revspeed = 2000;

  // set rotation status
  if (!twister.isTurning) {
    myservo.writeMicroseconds(stopped);
  } 
  else {
    if (twister.isTurningFWD) {
      myservo.writeMicroseconds(fwdspeed);
    } 
    else {
      myservo.writeMicroseconds(revspeed);
    }
  }

  // check for threshold crossings
  if (twister.totalTurns >= inputs.fwdTurns && twister.isTurningFWD) {
    myservo.writeMicroseconds(stopped);

    buzzer.high();
    delay(500);

    twister.isTurningFWD = false;

  } else if (twister.totalTurns <= inputs.fwdTurns - inputs.revTurns && twister.isTurning && !twister.isTurningFWD) {
    
    myservo.writeMicroseconds(stopped);
    
    buzzer.low();

    twister.isTurning = false;
    twister.isTurningFWD = true;

    twister.totalTurns = 0;

    delay(1000);

    allDone();
    
    delay(5000);
    
    inputs.isUpdated = true;
    
     updateEEPROM();

  }

}



