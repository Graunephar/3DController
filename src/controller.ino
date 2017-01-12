#include <I2Cdev.h>
#include <MPU6050.h>
#include "RunningAverage.h" //TODO: Use platform io lib when approved


#define threshold 9000
#define avglengt 10000

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

int initialavg;

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
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    calibrate();
  }

void loop() {
    int reading = read();
    average.addValue(reading);

    double avg = average.getAverage();

    Serial.print(reading);
    Serial.print(",");
    Serial.print(avg);
    Serial.print(",");
    Serial.print(avg + threshold);
    Serial.print(",");
    Serial.println(avg - threshold);




    //Serial.print(avg); Serial.println(" ");

    delay(100);
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
