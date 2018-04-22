/*
 * 8-bit Oscilloscope
 * Gives a visual rendering of data received from serial port
 * 
 * By Farzad Noorian (farzad.noorian@sydney.edu.au) 2016
 * 
 * Originally based on a project by (c) 2008 Sofian Audry (info@sofianaudry.com)
 * See http://accrochages.drone.ws
 *
 * Changes include code cleanup and single byte frame reception
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 
 
import processing.serial.*;

Serial port;  // Create object from Serial class
int[] values;  // Data received from the serial port
float zoom;

void setup() 
{
  size(1280, 480);

  // Open the port that the board is connected to and use the same speed
  port = new Serial(this, Serial.list()[0], 115200);
  
  while (port.available() >= 1) { // Flush port
    port.read();
  }
  
  values = new int[width];
  zoom = 1.0f;
  smooth();
}

int scale_Y(int val) {
  return (int)(height - val / 255.0f * (height - 1));
}

int readPort() {
  int value = -1;
  if (port.available() >= 1) {
      value = port.read() ;
  }
  return value;
}

void addToBuffer(int value) {
  for (int i=0; i<width-1; i++)
    values[i] = values[i+1];
  values[width-1] = value;
}

void drawLines() {
  stroke(255);
  
  int displayWidth = (int) (width / zoom);
  
  int k = values.length - displayWidth;
  
  int x0 = 0;
  int y0 = scale_Y(values[k]);
  for (int i=1; i<displayWidth; i++) {
    k++;
    int x1 = (int) (i * (width-1) / (displayWidth-1));
    int y1 = scale_Y(values[k]);
    line(x0, y0, x1, y1);
    x0 = x1;
    y0 = y1;
  }
}

void keyReleased() {
  switch (key) {
    case '+':
      zoom *= 2.0f;
      println(zoom);
      if ( (int) (width / zoom) <= 1 )
        zoom /= 2.0f;
      break;
    case '-':
      zoom /= 2.0f;
      if (zoom < 1.0f)
        zoom *= 2.0f;
      break;
  }
}

void draw()
{
  background(0);
  
  int val;
  while ((val = readPort()) != -1) {
    addToBuffer(val);
  }
  
  drawLines();
}