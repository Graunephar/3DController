
#include "OneButton.h"
#include <Keyboard.h>


//Define all the buttons
#define BUTTONPIN1 2
#define BUTTONPIN2 3
#define BUTTONPIN3 4
#define BUTTONPIN4 5
#define BUTTONPIN5 6




OneButton button1(BUTTONPIN1, true);
OneButton button2(BUTTONPIN2, true);
OneButton button3(BUTTONPIN3, true);
OneButton button4(BUTTONPIN4, true);
OneButton button5(BUTTONPIN5, true);




const char jump = ' ';
const int bend = KEY_DOWN_ARROW;
const int hit = KEY_RIGHT_SHIFT	;
const int cover = KEY_UP_ARROW;



void setup() {
  // Setup the Serial port. see http://arduino.cc/en/Serial/IfSerial
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  button1.attachClick(pressJump);
  button2.attachClick(pressBend);
  button3.attachClick(pressHit);
  button4.attachClick(pressCover);
  button5.attachClick(startAgain);
  }


void loop() {


  // keep watching the push buttons:
  button1.tick();
  button2.tick();
  button3.tick();
  button4.tick();
  button5.tick();

}

// ----- button callback functions

void startAgain() {

Serial.println("Restart");

}

void pressJump() {
  pressKey(jump);
}

void pressBend() {
  pressSpecialKey(bend);
}

void pressHit() {
  pressSpecialKey(hit);
}

void pressCover(){
  pressSpecialKey(cover);
}

void pressKey(char key) {
  Keyboard.press(key);
  Keyboard.release(key);
}

void pressSpecialKey(int key) {
  Keyboard.press(key);
  Keyboard.release(key);
}
