/*
"The Troll" Arduino compatible practical joke machine!
by Patrick Thomas Mitchell
http://www.engineeringshock.com/the-troll-project-page.html

Library version 1.0.9 July 30, 2019 by LeRoy Miller

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


#include "Arduino.h"
#include "troll.h"
#include <SPI.h>

int timings[58] = {4250, 4500, 4000, 10000,13500,5000,3500,8500,6000,4000,3000,2000,1000,1000,1000,1500,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1500,
1000,1500,1500,1000,1500,1000,6500,4000,3500,1500,3500,13000,3000,4000,11000,500,10500,6000,2500,5500,8000,10000,3750,4000};

troll::troll(bool SPEAKER) {
_SPEAKER = SPEAKER;
//troll::setAtten(0);
}

void troll::begin() { 
  pinMode(SW1,INPUT);
  pinMode(SW2,INPUT);
  pinMode(SW3,INPUT);
  pinMode(SW4,INPUT);
  pinMode(SELECT,INPUT);
  pinMode(IN,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  SPI.begin();             // Initialize SPI
  SPI.setClockDivider(SPI_CLOCK_DIV32); // low frequency SPI
  pinMode(CS,OUTPUT);    // Chip select pins is an output
  digitalWrite(CS,HIGH); // Set chip select to be HIGH (5v) by default.  The chip on the shield is selected when this line is brought low. 
  SPI.setBitOrder(MSBFIRST);  // OTP requires MSB first
  SPI.setDataMode(SPI_MODE0);  // Use MODE0, as all other modes to not work
  digitalWrite(CS, LOW);
  SPI.transfer(_RAMPUP);
  SPI.transfer(0x00);
if (_SPEAKER) {
SPI.transfer(_RAMPDOWN);
SPI.transfer(0x00);
}
  digitalWrite(CS,HIGH);
}

void troll::sound(int value, int wait) {
delay(7);
// Transmit Data
  digitalWrite(CS,LOW);
  SPI.transfer(_PLAY);
  SPI.transfer(value);
if (_SPEAKER) {
SPI.transfer(_RAMPDOWN);
SPI.transfer(0x00);
}
  digitalWrite(CS,HIGH);
  delay(wait); 
}

int troll::button() {
  return digitalRead(SELECT);
  
}

int troll::externalTrigger() {
  return digitalRead(IN);
}

int troll::readSwitch() {
  /* This will return a number between 0 and 15 which means
     that it's a 4 bit binary number -  with sw1 being in the 8th place
     and sw4 being in the ones place.

     SW1, SW2, SW3, SW4
      8    4    2    1

     if all switches are LOW they return 15, if all are HIGH they return 0
   */

int temp = 0;
   if (digitalRead(SW1) == LOW) {
    temp = temp + 8;
   } 
  if (digitalRead(SW2) == LOW) {
    temp = temp + 4;
  }
  if (digitalRead(SW3) == LOW) {
    temp = temp + 2;
  }
  if (digitalRead(SW4) == LOW) {
    temp = temp + 1;
  }
  return temp;
}

void troll::setAtten(int n) { //Rusty Haddock shared code on Kickstarter
// Sets attenuation (n=0 high volume, n=15 lowest volume)

digitalWrite(CS, LOW);
SPI.transfer(0x44);
SPI.transfer(n & 15);
digitalWrite(CS, HIGH);

}
