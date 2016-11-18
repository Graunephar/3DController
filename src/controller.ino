
#include <Keyboard.h>
#include <Button.h> http://platformio.org/lib/show/919/Button/examples

//Define all the buttons
#define BUTTONPIN1 2
#define BUTTONPIN2 3
#define BUTTONPIN3 4
#define BUTTONPIN4 5
#define BUTTONPIN5 6

Button button1(BUTTONPIN1);
Button button2(BUTTONPIN2);
Button button3(BUTTONPIN3);
Button button4(BUTTONPIN4);
Button button5(BUTTONPIN5);

const char jump = ' ';
const int bend = KEY_DOWN_ARROW;
const int hit = KEY_RIGHT_SHIFT	;
const int cover = KEY_UP_ARROW;

void setup() {

  button1.begin();
  button2.begin();
  button3.begin();
  button4.begin();
  button5.begin();

  while (!Serial) { }; // for Leos
	Serial.begin(9600)

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
