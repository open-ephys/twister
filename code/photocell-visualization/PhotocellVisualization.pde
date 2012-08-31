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

import processing.serial.*;

Serial myPort;  

float timeWindow = 5000;

int plotWidth = 500;
int plotHeight = 300;
float lastX = 0;

int elapsedSecs = 0;

color[] plotColors = {color(255), color(170), color(255,214,3), color(255,100,3)};
color backgroundColor = 42;

void setup () {
  // set the window size:
  size(plotWidth, plotHeight);        

  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
  background(backgroundColor);

  clearPlots();

}

void draw () {
  
  // everything happens in the serialEvent() function

}

void serialEvent (Serial myPort) {

  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    inString = trim(inString);
    String[] splitString = split(inString, ' ');

    int sensorNum = int(splitString[1]);
    int sensorVal = int(splitString[2]);
    int threshVal = int(splitString[3]);
   
      float x = map(millis() % timeWindow, 0, timeWindow, 0, plotWidth);
      float y = map(sensorVal, 0, 1023, 0, plotHeight);
      float t = map(threshVal, 0, 1023, 0, plotHeight);
      
      if (x < lastX) {
        clearPlots();
      }
      
      plotData(x,y,sensorNum);
      plotData(x,t,sensorNum+2);

      lastX = x;
    
  }
}

void plotData(float x, float y, int plotnum) {
 
  fill(plotColors[plotnum]);
  ellipse(x,y,3,3);
  drawClock(millis());
}

void clearPlots() {
  
  background(backgroundColor);
  
}


