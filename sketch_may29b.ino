#include "M5Atom.h"

int oldX, oldY;

void setup() {
  Serial.begin(115200);

  M5.begin(true, false, true);
  M5.IMU.Init();
  oldX = -1;
  oldY = -1;
}

void loop() {
  float accX, accY, accZ;
  int x, y;

  M5.IMU.getAccelData(&accX, &accY, &accZ);
  x = constrain(accX * 5 + 2, 0, 4);
  y = constrain(accY * 5 + 2, 0, 4);
  Serial.print("x: ");
  Serial.println(accX);
  Serial.print("y: ");
  Serial.println(accX);
  Serial.print("z: ");
  Serial.println(accZ);
  if ((accX + accY)/2 < 0) {
    M5.dis.fillpix(0xffffff);
  }
if ((accX + accY)/2 >= 0) {
    M5.dis.fillpix(0xffffff);
    delay(50);
    M5.dis.fillpix(0xffffff);
    delay(50);
    M5.dis.fillpix(0xffffff);


}
  delay(100);
  }
