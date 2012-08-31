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


void printPhotocellInfo() {

  for (int p = 0; p < 2; p++) {

    Serial.print("Photocell ");
    Serial.print(p);
    Serial.print(" ");
    Serial.print(photocells.values[p]);
    Serial.print(" ");
    Serial.println(photocells.thresh[p]);

  }

}

void printVariables() {

  Serial.print(twister.totalTurns); 
  Serial.print(" ");
  Serial.print(inputs.fwdTurns); 
  Serial.print(" ");
  Serial.print(inputs.revTurns); 
  Serial.print(" ");
  Serial.print(inputs.buttonState); 
  Serial.print(" ");
  Serial.print(photocells.counter); 
  Serial.print(" ");

}

