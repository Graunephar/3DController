
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


int lastreading1;
int lastreading2;
int lastreading3;
int lastreading4;
int lastreading5;

int reading1 = 0;
int reading2 = 0;
int reading3 = 0;
int reading4 = 0;
int reading5 = 0;



void setup() {

  pinMode(BUTTONPIN1, INPUT_PULLUP);
  pinMode(BUTTONPIN2, INPUT_PULLUP);
  pinMode(BUTTONPIN3, INPUT_PULLUP);
  pinMode(BUTTONPIN4, INPUT_PULLUP);
  pinMode(BUTTONPIN5, INPUT_PULLUP);

  }


void loop() {


    lastreading1 = reading1;
    lastreading2 = reading2;
    lastreading3 = reading3;
    lastreading4 = reading4;
    lastreading5 = reading5;

    reading1 = digitalRead(BUTTONPIN1);
    reading2 = digitalRead(BUTTONPIN2);
    reading3 = digitalRead(BUTTONPIN3);
    reading4 = digitalRead(BUTTONPIN4);
    reading5 = digitalRead(BUTTONPIN5);

    if(reading1 != lastreading1 && reading1 == LOW) pressCover();
    if(reading2 != lastreading2 && reading2 == LOW) pressBend();
    if(reading3 != lastreading3 && reading3 == LOW) pressHit();
    if(reading4 != lastreading4 && reading4 == LOW) pressJump();
    if(reading5 != lastreading5 && reading5 == LOW) startAgain();


    delay(10);

}

// ----- button callback fun  ctions

void startAgain() {
  pressKey(jump);
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
