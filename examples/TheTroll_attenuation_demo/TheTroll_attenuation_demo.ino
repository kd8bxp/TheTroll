/*
"The Troll" Arduino compatible practical joke machine!
by Patrick Thomas Mitchell
http://www.engineeringshock.com/the-troll-project-page.html

Library version 1.0.3 June 26, 2019 by LeRoy Miller

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

/* Attenuation Demo

Attenuation sample code by Rusty Haddock as shared on the Kickstarter project forums.

Because some sounds are very loud, and some are not so loud, it maybe desired to change
the attenuation levels of sounds.
An attenuation of zero is the highest and 15 would be the lowest "volume".

Here we are using the SCREAM2 sound, and the dip switches to set the attenuation level (as a demo)
Hit the select button to hear the sound. For this example the DIP swiches are representing a binary number 
where switch 4 is the ones spot, switch 3 is the two spot, switch 2 is the fours spot, and switch 1 is the eights spot.

This is DEMO code, to show how Attenuation works, with some trial and error, and your own sense as to
how loud or soft you want a sound you should use t.setAtten(x) before each sound, and not use the dip switches to set it.

t.setAtten(0); would be the default, power on levels.
*/


#include <troll.h>

troll t(true); // Using the Internal Speaker will rampdown after each use this saves power


void setup() {
t.begin();
}

void loop() {

int btn = t.button(); //When the button is pressed it goes LOW
if (btn == LOW) {
int readSwitch = t.readSwitch();
t.setAtten(readSwitch);
digitalWrite(LED, HIGH);
t.sound(SCREAM2); 
} else {
digitalWrite(LED, LOW);
}
delay(100);
}
