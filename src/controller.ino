// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>

#define bumpthreshold 2973 // the treshold for a movement

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int16_t oldAcX,oldAcY,oldAcZ,oldTmp,oldGyX,oldGyY,oldGyZ;
int16_t deltaAcX,deltaAcY,deltaAcZ,deltaTmp,deltaGyX,deltaGyY,deltaGyZ;
int16_t total = 0;


bool Xmovement = false;
bool Ymovement = false;
bool Zmovement = false;


void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop(){
  checkBumps();

  //if(Xmovement) Serial.println("X MOVEMENT");
  //if(Ymovement) Serial.println("Y MOVEMENT");
  //if(Zmovement) Serial.println("Z MOVEMENT");

  total += deltaAcZ;
  Serial.print("TOTAL: "); Serial.println(total);

  delay(10);


}




void checkBumps() {
  resetBump();
  readAndCalculateDeltas();
  checkDeltas();

}

void checkDeltas() {
  if(abs(deltaAcX) > bumpthreshold) Xmovement = true;
  if(abs(deltaAcY) > bumpthreshold) Ymovement = true;
  if(abs(deltaAcZ) > bumpthreshold) Zmovement = true;

}

void resetBump() {
  Xmovement = false;
  Ymovement = false;
  Zmovement = false;
}

void readAndCalculateDeltas() {
  saveOldValues();
  readWire();
  calculateDeltas();
}


void readWire() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers

  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

void calculateDeltas() {
  deltaAcX = oldAcX - AcX;
  deltaAcY = oldAcY - AcY;
  deltaAcZ = oldAcZ - AcZ;
  deltaGyX = oldGyX - GyX;
  deltaGyY = oldGyY - GyY;
  deltaGyY = oldGyY - GyY;

}

void saveOldValues() {
  oldAcX = AcX;
  oldAcY = AcY;
  oldAcZ = AcZ;
  oldGyX = GyX;
  oldGyY = GyY;
  oldGyZ = GyZ;
}

void print(int16_t AX, int16_t AY, int16_t AZ, int16_t GX, int16_t GY, int16_t GZ) {

  Serial.print("AcX = "); Serial.print(AX);
  Serial.print(" | AcY = "); Serial.print(AY);
  Serial.print(" | AcZ = "); Serial.print(AZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GX);
  Serial.print(" | GyY = "); Serial.print(GY);
  Serial.print(" | GyZ = "); Serial.println(GZ);
}
