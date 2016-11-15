#include <Keyboard.h>
#include <Arduino.h>
#include <Button.h>        //https://github.com/JChristensen/Button


//Define all the buttons
#define BUTTONPIN1 2
#define BUTTONPIN2 3
#define BUTTONPIN3 4
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.
#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true        //Since the pullup resistor will keep the pin high unless the


Button Button1(BUTTONPIN1, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the button
Button Button2(BUTTONPIN2, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the button
Button Button3(BUTTONPIN3, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the button


const char jump = 's';
const char bend = 'b';
const char hit = 'h';
const char cover = 'c';




void setup() {

  Keyboard.begin();

}

void loop() {

  if(Button1.isPressed()) pressKey(jump);

  if(Button2.wasPressed()) pressKey(bend);

  if(Button3.wasPressed()) pressKey(hit);


}

void pressKey(char key) {
  Keyboard.press(key);

}
