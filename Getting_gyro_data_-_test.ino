#include "M5Atom.h"

float gyroX, gyroY, gyroZ;

void setup() {
  M5.begin();
  M5.IMU.Init();
}
void loop() {
  M5.dis.fillpix(0x00ff00);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  Serial.println(gyroX);
  delay(5000);
}
