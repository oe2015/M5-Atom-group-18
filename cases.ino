#include "M5Atom.h"
#include <FastLED.h>

CRGB leds[NUM_LEDS];

uint32_t colors[] = {0x00FF00, 0xffffff, 0x707070, 0x0000f0}; //array  of colors
int array_size = 4;

int bottom_offset = 20;
const int ledpin=21;
int FSM = 0;

uint32_t black_color = 0x000000;

bool switch_flag = true;

int delay_period = 300;

  float accX, accY, accZ;
  int x, y;
  
int oldX, oldY;

void setup() {
  Serial.begin(115200);

  M5.begin(true, false, true);
  M5.IMU.Init();
  oldX = -1;
  oldY = -1;
}

void loop()
{

    switch (FSM)
    {
      case 0:
      {
        M5.dis.fillpix(black_color);
           if (M5.Btn.wasPressed())
        {
          FSM++;
        }
      break;
      }

      case 1:
{   
      while (FSM==1)
      {
        M5.dis.fillpix(colors[0]); // turn on color
        delay(delay_period);
        M5.dis.fillpix(black_color); //turn off color
        delay(delay_period);
        if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
        break;
      }
      break;
      
}
      case 2:
{
      while(FSM==2)
      {
        M5.dis.fillpix(colors[1]); // turn on color
        delay(delay_period);
        M5.dis.fillpix(black_color); //turn off color
        delay(delay_period);
          if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
        break;
      }
      break;    
}

case 3:
{
  while(FSM==3) {
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
  if (accZ< -0.1) 
  {
    M5.dis.fillpix(0x00FF00);
    delay(500);
  }
else {
    {
        M5.dis.fillpix(colors[0]); // turn on color
        delay(delay_period);
        M5.dis.fillpix(black_color); //turn off color
        delay(delay_period);
        if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
        break;
      }
      break;
}
  delay(100);
  if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
 break;
  }
  break;
}



case 4:
{
  while(FSM==4) {
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
  if (accZ < -0.1) 
  {
    M5.dis.fillpix(0xffffff);
    delay(500);
  }
else {
    {
        M5.dis.fillpix(colors[1]); // turn on color
        delay(delay_period);
        M5.dis.fillpix(black_color); //turn off color
        delay(delay_period);
        if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
        break;
      }
      break;
}
  delay(100);
  if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
 break;
  }
  break;
}

case 5:
{
  FSM=0;
  break;
}

}
    M5.update(); //always have this here

}
