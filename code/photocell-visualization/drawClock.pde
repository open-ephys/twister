//    Visualization Sketch for Tetrode Twister
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

void drawClock(float ts) {
 
   fill(255);

  
   int milliseconds = int(ts) % 1000;
   int totalseconds = (int(ts) - milliseconds)/1000;
   int seconds = int(totalseconds % 60);
   int minutes = int((totalseconds - seconds) / 60);
   
   if (elapsedSecs < totalseconds) {
   
   String minuteString = String.valueOf(minutes);
   
   String secondString = String.valueOf(seconds);
   String secondFill;
   
   if (seconds < 10) {
     secondFill = "0";
   } else {
     secondFill = "";
   }
   
   String milliString = String.valueOf(milliseconds);
   String milliFill;
   
   if (milliseconds < 10) {
     milliFill = "00";
   } else if (milliseconds > 10 && milliseconds < 100) {
     milliFill = "0";
   } else {
     milliFill = "";
   }
     
   String[] clockValues = new String[4];
   
   clockValues[0] = minuteString;
   clockValues[1] = ":";
   clockValues[2] = secondFill;
   clockValues[3] = secondString;
   //clockValues[4] = ".";
   //clockValues[5] = milliFill;
   //clockValues[6] = milliString;
   
   // clear old time
   fill(backgroundColor);
   noStroke();
   rect(width*0.9, height*0.8, width*0.2, height*0.3);
   
   fill(255); 
   text(join(clockValues,""),width*0.8,height*0.9);
   
   }
   
   elapsedSecs = totalseconds;
}

