/*
"The Troll" Arduino compatible practical joke machine!
by Patrick Thomas Mitchell
http://www.engineeringshock.com/the-troll-project-page.html

Library version 1.0.2 June 24, 2019 by LeRoy Miller

If you find this or any of my projects useful or enjoyable please support me.  
Anything I do get goes to buy more parts and make more/better projects.  
https://www.patreon.com/kd8bxp  
https://ko-fi.com/lfmiller  

Copyright (c) 2019 LeRoy Miller

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses>
*/

/* This is still a work in progress, stay tune for updates */

#include "troll.h"
#include <Wire.h>

#define REMOTE 0x08 //I2C address of slave device

troll t(true); // Using the Internal Speaker will rampdown after each use this saves power

void setup() {

  Wire.begin();
  t.begin();
}

void loop() {
//Test of Troll Library

//This example shows how easy it is to blink the onboard LED.
//Notice that while the sound is playing the LED is also on. So the sound is blocking
//acting like a delay while playing.
int btn = t.button();
if (btn == LOW) {
  
digitalWrite(LED, HIGH);
say(0x06);
  delay(700);
  say(0x8F);
t.sound(RED_ALERT); // This will play the RED ALERT Sound from Star Trek TNG sound 0x38

} else {
digitalWrite(LED, LOW);
//delay(1000);
}
//btn = HIGH;
delay(100);
}

void sendOverI2C(int address, int intruction) {
  Wire.beginTransmission(REMOTE); //transmit to REMOTE device
  Wire.write(address);
  delay(10);
  Wire.write(intruction);
  Wire.endTransmission();
}

void say(int words) {
  sendOverI2C(0x01,words);
}
