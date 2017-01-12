#include <I2Cdev.h>
#include <MPU6050.h>
#include "RunningAverage.h" //TODO: Use platform io lib when approved
#include <SoftwareSerial.h>
#include <Keyboard.h>



#define threshold 9000
#define avglengt 10000
#define steplengt 650
#define bumpthreshold 10000 // the treshold for a hit

//Button chars
const char jump = ' ';
const int bend = KEY_DOWN_ARROW;
const int hit = KEY_RIGHT_SHIFT	;
const int cover = KEY_UP_ARROW;

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t resetvalue; // used for storing inital reading

RunningAverage average(avglengt);

enum state {
  DOWN,
  UP,
  HIT
};

state lastState;

unsigned long timestamp;


void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(9600);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    calibrate();
    Serial.println("GLAR");
    pressJump();
  }

  void loop() {


      int reading = read();
      average.addValue(reading);

      double avg = average.getAverage();

      if(reading >= avg + threshold) { // Reading is 'threshold' bigger than average
        changeState(UP);
        //delay(400);
      } else if(reading <= avg - threshold) {
        changeState(DOWN);
        //delay(400);
      } else if(ax > bumpthreshold) {
        changeState(HIT);
      }

      //Serial.print(avg); Serial.println(" ");

      delay(100);
  }


void changeState(state newstate) {

      if((millis() - timestamp) < steplengt) return; // functions as old delays

      lastState = newstate;
      timestamp = millis();

      switch (newstate) {
        case 1: pressJump();
        Serial.println("UP");
        break;
        case 0: pressBend();
        Serial.println("NED");
        break;
        case 2: pressHit();
        Serial.println("HIT");

      }
      //Serial.write(newstate);


  }


uint16_t read() {
  accelgyro.getAcceleration(&ax, &ay, &az);
  return ay;

}

void calibrate() {
  for (int i = 0; i < avglengt; i++) {
    uint16_t value = read();
    average.addValue(value);
    delay(1);
  }
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
  delay(100);
  Keyboard.release(key);
}

void pressSpecialKey(int key) {
  Keyboard.press(key);
  delay(100);
  Keyboard.release(key);
}
