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

// Functions for writing to the LCD screen

void startupScreen(int a, int b) {

  lcd.print(" Tetrode Twister ");

  lcd.setCursor(0,1);

  lcd.print("for Arduino v");
  lcd.print(a);
  lcd.print(".");
  lcd.print(b);

  delay(3000);     

}

void showTurns() {

  if (inputs.isUpdated || twister.isUpdated) {

    lcd.clear();
    lcd.print("FWD  REV  COUNT");
    lcd.setCursor(0,1);

    printTurns(inputs.fwdTurns);
    printTurns(inputs.revTurns);
    lcd.print("  ");
    printTurns(twister.totalTurns);

    inputs.isUpdated = false;
    twister.isUpdated = false;
  }
}

void allDone() {

  lcd.clear();
  lcd.print("  Fire up that   ");
  lcd.setCursor(0,1);
  lcd.print("   heat gun!     ");

}

void printTurns(int nTurns) {

  if (nTurns < 100 && nTurns >= -9) {
    lcd.print(" ");
  }
  if (nTurns < 10 && nTurns >= 0) { 
    lcd.print(" ");
  }
  lcd.print(nTurns);
  lcd.print("  ");

}

void resumeDialog() { // allow user to cancel restart

  boolean resume = true;

  int remainingSeconds = 5;

  lcd.clear();
  lcd.print("Twisting error");
  lcd.setCursor(0,1);
  lcd.print("CONTINUE in ");
  lcd.print(remainingSeconds);

  unsigned long theTime = millis();

  while (remainingSeconds > 0) {
    while (millis() - theTime < 1000) {
      inputs.check(twister.isTurning, verPCB);
      if (inputs.buttonState == LOW) {
        remainingSeconds = 0;  
        resume = false;
        EEPROM.write(0,0);
        EEPROM.write(1,0);
        delay(500);
        break; 
      }
    }
    lcd.setCursor(12,1);
    remainingSeconds--;
    lcd.print(remainingSeconds);
    theTime = millis();
  }

  if (resume) {
    twister.totalTurns = remainingTurns;
    twister.isTurning = true;
    twister.isUpdated = true;

    switch (turnDirection) {
      case 0:
        twister.isTurningFWD = true;
        break;
      case 1:
        twister.isTurningFWD = false;
        break;
    }
  }

}


